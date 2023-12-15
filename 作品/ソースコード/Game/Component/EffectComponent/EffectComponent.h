/**
* @file EffectComponent.h
* @brief EffectComponentクラスの定義
*/

#pragma once

//--------- INCLUDES -----------
#include "../Component.h"
#include <string>
#include <SimpleMath.h>
#include <Effekseer.h>

//--------- 前方宣言 -----------
class AssetHandle;

/**
* @class EffectComponent
* @brief エフェクトコンポーネント
* @detail エフェクトの再生ができる
*         Init関数で指定されたファイルのエフェクト持つ
*/
class EffectComponent : public Component
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	EffectComponent();

	/**
	* デストラクタ
	*/
	~EffectComponent();

private:
	/** エフェクトのアセットへのハンドル */
	std::shared_ptr<AssetHandle> mAssetHandle;

	/** エフェクトハンドル */
	Effekseer::Handle mEffectHandle;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @detail 指定されたファイルのエフェクトを読み込む
	* @return void
	*/
	void Init(std::string_view _filePath);

	/**
	* @fn PlayEffect
	* @brief エフェクト再生関数
	* @param const DirectX::SimpleMath::Vector3 (_playPosition) 再生位置
	* @return void
	*/
	void PlayEffect(const DirectX::SimpleMath::Vector3 _playPosition);
};

