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

private:
	/** アウトラインカラー */
	DirectX::SimpleMath::Color mOutlineColor;

public:
	/**
	* @fn UpdateBuffer
	* @brief バッファーの更新処理
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

	/**
	* @fn SetOutlineColor
	* @brief アウトラインカラーのセッター
	* @param const DirectX::SimpleMath::Color (_color)
	* @return void
	*/
	inline void SetOutlineColor(const DirectX::SimpleMath::Color _color);

};

//---------- INLINES ----------

inline void OutlinePixelShader::SetOutlineColor(const DirectX::SimpleMath::Color _color)
{
	mOutlineColor = _color;
}