#pragma once

/**
* @file IAssetProvider.h
* @brief IAssetProviderクラスの定義
*/

//---------- INCLUDES ---------
#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "IAsset.h"

//----------- 前方宣言 --------
class AssetHandle;


/**
* @class IAssetProvider
* @brief アセットプロバイダーのインターフェースクラス
*/
class IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	IAssetProvider()
	{
		// 処理なし
	}

	/**
	* デフォルトデストラクタ
	*/
	virtual ~IAssetProvider()
	{
		// 処理なし
	}

private:
	/** キャッシュマップ <ファイルパス, アセット> */
	std::unordered_map<std::string, std::shared_ptr<IAsset>> mCacheMap;

protected:
	/** 読み込み時の設定 */
	std::vector<char> mLoadSetting;

public:
	/**
	* @fn GetProviderType
	* @brief プロバイターのTypeを返す
	* @detail typeidを使用してプロバイターの型を返している
	* @return std::type_info プロバイダーの型
	*/
	inline virtual const std::type_info& GetProviderType() const = 0;

	/**
	* @fn Provide
	* @brief アセットを読み込み関数
	* @param const std::string& (_filePath)
	* @return std::shared_ptr<AssetHandle>
	*/
	virtual std::shared_ptr<AssetHandle> Provide(const std::string& _filePath);

	/**
	 * @fn SettingBase
	 * @brief 読み込み時のセッティングをする
	 * @detail 可変長引数で渡された値をコピーしている
	 *         実際に設定を値をとして持つのは各プロバイダーが行っている
	 * @param const SettingParam... (_setting)
	 * @return void
	*/
	template<class... SettingParam>
	inline void SettingBase(const SettingParam... _setting);

protected:
	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	virtual void Setting() = 0;

	/**
	* @fn LoadBase
	* @brief アセット読み込みを実際に実行する処理
	* @detail 読み込みが完了するとキャッシュマップに登録する
	* @param const std::string& _filePath
	*/
	virtual std::shared_ptr<IAsset> LoadBase(const std::string& _filePath);

	/**
	* @fn LoadBase
	* @brief アセット読み込みを実際に実行する処理
	* @detail 読み込みが完了するとキャッシュマップに登録する
	* @param const std::string& _filePath
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const = 0;

private:
	/**
	* @fn AddCacheMap
	* @brief 読み込んだアセットをキャッシュマップに登録
	* @detail キーの重複があれば登録しない
	* @param const std::string& (_filePath) キーとして扱う
	* @param std::shared_ptr<IAsset> (_asset)
	*/
	inline void AddCacheMap(const std::string& _filePath, std::shared_ptr<IAsset> _asset);

	/**
	* @fn GetAssetFromCacheMap
	* @brief キャッシュマップからアセット取得する
	* @param const std::string& (_cacheKey) 
	* @param std::shared_ptr<IAsset>
	*/
	inline std::shared_ptr<IAsset> GetAssetFromCacheMap(const std::string& _cacheKey);
};

//----------- INLINES ------------

inline void IAssetProvider::AddCacheMap(const std::string& _filePath, std::shared_ptr<IAsset> _asset)
{
	// キャッシュマップに登録
	bool success = mCacheMap.try_emplace(_filePath, _asset).second;

	if (!success)
	{
		std::cout << _filePath << "はすでにキャッスに登録済みです" << std::endl;
	}
}

inline std::shared_ptr<IAsset> IAssetProvider::GetAssetFromCacheMap(const std::string& _cacheKey)
{
	// キャッシュマップに指定されたキーがあるか
	if (mCacheMap.contains(_cacheKey))
	{
		return mCacheMap.at(_cacheKey);
	}

	std::cout << _cacheKey << "はキャッシュマップに登録されていません" << std::endl;

	return nullptr;
}

template<class ...SettingParam>
inline void IAssetProvider::SettingBase(SettingParam ..._setting)
{
	// 読み込み設定をコピーする
	size_t settingSize = sizeof...(_setting);
	mLoadSetting.resize(settingSize);
	std::memcpy(mLoadSetting.data(), &_setting..., settingSize);

	// 実際に使える値に変換する
	Setting();
}
