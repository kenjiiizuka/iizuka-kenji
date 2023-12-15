/**
* @file OutlinePixelShader.h
* @brief OutlinePixelShaderクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "PixelShader.h"

/**
* @class OutlinePixelShader
* @brief アウトライン描画用のピクセルシェーダー
*/
class OutlinePixelShader : public PixelShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity) このシェーダーを使う描画オブジェクト
	*/
	OutlinePixelShader(VisualEntity* _entity);

	/**
	* デストラクタ
	*/
	~OutlinePixelShader();
};


