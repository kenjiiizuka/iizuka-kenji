//------------ INCLUDES -----------
#include "DirectX11DepthStencilState.h"
#include "DirectX11Device.h"

DirectX11DepthStencilState::DirectX11DepthStencilState()
	: mDepthStencilDesc({})
	, mDepthStencilState(nullptr)
{
	// 処理なし
}

DirectX11DepthStencilState::~DirectX11DepthStencilState()
{
	// 処理なし
}

void DirectX11DepthStencilState::SetupDepthStencilStateDesc(const D3D11_DEPTH_WRITE_MASK& _depthWriteMask, const D3D11_COMPARISON_FUNC& _depthFunc, const BOOL _depthEnable, const BOOL _stencilEnable)
{
	mDepthStencilDesc.DepthWriteMask = _depthWriteMask;
	mDepthStencilDesc.DepthFunc = _depthFunc;
	mDepthStencilDesc.DepthEnable = _depthEnable;
	mDepthStencilDesc.StencilEnable = _stencilEnable;
}

void DirectX11DepthStencilState::CreateDepthStencilState(const std::shared_ptr<DirectX11Device> _device)
{
	_device->GetDevice()->CreateDepthStencilState(&mDepthStencilDesc, &mDepthStencilState);
}

