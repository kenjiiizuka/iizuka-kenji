/**
* @file SphereMesh.h
* @brief SphereMeshクラスの定義
*/

#pragma once

//----------- INCLUDES ------------
#include "../../Component/StaticMeshComponent/StaticMesh.h"

/**
* @class SphereMesh
* @brief 球メッシュクラス
* @detail 球メッシュを作成し、描画している
*/
class SphereMesh : public StaticMesh
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SphereMesh();

	/**
	* デストラクタ
	*/
	~SphereMesh();

private:
	/** 水平方向の分割数 */
	uint16_t mDivisionHorizontal;

	/** 垂直方向の分割数 */
	uint16_t mDivisionVertical;

	/** 半径 */
	float mRadius;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail SphereMeshの作成をする
	* @param const float     (_radius)
	* @param const uint16_t  (_divisionHorizontal)
	* @param const uint16_t  (_divisionVertical)
	* @param 
	*/
	void Initialize(const float _radius, const uint16_t _divisionHorizontal = 100, const uint16_t _divisionVertical = 100);

private:
	/**
	* @fn CreateVisualEntity
	* @brief 球メッシュのデータを作成
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

};

