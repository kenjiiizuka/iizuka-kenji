#include "DirectX11Device.h"
#include "DirectX11RasterizerState.h"
#include "DirectX11SamplerState.h"

DirectX11Device::DirectX11Device()
	:mDevice(nullptr)
{
	// ˆ—‚È‚µ
}

DirectX11Device::~DirectX11Device()
{
	// ˆ—‚È‚µ
}

HRESULT DirectX11Device::CreateRasterizerState(const std::shared_ptr<DirectX11RasterizerState>& _rasterizer)
{
	D3D11_RASTERIZER_DESC desc = _rasterizer->GetRasterizerDesc();
	ID3D11RasterizerState** rasterizer = _rasterizer->GetRasterizerStateWPtr();
	return mDevice->CreateRasterizerState(&desc, rasterizer);	
}

HRESULT DirectX11Device::CreateSamplerState(const std::shared_ptr<DirectX11SamplerState>& _samplerState)
{
	D3D11_SAMPLER_DESC desc = _samplerState->GetSamplerStateDesc();
	ID3D11SamplerState** sampler = _samplerState->GetSamplerStateWPtr();
	return mDevice->CreateSamplerState(&desc, sampler);
}
