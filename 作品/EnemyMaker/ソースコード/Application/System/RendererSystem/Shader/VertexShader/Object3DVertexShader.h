/**
* @file Object3DVertexShader.h
* @brief Object3DVertexShaderクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "VertexShader.h"

/**
* @class Object3DVertexShader
* @brief 3Dオブジェクトを描画する頂点シェーダー 
*/
class Object3DVertexShader : public VertexShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity)
	*/
	Object3DVertexShader(VisualEntity* _entity);

	/**
	* @fn UpdateBuffer
	* @brief バッファーの更新処理
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;
};

