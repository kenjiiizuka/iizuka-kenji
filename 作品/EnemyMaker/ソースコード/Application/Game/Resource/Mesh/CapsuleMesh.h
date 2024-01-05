/**
* @file CapsuleMesh.h
* @brief CapsuleMeshクラス定義
*/

#pragma once

//------------ INCLUDES -----------
#include "../../Component/StaticMeshComponent/StaticMesh.h"

/**
* @class CapsuleMesh
* @brief カプセル型のメッシュを表示作成する
*/
class CapsuleMesh : public StaticMesh
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	CapsuleMesh();

	/**
	* デストラクタ
	*/
	~CapsuleMesh();

private:
	/** カプセルの半径 */
	float mRadius;

	/** 高さ */
	float mHeight;

	/** 水平方向の分割数 */
	uint16_t mDivisionHorizontal;

	/** 垂直方向の分割数 */
	uint16_t mDivisionVertical;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param const float    (_radius)
	* @param const float    (_height)
	* @param const uint16_t (_divisionHorizontal)
	* @param const uint16_t (_divisionVertical)
	* @return void
	*/
	void Initialize(const float _radius, const float _height, const uint16_t _divisionHorizontal, const uint16_t _divisionVertical);

	/**
	* @fn Draw
	* @brief 描画処理
	* @detail セットされたトランスフォームからスケールを除いた行列を計算しています
	* @return void
	*/
	void Draw() override;

private:
	/**
	* @fn CreateVisualEntity
	* @brief カプセルメッシュのデータを作成
	*/
	void CreateVisualEntity() override;

	/**
	* @fn MakeVertexData
	* @brief 頂点データの作成
	* @param VisualEntityData::Description& (_desc) 作成した頂点データを格納する先
	* @return void
	*/
	void MakeVertexData(VisualEntityData::Description& _desc);

	/**
	* @fn MakeIndexData
	* @brief インデックスデータを作成
	* @param VisualEntityData::Description& (_desc) 作成したインデックスデータを格納する先
	*/
	void MakeIndexData(VisualEntityData::Description& _desc);

	/**
	* @fn MakeCylinder
	* @brief シリンダーメッシュを作成する
	* @param std::vector<Vertex>& (_vertices)
	* @return void
	*/
	void MakeCylinder(std::vector<Vertex>& _vertices);

	/**
	* @fn CalucCapsuleVertexPosition
	* @brief カプセルの頂点位置を計算する
	* @return std::vector<Vertex>
	*/
	std::vector<Vertex> CalucCapsuleVertexPosition();

public:
	/**
	* @fn SetRadius
	* @brief 半径をセットする関数
	* @param const float (_radius)
	* @return void
	*/
	void SetRadius(const float _radius);

	/**
	* @fn SetHeight
	* @brief 高さのセッター
	* @param const float (_height)
	* @return void
	*/
	void SetHeight(const float _height);

	/**
	* @fn SetTransform
	* @brief トランスフォームのセッター
	* @param const Transform& (_transform)
	* @return void
	*/
	inline void SetTransform(const Transform& _transform) noexcept;	
};

//--------- INLINES ----------

inline void CapsuleMesh::SetTransform(const Transform& _transform) noexcept
{
	mTransform = _transform;
}