#include "RenderTarget.h"
#include "../Renderer.h"

RenderTarget::RenderTarget()
	: mRenderTargetView(nullptr)
{

}

RenderTarget::~RenderTarget()
{
	SAFE_RELEASE(mRenderTargetView);
}

void RenderTarget::Clear(DirectX::SimpleMath::Vector4 _color)
{
	const float color[4] = { _color.x,_color.y,_color.z,1.0f };
	Renderer::GetInstance().GetDeviceContext()->ClearRenderTargetView(mRenderTargetView, color);
}

HRESULT RenderTarget::Create(DXGI_FORMAT _format, uint16_t _width, uint16_t _height)
{
	D3D11_TEXTURE2D_DESC desc = MakeTextureDesc(_format,_width, _height);
	desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
	return CreateResource(desc, nullptr);
}

HRESULT RenderTarget::CreateFromScreen()
{
	HRESULT hr;
	// バックバッファのポインタを取得
	ID3D11Texture2D* backBuffer = nullptr;	
	hr = Renderer::GetInstance().GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&mTexture2D);
	if (FAILED(hr))
	{
		return hr;
	}

	// バックバッファのポインタからレンダーターゲットビューを作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.Texture2D.MipSlice = 0;
	hr = Renderer::GetInstance().GetDevice()->CreateRenderTargetView(mTexture2D, &rtvDesc, &mRenderTargetView);
	if (SUCCEEDED(hr))
	{
		D3D11_TEXTURE2D_DESC desc;
		mTexture2D->GetDesc(&desc);
		mWidth = desc.Width;
		mHeight = desc.Height;
	}
	return hr;
}

HRESULT RenderTarget::CreateResource(D3D11_TEXTURE2D_DESC& _desc, const void* _pData)
{
	HRESULT hr;
	hr = View::CreateResource(_desc, nullptr);
	if (FAILED(hr)) 
	{
		return hr;
	}
	// レンダーターゲットビューの設定と生成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.Format = _desc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	// 作成
	return Renderer::GetInstance().GetDevice()->CreateRenderTargetView(mTexture2D, &rtvDesc, &mRenderTargetView);
}

