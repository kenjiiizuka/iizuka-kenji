#include "Shader.h"
#include <fstream>
#include <assert.h>
#include <d3dcompiler.h>
#include <iostream>

#pragma comment(lib, "d3dcompiler.lib")

std::unordered_map<std::string, std::vector<ID3D11Buffer*>> Shader::mBuffers = {};
std::unordered_map<std::string, int>                        Shader::mRefCounts = {};
ID3D11Buffer*                                               Shader::mpView_ProjectionBuffer = nullptr;
ID3D11Buffer*                                               Shader::mpWorldBuffer           = nullptr;

Shader::Shader(VisualEntity* _entity)
	: mVisualEntity(_entity)
	, mbIsDropShadow(true)
{
	
}

HRESULT Shader::MakeBuffer(void* _pData, UINT _fileSize)
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

	// 定数バッファ作成 _ViewProjection用
	if (!mpView_ProjectionBuffer) 
	{
		// 作成するバッファの情報
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.ByteWidth = sizeof(DirectX::SimpleMath::Matrix) * 2; // 定数バッファのサイズの設定
		bufDesc.Usage = D3D11_USAGE_DEFAULT;              // 使用方法
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;   // 定数バッファ
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = 0;
		hr = pDevice->CreateBuffer(&bufDesc, nullptr, &mpView_ProjectionBuffer);
		std::cout << bufDesc.ByteWidth << std::endl;
		if (FAILED(hr)) 
		{
			std::cout << "定数バッファの作成失敗" << "View_Projection用" << std::endl;
			return hr;
		}
	}

	// 定数バッファ作成 World用
	if (!mpWorldBuffer) 
	{
		// 作成するバッファの情報
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.ByteWidth = sizeof(DirectX::SimpleMath::Matrix); // 定数バッファのサイズの設定
		bufDesc.Usage = D3D11_USAGE_DEFAULT;              // 使用方法
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;   // 定数バッファ
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = 0;
		hr = pDevice->CreateBuffer(&bufDesc, nullptr, &mpWorldBuffer);
		std::cout << bufDesc.ByteWidth << std::endl;
		if (FAILED(hr)) 
		{
			std::cout << "定数バッファの作成失敗" << "World用" << std::endl;
			return hr;
		}
	}

	return hr;
}

bool Shader::LoadWithShaderReflection(std::string _shaderName)
{
	// 重複チェック
	if (!CheckDuplication(_shaderName)) 
	{
		mRefCounts[mShaderName] += 1;    // リファレンスカウントを増やす
		mpBufferRef = mBuffers[mShaderName];

		// std::cout << "すでに読み込まれています" << _shaderName << std::endl << "参照カウント" << mRefCounts[mShaderName] << std::endl;
		return false;
	}

	// 頂点シェーダーファイルパス作成
	std::string filePath = "assets/shader/";
	filePath.append(_shaderName);

	// ファイルオープン
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) 
	{
		std::string error = "頂点シェーダーの読み込みに失敗  ";
		error.append(filePath);
		// printf("%s", error.c_str());
		return false;
	}

	// ファイルのサイズを取得
	file.seekg(0, std::ios_base::end);             // ファイルポインタをファイルの終端まで移動
	UINT fileSize = (UINT)file.tellg();

	// メモリに読み込み
	file.clear();                                  // EOFフラグをリセット
	file.seekg(0, std::ios_base::beg);             // ファイルポインタをファイルの先頭に移動
	char* data = new char[fileSize];
	file.read(data, fileSize);

	// シェーダーの名前を設定
	mShaderName = _shaderName;
	// 定数バッファの作成
	MakeBuffer(data, fileSize);
	// シェーダー作成
	MakeShader(data, fileSize, _shaderName);
	// リファレンスカウントの初期化
	mRefCounts[mShaderName] = 1;

	// 終了処理
	if (data) { delete[] data; }
	file.close(); // ファイルクローズ

	return true;
}

void Shader::Uninit()
{
	mRefCounts[mShaderName]--;
	if (mRefCounts[mShaderName] <= 0)
	{
		// 定数バッファの解放
		for (ID3D11Buffer* buf : mBuffers[mShaderName]) 
		{
			if (buf) 
			{
				buf->Release();
			}
		}
	}
}

void Shader::WriteBuffer(UINT _slot, void* _pData)
{	
	if (mpBufferRef[_slot]) 
	{
		Renderer::GetInstance().GetDeviceContext()->UpdateSubresource(mpBufferRef[_slot], 0, nullptr, _pData, 0, 0);
	}	
}

void Shader::WriteView_ProjectionMatrix(void* _view_ProjectionMatrix)
{
	Renderer::GetInstance().GetDeviceContext()->UpdateSubresource(mpView_ProjectionBuffer, 0, nullptr, _view_ProjectionMatrix, 0, 0);
}

void Shader::WriteWorldMatrix(void* _worldMatrix)
{
	Renderer::GetInstance().GetDeviceContext()->UpdateSubresource(mpWorldBuffer, 0, nullptr, _worldMatrix, 0, 0);
}
