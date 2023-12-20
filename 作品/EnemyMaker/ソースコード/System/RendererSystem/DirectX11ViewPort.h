/**
* @file DirectX11ViewPort.h
* @brief DirectX11ViewPort
*/

#pragma once

//-------- INCLUDES --------
#include <d3d11.h>

/**
* @class DirectX11ViewPort
* @brief ビューポートクラス
*/
class DirectX11ViewPort
{
public:	
	/**
	* デフォルトコンストラクタ
	*/
	DirectX11ViewPort();

	/**
	* デストラクタ
	*/
	~DirectX11ViewPort();

private:
	/** ビューポート */
	D3D11_VIEWPORT mViewPort;

public:
	/**
	* @fn SetupViewPort
	* @brief ビューポートの設定をする関数
	* @param const FLOAT (_width)
	* @param const FLAOT (_height)
	* @param const FLAOT (_maxDepth)
	* @param const FLAOT (_minDepth)
	* @param const FLAOT (_topLeftX)
	* @param const FLAOT (_topLeftY)
	* @return void
	*/
	void SetupViewPort(const FLOAT _width, const FLOAT _height, const FLOAT _maxDepth, const FLOAT _minDepth, const FLOAT _topLeftX, const FLOAT _topLeftY);	

	/**
	* @fn GetViewPort
	* @brief ビューポートのゲッター
	* @return D3D11_VIEWPORT
	*/
	inline D3D11_VIEWPORT GetViewPort() const;
};

//-------- INLINES ---------

inline D3D11_VIEWPORT DirectX11ViewPort::GetViewPort() const
{
	return mViewPort;
}
