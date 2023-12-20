/**
* @file StaticMeshProvider.h
* @brief StaticMeshProviderクラスの定義
*/

#pragma once

//--------------- INCLUDES ------------
#include <assimp/scene.h>
#include "../IAssetProvider.h"

//------------ INCLUDES -------------
class StaticMeshAsset;

/**
* @class StaticMeshProvider
* @brief スタティックメッシュの読み込みをするクラス
*/
class StaticMeshProvider final : public IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	StaticMeshProvider();

	/**
	* デストラクタ
	*/
	~StaticMeshProvider();

public:
	/**
	 * @fn GetProviderType
	 * @brief プロバイターのTypeを返す
	 * @detail typeidを使用してプロバイターの型を返している
	 * @return std::type_info プロバイダーの型
	*/
	inline virtual const std::type_info& GetProviderType() const override;

	/**
	 * @fn Load
	 * @brief アセット読み込みを実際に実行する処理
	 * @detail 読み込みが完了するとキャッシュマップに登録する
	 * @param const std::string& _filePath
	 * @return std::shared_ptr<IAsset>
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const override;

protected:
	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	void Setting() override;

private:
	/**
	* @fn LoadVertexData
	* @brief 頂点データの読み込み
	* @param std::shared_ptr<StaticMeshAsset>& (_staticMeshAsset)
	* @param const aiMesh&                     (_aiMesh)
	* @return void
	*/
	void LoadVertexData(std::shared_ptr<StaticMeshAsset>& _staticMeshAsset, const aiMesh& _aiMesh) const;

	/**
	* @fn LoadMaterialData
	* @brief マテリアルデータの読み込み
	* @param  std::shared_ptr<StaticMeshAsset>&        (_staticMesh)
	* @param const aiMaterial&                         (_aiMaterial)
	* @param const std::string&                        (_filePath)
	* @return void
	*/
	void LoadMaterialData(std::shared_ptr<StaticMeshAsset>& _staticMesh, const aiMaterial& _aiMaterial, const std::string& _filePath) const;

};

//--------- INLINES ---------

inline const std::type_info& StaticMeshProvider::GetProviderType() const
{
	return typeid(StaticMeshProvider);
}
