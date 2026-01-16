/**************************************************//*
	@file	| Player.cpp
	@brief	| プレイヤークラスのcppファイル
	@note	| CEntityを継承
*//**************************************************/
#include "Player.h"
#include "BillboardRenderer.h"
#include "Input.h"
#include "Oparation.h"
#include "StructMath.h"
#include "Camera.h"
#include "Main.h"
#include "Field.h"
#include "Geometory.h"

constexpr float ce_fMoveSpeed = 0.2f;

/*****************************************//*
	@brief　	| コンストラクタ
*//*****************************************/
CPlayer::CPlayer()
	: CEntity()
	, m_f3TargetPos(StructMath::FtoF3(0.0f))
	, m_bIsMove(false)
{
	// ビルボードレンダラーの追加
	AddComponent<CBillboardRenderer>();
}

/*****************************************//*
	@brief　	| デストラクタ
*//*****************************************/
CPlayer::~CPlayer()
{
}

/*****************************************//*
	@brief　	| 初期化処理
*//*****************************************/
void CPlayer::Init()
{
	// 基底クラスの初期化処理
	CEntity::Init();

	// ビルボードレンダラーの設定
	CBillboardRenderer* pRenderer = GetComponent<CBillboardRenderer>();
	pRenderer->SetKey("Player");

	m_tParam.m_f3Size = DirectX::XMFLOAT3{ 2.0f, 2.0f, 2.0f };
}

/*****************************************//*
	@brief　	| 更新処理
*//*****************************************/
void CPlayer::Update()
{
	// 移動処理
	Move();

	// 基底クラスの更新処理
	CEntity::Update();
}

/*****************************************//*
	@brief　	| 描画処理
*//*****************************************/
void CPlayer::Draw()
{
	// 目標位置までの線を描画
	if (m_bIsMove)
	{
		Geometory::AddLine(m_tParam.m_f3Pos, m_f3TargetPos, DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
		Geometory::DrawLines();
	}

	// 基底クラスの描画処理
	CEntity::Draw();
}

/*****************************************//*
	@brief　	| 移動処理
*//*****************************************/
void CPlayer::Move()
{
	// 速度ベクトルの初期化
	m_f3Velocity = StructMath::FtoF3(0.0f);

	// 位置の保存
	m_f3OldPos = m_tParam.m_f3Pos;

	if (IsMouseButtonTrigger(MOUSEBUTTON_R))
	{
		// フィールド平面(y=-10)との交点
		const DirectX::XMFLOAT3 hitOnField = GetScene()->GetGameObject<CField>()->GetMovePos();

		// ターゲットは「画面で指したフィールド交点のXZ」を採用し、Yはプレイヤー高さ固定
		m_f3TargetPos = hitOnField;
		m_bIsMove = true;
	}

	if (m_bIsMove)
	{
		// XZ平面だけで距離判定（Yは見ない）
		const float dx = m_f3TargetPos.x - m_tParam.m_f3Pos.x;
		const float dz = m_f3TargetPos.z - m_tParam.m_f3Pos.z;
		const float distXZ = sqrtf(dx * dx + dz * dz);

		if (distXZ < 0.5f)
		{
			m_bIsMove = false;
		}
		else
		{
			// 方向ベクトルもXZのみ
			DirectX::XMFLOAT3 toTarget = DirectX::XMFLOAT3{ dx, 0.0f, dz };
			m_f3Velocity += toTarget;
		}
	}

	// 速度ベクトルの正規化
	m_f3Velocity = StructMath::Normalize(m_f3Velocity);

	// 位置の更新（XZ移動）
	m_tParam.m_f3Pos += m_f3Velocity * ce_fMoveSpeed;

	// 念のためY固定（他処理で変わっても戻す）
	m_tParam.m_f3Pos.y = m_f3OldPos.y;
}