//----------- INCLUDES ------------
#include "TextureProvider.h"
#include "Texture.h"
#include "../../../Utility/StringEncoding.h"
#include <WICTextureLoader.h>
#include <DirectXTex.h>

TextureProvider::TextureProvider()
{
	// 処理なし
}

TextureProvider::~TextureProvider()
{
	// 処理なし
}

std::shared_ptr<IAsset> TextureProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	// カンマの位置を取得
	size_t dotPos = _filePath.find('.');

	// 末尾の文字列を取得
	std::string fileType = _filePath.substr(dotPos);

	// TGAかどうかを判断する
	if (fileType == ".tag")
	{
		if (!CreateTextureFromTGA(_filePath, texture))
		{
			return std::shared_ptr<IAsset>();
		}
	}

	if (!LoadByWICTexture(_filePath, texture))
	{
		return std::shared_ptr<IAsset>();
	}

	return texture;
}

bool TextureProvider::LoadByWICTexture(std::string_view _filePath, std::shared_ptr<Texture>& _texture) const
{
	std::wstring wFilePath = ::SJIS_To_Wide(_filePath.data());	 // ワイド型に変換
	// 読み込み
	HRESULT hr = DirectX::CreateWICTextureFromFile
	(
		Renderer::GetInstance().GetDevice(),
		wFilePath.c_str(),
		nullptr,
		&_texture->mResource
	);

	// エラーチェック
	if (FAILED(hr)) 
	{
		std::cout<< _filePath << "Texture読み込み失敗" << std::endl;
		_texture->mResource = nullptr;
		return false;
	}

	return true;
}

bool TextureProvider::CreateTextureFromTGA(std::string_view _filePath, std::shared_ptr<Texture>& _texture) const
{

	std::wstring wFilePath = ::SJIS_To_Wide(_filePath.data());	 // ワイド型に変換

	DirectX::ScratchImage textureData;
	HRESULT hr = DirectX::LoadFromTGAFile(wFilePath.c_str(), nullptr, textureData);
	if (FAILED(hr)) 
	{
		std::cout << _filePath << "Texture読み込み失敗" << std::endl;
		return false;
	}

	const DirectX::TexMetadata& metaData = textureData.GetMetadata();
	D3D11_TEXTURE2D_DESC texDesc{};
	texDesc.Width = static_cast<UINT>(metaData.width);
	texDesc.Height = static_cast<UINT>(metaData.height);
	texDesc.MipLevels = static_cast<UINT>(metaData.mipLevels);
	texDesc.ArraySize = 1;
	texDesc.Format = metaData.format;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	ID3D11Texture2D* texture = nullptr;
	hr = Renderer::GetInstance().GetDevice()->CreateTexture2D(&texDesc, nullptr, &texture);
	if (FAILED(hr)) 
	{
		std::cout << _filePath << "CreateTexture2D失敗" << std::endl;
		return false;
	}

	const DirectX::Image* image = textureData.GetImage(0, 0, 0);
	Renderer::GetInstance().GetDeviceContext()->UpdateSubresource(texture, 0, nullptr, image->pixels, static_cast<UINT>(image->rowPitch), 0);
	hr = Renderer::GetInstance().GetDevice()->CreateShaderResourceView(texture, nullptr, &_texture->mResource);
	if (FAILED(hr)) 
	{
		std::cout << _filePath << "Textureの作成に失敗" << std::endl;
		return false;
	}

	return true;
}
