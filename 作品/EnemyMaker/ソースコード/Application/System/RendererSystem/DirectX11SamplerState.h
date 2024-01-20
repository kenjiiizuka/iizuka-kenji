/**
* @file DirectX11SamplerState.h
* @brief DirectX11SamplerStateクラスの定義
*/

#pragma once

//---------- INCLUDES ---------
#include <d3d11.h>


/**
* @class DirectX11SamplerState
* @brief ID3D11SamplerStateをラップしたクラス
*/
class DirectX11SamplerState final
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	DirectX11SamplerState();

	/**
	* デストラクタ
	*/
	~DirectX11SamplerState();

private:
	/** サンプラーステート */
	ID3D11SamplerState* mSamplerState;

	/** サンプラーステートデスク */
	D3D11_SAMPLER_DESC mSamplerStateDesc;

public:
	/**
	* @fn Release
	* @brief サンプラーステートの解放処理
	* @return void
	*/
	void Release();

	/**
	* @fn SetupSamplerStateDesc
	* @brief SamplerStateDescの設定をする
	* @return void
	*/
	void SetupSamplerStateDesc();

	/**
	* @fn GetSamplerState
	* @brief サンプラーステートのゲッター
	* @return void
	*/
	inline ID3D11SamplerState* GetSamplerState() const;

	/**
	* @fn GetSamplerStateWPtr
	* @brief サンプラーステートのダブルポインタを返す
	* @return ID3D11SamplerState**
	*/
	inline ID3D11SamplerState** GetSamplerStateWPtr();

	/**
	* @fn GetSamplerStateDesc
	* @brief サンプラーステートデスクを返す
	* @return D3D11_SAMPLER_DESC
	*/
	inline D3D11_SAMPLER_DESC GetSamplerStateDesc();


};

//-------- INLINES --------

inline ID3D11SamplerState* DirectX11SamplerState::GetSamplerState() const
{
	return mSamplerState;
}

inline ID3D11SamplerState** DirectX11SamplerState::GetSamplerStateWPtr()
{
	return &mSamplerState;
}

inline D3D11_SAMPLER_DESC DirectX11SamplerState::GetSamplerStateDesc()
{
	return mSamplerStateDesc;
}
