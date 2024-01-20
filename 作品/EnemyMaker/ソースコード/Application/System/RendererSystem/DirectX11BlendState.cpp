//----------- INCLUDES ----------
#include "DirectX11BlendState.h"
#include "DirectX11Device.h"

DirectX11BlendState::DirectX11BlendState()
	: mBlendDesc({})
	, mBlendState(nullptr)
{
	// ˆ—‚È‚µ
}

DirectX11BlendState::~DirectX11BlendState()
{
	// ˆ—‚È‚µ
}

void DirectX11BlendState::Release()
{
	mBlendState->Release();
}

void DirectX11BlendState::SetupBlendDesc(const BOOL _alphaToCoverageEnable)
{
	mBlendDesc.AlphaToCoverageEnable = _alphaToCoverageEnable;
	mBlendDesc.IndependentBlendEnable = TRUE;
	mBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	mBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	mBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	mBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	mBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	mBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	mBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	mBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

HRESULT DirectX11BlendState::CreateBlendState(const std::shared_ptr<DirectX11Device> _device)
{
	return _device->GetDevice()->CreateBlendState(&mBlendDesc, &mBlendState);
}


