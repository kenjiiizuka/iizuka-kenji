#include "DirectX11RasterizerState.h"

DirectX11RasterizerState::DirectX11RasterizerState()
	: mRasterizerDesc({})
	, mRasterizerState(nullptr)
{
	// �����Ȃ�
}

DirectX11RasterizerState::~DirectX11RasterizerState()
{
	// �����Ȃ�
}

void DirectX11RasterizerState::SetupRasterizerDesc(const D3D11_FILL_MODE& _fillMode, const D3D11_CULL_MODE& _cullMode)
{
	mRasterizerDesc.FillMode = _fillMode;
	mRasterizerDesc.CullMode = _cullMode;
	mRasterizerDesc.DepthClipEnable = TRUE;
	mRasterizerDesc.MultisampleEnable = FALSE;
}

