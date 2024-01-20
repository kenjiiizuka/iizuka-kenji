/**
* @file DepthWritePixelShader.h
* @brief DepthWritePixelShaderクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "PixelShader.h"

/**
* @class DepthWritePixelShader
* @brief zバッファ書き込みのためのピクセルシェーダー
*/
class DepthWritePixelShader : public PixelShader
{
public:
	/**
	* シェーダーの読み込み
	* 
	* @param VisualEntity* (_entity) 定数バッファなどが存在しないので nullptr
	*/
	DepthWritePixelShader(VisualEntity* _entity = nullptr);

};

