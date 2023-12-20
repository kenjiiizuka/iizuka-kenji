//---------- INCLUDES -----------
#include "DirectX11SamplerState.h"

DirectX11SamplerState::DirectX11SamplerState()
	: mSamplerState(nullptr)
	, mSamplerStateDesc({})
{
	// �����Ȃ�
}

DirectX11SamplerState::~DirectX11SamplerState()
{
	// �����Ȃ�
}

void DirectX11SamplerState::Release()
{
	mSamplerState->Release();
}

void DirectX11SamplerState::SetupSamplerStateDesc()
{
	mSamplerStateDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	mSamplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	mSamplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	mSamplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	mSamplerStateDesc.MaxAnisotropy = 4;
	mSamplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;
}

