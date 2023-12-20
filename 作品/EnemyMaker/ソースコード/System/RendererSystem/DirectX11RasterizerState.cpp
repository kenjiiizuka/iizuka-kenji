#include "DirectX11RasterizerState.h"

DirectX11RasterizerState::DirectX11RasterizerState()
	: mRasterizerDesc({})
	, mRasterizerState(nullptr)
{
	// ˆ—‚È‚µ
}

DirectX11RasterizerState::~DirectX11RasterizerState()
{
	// ˆ—‚È‚µ
}

void DirectX11RasterizerState::SetupRasterizerDesc(const D3D11_FILL_MODE& _fillMode, const D3D11_CULL_MODE& _cullMode)
{
	mRasterizerDesc.FillMode = _fillMode;
	mRasterizerDesc.CullMode = _cullMode;
	mRasterizerDesc.DepthClipEnable = TRUE;
	mRasterizerDesc.MultisampleEnable = FALSE;
}

