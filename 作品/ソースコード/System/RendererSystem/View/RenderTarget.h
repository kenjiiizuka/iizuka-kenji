#pragma once
#include "View.h"
#include <SimpleMath.h>

/** RenderTargetクラス */
class RenderTarget : public View
{
public:
	RenderTarget();
	~RenderTarget();

private:
	/** レンダーターゲットビュー */
	ID3D11RenderTargetView* mRenderTargetView;

public:
	/**
	 * @fn Clear
	 * @brief 画面クリア
	 * @return void
	*/
	void Clear(DirectX::SimpleMath::Vector4 _color = DirectX::SimpleMath::Vector4::One);
	
	/**
	 * @fn Create
	 * @brief レンダーターゲットの作成
	 * @param DXGI_FORMAT (_format)
	 * @param UINT (_width) レンダーターゲットの横幅
	 * @param UINT (_height) レンダーターゲットの縦幅
	 * @return HRESULT
	*/
	HRESULT Create(DXGI_FORMAT _format, uint16_t _width, uint16_t _height);

	/**
	 * @fn CreateFromScreen
	 * @brief バックバッファからレンダーターゲットビューを作成する
	 * @return HRESULT
	*/
	HRESULT CreateFromScreen();

protected:
	/**
	 * @fn CreateResource
	 * @brief レンダーターゲットの作成関数
	 * @param D3D11_TEXTURE2D_DESC& (_desc)
	 * @param const void* (pData)
	 * @return HRESULT
	*/
	HRESULT CreateResource(D3D11_TEXTURE2D_DESC& _desc, const void* _pData) override;

public:
	/**
	 * @fn GetView
	 * @brief レンダーターゲットビューを返す
	 * @return ID3D11RenderTargetView*
	*/
	inline ID3D11RenderTargetView* GetView() const;

};

//---------------- INLINES ----------------

inline ID3D11RenderTargetView* RenderTarget::GetView() const
{
	return mRenderTargetView;
}
