/**************************************************//*
	@file	| Field.cpp
	@brief	| フィールドクラスのcppファイル
	@note	| CGameObjectを継承
*//**************************************************/
#include "Field.h"
#include "Sprite3DRenderer.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "CameraGame.h"
#include "Oparation.h"
#include "Input.h"
#include "ImguiSystem.h"
#include "Defines.h"
#include <cmath>

/*****************************************//*
	@brief　	| コンストラクタ
*//*****************************************/
CField::CField()
{
	AddComponent<CSprite3DRenderer>();
}

/*****************************************//*
	@brief　	| デストラクタ
*//*****************************************/
CField::~CField()
{
}

/*****************************************//*
	@brief　	| 初期化処理
*//*****************************************/
void CField::Init()
{
	// 基底クラスの初期化処理
	CGameObject::Init();

	// スプライトレンダラーの設定
	CSprite3DRenderer* pRenderer = GetComponent<CSprite3DRenderer>();
	pRenderer->SetKey("Field");

	m_tParam.m_f3Pos = DirectX::XMFLOAT3{ 0.0f, -1.0f, 0.0f };
	m_tParam.m_f3Rotate = { DirectX::XMConvertToRadians(90.0f), 0.0f, 0.0f };
	m_tParam.m_f3Size = DirectX::XMFLOAT3{ 100.0f, 100.0f, 1.0f };
	m_tParam.m_f4Color = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
}

/*****************************************//*
	@brief　	| インスペクター表示処理
	@param　	| isEnd：終了フラグ
	@return		| 表示した項目数
*//*****************************************/
int CField::Inspecter(bool isEnd)
{
	// 基底クラスのインスペクター表示処理
	int itemCount = CGameObject::Inspecter(false);

	// マウス位置表示
	if (ImGui::CollapsingHeader(std::string("[MousePos]").c_str()))
	{
		DirectX::XMFLOAT3 movePos = GetMovePos();
		ImGui::Text("X: %.2f", movePos.x);
		ImGui::Text("Y: %.2f", movePos.y);
		ImGui::Text("Z: %.2f", movePos.z);
	}

	if (isEnd)
	{
		ImGui::End();
	}

	return itemCount;
}

/*****************************************//*
	@brief　	| 移動位置の取得
	@return		| (DirectX::XMFLOAT3)移動位置
	@note		| マウスカーソルがフィールド上にある場合、その位置を返す
*//*****************************************/
DirectX::XMFLOAT3 CField::GetMovePos()
{
	CCamera* pCamera = CCamera::GetInstance();

	// マウス座標（画面中心原点）
	const POINT mouse = *GetMousePosition(true);

	// Screen(中心原点) -> NDC
	const float ndcX = static_cast<float>(mouse.x) / (SCREEN_WIDTH * 0.5f);
	const float ndcY = -static_cast<float>(mouse.y) / (SCREEN_HEIGHT * 0.5f);

	// ★重要：レイ生成は「転置していない」View/Projを使う
	const DirectX::XMFLOAT4X4 viewF = pCamera->GetViewMatrix(false);
	const DirectX::XMFLOAT4X4 projF = pCamera->GetProjectionMatrix(false);

	const DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&viewF);
	const DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&projF);
	const DirectX::XMMATRIX invViewProj = DirectX::XMMatrixInverse(nullptr, view * proj);

	// DirectX NDC: z=0 near, z=1 far
	DirectX::XMVECTOR nearClip = DirectX::XMVectorSet(ndcX, ndcY, 0.0f, 1.0f);
	DirectX::XMVECTOR farClip  = DirectX::XMVectorSet(ndcX, ndcY, 1.0f, 1.0f);

	DirectX::XMVECTOR nearWorld = DirectX::XMVector4Transform(nearClip, invViewProj);
	DirectX::XMVECTOR farWorld  = DirectX::XMVector4Transform(farClip,  invViewProj);

	// 同次除算
	nearWorld = DirectX::XMVectorScale(nearWorld, 1.0f / DirectX::XMVectorGetW(nearWorld));
	farWorld  = DirectX::XMVectorScale(farWorld,  1.0f / DirectX::XMVectorGetW(farWorld));

	// レイ生成（ワールド）
	const DirectX::XMVECTOR rayOrigin = nearWorld;
	const DirectX::XMVECTOR rayDir = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(farWorld, nearWorld));

	// フィールド平面 y = -10（Fieldの位置）
	const float fieldY = m_tParam.m_f3Pos.y;

	const float oy = DirectX::XMVectorGetY(rayOrigin);
	const float dy = DirectX::XMVectorGetY(rayDir);

	// レイが平面と平行
	if (fabsf(dy) < 1e-6f)
	{
		return DirectX::XMFLOAT3{ 0.0f, fieldY, 0.0f };
	}

	const float t = (fieldY - oy) / dy;
	if (t < 0.0f)
	{
		// カメラ後方なら無効（仕様に合わせて変更可）
		return DirectX::XMFLOAT3{ 0.0f, fieldY, 0.0f };
	}

	const DirectX::XMVECTOR hit = DirectX::XMVectorAdd(rayOrigin, DirectX::XMVectorScale(rayDir, t));

	DirectX::XMFLOAT3 hitPos{};
	DirectX::XMStoreFloat3(&hitPos, hit);
	return hitPos;
}