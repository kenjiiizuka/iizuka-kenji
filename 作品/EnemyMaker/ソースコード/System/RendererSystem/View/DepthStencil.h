#pragma once
#include "View.h"

/** デプスステンシル */
class DepthStencil : public View
{
public:
	DepthStencil();
	~DepthStencil();

private:
	/** デプスステンシルビュー */
	ID3D11DepthStencilView* mDepthStencilView;

public:
	/**
	 * @fn Clear
	 * @brief 画面クリア
	 * @return void
	*/
	void Clear();

	/**
	 * @fn Create
	 * @brief デプスステンシルビューを作成
	 * @param UINT (_width) 横幅
	 * @param UINT (_height) 縦幅
	 * @param bool (_useStencil) ステンシルを使うか
	 * @return HRESULT
	*/
	HRESULT Create(uint16_t _width, uint16_t _height, bool _useStencil);

private:
	/**
	 * @fn CreateResource
	 * @brief デプスステンシルビューの作成
	 * @param D3D11_TEXTURE2D_DESC& (_desc)
	 * @param const void* (_pData)
	 * @return HRESULT
	*/
	HRESULT CreateResource(D3D11_TEXTURE2D_DESC& _desc, const void* _pData) override;

public: 
	/**
	 * @fn GetView
	 * @brief デプスステンシルビューの取得
	 * @return ID3D11DepthStencilView*
	*/
	inline ID3D11DepthStencilView* GetView() const;
};

//-------------- INLINES -----------------

inline ID3D11DepthStencilView* DepthStencil::GetView() const
{
	return mDepthStencilView;
}
