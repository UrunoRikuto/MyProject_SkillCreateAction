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

	m_tParam.m_f3Pos = DirectX::XMFLOAT3{ 0.0f, -10.0f, 0.0f };
	m_tParam.m_f3Rotate = { DirectX::XMConvertToRadians(90.0f), 0.0f, 0.0f };
	m_tParam.m_f3Size = DirectX::XMFLOAT3{ 100.0f, 100.0f, 1.0f };
	m_tParam.m_f4Color = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
}

/*****************************************//*
	@brief　	| 移動位置の取得
	@return		| (DirectX::XMFLOAT3)移動位置
	@note		| マウスカーソルがフィールド上にある場合、その位置を返す
*//*****************************************/
DirectX::XMFLOAT3 CField::GetMovePos()
{
}
