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
	// �����Ȃ�
}

HRESULT VertexShader::MakeShader(void* _pData, UINT _fileSize, std::string _shaderName)
{
	HRESULT hr;
	ID3D11Device* pDevice = Renderer::GetInstance().GetDevice();

	// �V�F�[�_�[�쐬
	hr = pDevice->CreateVertexShader(_pData, _fileSize, nullptr, &mpVertexShaderRef);
	if (FAILED(hr)) 
	{
		std::cout << "���_�V�F�[�_�[�̍쐬�Ɏ��s���܂��� VertexShader::MakeShader" << std::endl;
		return hr;
	}
	// unordered_map�ɓo�^
	mpVertexShaders[mShaderName] = mpVertexShaderRef;

	// �V�F�[�_�[���t���N�V����
	ID3D11ShaderReflection* pReflection = nullptr;                   // ��̓��t���N�V����
	hr = D3DReflect(_pData, _fileSize, IID_PPV_ARGS(&pReflection));  // ���t���N�V����
	if (FAILED(hr)) 
	{
		std::cout << "���_�V�F�[�_�[�̃��t���N�V�����Ɏ��s VertexShader::MakeShader" << std::endl;
		return hr;
	}

	// �V�F�[�_�[�f�X�N�̎擾
	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);

	// ���̓��C�A�E�g�A���_�o�b�t�@�̍쐬
	float vertexBufSize = 0;                                                       // ���_�o�b�t�@�̃T�C�Y
	D3D11_SIGNATURE_PARAMETER_DESC sigDesc;
	std::vector<D3D11_INPUT_ELEMENT_DESC> pInputDescs(shaderDesc.InputParameters); // ���̃V�F�[�_�[�̓��̓p�����[�^�[���m�ۂ���

	// �t�H�[�}�b�g�̏���
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
		pReflection->GetInputParameterDesc(i, &sigDesc);       // �V�O�l�`���f�X�N���擾
		pInputDescs[i].SemanticName = sigDesc.SemanticName;  // �Z�}���e�B�b�N�l�[���ݒ�
		pInputDescs[i].SemanticIndex = sigDesc.SemanticIndex; // �Z�}���e�B�b�N�C���f�b�N�X�ݒ�

		// �e�v�f��0�`3�܂łȂ̂ŁA-1�������ʂ����͈̔͂Ɏ��܂�悤�ɂ���
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

	// InputLayout�̍쐬
	hr = pDevice->CreateInputLayout(pInputDescs.data(), shaderDesc.InputParameters, _pData, _fileSize, &mpInputLayoutRef);
	if (FAILED(hr)) 
	{
		std::cout << "�C���v�b�g���C�A�E�g�̍쐬�Ɏ��s���܂��� VeretexShaderComponent::MakeShader" << std::endl;
		pInputDescs.clear();
		return hr;
	}
	pInputDescs.clear();
	// InputLayout���Ǘ����Ă���unordered_map�ɓo�^
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
		std::cout << "���t���N�V�����Ɏ��s���܂���" << std::endl;
		return hr;
	}

	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);
	mBuffers[mShaderName].resize(shaderDesc.ConstantBuffers, nullptr); // ���̃V�F�[�_�[�̒萔�o�b�t�@�������z������T�C�Y
	mBuffers[mShaderName][0] = mBuffers[mShaderName][1] = nullptr; // �P�C�Q��ViewProjection��WorldMatrix�̒萔�o�b�t�@���K�����݂���̂Ŕ�΂��i���������������j
	for (UINT i = 2; i < shaderDesc.ConstantBuffers; i++) 
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

bool VertexShader::CheckDuplication(std::string _shaderName)
{
	// �d���Ȃ�
	if (mpVertexShaders.count(_shaderName) < 1) 
	{
		return true;
	}
	// Load�ς݁@unordered_map����擾
	mpVertexShaderRef = mpVertexShaders[_shaderName];
	mpInputLayoutRef = mpInputLayouts[_shaderName];
	mShaderName = _shaderName;
	return false;
}

void VertexShader::Uninit()
{
	Shader::Uninit();
	// ���t�@�����X�J�E���g���O�ȉ�
	if (mRefCounts[mShaderName] <= 0) 
	{
		mpVertexShaders[mShaderName]->Release();
		mpVertexShaders.erase(mShaderName);
		mpInputLayouts[mShaderName]->Release();
		mpInputLayouts.erase(mShaderName);
		std::cout << "���_�V�F�[�_�[�̐�" << mpVertexShaders.size() << std::endl;
		std::cout << "���̓��C�A�E�g�̐�" << mpInputLayouts.size() << std::endl;
	}
}

void VertexShader::BindShader()
{
	ID3D11DeviceContext* pContext = Renderer::GetInstance().GetDeviceContext(); // �f�o�C�X�R���e�L�X�g�̎擾

	// �V�F�[�_�[�̃Z�b�g
	// �Z�b�g���Ă���V�F�[�_�[�̖��O�𓯂��Ȃ�Z�b�g���Ȃ�
	if (mShaderName != mCurrentBindShaderName) 
	{
		pContext->IASetInputLayout(mpInputLayoutRef);
		pContext->VSSetShader(mpVertexShaderRef, nullptr, 0);
		mCurrentBindShaderName = mShaderName;
	}

	// �萔�o�b�t�@�̃Z�b�g
	for (UINT i = 0; i < mpBufferRef.size(); i++) { /* 0�Ԗڂ�View_projection�s��Ȃ̂Ŕ�΂�*/
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
	// ���[���h�s��̍X�V
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
