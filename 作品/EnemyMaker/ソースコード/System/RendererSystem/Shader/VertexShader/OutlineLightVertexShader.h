/**
* @file OutlineLightVertexShader.h
* @brief OutlineLightVertexShaderクラス
*/

#pragma once

//--------- INCLUDES ---------
#include "VertexShader.h"

/**
* @class OutlineLightVertexShader
* @brief スタティックメッシュのアウトライン描画用のシェーダー
*/
class OutlineLightVertexShader : public VertexShader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_entity)
	*/
	OutlineLightVertexShader(VisualEntity* _entity);

	/**
	* デストラクタ
	*/
	~OutlineLightVertexShader();

private:
	/** アウトラインの太さ */
	float mOutlineThickness;

private:
	/**
	* @fn UpdateBuffer
	* @brief 定数バッファ―の更新処理
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

public:
	/**
	* @fn SetOutlineThickness
	* @brief アウトラインの太さをセットする
	* @param const float (_thickness)
	* @return void
	*/
	inline void SetOutlineThickness(const float _thickness) noexcept;

};

//------------ INLINES -------------

inline void OutlineLightVertexShader::SetOutlineThickness(const float _thickness) noexcept
{
	mOutlineThickness = _thickness;
}