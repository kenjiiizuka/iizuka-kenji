#include "PixelShader.h"
#include "../../Renderer.h"
#include "../../VisualEntity/VisualEntity.h"
#include "../../../AssetSystem/Texture/TextureAssetInclude.h"
#include <iostream>
#include <d3dcompiler.h>

std::unordered_map<std::string, ID3D11PixelShader*> PixelShader::mpPixelShaders = {};
std::string                                         PixelShader::mCurrentBindShaderName = "None";
std::shared_ptr<AssetHandle> PixelShader::mWhiteTexture;


PixelShader::PixelShader(VisualEntity* _entity)
	: Shader(_entity)
	, mPixelShaderRef(nullptr)
{
	if (!mWhiteTexture)
	{
		mWhiteTexture = AssetManager::GetInstance().Load<TextureProvider>("assets/shader/White.png");
	}
}

HRESULT PixelShader::MakeShader(void* _pData, UINT _fileSize, std::string _shaderName)
{
	HRESULT hr = Renderer::GetInstance().GetDevice()->CreatePixelShader(_pData, _fileSize, nullptr, &mPixelShaderRef);
	if (FAILED(hr)) 
	{
		std::cout << "�s�N�Z���V�F�[�_�[�̍쐬�Ɏ��s���܂��� PixelShader::MakeShader" << std::endl;
		return hr;
	}
	// unordered_map�ɓo�^
	mpPixelShaders[mShaderName] = mPixelShaderRef;

	// �T���v���[�X�e�[�g�̃Z�b�g
	ID3D11SamplerState* sampler = Renderer::GetInstance().GetSamplerState();
	SetSampler(0, sampler);
	return hr;
}

HRESULT PixelShader::MakeBuffer(void* _pData, UINT _fileSize)
{
	HRESULT hr;
	ID3D11Device* pDevice = Renderer::GetInstance().GetDevice();

	// ��͗p���t���N�V�����쐬
	ID3D11ShaderReflection* pReflection = nullptr;
	hr = D3DReflect(_pData, _fileSize, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) 
	{
		std::cout << "���t���N�V�����Ɏ��s���܂���" << std::endl;
		return hr;
	}

	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);
	mBuffers[mShaderName].resize(shaderDesc.ConstantBuffers, nullptr); // ���̃V�F�[�_�[�̒萔�o�b�t�@�������z������T�C�Y
	for (UINT i = 0; i < shaderDesc.ConstantBuffers; i++)
	{
		// �V�F�[�_�[�̒萔�o�b�t�@�̏����擾
		D3D11_SHADER_BUFFER_DESC shaderBufferDesc;
		ID3D11ShaderReflectionConstantBuffer* srcBuf = pReflection->GetConstantBufferByIndex(i); // �萔�o�b�t�@�����o��
		srcBuf->GetDesc(&shaderBufferDesc);

		// �쐬����o�b�t�@�̏��
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.ByteWidth = shaderBufferDesc.Size;        // �萔�o�b�t�@�̃T�C�Y�̐ݒ�
		bufDesc.Usage = D3D11_USAGE_DEFAULT;              // �g�p���@
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;   // �萔�o�b�t�@
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = 0;
		//bufDesc.StructureByteStride = sizeof(float);
		// �o�b�t�@�̍쐬
		std::cout << bufDesc.ByteWidth << std::endl;
		hr = pDevice->CreateBuffer(&bufDesc, nullptr, &mBuffers[mShaderName][i]);
		if (FAILED(hr)) {
			std::cout << "�萔�o�b�t�@�̍쐬���s" << i << std::endl;
			return hr;
		}
	}
	// �Q�Ƃ��擾
	mpBufferRef = mBuffers[mShaderName];

	return S_OK;
}

bool PixelShader::CheckDuplication(std::string _shaderName)
{
	// �d���Ȃ�
	if (mpPixelShaders.count(_shaderName) < 1) 
	{
		return true;
	}
	// ���[�h�ς�
	mPixelShaderRef = mpPixelShaders[_shaderName];
	mShaderName = _shaderName;
	return false;
}

void PixelShader::Uninit()
{
	Shader::Uninit();
	if (mRefCounts[mShaderName] <= 0) 
	{
		if (mpPixelShaders[mShaderName])
		{
			mpPixelShaders[mShaderName]->Release();
			mpPixelShaders.erase(mShaderName);
			std::cout << "�s�N�Z���V�F�[�_�[�̐�" << mpPixelShaders.size() << std::endl;
		}	
	}
}

void PixelShader::BindShader()
{
	if (mShaderName != mCurrentBindShaderName) 
	{
		// �V�F�[�_�[�̃Z�b�g
		Renderer::GetInstance().GetDeviceContext()->PSSetShader(mPixelShaderRef, nullptr, 0);
		mCurrentBindShaderName = mShaderName;
	}

	// �萔�o�b�t�@�̃Z�b�g
	for (UINT i = 0; i < mpBufferRef.size(); i++) 
	{
		Renderer::GetInstance().GetDeviceContext()->PSSetConstantBuffers(i, 1, &mpBufferRef[i]);
	}
}

void PixelShader::SetTexture(UINT _slot, ID3D11ShaderResourceView* _texture)
{
	Renderer::GetInstance().GetDeviceContext()->PSSetShaderResources(_slot, 1, &_texture);
}

void PixelShader::SetSampler(UINT _slot, ID3D11SamplerState* _samplerState)
{
	Renderer::GetInstance().GetDeviceContext()->PSSetSamplers(_slot, 1, &_samplerState);
}


