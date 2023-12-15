#include "SwapChain.h"

SwapChain::SwapChain()
	: mSwapChain(nullptr)
	, mSwapChainDesc({})
{
}

SwapChain::~SwapChain()
{
}

void SwapChain::SetupSwapChainDesc(const HWND& _outPutWindow, const UINT& _bufferWidth, const UINT& _bufferHeight, const BOOL& _windowMode)
{
	mSwapChainDesc.BufferCount = 1;                                 // スワップチェーンが持つバッファの数
	mSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // スワップチェーンが持つバッファの使用方法　レンダーターゲットとして使用する
	mSwapChainDesc.OutputWindow = _outPutWindow;                    // スワップチェーンの出力先のウィンドウ
	mSwapChainDesc.SampleDesc.Count = 1;                            // マルチサンプリングの設定
	mSwapChainDesc.SampleDesc.Quality = 0;                          // マルチサンプリングの品質の設定
	mSwapChainDesc.BufferDesc.Width = _bufferWidth;                 // バッファの幅を設定（画面サイズ）
	mSwapChainDesc.BufferDesc.Height = _bufferHeight;               // バッファの高さを設定 (画面サイズ)
	mSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // バッファのフォーマットの設定 (8ビットのRGBA)
	mSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;          // バッファのリフレッシュレートの分母
	mSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;           // バッファのリフレッシュレートの分子
	mSwapChainDesc.Windowed = _windowMode;                          // ウィンドウモード
}

void SwapChain::Release()
{
	mSwapChain->Release();
}

void SwapChain::Present()
{
	mSwapChain->Present(1, 0);
}
