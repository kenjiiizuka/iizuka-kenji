//----------- INCLUDES ------------
#include "TextureProvider.h"
#include "Texture.h"
#include "../../../Utility/StringEncoding.h"
#include <WICTextureLoader.h>
#include <DirectXTex.h>

TextureProvider::TextureProvider()
{
	// �����Ȃ�
}

TextureProvider::~TextureProvider()
{
	// �����Ȃ�
}

std::shared_ptr<IAsset> TextureProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	// �J���}�̈ʒu���擾
	size_t dotPos = _filePath.find('.');

	// �����̕�������擾
	std::string fileType = _filePath.substr(dotPos);

	// TGA���ǂ����𔻒f����
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
	std::wstring wFilePath = ::SJIS_To_Wide(_filePath.data());	 // ���C�h�^�ɕϊ�
	// �ǂݍ���
	HRESULT hr = DirectX::CreateWICTextureFromFile
	(
		Renderer::GetInstance().GetDevice(),
		wFilePath.c_str(),
		nullptr,
		&_texture->mResource
	);

	// �G���[�`�F�b�N
	if (FAILED(hr)) 
	{
		std::cout<< _filePath << "Texture�ǂݍ��ݎ��s" << std::endl;
		_texture->mResource = nullptr;
		return false;
	}

	return true;
}

bool TextureProvider::CreateTextureFromTGA(std::string_view _filePath, std::shared_ptr<Texture>& _texture) const
{

	std::wstring wFilePath = ::SJIS_To_Wide(_filePath.data());	 // ���C�h�^�ɕϊ�

	DirectX::ScratchImage textureData;
	HRESULT hr = DirectX::LoadFromTGAFile(wFilePath.c_str(), nullptr, textureData);
	if (FAILED(hr)) 
	{
		std::cout << _filePath << "Texture�ǂݍ��ݎ��s" << std::endl;
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
		std::cout << _filePath << "CreateTexture2D���s" << std::endl;
		return false;
	}

	const DirectX::Image* image = textureData.GetImage(0, 0, 0);
	Renderer::GetInstance().GetDeviceContext()->UpdateSubresource(texture, 0, nullptr, image->pixels, static_cast<UINT>(image->rowPitch), 0);
	hr = Renderer::GetInstance().GetDevice()->CreateShaderResourceView(texture, nullptr, &_texture->mResource);
	if (FAILED(hr)) 
	{
		std::cout << _filePath << "Texture�̍쐬�Ɏ��s" << std::endl;
		return false;
	}

	return true;
}
