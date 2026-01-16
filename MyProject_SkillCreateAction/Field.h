/**************************************************//*
	@file	| Field.h
	@brief	| フィールドクラスのヘッダーファイル
	@note	| CGameObjectを継承
*//**************************************************/
#pragma once
#include "GameObject.h"

// @brief フィールドクラス
class CField : public CGameObject
{
public:

	// @brief コンストラクタ
	CField();

	// @brief デストラクタ
	virtual ~CField();

	// @brief 初期化処理
	virtual void Init() override;

	// @brief インスペクター表示処理
	virtual int Inspecter(bool isEnd = true) override;

	// @brief 移動位置の取得
	// @note マウスクリックによる移動位置の取得
	DirectX::XMFLOAT3 GetMovePos();
};
