
//-----------LINK ---------
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")


//----------- INCLUDES -----------
#include "Renderer.h"
#include "../../Application.h"
#include <iostream>
#include "View/RenderTarget.h"
#include "View/DepthStencil.h"
#include "SwapChain.h"
#include "DirectX11Device.h"
#include "DirectX11DeviceContext.h"
#include "DirectX11DepthStencilState.h"
#include "DirectX11BlendState.h"
#include "DirectX11RasterizerState.h"
#include "DirectX11SamplerState.h"
#include "DirectX11ViewPort.h"

using namespace DirectX::SimpleMath;

Renderer::Renderer()
	: mApplication(nullptr)
	, mFeatureLevel(D3D_FEATURE_LEVEL_11_0)
{
	// 処理なし
}

Renderer::~Renderer()
{
	// 処理なし
}

void Renderer::Initialize(Application* _app)
{
	HRESULT hr = S_OK;

	mApplication = _app;

	// 画面サイズ取得
	UINT width = static_cast<UINT>(mApplication->GetWidth());
	UINT height = static_cast<UINT>(mApplication->GetHeight());

	// スワップチェーンの設定
	mSwapChain = std::make_shared<SwapChain>();
	mSwapChain->SetupSwapChainDesc
	(
		mApplication->GetWindow(), 
		width,
		height, 
		TRUE
	);
	DXGI_SWAP_CHAIN_DESC swapChainDesc = mSwapChain->GetSwapChainDesc();

	// デバイス、スワップチェーンの作成
	mDevice = std::make_shared<DirectX11Device>();
	mDeviceContext = std::make_shared<DirectX11DeviceContext>();

	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		mSwapChain->GetSwapChainWPtr(),
		mDevice->GetDeviceWPtr(),
		&mFeatureLevel,
		mDeviceContext->GetContextWPtr()
	);

	
	// エラー処理
	if (FAILED(hr)) 
	{
		MessageBox(mApplication->GetWindow(), L"デバイスまたはスワップチェーンの作成に失敗", L"Renderer.cpp Error", MB_OK);
		return;
	}

	// レンダーターゲットビューの作成
	mRenderTargetView = std::make_shared<RenderTarget>();
	hr = mRenderTargetView->CreateFromScreen();	
	if (FAILED(hr)) 
	{
		MessageBox(mApplication->GetWindow(), L"レンダーターゲットビューの作成に失敗", L"Renderer.cpp Error", MB_OK);
		return;
	}
	
	// デプスステンシルビューの作成
	mDepthStencilView = std::make_shared<DepthStencil>();
	mDepthStencilView->Create(width, height, false);

	// レンダーターゲットの設定
	ResetRenderTarget();

	// ビューポートの設定(描画領域)
	mViewPort = std::make_shared<DirectX11ViewPort>();
	mViewPort->SetupViewPort(static_cast<FLOAT>(width), static_cast<FLOAT>(height), 1.0f, 0.0f, 0.0f, 0.0f);
	mDeviceContext->SetViewPort(mViewPort);
	
	// ラスタライザステート作成
	// ぬりつぶし
	mRasterizerSolidBack = std::make_shared<DirectX11RasterizerState>();
	mRasterizerSolidBack->SetupRasterizerDesc(D3D11_FILL_SOLID, D3D11_CULL_BACK);
	hr = mDevice->CreateRasterizerState(mRasterizerSolidBack);
	if (FAILED(hr))
	{
		std::cout << "ラスタライザーステートの作成に失敗しました" << std::endl;
	}

	// ぬりつぶし Cull_Front
	mRasterizerSolidFront = std::make_shared<DirectX11RasterizerState>();
	mRasterizerSolidFront->SetupRasterizerDesc(D3D11_FILL_SOLID, D3D11_CULL_FRONT);
	hr = mDevice->CreateRasterizerState(mRasterizerSolidFront);
	if (FAILED(hr))
	{
		std::cout << "ラスタライザーステートの作成に失敗しました" << std::endl;
	}

	// ワイヤフレーム
	mRasterizerFrame = std::make_shared<DirectX11RasterizerState>();
	mRasterizerFrame->SetupRasterizerDesc(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);
	hr = mDevice->CreateRasterizerState(mRasterizerFrame);
	if (FAILED(hr))
	{
		std::cout << "ラスタライザーステートの作成に失敗しました" << std::endl;
	}

	mDeviceContext->SetRasterizerState(mRasterizerSolidBack);
			
	// ブレンドステートの設定	
	mBlendState = std::make_shared<DirectX11BlendState>();
	mBlendState->SetupBlendDesc();
	hr = mBlendState->CreateBlendState(mDevice);
	if (FAILED(hr))
	{
		std::cout << "ブレンドステートの作成に失敗しました" << std::endl;
		return;
	}

	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	mDeviceContext->SetBlendState(mBlendState, blendFactor);

	// デプスステンシルステート作成
	// デプスステンシル有効ステート
	mDepthStencilEnable = std::make_shared<DirectX11DepthStencilState>();
	mDepthStencilEnable->SetupDepthStencilStateDesc(D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS_EQUAL);
	mDepthStencilEnable->CreateDepthStencilState(mDevice);

	// デプスステンシル無効ステート	
	mDepthStencilDisable = std::make_shared<DirectX11DepthStencilState>();
	mDepthStencilDisable->SetupDepthStencilStateDesc(D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_LESS_EQUAL);
	mDepthStencilDisable->CreateDepthStencilState(mDevice);
	
	mDeviceContext->GetContext()->OMSetDepthStencilState(mDepthStencilEnable->GetDepthStencilState(), 0);

	// サンプラーステートの設定 テクスチャのサンプリング方法を設定するための者
	mSamplerState = std::make_shared<DirectX11SamplerState>();
	mSamplerState->SetupSamplerStateDesc();
	mDevice->CreateSamplerState(mSamplerState);
	mDeviceContext->SetSamplerState(0, 1, mSamplerState);
}

