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
	// �����Ȃ�
}

GeometryShader::~GeometryShader()
{
	// �����Ȃ�
}

void GeometryShader::Uninit()
{
	Shader::Uninit();
	if (mRefCounts[mShaderName] <= 0)
	{
		mGeometryShaders[mShaderName]->Release();
		mGeometryShaders.erase(mShaderName);
		std::cout << "�W�I���g���V�F�[�_�[�̐�" << mGeometryShaders.size() << std::endl;
	}
}

void GeometryShader::UpdateBuffer(uint8_t _dataID)
{
	// �����Ȃ�
}

HRESULT GeometryShader::MakeShader(void* _pData, UINT _fileSize, std::string _shaderName)
{
	Renderer& renderer = Renderer::GetInstance();

	// �W�I���g���V�F�[�_�[�̍쐬
	HRESULT hr = renderer.GetDevice()->CreateGeometryShader(_pData, static_cast<SIZE_T>(_fileSize), nullptr, &mGeometryShader);

	// �쐬�Ɏ��s���Ă�����G���[���b�Z�[�W���o��
	if (FAILED(hr))
	{
		std::cout << _shaderName << " GeometryShader�̍쐬�Ɏ��s" << std::endl;
		return hr;
	}

	// map�ɓo�^
	if (!mGeometryShaders.try_emplace(_shaderName, mGeometryShader).second)
	{
		std::cout << _shaderName << "���łɓo�^�ς�" << std::endl;
	}

	mShaderName = _shaderName;
	return hr;
}

HRESULT GeometryShader::MakeBuffer(void* _pData, UINT _fileSize)
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

bool GeometryShader::CheckDuplication(std::string _shaderName)
{
	// ���[�h�ς݂Ȃ�map����擾����
	if (mGeometryShaders.contains(_shaderName))
	{
		mGeometryShader = mGeometryShaders.at(_shaderName);
		mShaderName = _shaderName;
		return false;
	}

	// �d���Ȃ�
	return true;
}

void GeometryShader::BindShader()
{
	Renderer& renderer = Renderer::GetInstance();

	if (mShaderName != mCurrentBindShaderName)
	{
		// �V�F�[�_�[�̃Z�b�g
		renderer.GetDeviceContext()->GSSetShader(mGeometryShader, nullptr, 0);
		mCurrentBindShaderName = mShaderName;
	}

	// �萔�o�b�t�@�̃Z�b�g
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
