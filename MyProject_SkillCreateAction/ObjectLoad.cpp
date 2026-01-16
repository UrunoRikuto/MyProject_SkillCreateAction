/**************************************************//*
	@file	| ObjectLoad.cpp
	@brief	| オブジェクトロードクラスのcppファイル
	@note	| オブジェクトのロード、アンロードを行う
*//**************************************************/
#include "ObjectLoad.h"
#include "RendererComponent.h"
#include "Defines.h"

/*****************************************//*
	@brief　	| 全てのオブジェクトをロード
*//****************************************/
void CObjectLoad::LoadAll()
{
	// フェード用テクスチャのロード
    CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Fade.png"), "Fade");
	// 地面用テクスチャのロード
	CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Field.png"), "Field");
	// プレイヤー用テクスチャのロード
	CRendererComponent::Load(RendererKind::Texture, TEXTURE_PATH("Player.png"), "Player");
}


/*****************************************//*
	@brief　	| 全てのオブジェクトをアンロード
*//****************************************/
void CObjectLoad::UnLoadAll()
{
    CRendererComponent::UnLoad();
}
