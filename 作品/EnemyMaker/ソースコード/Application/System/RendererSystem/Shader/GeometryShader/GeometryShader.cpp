//---------- INCLUDES -----------
#include <iostream>
#include <d3dcompiler.h>
#include "GeometryShader.h"
#include "../../Renderer.h"

std::unordered_map<std::string, ID3D11GeometryShader*> GeometryShader::mGeometryShaders{};
std::string GeometryShader::mCurrentBindShaderName = "None";

GeometryShader::GeometryShader(VisualEntity* _visualEntity)
	: Shader(_visualEntity)
	, mGeometryShader(nullptr)
{
	// 処理なし
}

GeometryShader::~GeometryShader()
{
	// 処理なし
}

void GeometryShader::Uninit()
{
	Shader::Uninit();
	if (mRefCounts[mShaderName] <= 0)
	{
		mGeometryShaders[mShaderName]->Release();
		mGeometryShaders.erase(mShaderName);
		std::cout << "ジオメトリシェーダーの数" << mGeometryShaders.size() << std::endl;
	}
}

void GeometryShader::UpdateBuffer(uint8_t _dataID)
{
	// 処理なし
}

HRESULT GeometryShader::MakeShader(void* _pData, UINT _fileSize, std::string _shaderName)
{
	Renderer& renderer = Renderer::GetInstance();

	// ジオメトリシェーダーの作成
	HRESULT hr = renderer.GetDevice()->CreateGeometryShader(_pData, static_cast<SIZE_T>(_fileSize), nullptr, &mGeometryShader);

	// 作成に失敗していたらエラーメッセージを出す
	if (FAILED(hr))
	{
		std::cout << _shaderName << " GeometryShaderの作成に失敗" << std::endl;
		return hr;
	}

	// mapに登録
	if (!mGeometryShaders.try_emplace(_shaderName, mGeometryShader).second)
	{
		std::cout << _shaderName << "すでに登録済み" << std::endl;
	}

	mShaderName = _shaderName;
	return hr;
}

HRESULT GeometryShader::MakeBuffer(void* _pData, UINT _fileSize)
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

bool GeometryShader::CheckDuplication(std::string _shaderName)
{
	// ロード済みならmapから取得する
	if (mGeometryShaders.contains(_shaderName))
	{
		mGeometryShader = mGeometryShaders.at(_shaderName);
		mShaderName = _shaderName;
		return false;
	}

	// 重複なし
	return true;
}

void GeometryShader::BindShader()
{
	Renderer& renderer = Renderer::GetInstance();

	if (mShaderName != mCurrentBindShaderName)
	{
		// シェーダーのセット
		renderer.GetDeviceContext()->GSSetShader(mGeometryShader, nullptr, 0);
		mCurrentBindShaderName = mShaderName;
	}

	// 定数バッファのセット
	for (UINT i = 0; i < mpBufferRef.size(); i++)
	{
		Renderer::GetInstance().GetDeviceContext()->GSSetConstantBuffers(i, 1, &mpBufferRef[i]);
	}
}

void GeometryShader::Deallocate()
{
	Renderer::GetInstance().GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);
	mCurrentBindShaderName = "None";
}
