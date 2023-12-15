#pragma once
#include "VertexShader.h"

/** シャドウマップ描画用シェーダー */
class ShadowVertexShader final : public VertexShader
{
public:
	/**
	* シェーダーの読み込み
	*/
	ShadowVertexShader(VisualEntity* _entity);

	/**
　　 * @fn UpdateBuffer
	 * @brief 定数バッファの書き込みとセット
	 * @param uint8_t (_dataID)
　　 * @return void
　　*/
	void UpdateBuffer(uint8_t _dataID) override;
};

