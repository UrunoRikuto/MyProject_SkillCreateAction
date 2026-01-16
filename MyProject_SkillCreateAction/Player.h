/**************************************************//*
	@file	| Player.h
	@brief	| プレイヤークラスのヘッダーファイル
	@note	| CEntityを継承
*//**************************************************/
#pragma once
#include "Entity.h"

// @brief プレイヤークラス
class CPlayer final:  public CEntity
{
public:

	// @brief コンストラクタ
	CPlayer();

	// @brief デストラクタ
	virtual ~CPlayer();

	// @brief 初期化処理
	virtual void Init() override;

	// @brief 更新処理
	virtual void Update() override;

private:
	// @brief 移動処理
	void Move();
};

