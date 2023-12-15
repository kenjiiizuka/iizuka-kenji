/**
* @file TextureProvider.h
* @brief TextureProviderクラスの定義
*/

#pragma once

//---------- INCLUDES ------------
#include "../IAssetProvider.h"


//---------- 前方宣言 -----------
class Texture;

/**
* @class TextureProvider
* @brief テクスチャを読み込むクラス
*/
class TextureProvider : public IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	TextureProvider();

	/**
	* デストラクタ
	*/
	~TextureProvider();

private:
	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	virtual void Setting() {};

	/**
	* @fn LoadBase
	* @brief アセット読み込みを実際に実行する処理
	* @detail 読み込みが完了するとキャッシュマップに登録する
	* @param const std::string& (_filePath)
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const;

	/**
	* @fn LoadByWICTexture
	* @brief WICによってテクスチャを読み込む関数
	* @param std::string_view          (_filePath)
	* @param std::shared_ptr<Texture>& (_texture)
	* @return void
	*/
	bool LoadByWICTexture(std::string_view _filePath, std::shared_ptr<Texture>& _texture) const;

	/**
	* @fn CreateTextureFromTGA
	* @brief TGAテクスチャを作成する
	* @param std::string_view          (_filePath)
	* @param std::shared_ptr<Texture>& (_texture)
	* @return void
	*/
	bool CreateTextureFromTGA(std::string_view _filePath, std::shared_ptr<Texture>& _texture) const;

public:
	/**
	* @fn GetProviderType
	* @brief プロバイターのTypeを返す
	* @detail typeidを使用してプロバイターの型を返している
	* @return std::type_info プロバイダーの型
	*/
	inline virtual const std::type_info& GetProviderType() const;

};

//----------- INLINES ----------

inline const std::type_info& TextureProvider::GetProviderType() const
{
	return typeid(TextureProvider);
}


