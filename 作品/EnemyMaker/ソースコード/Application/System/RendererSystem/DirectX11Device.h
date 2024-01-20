/**
* @file DirectX11Device.h
* @brief DirectX11Deviceクラスの定義
*/

#pragma once
//------------ INCLUDES ----------
#include <d3d11.h>
#include <memory>

//----------- 前方宣言 ---------
class DirectX11RasterizerState;
class DirectX11SamplerState;

/**
* @fn DirectX11Device
* @brief ID3D11Deviceをラップしたクラス
*/
class DirectX11Device final
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	DirectX11Device();

	/**
	* デストラクタ
	*/
	~DirectX11Device();

private:
	/** デバイス */
	ID3D11Device* mDevice;

public:
	/**
	* @fn CreateRasterizerState
	* @brief ラスタライザーステート作成関数
	* @param const std::shared_ptr<DirectX11RasterizerState>& (_rasterizer)
	* @return HRESULT
	*/
	HRESULT CreateRasterizerState(const std::shared_ptr<DirectX11RasterizerState>& _rasterizer);

	/**
	* @fn CreateSamplerState
	* @brief サンプラーステート作成関数
	* @param const std::shared_ptr<DirectX11SamplerState>& (_samplerState)
	* @return HRESULT
	*/
	HRESULT CreateSamplerState(const std::shared_ptr<DirectX11SamplerState>& _samplerState);

public:
	/**
	* @fn GetDevice
	* @brief デバイスのゲッター
	* @return ID3D11Device*
	*/
	inline ID3D11Device* GetDevice();

	/**
	* @fn GetDevice
	* @brief Deviceのダブルポインタのゲッター
	* @return ID3D11Device**
	*/
	inline ID3D11Device** GetDeviceWPtr();
};

//----------- INLINES -----------

inline ID3D11Device* DirectX11Device::GetDevice()
{
	return mDevice;
}

inline ID3D11Device** DirectX11Device::GetDeviceWPtr()
{
	return &mDevice;
}