void Renderer::Uninitialize()
{
	mSamplerState->Release();
	mDeviceContext->GetContext()->ClearState();
	//mRenderTargetView->Release();
	mSwapChain->Release();
	mDeviceContext->GetContext()->Release();
	mDevice->GetDevice()->Release();
}

void Renderer::BeginRenderer()
{		
	mRenderTargetView->Clear({ 0,0,1,1 });
	mDepthStencilView->Clear();
}

void Renderer::EndRenderer()
{
	mSwapChain->Present(); // バックバッファにレンダリングされたイメージをウィンドウに表示する関数
}

ID3D11Device* Renderer::GetDevice()
{
	return mDevice->GetDevice();
}

ID3D11DeviceContext* Renderer::GetDeviceContext()
{
	return mDeviceContext->GetContext();
}

float Renderer::GetWidth()
{
	return mApplication->GetWidth();
}

float Renderer::GetHeight()
{
	return mApplication->GetHeight();
}

void Renderer::Draw(D3D_PRIMITIVE_TOPOLOGY _topology, UINT _numVertex, UINT _startVertexLocation)
{
	mDeviceContext->GetContext()->IASetPrimitiveTopology(_topology);
	mDeviceContext->GetContext()->Draw(_numVertex, _startVertexLocation);
}

void Renderer::SetRasterizerSolidBack()
{
	mDeviceContext->SetRasterizerState(mRasterizerSolidBack);
}

void Renderer::SetRasterizerSolidFront()
{
	mDeviceContext->SetRasterizerState(mRasterizerSolidFront);
}

void Renderer::SetRasterizerWireFrame()
{
	mDeviceContext->SetRasterizerState(mRasterizerFrame);
}

IDXGISwapChain* Renderer::GetSwapChain()
{
	return *mSwapChain->GetSwapChainWPtr();
}

ID3D11SamplerState* Renderer::GetSamplerState()
{
	return mSamplerState->GetSamplerState();
}

void Renderer::SetRenderTarget(std::shared_ptr<RenderTarget> _targetTarget, std::shared_ptr<DepthStencil> _depthStencil)
{
	ID3D11RenderTargetView* view = _targetTarget->GetView();
	ID3D11DepthStencilView* depth = _depthStencil->GetView();
	mDeviceContext->GetContext()->OMSetRenderTargets(1, &view, depth);

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<FLOAT>(_targetTarget->GetWidth());
	vp.Height = static_cast<FLOAT>(_targetTarget->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	mDeviceContext->GetContext()->RSSetViewports(1, &vp);
}

void Renderer::ResetRenderTarget()
{
	ID3D11RenderTargetView* view = mRenderTargetView->GetView();
	ID3D11DepthStencilView* depth = mDepthStencilView->GetView();
	mDeviceContext->GetContext()->OMSetRenderTargets(1, &view, depth);

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<FLOAT>(mRenderTargetView->GetWidth());
	vp.Height = static_cast<FLOAT>(mDepthStencilView->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	mDeviceContext->GetContext()->RSSetViewports(1, &vp);
}
