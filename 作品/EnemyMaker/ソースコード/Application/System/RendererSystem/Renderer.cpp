
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
	// �����Ȃ�
}

Renderer::~Renderer()
{
	// �����Ȃ�
}

void Renderer::Initialize(Application* _app)
{
	HRESULT hr = S_OK;

	mApplication = _app;

	// ��ʃT�C�Y�擾
	UINT width = static_cast<UINT>(mApplication->GetWidth());
	UINT height = static_cast<UINT>(mApplication->GetHeight());

	// �X���b�v�`�F�[���̐ݒ�
	mSwapChain = std::make_shared<SwapChain>();
	mSwapChain->SetupSwapChainDesc
	(
		mApplication->GetWindow(), 
		width,
		height, 
		TRUE
	);
	DXGI_SWAP_CHAIN_DESC swapChainDesc = mSwapChain->GetSwapChainDesc();

	// �f�o�C�X�A�X���b�v�`�F�[���̍쐬
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

	
	// �G���[����
	if (FAILED(hr)) 
	{
		MessageBox(mApplication->GetWindow(), L"�f�o�C�X�܂��̓X���b�v�`�F�[���̍쐬�Ɏ��s", L"Renderer.cpp Error", MB_OK);
		return;
	}

	// �����_�[�^�[�Q�b�g�r���[�̍쐬
	mRenderTargetView = std::make_shared<RenderTarget>();
	hr = mRenderTargetView->CreateFromScreen();	
	if (FAILED(hr)) 
	{
		MessageBox(mApplication->GetWindow(), L"�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s", L"Renderer.cpp Error", MB_OK);
		return;
	}
	
	// �f�v�X�X�e���V���r���[�̍쐬
	mDepthStencilView = std::make_shared<DepthStencil>();
	mDepthStencilView->Create(width, height, false);

	// �����_�[�^�[�Q�b�g�̐ݒ�
	ResetRenderTarget();

	// �r���[�|�[�g�̐ݒ�(�`��̈�)
	mViewPort = std::make_shared<DirectX11ViewPort>();
	mViewPort->SetupViewPort(static_cast<FLOAT>(width), static_cast<FLOAT>(height), 1.0f, 0.0f, 0.0f, 0.0f);
	mDeviceContext->SetViewPort(mViewPort);
	
	// ���X�^���C�U�X�e�[�g�쐬
	// �ʂ�Ԃ�
	mRasterizerSolidBack = std::make_shared<DirectX11RasterizerState>();
	mRasterizerSolidBack->SetupRasterizerDesc(D3D11_FILL_SOLID, D3D11_CULL_BACK);
	hr = mDevice->CreateRasterizerState(mRasterizerSolidBack);
	if (FAILED(hr))
	{
		std::cout << "���X�^���C�U�[�X�e�[�g�̍쐬�Ɏ��s���܂���" << std::endl;
	}

	// �ʂ�Ԃ� Cull_Front
	mRasterizerSolidFront = std::make_shared<DirectX11RasterizerState>();
	mRasterizerSolidFront->SetupRasterizerDesc(D3D11_FILL_SOLID, D3D11_CULL_FRONT);
	hr = mDevice->CreateRasterizerState(mRasterizerSolidFront);
	if (FAILED(hr))
	{
		std::cout << "���X�^���C�U�[�X�e�[�g�̍쐬�Ɏ��s���܂���" << std::endl;
	}

	// ���C���t���[��
	mRasterizerFrame = std::make_shared<DirectX11RasterizerState>();
	mRasterizerFrame->SetupRasterizerDesc(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);
	hr = mDevice->CreateRasterizerState(mRasterizerFrame);
	if (FAILED(hr))
	{
		std::cout << "���X�^���C�U�[�X�e�[�g�̍쐬�Ɏ��s���܂���" << std::endl;
	}

	mDeviceContext->SetRasterizerState(mRasterizerSolidBack);
			
	// �u�����h�X�e�[�g�̐ݒ�	
	mBlendState = std::make_shared<DirectX11BlendState>();
	mBlendState->SetupBlendDesc();
	hr = mBlendState->CreateBlendState(mDevice);
	if (FAILED(hr))
	{
		std::cout << "�u�����h�X�e�[�g�̍쐬�Ɏ��s���܂���" << std::endl;
		return;
	}

	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	mDeviceContext->SetBlendState(mBlendState, blendFactor);

	// �f�v�X�X�e���V���X�e�[�g�쐬
	// �f�v�X�X�e���V���L���X�e�[�g
	mDepthStencilEnable = std::make_shared<DirectX11DepthStencilState>();
	mDepthStencilEnable->SetupDepthStencilStateDesc(D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS_EQUAL);
	mDepthStencilEnable->CreateDepthStencilState(mDevice);

	// �f�v�X�X�e���V�������X�e�[�g	
	mDepthStencilDisable = std::make_shared<DirectX11DepthStencilState>();
	mDepthStencilDisable->SetupDepthStencilStateDesc(D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_LESS_EQUAL);
	mDepthStencilDisable->CreateDepthStencilState(mDevice);
	
	mDeviceContext->GetContext()->OMSetDepthStencilState(mDepthStencilEnable->GetDepthStencilState(), 0);

	// �T���v���[�X�e�[�g�̐ݒ� �e�N�X�`���̃T���v�����O���@��ݒ肷�邽�߂̎�
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
	mSwapChain->Present(); // �o�b�N�o�b�t�@�Ƀ����_�����O���ꂽ�C���[�W���E�B���h�E�ɕ\������֐�
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
