/**
* @file AssetManager.h
* @brief AssetManagerクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include <memory>
#include <vector>
#include <iostream>
#include "../Singleton.h"
#include "IAssetProvider.h"

//--------- 前方宣言 ------------
class AssetHandle;

//--------- コンセプト ----------
template<class Provider>
concept DerivedProvider = std::derived_from<Provider, IAssetProvider>;

/**
* @class AssetManager
* @brief アセットに関するインターフェースをシステムとユーザーに提供するクラス 
*/
class AssetManager final : public Singleton<AssetManager>
{
	/**----------------------------------------------------------------------------------------------
	* 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
	* クラス外から生成、破棄できないようにするためにフレンド指定する
	------------------------------------------------------------------------------------------------*/
	friend class Singleton<AssetManager>;

private:
	/**
	* デフォルトコンストラクタ
	*/
	AssetManager()
	{
		// 処理なし
	}

	/**
	* デフォルトデストラクタ
	*/
	~AssetManager()
	{
		// 処理なし
	}

	/**
	* コピーコンストラクタ
	* コピー禁止のためdelete指定
	*/
	AssetManager(const AssetManager&) = delete;

	/**
	* = 演算子のオーバーロード
	* 代入禁止のためdelete指定
	*/
	void operator=(const AssetManager&) = delete;

	/** 登録されたアセットプロバイダー */
	std::vector<std::shared_ptr<IAssetProvider>> mProviders;

public:
	/**
	* @fn アセットプロバイダーの登録
	* @brief 型で指定されたプロバイダーの登録をする
	* @detail 登録の前にすでに登録されていないかチェックが入り、二重登録は起きない
	* @return void
	*/
	template<DerivedProvider Provider>
	inline void RegisterAssetProvider();

	/**
	* @fn Load
	* @brief アセット読み込み関数
	* @param const std::string& (_filePath)
	* @param const Setting... (_setting)
	*/
	template<DerivedProvider Provider>
	inline std::shared_ptr<AssetHandle> Load(const std::string& _filePath);

	template<DerivedProvider Provider, class... Setting>
	inline void ProviderSetting(const Setting... _setting);
private:
	/**
	* @fn GetProvider
	* @brief プロバイダーの取得関数
	* @return std::shared_ptr<Provider>
	*/
	template<DerivedProvider Provider>
	inline std::shared_ptr<Provider> GetProvider() const;

};

//----------- INLINES --------------
template<DerivedProvider Provider>
inline void AssetManager::RegisterAssetProvider()
{
	// 現在登録されているプロバイダー重複していないか確認
	for (std::shared_ptr<IAssetProvider> provider : mProviders)
	{	
		if (provider->GetProviderType() == typeid(Provider))
		{
			std::cout << "このプロバイダーはすでに登録されています。" << typeid(Provider).name() << std::endl;
			return;
		}
	}

	// プロバイダーの作成
	mProviders.emplace_back(std::make_shared<Provider>());
}

template<DerivedProvider Provider>
inline  std::shared_ptr<AssetHandle> AssetManager::Load(const std::string& _filePath)
{
	// プロバイダーの取得
	std::shared_ptr<Provider> provider = GetProvider<Provider>();

	// プロバイダーが取得できているか確認
	if (!provider)
	{
		return nullptr;
	}

	// プロバイダーからアセット読み込み
	std::shared_ptr<AssetHandle> newHandle = provider->Provide(_filePath);

	return newHandle;
}

template<DerivedProvider Provider, class ...Setting>
inline void AssetManager::ProviderSetting(const Setting... _setting)
{
	// プロバイダーを取得
	std::shared_ptr<Provider> provider = GetProvider<Provider>();

	// プロバイダーが存在するか
	if (!provider)
	{
		return;
	}
	provider->SettingBase(_setting...);
}

template<DerivedProvider Provider>
inline std::shared_ptr<Provider> AssetManager::GetProvider() const
{
	// 指定されたプロバイダーを探す
	for (std::shared_ptr<IAssetProvider> provider : mProviders)
	{
		if (provider->GetProviderType() == typeid(Provider))
		{
			return std::static_pointer_cast<Provider>(provider);
		}
	}

	std::cout << "指定されたプロバイダーは登録されていません" << typeid(Provider).name() << std::endl;
	return nullptr;
}
