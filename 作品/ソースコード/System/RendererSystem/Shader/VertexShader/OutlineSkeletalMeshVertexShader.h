/**
* @file OutlineSkeletalMeshVertexShader.h
* @brief OutlineSkeletalMeshVertexShaderクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include "VertexShader.h"

//-------- 前方宣言 ----------
class Skeleton;

/**
* @class OutlineSkeletalMeshVertexShader
* @brief SkeletalMeshのアウトラインを描画するシェーダー
*/
class OutlineSkeletalMeshVertexShader : public VertexShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity)
	*/
	OutlineSkeletalMeshVertexShader(VisualEntity* _entity);

	/**
	* デストラクタ
	*/
	~OutlineSkeletalMeshVertexShader();

	/**
	* @fn UpdateBuffer
	* @brief 定数バッファ―の更新処理
	* @param uint8_t _dataID 
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

private:
	/** 表示するSkeletalMeshのスケルトン */
	std::weak_ptr<Skeleton> mSkeleton;

	/** アウトラインの太さ */
	float mOutlineThickness;

public:
	/**
	* @fn SetSkeleton
	* @brief スケルトンのセット
	* @return void
	*/
	inline void SetSkeleton(std::shared_ptr<Skeleton> _skeleton);

};

//--------- INLINES ---------

inline void OutlineSkeletalMeshVertexShader::SetSkeleton(std::shared_ptr<Skeleton> _skeleton)
{
	mSkeleton = _skeleton;
}
