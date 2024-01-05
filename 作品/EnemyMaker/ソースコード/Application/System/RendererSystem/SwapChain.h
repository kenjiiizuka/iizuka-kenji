/**
* @file SwapChain.h
* @brief SwapChainクラスの定義
*/

#pragma once

//----------- INCLUDES ----------
#include <d3d11.h>

/**
* @class SwapChain
* @brief DX11のSwapChainをラップしたクラス
*/
class SwapChain
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SwapChain();

	/**
	* デストラクタ
	*/
	~SwapChain();

private:
	/** スワップチェーン */
	IDXGISwapChain* mSwapChain;

	/** スワップチェーンデスク */
	DXGI_SWAP_CHAIN_DESC mSwapChainDesc;

public:
	/**
	* @fn CreateSwapChainDesc
	* @brief スワップチェーンデスクの作成関数
	* @param const HWND& (_outPutWindow)
	* @param const UINT& (_bufferWidth)
	* @param const UINT& (_bufferHeight)
	* @param const BOOL& (_windowMode)
	* @return void
	*/
	void SetupSwapChainDesc(const HWND& _outPutWindow, const UINT& _bufferWidth, const UINT& _bufferHeight, const BOOL& _windowMode);

	/**
	* @fn Release
	* @brief 解放関数
	* @return void
	*/
	void Release();

	/**
	* @fn Present
	* @brief 画面表示
	* @return void
	*/
	void Present();

	/**
	* @fn GetSwapChainDesc
	* @brief スワップチェーンデスクの作成
	* @return DXGI_SWAP_CHAIN_DESC
	*/
	inline DXGI_SWAP_CHAIN_DESC GetSwapChainDesc() const noexcept;

	/**
	* @fn GetSwapChainWPtr
	* @brief SwapChainのダブルポインタを返す
	* @return IDXGISwapChain**
	*/
	inline IDXGISwapChain** GetSwapChainWPtr();
};

//--------- INLINES ----------

inline DXGI_SWAP_CHAIN_DESC SwapChain::GetSwapChainDesc() const noexcept
{
	return mSwapChainDesc;
}

inline IDXGISwapChain** SwapChain::GetSwapChainWPtr()
{
	return &mSwapChain;
}

