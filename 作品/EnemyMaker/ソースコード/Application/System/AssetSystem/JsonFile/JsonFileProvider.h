/**
* @file JsonFileProvider.h
* @brief JsonFileProviderクラスの定義
*/
#pragma once

//------------ INCLUDES -------------
#include "../IAssetProvider.h"

/**
* @class JsonFileProvider
* @brief json形式のファイルの読み込みをする
*/
class JsonFileProvider : public IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	JsonFileProvider();

	/**
	* デストラクタ
	*/
	~JsonFileProvider();

private:
	/** ファイルがなかった場合に新しく作成するか */
	bool mbCreateFile;

private:
	/**
	* @fn LoadBase
	* @brief アセット読み込みを実際に実行する処理
	* @detail 読み込みが完了するとキャッシュマップに登録する
	* @param const std::string& _filePath
	*/
	std::shared_ptr<IAsset> Load(const std::string& _filePath) const;

	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	void Setting();

public:

	/**
	* @fn GetProviderType
	* @brief プロバイターのTypeを返す
	* @detail typeidを使用してプロバイターの型を返している
	* @return std::type_info プロバイダーの型
	*/
	inline const std::type_info& GetProviderType() const;

};

//------------ INLINES ----------

inline const std::type_info& JsonFileProvider::GetProviderType() const
{
	return typeid(JsonFileProvider);
}
