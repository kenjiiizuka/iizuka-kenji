/**
* @file DirectX11DepthStencilState.h
* @brief DirectX11DepthStencilStateクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include <d3d11.h>
#include <memory>

//---------- INCLUDES ---------
class DirectX11Device;

/**
* @class DirectX11DepthStencilState
* @brief DepthStencilStateをラップしたクラス
*/
class DirectX11DepthStencilState
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	DirectX11DepthStencilState();

	/**
	* デストラクタ
	*/
	~DirectX11DepthStencilState();

private:
	/** デプスステンシルステート */
	ID3D11DepthStencilState* mDepthStencilState;

	/** デプスステンシルデスク */
	D3D11_DEPTH_STENCIL_DESC mDepthStencilDesc;

public:
	/**
	* @fn SetupDepthStencilStateDesc
	* @brief デプスステンシルステートデスクの設定関数
	* @param const D3D11_DEPTH_WRITE_MASK& (_depthWriteMask)
	* @param const D3D11_COMPARISON_FUNC&  (_depthFunc)
	* @param const BOOL                    (_depthEnable)
	* @param const BOOL                    (_stencilEnable)
	* @return void
	*/
	void SetupDepthStencilStateDesc(const D3D11_DEPTH_WRITE_MASK& _depthWriteMask, const D3D11_COMPARISON_FUNC& _depthFunc, const BOOL _depthEnable = TRUE, const BOOL _stencilEnable = FALSE);

	/**
	* @fn CreateDepthStencilState
	* @brief デプスステンシル作成
	* @param const std::shared_ptr<DirectX11Device> (_device)
	* @return void
	*/
	void CreateDepthStencilState(const std::shared_ptr<DirectX11Device> _device);

	/**
	* @fn GetDepthStencilState
	* @brief デプスステンシルステートを返す
	* @return ID3D11DepthStencilState*
	*/
	inline ID3D11DepthStencilState* GetDepthStencilState() const;

};

//-------------- INLINES -----------

inline ID3D11DepthStencilState* DirectX11DepthStencilState::GetDepthStencilState() const
{
	return mDepthStencilState;
}
