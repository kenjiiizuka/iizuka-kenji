/**
* @file DirectX11RasterizerState
* @brief DirectX11RasterizerStateクラスの定義
*/

#pragma once

//----------- INCLUDES ---------
#include <d3d11.h>

/**
* @class DirectX11RasterizerState
* @brief ID3D11RasterizerStateをラップしたクラス
*/
class DirectX11RasterizerState
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	DirectX11RasterizerState();

	/**
	* デストラクタ
	*/
	~DirectX11RasterizerState();

private:
	/** ラスタライザーステート */
	ID3D11RasterizerState* mRasterizerState;

	/** ラスタライザーデスク */
	D3D11_RASTERIZER_DESC mRasterizerDesc;

public:
	/**
	* @fn SetupRasterizerDesc
	* @brief ラスタライザーデスクの設定
	* @param const D3D11_FILL_MODE& (_fillMode)
	* @param const D3D11_CULL_MODE& (_cullMode)
	* @return void
	*/
	void SetupRasterizerDesc(const D3D11_FILL_MODE& _fillMode, const D3D11_CULL_MODE& _cullMode);

	/**
	* @fn GetRasterizerState
	* @brief ラスタライザーステートを取得する関数
	* @return ID3D11RasterizerState*
	*/
	inline ID3D11RasterizerState* GetRasterizerState() const;

	/**
	* @fn ID3D11RasterizerState**
	* @brief ラスタライザーステートのダブルポインタを返す
	* @return ID3D11RasterizerState**
	*/
	inline ID3D11RasterizerState** GetRasterizerStateWPtr();

	/**
	* @fn GetRasterizerDesc
	* @brief ラスタライザーステートのゲッター
	* @return D3D11_RASTERIZER_DESC
	*/
	inline D3D11_RASTERIZER_DESC GetRasterizerDesc() const;

};

//--------- INLINES -----------

inline ID3D11RasterizerState* DirectX11RasterizerState::GetRasterizerState() const
{
	return mRasterizerState;
}

inline ID3D11RasterizerState** DirectX11RasterizerState::GetRasterizerStateWPtr()
{
	return &mRasterizerState;
}

inline D3D11_RASTERIZER_DESC DirectX11RasterizerState::GetRasterizerDesc() const
{
	return mRasterizerDesc;
}
