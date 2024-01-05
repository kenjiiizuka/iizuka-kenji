//-------- INCLUDES -------
#include "VertexShader.h"
#include "../../VisualEntity/VisualEntity.h"
#include "../../Renderer.h"
#include <iostream>
#include <d3dcompiler.h>
#include "../../../../Utility/Debug.h"

//------- LINK --------
#pragma comment(lib, "d3dcompiler.lib")

std::unordered_map<std::string, ID3D11VertexShader*> VertexShader::mpVertexShaders = {};
std::unordered_map<std::string, ID3D11InputLayout*>  VertexShader::mpInputLayouts = {};
std::string                                          VertexShader::mCurrentBindShaderName = "None";

using namespace DirectX::SimpleMath;


VertexShader::VertexShader(VisualEntity* _entity)
	: Shader(_entity)
	,mpVertexShaderRef(nullptr)
	, mpInputLayoutRef(nullptr)
{
	// 処理なし
}

HRESULT VertexShader::MakeShader(void* _pData, UINT _fileSize, std::string _shaderName)
{
	HRESULT hr;
	ID3D11Device* pDevice = Renderer::GetInstance().GetDevice();

	// シェーダー作成
	hr = pDevice->CreateVertexShader(_pData, _fileSize, nullptr, &mpVertexShaderRef);
	if (FAILED(hr)) 
	{
		std::cout << "頂点シェーダーの作成に失敗しました VertexShader::MakeShader" << std::endl;
		return hr;
	}
	// unordered_mapに登録
	mpVertexShaders[mShaderName] = mpVertexShaderRef;

	// シェーダーリフレクション
	ID3D11ShaderReflection* pReflection = nullptr;                   // 解析リフレクション
	hr = D3DReflect(_pData, _fileSize, IID_PPV_ARGS(&pReflection));  // リフレクション
	if (FAILED(hr)) 
	{
		std::cout << "頂点シェーダーのリフレクションに失敗 VertexShader::MakeShader" << std::endl;
		return hr;
	}

	// シェーダーデスクの取得
	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);

	// 入力レイアウト、頂点バッファの作成
	float vertexBufSize = 0;                                                       // 頂点バッファのサイズ
	D3D11_SIGNATURE_PARAMETER_DESC sigDesc;
	std::vector<D3D11_INPUT_ELEMENT_DESC> pInputDescs(shaderDesc.InputParameters); // このシェーダーの入力パラメーター分確保する

	// フォーマットの準備
	DXGI_FORMAT formats[3][4] =
	{
		{
			DXGI_FORMAT_R32_UINT,
			DXGI_FORMAT_R32G32_UINT,
			DXGI_FORMAT_R32G32B32_UINT,
			DXGI_FORMAT_R32G32B32A32_UINT,
		},
		{
			DXGI_FORMAT_R32_SINT,
			DXGI_FORMAT_R32G32_SINT,
			DXGI_FORMAT_R32G32B32_SINT,
			DXGI_FORMAT_R32G32B32A32_SINT,
		},
		{
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
		},
	};

	for (UINT i = 0; i < pInputDescs.size(); i++)
	{
		pReflection->GetInputParameterDesc(i, &sigDesc);       // シグネチャデスクを取得
		pInputDescs[i].SemanticName = sigDesc.SemanticName;  // セマンティックネーム設定
		pInputDescs[i].SemanticIndex = sigDesc.SemanticIndex; // セマンティックインデックス設定

		// 各要素が0～3までなので、-1した結果がその範囲に収まるようにする
		BYTE elementCount = sigDesc.Mask;
		elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
		elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

		switch (sigDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			pInputDescs[i].Format = formats[0][elementCount - 1];
			vertexBufSize += sizeof(uint32_t) * elementCount;
			break;
		case D3D_REGISTER_COMPONENT_SINT32:
			pInputDescs[i].Format = formats[1][elementCount - 1];
			vertexBufSize += sizeof(uint32_t) * elementCount;
			break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			pInputDescs[i].Format = formats[2][elementCount - 1];
			vertexBufSize += sizeof(float) * elementCount;
			break;
		}
		pInputDescs[i].InputSlot = 0;
		pInputDescs[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		pInputDescs[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInputDescs[i].InstanceDataStepRate = 0;
	}

	// InputLayoutの作成
	hr = pDevice->CreateInputLayout(pInputDescs.data(), shaderDesc.InputParameters, _pData, _fileSize, &mpInputLayoutRef);
	if (FAILED(hr)) 
	{
		std::cout << "インプットレイアウトの作成に失敗しました VeretexShaderComponent::MakeShader" << std::endl;
		pInputDescs.clear();
		return hr;
	}
	pInputDescs.clear();
	// InputLayoutを管理しているunordered_mapに登録
	mpInputLayouts[mShaderName] = mpInputLayoutRef;

	return hr;
}

HRESULT VertexShader::MakeBuffer(void* _pData, UINT _fileSize)
{
	Shader::MakeBuffer(_pData, _fileSize);

	HRESULT hr;
	ID3D11Device* pDevice = Renderer::GetInstance().GetDevice();

	ID3D11ShaderReflection* pReflection = nullptr;
	hr = D3DReflect(_pData, _fileSize, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) {
		std::cout << "リフレクションに失敗しました" << std::endl;
		return hr;
	}

	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);
	mBuffers[mShaderName].resize(shaderDesc.ConstantBuffers, nullptr); // このシェーダーの定数バッファ数だけ配列をリサイズ
	mBuffers[mShaderName][0] = mBuffers[mShaderName][1] = nullptr; // １，２はViewProjectionとWorldMatrixの定数バッファが必ず存在するので飛ばす（もったいｎａｉ）
	for (UINT i = 2; i < shaderDesc.ConstantBuffers; i++) 
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

bool VertexShader::CheckDuplication(std::string _shaderName)
{
	// 重複なし
	if (mpVertexShaders.count(_shaderName) < 1) 
	{
		return true;
	}
	// Load済み　unordered_mapから取得
	mpVertexShaderRef = mpVertexShaders[_shaderName];
	mpInputLayoutRef = mpInputLayouts[_shaderName];
	mShaderName = _shaderName;
	return false;
}

void VertexShader::Uninit()
{
	Shader::Uninit();
	// リファレンスカウントが０以下
	if (mRefCounts[mShaderName] <= 0) 
	{
		mpVertexShaders[mShaderName]->Release();
		mpVertexShaders.erase(mShaderName);
		mpInputLayouts[mShaderName]->Release();
		mpInputLayouts.erase(mShaderName);
		std::cout << "頂点シェーダーの数" << mpVertexShaders.size() << std::endl;
		std::cout << "入力レイアウトの数" << mpInputLayouts.size() << std::endl;
	}
}

void VertexShader::BindShader()
{
	ID3D11DeviceContext* pContext = Renderer::GetInstance().GetDeviceContext(); // デバイスコンテキストの取得

	// シェーダーのセット
	// セットしているシェーダーの名前を同じならセットしない
	if (mShaderName != mCurrentBindShaderName) 
	{
		pContext->IASetInputLayout(mpInputLayoutRef);
		pContext->VSSetShader(mpVertexShaderRef, nullptr, 0);
		mCurrentBindShaderName = mShaderName;
	}

	// 定数バッファのセット
	for (UINT i = 0; i < mpBufferRef.size(); i++) { /* 0番目はView_projection行列なので飛ばす*/
		if (i == 0) 
		{
			pContext->VSSetConstantBuffers(0, 1, &mpView_ProjectionBuffer);
		}
		else if (i == 1) 
		{
			pContext->VSSetConstantBuffers(1, 1, &mpWorldBuffer);
		}
		else 
		{
			pContext->VSSetConstantBuffers(i, 1, &mpBufferRef[i]);
		}
	}
}

void VertexShader::UpdateBuffer(uint8_t _dataID)
{
	// ワールド行列の更新
	Matrix world = mVisualEntity->GetWorldMatrix();
	world = world.Transpose();
	Shader::WriteWorldMatrix(&world);
}

void VertexShader::SetTexture(UINT _slot, ID3D11ShaderResourceView* _texture)
{
	Renderer::GetInstance().GetDeviceContext()->VSSetShaderResources(_slot, 1, &_texture);
}

void VertexShader::SetSampler(UINT _slot, ID3D11SamplerState* _samplerState)
{
	Renderer::GetInstance().GetDeviceContext()->VSSetSamplers(_slot, 1, &_samplerState);
}
