/**
* @file VertexObject2DShader.h
* @brief VertexObject2DShaderクラスの定義
*/

#pragma once

//----------- INCLUDES ----------
#include "VertexShader.h"

/**
* @class VertexObject2DShader
* @brief 2Dオブジェクト描画用頂点シェーダー
*/
class VertexObject2DShader : public VertexShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity) 個のシェーダーの使用する描画オブジェクト
	*/
	VertexObject2DShader(VisualEntity* _entity);

public:
	/**
	* @fn UpdateBuffer
	* @brief 更新処理
	* @param uint8_t (_dataID)
	* @return void
	*/
	virtual void UpdateBuffer(uint8_t _dataID);
};

