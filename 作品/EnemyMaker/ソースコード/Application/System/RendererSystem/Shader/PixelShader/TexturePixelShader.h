/**
* @file TexturePixelShader.h
* @brief TexturePixelShaderクラスの定義
*/

#pragma once

//----------- INCLUDES ---------
#include "PixelShader.h"

/**
* @class TexturePixelShader
* @brief テクスチャのみを表示するピクセルシェーダー
*/
class TexturePixelShader : public PixelShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity) 
	*/
	TexturePixelShader(VisualEntity* _entity);

	/**
	* @fn UpdateBuffer
	* @brief 定数バッファ更新処理
	* @return uint8_t (_dataID)
	*/
	void UpdateBuffer(uint8_t _dataID) override;
};

