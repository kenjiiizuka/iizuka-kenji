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

	// ��͗p���t���N�V�����쐬
	ID3D11ShaderReflection* pReflection = nullptr;
	hr = D3DReflect(_pData, _fileSize, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) 
	{
		std::cout << "���t���N�V�����Ɏ��s���܂���" << std::endl;
		return hr;
	}

	// �萔�o�b�t�@�쐬 _ViewProjection�p
	if (!mpView_ProjectionBuffer) 
	{
		// �쐬����o�b�t�@�̏��
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.ByteWidth = sizeof(DirectX::SimpleMath::Matrix) * 2; // �萔�o�b�t�@�̃T�C�Y�̐ݒ�
		bufDesc.Usage = D3D11_USAGE_DEFAULT;              // �g�p���@
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;   // �萔�o�b�t�@
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = 0;
		hr = pDevice->CreateBuffer(&bufDesc, nullptr, &mpView_ProjectionBuffer);
		std::cout << bufDesc.ByteWidth << std::endl;
		if (FAILED(hr)) 
		{
			std::cout << "�萔�o�b�t�@�̍쐬���s" << "View_Projection�p" << std::endl;
			return hr;
		}
	}

	// �萔�o�b�t�@�쐬 World�p
	if (!mpWorldBuffer) 
	{
		// �쐬����o�b�t�@�̏��
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.ByteWidth = sizeof(DirectX::SimpleMath::Matrix); // �萔�o�b�t�@�̃T�C�Y�̐ݒ�
		bufDesc.Usage = D3D11_USAGE_DEFAULT;              // �g�p���@
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;   // �萔�o�b�t�@
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = 0;
		hr = pDevice->CreateBuffer(&bufDesc, nullptr, &mpWorldBuffer);
		std::cout << bufDesc.ByteWidth << std::endl;
		if (FAILED(hr)) 
		{
			std::cout << "�萔�o�b�t�@�̍쐬���s" << "World�p" << std::endl;
			return hr;
		}
	}

	return hr;
}

bool Shader::LoadWithShaderReflection(std::string _shaderName)
{
	// �d���`�F�b�N
	if (!CheckDuplication(_shaderName)) 
	{
		mRefCounts[mShaderName] += 1;    // ���t�@�����X�J�E���g�𑝂₷
		mpBufferRef = mBuffers[mShaderName];

		// std::cout << "���łɓǂݍ��܂�Ă��܂�" << _shaderName << std::endl << "�Q�ƃJ�E���g" << mRefCounts[mShaderName] << std::endl;
		return false;
	}

	// ���_�V�F�[�_�[�t�@�C���p�X�쐬
	std::string filePath = "assets/shader/";
	filePath.append(_shaderName);

	// �t�@�C���I�[�v��
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) 
	{
		std::string error = "���_�V�F�[�_�[�̓ǂݍ��݂Ɏ��s  ";
		error.append(filePath);
		// printf("%s", error.c_str());
		return false;
	}

	// �t�@�C���̃T�C�Y���擾
	file.seekg(0, std::ios_base::end);             // �t�@�C���|�C���^���t�@�C���̏I�[�܂ňړ�
	UINT fileSize = (UINT)file.tellg();

	// �������ɓǂݍ���
	file.clear();                                  // EOF�t���O�����Z�b�g
	file.seekg(0, std::ios_base::beg);             // �t�@�C���|�C���^���t�@�C���̐擪�Ɉړ�
	char* data = new char[fileSize];
	file.read(data, fileSize);

	// �V�F�[�_�[�̖��O��ݒ�
	mShaderName = _shaderName;
	// �萔�o�b�t�@�̍쐬
	MakeBuffer(data, fileSize);
	// �V�F�[�_�[�쐬
	MakeShader(data, fileSize, _shaderName);
	// ���t�@�����X�J�E���g�̏�����
	mRefCounts[mShaderName] = 1;

	// �I������
	if (data) { delete[] data; }
	file.close(); // �t�@�C���N���[�Y

	return true;
}

void Shader::Uninit()
{
	mRefCounts[mShaderName]--;
	if (mRefCounts[mShaderName] <= 0)
	{
		// �萔�o�b�t�@�̉��
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
