/**
* @file SkeletalMeshVertexShader.h
* @brief SkeletalMeshVertexShaderクラスの定義
*/

#pragma once

//---------- INCLUDES --------
#include "VertexShader.h"
#include "../../../../Game/Component/TransformComponent/Transform.h"

//--------- 前方宣言 ---------
class SkeletalMesh;
class Skeleton;

/**
* @class SkeletalMeshVertexShader
* @brief スケルタルメッシュを表示するための頂点シェーダー
*/
class SkeletalMeshVertexShader final : public VertexShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity) 
	*/
	SkeletalMeshVertexShader(VisualEntity* _entity);

	/**
	* @fn UpdateBuffer
	* @brief 定数バッファの更新関数
	* @param uint8_t (_dataID) 描画するVisualEntityDataのID
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

private:
	/** 表示するSkeletalMeshのスケルトン */
	std::weak_ptr<Skeleton> mSkeleton;

public:
	/**
	* @fn SetSkeletalMesh
	* @brief スケルタルメッシュをセットする
	* @param std::shared_ptr<SkeletalMesh_Re> _skeletalMesh
	* @return void
	*/
	inline void SetSkeletalMesh(std::shared_ptr<Skeleton> _skeletalMesh);
};

//------------ INLINES --------------------

inline void SkeletalMeshVertexShader::SetSkeletalMesh(std::shared_ptr<Skeleton> _skeletalMesh)
{
	mSkeleton = _skeletalMesh;
}
