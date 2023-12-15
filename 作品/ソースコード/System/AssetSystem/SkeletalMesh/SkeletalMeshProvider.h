/**
* @file SkeletalMeshProvider.h
* @brief SkeletalMeshProviderクラスの定義
*/

#pragma once

//----------- INCLUDES -----------
#include <assimp/scene.h>
#include <memory>
#include <SimpleMath.h>
#include "../IAssetProvider.h"
#include "SkeletalMeshAsset.h"


//---------- 前方宣言 -----------
class BoneAsset;

/**
* @class SkeletalMeshProvider
* @brief SkeletalMeshの読み込をするクラス
*/
class SkeletalMeshProvider : public IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SkeletalMeshProvider();

	/**
	* デストラクタ
	*/
	~SkeletalMeshProvider();

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


private:
	/**
	* @fn LoadVertexData
	* @brief 頂点データの読み込み
	* @param  std::shared_ptr<SkeletalMeshAsset>&      (_skeletalMesh)
	* @param const aiMesh&                             (_aiMesh)
	* @return void
	*/
	void LoadVertexData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiMesh& _aiMesh) const;

	/**
	* @fn SetWeightAndBoneIndex
	* @brief スキンウェイトとボーンインデックスを頂点データにセットする
	* @param SkeletalMeshAsset::Vertex& (_vertex)
	* @param const float                (_weight)
	* @param const int16_t              (_boneIndex)
	* @return void
	*/
	void SetWeightAndBoneIndex(SkeletalMeshAsset::Vertex& _vertex, const float _weight, const int16_t _boneIndex) const;

	/**
	* @fn LoadMaterialData
	* @brief マテリアルデータの読み込み
	* @param  std::shared_ptr<SkeletalMeshAsset>&      (_skeletalMesh)
	* @param const aiMaterial&                         (_aiMaterial)
	* @param const std::string&                        (_filePath)
	* @return void
	*/
	void LoadMaterialData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiMaterial& _aiMaterial, const std::string& _filePath) const;

	/**
	* @fn LoadBoneData
	* @brief ボーンデータの読み込み
	* @param std::shared_ptr<SkeletalMeshAsset>&       (_skeletalMesh)
	* @param aiBone**                                  (_aiBones)
	* @param const size_t                              (_boneNum)
	* @return void
	*/
	void LoadBoneData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, aiBone** _aiBones, const size_t _boneNum) const;

	/**
	* @fn LoadNode
	* @brief ノード読み込み
	* @param std::shared_ptr<SkeletalMeshAsset>& (_skeletalMesh)
	* @param const aiNode*                       (_rootNode)
	* @return void
	*/
	void LoadNode(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiNode* _rootNode) const;

	/**
	* @fn ReadNode
	* @brief ノードを読み取る関数
	* @param std::shared_ptr<BoneAsset>& (_boneAsset)
	* @param const aiNode&               (_aiNode)
	* @return void
	*/
	void ReadNode(std::shared_ptr<BoneAsset>& _boneAsset, const aiNode& _aiNode) const;

	/**
	* @fn RegisterBoneMapAndSetBoneIndex
	* @brief マップにボーンを登録し、ボーンにインデックスをセットする関数
	* @detail ボーンをルートからすべて参照するためには再起の処理が必要であるため、処理速度的に重たい
	*         再起関数を使用する回数を減らすために、Mapに登録とインデックスのセットを同じ関数ないで行う
	* @param std::shared_ptr<SkeletalMeshAsset>& (_skeletalMeshAsset)
	* @param const std::shared_ptr<BoneAsset>&   (_boneAsset)
	* @return void
	*/
	void RegisterBoneMapAndSetBoneIndex(std::shared_ptr<SkeletalMeshAsset>& _skeletalMeshAsset, const std::shared_ptr<BoneAsset>& _boneAsset) const;

	/**
	* @fn ConvAiMatrix
	* @brief Assimpの行列をDirectX::SimpleMath::Matrixに変換する
	* @param const aiMatrix4x4& _aiMatrix
	* @return DirectX::SimpleMath::Matrix
	*/
	DirectX::SimpleMath::Matrix ConvAiMatrix(const aiMatrix4x4& _aiMatrix) const noexcept;

protected:
	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	void Setting() override;
};

//---------- INLINES -----------

inline const std::type_info& SkeletalMeshProvider::GetProviderType() const
{
	return typeid(SkeletalMeshProvider);
}

