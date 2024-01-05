#pragma once
#include <d3d11.h>
#include <stdint.h>

class View
{
public:
	/**
	* 値の初期化
	*/
	View();

	virtual ~View();

protected:
	/** リソースの横幅 */
	uint16_t mWidth;

	/** リソースの縦幅 */
	uint16_t mHeight;

	/** リソース */
	ID3D11ShaderResourceView* mShaderResource;

	/** Texture2D */
	ID3D11Texture2D* mTexture2D;

public:
	//HRESULT Create();

protected:
	/**
	 * @fn MakeTexture2D
	 * @brief Texture2Dのデスク指定された値で作成する関数
	 * @param DXGI_FORMAT (_format) 
	 * @param uint16_t (_width)
	 * @param uint16_t (_height)
	 * @return D3D11_TEXTURE2D_DESC
	*/
	D3D11_TEXTURE2D_DESC MakeTextureDesc(DXGI_FORMAT _format, uint16_t _width, uint16_t _height);

	/**
	 * @fn CreateResource
	 * @brief シェーダーリソースの作成関数
	 * @param D3D11_TEXTURE2D_DESC& (_desc)
	 * @param const void* (pData)
	 * @return HRESULT
	*/
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& _desc, const void* pData);


public:
	/**
	 * @fn GetWidth
	 * @brief 横幅の取得
	 * @return uint16_t
	*/
	inline uint16_t GetWidth() const noexcept;

	/**
	 * @fn GetHeight
	 * @brief 縦幅の取得
	 * @return uint16_t
	*/
	inline uint16_t GetHeight() const noexcept;

	/**
	 * @fn ID3D11ShaderResourceView
	 * @brief シェーダーリソースの取得
	 * @return ID3D11ShaderResourceView*
	*/
	inline ID3D11ShaderResourceView* GetResource() const;
};

//------------------ INLINES -------------------

inline uint16_t View::GetWidth() const noexcept
{
	return mWidth;
}

inline uint16_t View::GetHeight() const noexcept
{
	return mHeight;
}

inline ID3D11ShaderResourceView* View::GetResource() const
{
	return mShaderResource;
}


