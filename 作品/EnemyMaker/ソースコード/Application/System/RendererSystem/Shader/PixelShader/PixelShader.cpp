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
		std::cout << "ピクセルシェーダーの作成に失敗しました PixelShader::MakeShader" << std::endl;
		return hr;
	}
	// unordered_mapに登録
	mpPixelShaders[mShaderName] = mPixelShaderRef;

	// サンプラーステートのセット
	ID3D11SamplerState* sampler = Renderer::GetInstance().GetSamplerState();
	SetSampler(0, sampler);
	return hr;
}

HRESULT PixelShader::MakeBuffer(void* _pData, UINT _fileSize)
{
	HRESULT hr;
	ID3D11Device* pDevice = Renderer::GetInstance().GetDevice();

	// 解析用リフレクション作成
	ID3D11ShaderReflection* pReflection = nullptr;
	hr = D3DReflect(_pData, _fileSize, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) 
	{
		std::cout << "リフレクションに失敗しました" << std::endl;
		return hr;
	}

	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);
	mBuffers[mShaderName].resize(shaderDesc.ConstantBuffers, nullptr); // このシェーダーの定数バッファ数だけ配列をリサイズ
	for (UINT i = 0; i < shaderDesc.ConstantBuffers; i++)
	{
		// シェーダーの定数バッファの情報を取得
		D3D11_SHADER_BUFFER_DESC shaderBufferDesc;
		ID3D11ShaderReflectionConstantBuffer* srcBuf = pReflection->GetConstantBufferByIndex(i); // 定数バッファを取り出す
		srcBuf->GetDesc(&shaderBufferDesc);

		// 作成するバッファの情報
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.ByteWidth = shaderBufferDesc.Size;        // 定数バッファのサイズの設定
		bufDesc.Usage = D3D11_USAGE_DEFAULT;              // 使用方法
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;   // 定数バッファ
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = 0;
		//bufDesc.StructureByteStride = sizeof(float);
		// バッファの作成
		std::cout << bufDesc.ByteWidth << std::endl;
		hr = pDevice->CreateBuffer(&bufDesc, nullptr, &mBuffers[mShaderName][i]);
		if (FAILED(hr)) {
			std::cout << "定数バッファの作成失敗" << i << std::endl;
			return hr;
		}
	}
	// 参照を取得
	mpBufferRef = mBuffers[mShaderName];

	return S_OK;
}

bool PixelShader::CheckDuplication(std::string _shaderName)
{
	// 重複なし
	if (mpPixelShaders.count(_shaderName) < 1) 
	{
		return true;
	}
	// ロード済み
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
			std::cout << "ピクセルシェーダーの数" << mpPixelShaders.size() << std::endl;
		}	
	}
}

void PixelShader::BindShader()
{
	if (mShaderName != mCurrentBindShaderName) 
	{
		// シェーダーのセット
		Renderer::GetInstance().GetDeviceContext()->PSSetShader(mPixelShaderRef, nullptr, 0);
		mCurrentBindShaderName = mShaderName;
	}

	// 定数バッファのセット
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


