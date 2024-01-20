/**
* @file BinaryFileProvider.h
* @brief BinaryFileProviderクラスの定義
*/


#pragma once

//------------ INCLUDES -----------
#include "../IAssetProvider.h"

/**
* @class BinaryFileProvider
* @brief バイナリファイルの読み込みをする機能を持つ
*/
class BinaryFileProvider : public IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BinaryFileProvider();

	/**
	* デフォルトデストラクタ
	*/
	~BinaryFileProvider();
	
private:
	/** ファイルが開けなかった場合にファイルを作成するかどうかを表す */
	bool mbCreateFile;

public:
	/**
	 * @fn GetProviderType
	 * @brief プロバイターのTypeを返す
	 * @detail typeidを使用してプロバイターの型を返している
	 * @return const std::type_info& プロバイダーの型
	*/
	inline const std::type_info& GetProviderType() const final override;

	/**
	 * @fn Load
	 * @brief バイナリファイルを読み込む処理
	 * @param const std::string& (_filePath)
	 * @return std::shared_ptr<IAsset>
	*/
	std::shared_ptr<IAsset> Load(const std::string& _filePath) const override;
	
private:
	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	void Setting() override;
};

//--------- INLINES ---------

inline const std::type_info& BinaryFileProvider::GetProviderType() const
{
	return typeid(BinaryFileProvider);
}
