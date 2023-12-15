/**
* @file EffekseerEffectProvider.h
* @brief EffekseerEffectProviderクラスの定義
*/

#pragma once

//----------- INCLUDES -----------
#include "../IAssetProvider.h"

/**
* @class EffekseerEffectProvider
* @brief エフェクシアのエフェクトを読み込むクラス
*/
class EffekseerEffectProvider : public IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	EffekseerEffectProvider();

	/**
	* デストラクタ
	*/
	~EffekseerEffectProvider();

private:
	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	virtual void Setting();

	/**
	* @fn LoadBase
	* @brief アセット読み込みを実際に実行する処理
	* @detail 読み込みが完了するとキャッシュマップに登録する
	* @param const std::string& _filePath
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const;

public:
	/**
	* @fn GetProviderType
	* @brief プロバイターのTypeを返す
	* @detail typeidを使用してプロバイターの型を返している
	* @return std::type_info プロバイダーの型
	*/
	inline virtual const std::type_info& GetProviderType() const;

};

//---------- INLINES ---------

inline const std::type_info& EffekseerEffectProvider::GetProviderType() const
{
	return typeid(EffekseerEffectProvider);
}
