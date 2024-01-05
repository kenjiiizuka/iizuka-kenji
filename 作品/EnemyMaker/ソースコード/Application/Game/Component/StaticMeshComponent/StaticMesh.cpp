//----------- INCLUDES ----------
#include "StaticMesh.h"
#include "../../../System/RendererSystem/Shader/VertexShader/VertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/PixelShader.h"
#include "../../../System/RendererSystem/Shader/GeometryShader/FrustumCullingGeometryShader.h"
#include "../../../System/RendererSystem/Shader/ShaderStruct.h"
#include "../../../Utility/Debug.h"
#include"../../../System/RendererSystem/RendererManager.h"
#include "../../GameObject/GameObject.h"
#include "../../../System/AssetSystem/AssetHandle.h"
#include "../../../System/AssetSystem/StaticMesh/StaticMeshAsset.h"
#include "../../../System/AssetSystem/AssetManager.h"
#include "../../../System/AssetSystem/StaticMesh/StaticMeshProvider.h"
#include "../../../Utility/MathLibrary.h"

StaticMesh::StaticMesh()
	:mOwnerGameObject(nullptr)
{
	// �����Ȃ�
}

StaticMesh::~StaticMesh()
{
	// �����Ȃ�
}

void StaticMesh::Initialize(const std::string& _filePath)
{
	// �A�Z�b�g�̓ǂݍ���
	mAssetHandle = AssetManager::GetInstance().Load<StaticMeshProvider>(_filePath);

	// �A�Z�b�g���g���邩�`�F�b�N
	if (!mAssetHandle->IsValid())
	{
		std::cout << _filePath << "�͎g���܂���" << std::endl;
		return;
	}

	// �`��p�I�u�W�F�N�g�̍쐬
	CreateVisualEntity();

	// �����_�����O�}�l�[�W���[�̃I�u�W�F�N�g�w�ɓo�^
	RendererManager::GetInstance().RegisterEntity(mVisualEntity, RendererInf::Layer_Object);
}

void StaticMesh::Draw()
{
	mVisualEntity->SetWorldMatrix(mWorldMatrix);
}

void StaticMesh::CreateVisualEntity()
{
	// �A�Z�b�g�̎擾
	StaticMeshAsset staticMeshAsset = mAssetHandle->Get<StaticMeshAsset>();

	// ���_�f�[�^�A�C���f�b�N�X�A�}�e���A���f�[�^���擾
	std::vector<std::vector<StaticMeshAsset::Vertex>> verticesData = staticMeshAsset.GetVertices();
	std::vector<std::vector<uint32_t>> indicesData = staticMeshAsset.GetIndices();
	std::vector<VisualEntityData::Material> materials = staticMeshAsset.GetMaterials();

	// ���b�V���̐����擾����
	size_t numMesh = verticesData.size();

	// ���b�V���̐���VisualEntityData�𐶐�����	
	std::vector<std::shared_ptr<VisualEntityData>> entityData(numMesh);
	for (size_t mesh_i = 0; std::shared_ptr<VisualEntityData>&data : entityData)
	{
		// ���_�o�b�t�@�쐬�̂��߂ɒ��_�f�[�^���m�ۂ���
		StaticMeshAsset::Vertex* vertices;

		size_t vertexDataSize = verticesData[mesh_i].size();
		vertices = new StaticMeshAsset::Vertex[vertexDataSize];

		// ���_�f�[�^��������
		for (size_t vertices_i = 0; vertices_i < vertexDataSize; vertices_i++)
		{
			vertices[vertices_i] = verticesData[mesh_i][vertices_i];
		}
		// ���_�f�[�^��std::shared<void>�^�ɑ��
		std::shared_ptr<void> vertexData(
			vertices,
			[](void* data) {delete[] static_cast<StaticMeshAsset::Vertex*>(data); }
		);

		// �C���f�b�N�X�o�b�t�@���쐬���邽�߂Ƀf�[�^���m�ۂ���
		uint32_t* indices;
		size_t indexNum = indicesData[mesh_i].size();
		indices = new uint32_t[indexNum];

		// �C���f�b�N�X�f�[�^��������
		for (size_t indices_i = 0; indices_i < indexNum; indices_i++)
		{
			indices[indices_i] = indicesData[mesh_i][indices_i];
		}

		// �C���f�b�N�X�f�[�^��std::shared<void>�^�ɑ��

		std::shared_ptr<void> indexData(
			indices,
			[](void* data) {delete[] static_cast<uint32_t*>(data); }
		);

		// VisualEntityData�쐬�ׂ̈ɕK�v�ȏ����Z�b�g����
		VisualEntityData::Description desc;
		desc.mbAbleMap = true;
		desc.mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		desc.mpVertex = vertexData;
		desc.mVertexCount = static_cast<uint32_t>(verticesData[mesh_i].size());
		desc.mVertexTypeByteSize = sizeof(StaticMeshAsset::Vertex);
		desc.mbUseIndex = true;
		desc.mpIndex = indexData;
		desc.mIndexCount = static_cast<uint32_t>(indicesData[mesh_i].size());
		desc.mIndexTypeByteSize = sizeof(uint32_t);

		// VisualEntityData�̍쐬
		entityData[mesh_i] = (std::make_shared<VisualEntityData>(desc));

		// �}�e���A���̃Z�b�g
		entityData[mesh_i]->SetMaterial(materials[mesh_i]);

		mesh_i++;
	}

	// �`��p�I�u�W�F�N�g�̐���
	mVisualEntity = std::make_shared<VisualEntity>(entityData);

	// �V�F�[�_�[�̍쐬
	mVisualEntity->MakeVertexShader<Object3DVertexShader>();
	mVisualEntity->MakePixelShader<LightPixelShader>();
}

void StaticMesh::SetMaterialDiffuse(const DirectX::SimpleMath::Vector4 _diffuse)
{
	std::vector<std::shared_ptr<VisualEntityData>> entities = mVisualEntity->GetAllVisualEntityData();
	for (std::shared_ptr<VisualEntityData>& entity : entities)
	{
		entity->SetMaterialDiffuse(_diffuse);
	}
}

void StaticMesh::CalucWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix)
{
	DirectX::SimpleMath::Matrix transform = MathLibrary::MakeWorldMatrix(mTransform);
	mWorldMatrix = transform * _worldMatrix;
	// ���[���h��Ԃ̃g�����X�t�H�[�����v�Z
	MathLibrary::DecomposeMatrix(mWorldMatrix, mWorldTransform);
}