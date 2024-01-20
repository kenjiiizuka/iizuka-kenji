/**
* @file DirectX11DeviceContext.h
* @brief DirectX11DeviceContextクラスの定義
*/

#pragma once


//--------- INCLUDES ----------
#include <d3d11.h>
#include <memory>

//------- 前方宣言 --------
class DirectX11BlendState;
class DirectX11RasterizerState;
class DirectX11SamplerState;
class DirectX11ViewPort;

/**
* @class DirectX11DeviceContext
* @brief ID3D11DeviceContextをラップしたクラス
*/
class DirectX11DeviceContext final
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	DirectX11DeviceContext();

	/**
	* デストラクタ
	*/
	~DirectX11DeviceContext();

private:
	/** デバイスコンテキスト */
	ID3D11DeviceContext* mDeviceContext;

public:
	/**
	* @fn Release
	* @brief DeviceContextの解放
	* @return void
	*/
	void Release();

	/**
	* @fn SetBlendState
	* @brief ブレンドステートのセット
	* @param const std::shared_ptr<DirectX11BlendState> (_blendState)
	* @param const float (_blendFactor[4])
	* @return void
	*/
	void SetBlendState(const std::shared_ptr<DirectX11BlendState> _blendState, const float _blendFactor[4]);

	/**
	* @fn SetRasterizerState
	* @brief ラスタライザーステートのセット
	* @param const std::shared_ptr<DirectX11RasterizerState> (_rasterizerState)
	* @return void
	*/
	void SetRasterizerState(const std::shared_ptr<DirectX11RasterizerState> _rasterizerState);

	/**
	* @fn SetSamplerState
	* @brief サンプラーステートのセット
	* @param const UINT (_slot)
	* @param const UINT (_numSampler)
	* @param const std::shared_ptr<DirectX11SamplerState> (_samplerState)
	* @return void
	*/
	void SetSamplerState(const UINT _slot, const UINT _numSampler,const std::shared_ptr<DirectX11SamplerState> _samplerState);

	/**
	* @fn SetViewPort
	* @brief ビューポートのセッター
	* @param const std::shared_ptr<DirectX11ViewPort> (_viewPort)
	* @return void
	*/
	void SetViewPort(const std::shared_ptr<DirectX11ViewPort> _viewPort);

public:
	/**
	* @fn GetContext
	* @brief デバイスコンテキストを返す
	* @return ID3D11DeviceContext*
	*/
	inline ID3D11DeviceContext* GetContext() const;

	/**
	* @fn GetContextWPtr
	* @brief デバイスコンテキストとのダブルポインタを返す
	* @return ID3D11DeviceContext**
	*/
	inline ID3D11DeviceContext** GetContextWPtr();

};

//--------- INLINES ----------

inline ID3D11DeviceContext* DirectX11DeviceContext::GetContext() const
{
	return mDeviceContext;
}

inline ID3D11DeviceContext** DirectX11DeviceContext::GetContextWPtr()
{
	return &mDeviceContext;
}
