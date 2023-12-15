#pragma once
#include "PixelShader.h"

/** zバッファ書き込みのためのピクセルシェーダー */
class DepthWritePixelShader : public PixelShader
{
public:
	/**
	* シェーダーの読み込み
	* 
	* @param[in] VisualEntity* (_entity) 定数バッファなどが存在しないので nullptr
	*/
	DepthWritePixelShader(VisualEntity* _entity = nullptr);

};

