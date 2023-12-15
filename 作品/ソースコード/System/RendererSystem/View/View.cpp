#include "View.h"
#include "../Renderer.h"

View::View()
	: mWidth(0)
	, mHeight(0)
	, mShaderResource(nullptr)
	, mTexture2D(nullptr)
{

}

View::~View()
{
	SAFE_RELEASE(mShaderResource);
	//mShaderResource->Release();
	SAFE_RELEASE(mTexture2D);
	//mTexture2D->Release();
}

D3D11_TEXTURE2D_DESC View::MakeTextureDesc(DXGI_FORMAT _format, uint16_t _width, uint16_t _height)
{
	D3D11_TEXTURE2D_DESC desc{};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = _format;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Width = _width;
	desc.Height = _height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	return desc;
}

HRESULT View::CreateResource(D3D11_TEXTURE2D_DESC& _desc, const void* _pData)
{
	HRESULT hr = E_FAIL;
	ID3D11Device* device = Renderer::GetInstance().GetDevice();

	// テクスチャデータ作成
	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = _pData;
	data.SysMemPitch = _desc.Width * 4;
	hr = device->CreateTexture2D(&_desc, (_pData ? &data : nullptr), &mTexture2D);
	if (FAILED(hr))
	{
		return hr;
	}

	// 設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	if (_desc.Format == DXGI_FORMAT_R32_TYPELESS)
	{
		srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	}
	else
	{
		srvDesc.Format = _desc.Format;
	}
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// シェーダーリソースの作成
	hr = device->CreateShaderResourceView(mTexture2D, &srvDesc, &mShaderResource);
	if(SUCCEEDED(hr))
	{
		mWidth = _desc.Width;
		mHeight = _desc.Height;
	}

	return hr;
}

