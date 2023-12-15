/**
* @file SkeletalMeshAsset.h
* @brief SkeletalMeshAssetクラスの定義
*/


#pragma once


//---------- INCLUDES ---------
#include <SimpleMath.h>
#include <memory>
#include <unordered_map>
#include <string>
#include "../IAsset.h"
#include "../../RendererSystem/VisualEntity/VisualEntityData.h"

//--------- 前方宣言 --------
class BoneAsset;

/**
* @class SkeletalMeshAsset
* @brief スケルタルメッシュアセットクラス
*/
class SkeletalMeshAsset : public IAsset
{
	/**
	*  SkeletalMeshAssetの頂点データや、ボーンデータに対してSkeletalMeshProviderのみが
	*　アクセスできるようにするためフレンド指定
	*/
	friend class SkeletalMeshProvider;
	
public:
	/**
	* @struct Vertex
	* @brief SkeletalMeshの頂点データ構造体
	*/
	struct Vertex
	{
		DirectX::SimpleMath::Vector3 mPosition; /**< 頂点位置 */
		DirectX::SimpleMath::Vector3 mNormal;   /**< 法線 */
		DirectX::SimpleMath::Vector2 mUV;       /**< UV */
		DirectX::SimpleMath::Vector4 mColor;    /**< 頂点カラー */
		float mWeights[4];                      /**< 対応しているボーンへの重み */
		uint32_t mBoneIndices[4];                 /**< 対応しているボーンインデックス */

		/**
		* デフォルトコンストラクタ
		*/
		Vertex();

		/**
		* コンストラクタ
		* 
		* @param const DirectX::SimpleMath::Vector3 (_position)
		* @param const DirectX::SimpleMath::Vector3 (_normal)
		* @param const DirectX::SimpleMath::Vector2 (_uv)
		* @param const DirectX::SimpleMath::Vector4 (_color)
		*/
		Vertex(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _normal, const DirectX::SimpleMath::Vector2 _uv, const DirectX::SimpleMath::Vector4 _color);
	};

public:
	/**
	 * デフォルトコンストラクタ
	*/
	SkeletalMeshAsset();

	/**
	 * デストラクタ
	*/
	~SkeletalMeshAsset();

private:
	/** 頂点データ 複数メッシュの可能性もあるのでstd::vector<std::vector<Vertex>>型 */
	std::vector<std::vector<Vertex>> mVertices;

	/** インデックスバッファ作成のためのデータ 複数メッシュの可能性もあるのでstd::vector<std::vector<Vertex>>型 */
	std::vector<std::vector<uint32_t>> mIndices;

	/** マテリアルデータ　メッシュごとに一つ*/
	std::vector<VisualEntityData::Material> mMaterials;

	/** ボーンデータ 階層構造になっているので親ボーンのポインタからすべてのボーンにアクセスできる */
	std::shared_ptr<BoneAsset> mRootBone;

	/** ボーンを登録するMap 名前でボーンを取得したりする場合に取得しやすいようにするための変数 */
	std::unordered_map<std::string, std::weak_ptr<BoneAsset>> mBoneMap;

public:
	/**
	* @fn GetAssetType
	* @brief アセットのタイプを返す
	* @detail typeidを使用して型判別をしている
	* @return const std::type_info&
	*/
	inline const std::type_info& GetAssetType() const noexcept override;

	/**
	* @fn GetRootBone
	* @brief GetRootBoneAsset
	* @return std::weak_ptr<BoneAsset> ルートボーンアセットの弱参照
	*/
	inline std::weak_ptr<BoneAsset> GetRootBoneAsset() const;

	/**
	* @fn GetVertices
	* @brief 頂点データを返す
	* @return std::vector<std::vector<Vertex>>
	*/
	inline std::vector<std::vector<Vertex>> GetVertices() const;

	/**
	* @fn GetIndices
	* @brief インデックスデータを返す
	* @return std::vector<std::vector<uint32_t>>
	*/
	inline std::vector<std::vector<uint32_t>> GetIndices() const;

	/**
	* @fn GetMaterials
	* @brief マテリアルを返す
	* @return std::vector<VisualEntityData::Material>
	*/
	inline std::vector<VisualEntityData::Material> GetMaterials() const;
};

//-------------- INLINES -------------

inline const std::type_info& SkeletalMeshAsset::GetAssetType() const noexcept
{
	return typeid(SkeletalMeshAsset);
}

inline std::weak_ptr<BoneAsset> SkeletalMeshAsset::GetRootBoneAsset() const
{
	return mRootBone;
}

inline std::vector<std::vector<SkeletalMeshAsset::Vertex>> SkeletalMeshAsset::GetVertices() const
{
	return mVertices;
}

inline std::vector<std::vector<uint32_t>> SkeletalMeshAsset::GetIndices() const
{
	return mIndices;
}

inline std::vector<VisualEntityData::Material> SkeletalMeshAsset::GetMaterials() const
{
	return mMaterials;
}

