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

/*****************************************//*
	@brief　	| コンストラクタ
*//*****************************************/
CPlayer::CPlayer()
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
	@brief　	| 移動処理
*//*****************************************/
void CPlayer::Move()
{
	// 速度ベクトルの初期化
	m_f3Velocity = StructMath::FtoF3(0.0f);

	// 位置の保存
	m_f3OldPos = m_tParam.m_f3Pos;

	if (IsKeyPress('W'))m_f3Velocity.z += 1.0f;
	if (IsKeyPress('S'))m_f3Velocity.z -= 1.0f;
	if (IsKeyPress('D'))m_f3Velocity.x += 1.0f;	
	if (IsKeyPress('A'))m_f3Velocity.x -= 1.0f;

	// 速度ベクトルの正規化
	m_f3Velocity = StructMath::Normalize(m_f3Velocity);

	// 位置の更新
	m_tParam.m_f3Pos += m_f3Velocity;
}