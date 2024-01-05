/**
* @file EffekseerEffect.h
* @brief EffekseerEffectクラスの定義
*/

#pragma once

//-------- INCLUDES ----------
#include "../IAsset.h"
#include <Effekseer.h>

/**
* @class EffekseerEffect
* @brief エフェクシアのエフェクトをラップしたクラス
*/
class EffekseerEffect : public IAsset
{
	/**-----------------------------------------------------------------------------
	* EffekseerEffectProviderからのみが変数に代入できるようにするためにフレンド指定
	----------------------------------------------------------------------------- */
	friend class EffekseerEffectProvider;

public:
	/**
	* デフォルトコンストラクタ
	*/
	EffekseerEffect();

	/**
	* デストラクタ
	*/
	~EffekseerEffect();

private:
	/** エフェクトへの参照とエフェクトハンドル  */
	Effekseer::EffectRef mEffect;

public:
	/**
	* @fn GetEffect
	* @brief エフェクトを返す
	* @return std::pair<Effekseer::EffectRef, Effekseer::Handle>
	*/
	inline Effekseer::EffectRef GetEffect() const noexcept;

	/**
	* @fn GetAssetType
	* @brief アセットのタイプを返す
	* @detail typeidを使用して型判別をしている
	* @return const std::type_info&
	*/
	inline virtual const std::type_info& GetAssetType() const noexcept;

};

//------------ INLINES ----------

inline Effekseer::EffectRef EffekseerEffect::GetEffect() const noexcept
{
	return mEffect;
}

inline const std::type_info& EffekseerEffect::GetAssetType() const noexcept
{
	return typeid(EffekseerEffect);
}
