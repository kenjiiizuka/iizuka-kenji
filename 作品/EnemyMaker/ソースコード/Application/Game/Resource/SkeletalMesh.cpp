//----------- INCLUDES ------------
#include "SkeletalMesh.h"
#include "../../System/AssetSystem/SkeletalMesh/SkeletalMeshProvider.h"
#include "../../System/AssetSystem/AssetManager.h"
#include "../../System/AssetSystem/AssetHandle.h"
#include "../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../System/RendererSystem/RendererManager.h"
#include "../../System/RendererSystem/Shader/VertexShader/SkeletalMeshVertexShader.h"
#include "../../System/RendererSystem/Shader/PixelShader/LightPixelShader.h"
#include "Skeleton.h"
#include "../../Utility/MathLibrary.h"
#include "../../System/InputSystem/XInput.h"

SkeletalMesh::SkeletalMesh()
	: mbAnimate(false)
	, mOwnerGameObject(nullptr)
{
	// �����Ȃ�
}

SkeletalMesh::~SkeletalMesh()
{
	// �����Ȃ�
	mVisualEntity.reset();
}

void SkeletalMesh::Initialize(const std::string& _filePath)
{
	// �A�Z�b�g�̓ǂݍ���
	mAssetHandle = AssetManager::GetInstance().Load<SkeletalMeshProvider>(_filePath);

	// �A�Z�b�g���g���邩�`�F�b�N
	if (!mAssetHandle->IsValid())
	{
		std::cout << _filePath << "�͎g���܂���" << std::endl;
		return;
	}

	// �A�Z�b�g�擾
	SkeletalMeshAsset skeletalMeshAsset = mAssetHandle->Get<SkeletalMeshAsset>();

	// ���[�g�{�[���A�Z�b�g������΃X�P���g���𐶐�����
	std::weak_ptr<BoneAsset> rootBoneAsset = skeletalMeshAsset.GetRootBoneAsset();
	if (!rootBoneAsset.lock())
	{
		std::cout << _filePath << "�{�[��������܂���" << std::endl;
		return;
	}
	mSkeleton = std::make_shared<Skeleton>();
	mSkeleton->Initialize(rootBoneAsset.lock());

	// �`��p�I�u�W�F�N�g�̐���
	CreateVisualEntity();
	// �����_�����O�}�l�[�W���[�̃I�u�W�F�N�g�w�ɓo�^
	RendererManager::GetInstance().RegisterEntity(mVisualEntity, RendererInf::Layer_Object);
}

void SkeletalMesh::Update()
{
	mSkeleton->Update();
	mSkeleton->CalucWorldBoneMatrix(mWorldMatrix);
}

void SkeletalMesh::Draw()
{
	mVisualEntity->SetWorldMatrix(mWorldMatrix);
	mSkeleton->Draw();
}

void SkeletalMesh::CreateVisualEntity()
{
	SkeletalMeshAsset skeletalMeshAsset = mAssetHandle->Get<SkeletalMeshAsset>();

	// ���_�A�C���f�b�N�X�A�}�e���A���f�[�^���擾
	std::vector<std::vector<SkeletalMeshAsset::Vertex>> verticesData = skeletalMeshAsset.GetVertices();
	std::vector<std::vector<uint32_t>> indicesData = skeletalMeshAsset.GetIndices();
	std::vector<VisualEntityData::Material> materials = skeletalMeshAsset.GetMaterials();

	// ���b�V���̐����擾����
	size_t numMesh = verticesData.size();
	
	// ���b�V���̐���VisualEntityData�𐶐�����	
	std::vector<std::shared_ptr<VisualEntityData>> entityData(numMesh);
	for (size_t mesh_i = 0; std::shared_ptr<VisualEntityData>&data : entityData)
	{	
		// ���_�o�b�t�@�쐬�̂��߂ɒ��_�f�[�^���m�ۂ���
		SkeletalMeshAsset::Vertex* vertices;
		vertices = new SkeletalMeshAsset::Vertex[verticesData[mesh_i].size()];

		// ���_�f�[�^��������
		for (size_t vertices_i = 0; vertices_i < verticesData[mesh_i].size(); vertices_i++)
		{
			vertices[vertices_i] = verticesData[mesh_i][vertices_i];
		}
		// ���_�f�[�^��std::shared<void>�^�ɑ��
		std::shared_ptr<void> vertexData(
			vertices,
			[](void* data) {delete[] static_cast<SkeletalMeshAsset::Vertex*>(data); }
		);

	    // �C���f�b�N�X�o�b�t�@���쐬���邽�߂Ƀf�[�^���m�ۂ���
		uint32_t* indices;
		size_t indexNum = indicesData[mesh_i].size();
		indices = new uint32_t[indexNum];

		// ���_�f�[�^��������
		for (size_t indices_i = 0; indices_i < indicesData[mesh_i].size(); indices_i++)
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
		desc.mVertexCount =  static_cast<uint32_t>(verticesData[mesh_i].size());
		desc.mVertexTypeByteSize = sizeof(SkeletalMeshAsset::Vertex);
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
	std::shared_ptr<SkeletalMeshVertexShader> vertexShader = mVisualEntity->MakeVertexShader<SkeletalMeshVertexShader>();
	vertexShader->SetSkeletalMesh(mSkeleton);
	mVisualEntity->MakePixelShader<LightPixelShader>();
}

void SkeletalMesh::CalucWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix)
{
	mWorldMatrix =  MathLibrary::MakeWorldMatrix(mTransform);
	mWorldMatrix *= _worldMatrix;
	// ���[���h�g�����X�t�H�[�����v�Z
	MathLibrary::DecomposeMatrix(mWorldMatrix, mWorldTransform);
}
