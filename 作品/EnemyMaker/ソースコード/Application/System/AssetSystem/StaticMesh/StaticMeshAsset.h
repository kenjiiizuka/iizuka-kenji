/**
* @file StaticMeshAsset.h
* @brief StaticMeshAssetクラスの定義
*/


#pragma once


//----------- INCLUDES ----------
#include <SimpleMath.h>
#include <vector>
#include "../IAsset.h"
#include "../../RendererSystem/VisualEntity/VisualEntityData.h"

/**
* @class StaticMeshAsset
* @brief スタティックメッシュアセットクラス
*/
class StaticMeshAsset : public IAsset
{
	/**----------------------------------------------------------------------------------------------
    * 頂点データなどに読み込みをするStaticMeshProvider以外から触れないようにするためにフレンド指定
    ------------------------------------------------------------------------------------------------ */
	friend class StaticMeshProvider;

public:
	/**
	* @struct Vertex
	* @brief StaticMeshの頂点データ構造体
	*/
	struct Vertex
	{
		DirectX::SimpleMath::Vector3 mPosition; /**< 頂点座標 */
		DirectX::SimpleMath::Vector3 mNormal;   /**< 法線 */
		DirectX::SimpleMath::Vector2 mUV;       /**< UV */
		DirectX::SimpleMath::Vector4 mColor;    /**< 頂点カラー */

		/**
		* デフォルトコンストラクタ
		*/
		Vertex();

		/**
		* コンストラクタ
		* 
		* @param const DirectX::SimpleMath::Vector3& (_position)
		* @param const DirectX::SimpleMath::Vector3& (_normal)
		* @param const DirectX::SimpleMath::Vector2& (_uv)
		* @param const DirectX::SimpleMath::Vector4& (_color)
		*/
		Vertex(const DirectX::SimpleMath::Vector3& _position, const DirectX::SimpleMath::Vector3& _normal, const DirectX::SimpleMath::Vector2& _uv, const DirectX::SimpleMath::Vector4& _color);
	};

public:
	/**
	* デフォルトコンストラクタ
	*/
	StaticMeshAsset();

	/**
	* デストラクタ
	*/
	~StaticMeshAsset();


private:
	/** 頂点データ 複数メッシュを格納できるようにstd::vector<std::vector<Vertex>> */
	std::vector<std::vector<Vertex>> mVertices;

	/** インデックスバッファ作成のためのデータ 複数メッシュの可能性もあるのでstd::vector<std::vector<Vertex>>型 */
	std::vector<std::vector<uint32_t>> mIndices;

	/** マテリアルデータ　メッシュごとに一つ*/
	std::vector<VisualEntityData::Material> mMaterials;

public:
	/**
	* @fn GetAssetType
	* @brief アセットのタイプを返す
	* @detail typeidを使用して型判別をしている
	* @return const std::type_info&
	*/
	inline const std::type_info& GetAssetType() const noexcept override;

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

//---------- INLINES ----------

inline const std::type_info& StaticMeshAsset::GetAssetType() const noexcept
{
	return typeid(StaticMeshAsset);
}

inline std::vector<std::vector<StaticMeshAsset::Vertex>> StaticMeshAsset::GetVertices() const
{
	return mVertices;
}

inline std::vector<std::vector<uint32_t>> StaticMeshAsset::GetIndices() const
{
	return mIndices;
}

inline std::vector<VisualEntityData::Material> StaticMeshAsset::GetMaterials() const
{
	return mMaterials;
}

