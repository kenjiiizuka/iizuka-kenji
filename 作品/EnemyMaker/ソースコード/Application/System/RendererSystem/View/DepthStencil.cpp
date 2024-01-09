//------------ INCLUDES -----------
#include "DepthStencil.h"
#include "../Renderer.h"

DepthStencil::DepthStencil()
	:mDepthStencilView(nullptr)
{
	// 処理なし
}

DepthStencil::~DepthStencil()
{
	SAFE_RELEASE(mDepthStencilView);
}

void DepthStencil::Clear()
{
	Renderer::GetInstance().GetDeviceContext()->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

HRESULT DepthStencil::Create(uint16_t _width, uint16_t _height, bool _useStencil)
{
	DXGI_FORMAT format;
	format = _useStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
	D3D11_TEXTURE2D_DESC desc = MakeTextureDesc(format, _width, _height);
	desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
	return CreateResource(desc, nullptr);
}

HRESULT DepthStencil::CreateResource(D3D11_TEXTURE2D_DESC& _desc, const void* _pData)
{
	// ステンシル使用判定
	bool useStencil = (_desc.Format == DXGI_FORMAT_R24G8_TYPELESS);

	// リソース作成
	//_desc.BindFlags |!
	HRESULT hr = View::CreateResource(_desc, nullptr);
	if (FAILED(hr))
	{
		return hr;
	}

	// デプスステンシルビューの設定、作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = useStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	return Renderer::GetInstance().GetDevice()->CreateDepthStencilView(mTexture2D, &dsvDesc, &mDepthStencilView);
}

