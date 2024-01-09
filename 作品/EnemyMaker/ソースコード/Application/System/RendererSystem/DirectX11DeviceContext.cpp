//--------- INCLUDES ---------
#include "DirectX11DeviceContext.h"
#include "DirectX11BlendState.h"
#include "DirectX11RasterizerState.h"
#include "DirectX11SamplerState.h"
#include "DirectX11ViewPort.h"

DirectX11DeviceContext::DirectX11DeviceContext()
	: mDeviceContext(nullptr)
{
	// ˆ—‚È‚µ
}

DirectX11DeviceContext::~DirectX11DeviceContext()
{
	// ˆ—‚È‚µ
}

void DirectX11DeviceContext::Release()
{
	mDeviceContext->Release();
}

void DirectX11DeviceContext::SetBlendState(const std::shared_ptr<DirectX11BlendState> _blendState, const float _blendFactor[4])
{
	mDeviceContext->OMSetBlendState(_blendState->GetBlendState(), _blendFactor, 0xffffffff);
}

void DirectX11DeviceContext::SetRasterizerState(const std::shared_ptr<DirectX11RasterizerState> _rasterizerState)
{
	mDeviceContext->RSSetState(_rasterizerState->GetRasterizerState());
}

void DirectX11DeviceContext::SetSamplerState(const UINT _slot, const UINT _numSampler, const std::shared_ptr<DirectX11SamplerState> _samplerState)
{
	mDeviceContext->PSSetSamplers(_slot, _numSampler, _samplerState->GetSamplerStateWPtr());
}

void DirectX11DeviceContext::SetViewPort(const std::shared_ptr<DirectX11ViewPort> _viewPort)
{
	D3D11_VIEWPORT viewPort = _viewPort->GetViewPort();
	mDeviceContext->RSSetViewports(1, &viewPort);
}
