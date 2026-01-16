/**************************************************//*
	@file	| Entity.h
	@brief	| エンティティ基底クラス
	@note	| エンティティの共通処理を定義
			| CGameObjectを継承
*//**************************************************/
#pragma once
#include "GameObject.h"

// @brief エンティティ基底クラス
class CEntity : public CGameObject
{
public:
	// @brief コンストラクタ
	CEntity();

	// @brief デストラクタ
	virtual ~CEntity();

protected:
	// @brief 速度ベクトル
	DirectX::XMFLOAT3 m_f3Velocity;
};

