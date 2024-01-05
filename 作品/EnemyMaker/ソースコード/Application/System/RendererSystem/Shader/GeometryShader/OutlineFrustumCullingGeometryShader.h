/**
* @file OutlineFrustumCullingGeometryShader.h
* @brief OutlineFrustumCullingGeometryShaderクラスの定義
*/
#pragma once

//---------- INCLUDES ------------
#include "GeometryShader.h"

/**
* @class OutlineFrustumCullingGeometryShader
* @brief アウトライン用のフラストラムカリングシェーダー
*/
class OutlineFrustumCullingGeometryShader : public GeometryShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity) このシェーダーを使用する描画オブジェクト
	*/
	OutlineFrustumCullingGeometryShader(VisualEntity* _entity);

	/**
	* デストラクタ
	*/
	~OutlineFrustumCullingGeometryShader();

	/**
	* @fn UpdateBuffer
	* @brief バッファーの更新処理
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID);

};

