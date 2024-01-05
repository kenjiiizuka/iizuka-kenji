/**
* @file FrustumCullingGeometryShader.h
* @brief FrustumCullingGeometryShaderクラスの定義
*/
#pragma once

//---------- INCLUDES ----------
#include "GeometryShader.h"

/**
* @class FrustumCullingGeometryShader
* @brief フラストラムカリング用ジオメトリシェーダー
*/
class FrustumCullingGeometryShader : public GeometryShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity) このシェーダーを使用する描画オブジェクト
	*/
	FrustumCullingGeometryShader(VisualEntity* _entity);

	/**
	* デストラクタ
	*/
	~FrustumCullingGeometryShader();

	/**
	* @fn UpdateBuffer
	* @brief バッファーの更新処理
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

};

