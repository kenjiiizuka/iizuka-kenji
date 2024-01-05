//------------- INCLUDES ----------
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "SkeletalMeshProvider.h"
#include "SkeletalMeshAsset.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureProvider.h"
#include "../AssetManager.h"
#include "../AssetHandle.h"
#include "BoneAsset.h"

//---------- LIBRARY -----------
#ifdef _DEBUG
#pragma comment (lib,"assimp-vc142-mtd.lib")
#else
#pragma comment (lib,"assimp-vc142-mt.lib")
#endif // _DEBUG

//------------- NAMESPACEALIAS ----------------
namespace DXSimpleMath = DirectX::SimpleMath;


SkeletalMeshProvider::SkeletalMeshProvider()
{
	// �����Ȃ�
}

SkeletalMeshProvider::~SkeletalMeshProvider()
{
	// �����Ȃ�
}

std::shared_ptr<IAsset> SkeletalMeshProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<SkeletalMeshAsset> skeletalMesh = std::make_shared<SkeletalMeshAsset>();

	// �C���|�[�^�\�̐ݒ�
	Assimp::Importer importer{};
	int flag = 0;
	flag |= aiProcess_Triangulate;                     // �O�p�`�|���S���ɂ���
	flag |= aiProcess_JoinIdenticalVertices;           // �������_������	
	flag |= aiProcess_FlipUVs;                         // UV���]�@�\
	flag |= aiProcess_PopulateArmatureData; 
	flag |= aiProcess_ConvertToLeftHanded;
	flag |= aiProcessPreset_TargetRealtime_MaxQuality;

	//�ǂݍ���
	const aiScene* aiScene = importer.ReadFile(_filePath.c_str(), flag);

	// �ǂݍ��݂��ł��Ă��邩�`�F�b�N
	if (!aiScene)
	{
		std::cout << _filePath << "�̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return std::shared_ptr<IAsset>();
	}

	if (aiScene->mNumMeshes == 0)
	{
		std::cout << _filePath << "����FBX�ɂ̓��b�V���f�[�^������܂���" << std::endl;
		return std::shared_ptr<IAsset>();
	}

	// �f�[�^�ǂݍ���
	LoadNode(skeletalMesh, aiScene->mMeshes[0]->mBones[0]->mNode);
	for (size_t mesh_i = 0; mesh_i < aiScene->mNumMeshes; mesh_i++)
	{
		LoadBoneData(skeletalMesh, aiScene->mMeshes[mesh_i]->mBones, aiScene->mMeshes[mesh_i]->mNumBones);
		LoadVertexData(skeletalMesh, *aiScene->mMeshes[mesh_i]);
		LoadMaterialData(skeletalMesh, *aiScene->mMaterials[mesh_i], _filePath);		
	}

	return skeletalMesh;
}

void SkeletalMeshProvider::LoadVertexData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiMesh& _aiMesh) const
{
	// ���_�f�[�^�̓ǂݎ��
	std::vector<SkeletalMeshAsset::Vertex> vertices(_aiMesh.mNumVertices);
	for (size_t vertex_i = 0; vertex_i < _aiMesh.mNumVertices; vertex_i++)
	{
		aiVector3D pos = _aiMesh.mVertices[vertex_i];
		aiVector3D uv = _aiMesh.HasTextureCoords(0) ? _aiMesh.mTextureCoords[0][vertex_i] : aiVector3D(0.0f, 0.0f,0.0f);
		aiVector3D normal = _aiMesh.HasNormals() ? _aiMesh.mNormals[vertex_i] : aiVector3D(0.0f, 0.0f, 0.0f);
		aiColor4D color = _aiMesh.HasVertexColors(0) ? _aiMesh.mColors[0][vertex_i] : aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
		
		vertices[vertex_i] =
		{
			DXSimpleMath::Vector3(pos.x, pos.y, pos.z),
			DXSimpleMath::Vector3(normal.x, normal.y, normal.z),
			DXSimpleMath::Vector2(uv.x, uv.y),
			DXSimpleMath::Vector4(color.r, color.g, color.b, color.a)
		};
	}

	// �X�L���E�F�C�g�ƃ{�[���C���f�b�N�X�̓ǂݎ��
	for (size_t bone_i = 0; bone_i < _aiMesh.mNumBones; bone_i++)
	{
		// �o�^���݂̃{�[�����擾
		std::weak_ptr<BoneAsset> boneAsset = _skeletalMesh->mBoneMap[_aiMesh.mBones[bone_i]->mName.C_Str()];
		if (!boneAsset.lock())
		{
			continue;
		}
	
		for (size_t weights_i = 0; weights_i < _aiMesh.mBones[bone_i]->mNumWeights; weights_i++)
		{
			size_t vertexID = _aiMesh.mBones[bone_i]->mWeights[weights_i].mVertexId;
			int16_t boneIndex = static_cast<int16_t>(boneAsset.lock()->mIndex);
			float weight = _aiMesh.mBones[bone_i]->mWeights[weights_i].mWeight;	
			SetWeightAndBoneIndex(vertices[vertexID], weight, boneIndex);
		}
	}

	uint32_t indexNum = _aiMesh.mNumFaces * 3; // 3�͎O�p�|���S���Ȃ̂�, �|���S���~ 1�|���S���̒��_��
	std::vector<uint32_t> indices(indexNum);
	
	for (size_t face_i = 0; face_i < _aiMesh.mNumFaces; face_i++)
	{
		aiFace face = _aiMesh.mFaces[face_i];
		size_t index = face_i * 3;

		indices[index] = face.mIndices[0];
		indices[index + 1] = face.mIndices[1];
		indices[index + 2] = face.mIndices[2];
	}
	
	_skeletalMesh->mVertices.emplace_back(vertices);
	_skeletalMesh->mIndices.emplace_back(indices);
}

void SkeletalMeshProvider::SetWeightAndBoneIndex(SkeletalMeshAsset::Vertex& _vertex, const float _weight, const int16_t _boneIndex) const
{
	for (size_t weight_i = 0; uint32_t& boneIndex : _vertex.mBoneIndices)
	{
		// boneIndex�̒l�������l�ɂȂ��Ă���l�ɂ����������
		if(boneIndex == -1)
		{
			_vertex.mWeights[weight_i] = _weight;
			boneIndex = _boneIndex;
			return;
		}	
		weight_i++;
	}
}

void SkeletalMeshProvider::LoadMaterialData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiMaterial& _aiMaterial, const std::string& _filePath) const
{
	// �}�e���A���̍쐬
	VisualEntityData::Material material;

	// �f�B�t���[�Y�̓ǂݍ���
	aiColor3D diffuse = { 1.0f,1.0f,1.0f };
	if (_aiMaterial.Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
	{
		material.mDiffuse = { diffuse.r, diffuse.g,diffuse.b ,1.0 };
	}

	// �A���r�G���g�ǂݍ���
	aiColor3D ambient = {0.3f,0.3f,0.3f};
	if (_aiMaterial.Get(AI_MATKEY_COLOR_AMBIENT, ambient) == AI_SUCCESS)
	{
		ambient.r = (ambient.r == 0.0f) ? 0.3f : ambient.r;
		ambient.g = (ambient.g == 0.0f) ? 0.3f : ambient.g;
		ambient.b = (ambient.b == 0.0f) ? 0.3f : ambient.b;
		material.mAmbient = { ambient.r, ambient.g, ambient.b, 1.0f };
	}

	aiColor3D specular;
	if (_aiMaterial.Get(AI_MATKEY_COLOR_SPECULAR, specular) == AI_SUCCESS)
	{
		material.mSpecular = { specular.r, specular.g, specular.b };
	}

	float shininess;
	if (_aiMaterial.Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
	{
		material.mShininess = shininess;
	}

	// �e�N�X�`���̓ǂݍ���
	// �e�N�X�`�������邩�m�F�@�Ȃ���΃}�e���A����ǉ����ă��^�[��
	aiString aiPathOrigin;
	if (_aiMaterial.Get(AI_MATKEY_TEXTURE_DIFFUSE(0), aiPathOrigin) != AI_SUCCESS)
	{
		material.TextureEnable = false;
		_skeletalMesh->mMaterials.emplace_back(material);
		return;
	}

	std::string pathOrigin = aiPathOrigin.C_Str();
	// �e�N�X�`���̃t�@�C�������擾
	std::string textureFileName = pathOrigin;
	size_t nameStartPos = pathOrigin.find_last_of('\\');
	if (nameStartPos != std::string::npos)
	{
		textureFileName = pathOrigin.substr(nameStartPos + 1);
	}
	else
	{
		nameStartPos = pathOrigin.find_last_of('/');
		if (nameStartPos != std::string::npos)
		{
			textureFileName = pathOrigin.substr(nameStartPos + 1);
		}
	}

	// ���f���Ɠ����K�w�Ƀp�X��ݒ�
	std::string directory = _filePath;
	directory = directory.substr(0, directory.find_last_of('/') + 1);
	directory += textureFileName;

	std::shared_ptr<AssetHandle> handle = AssetManager::GetInstance().Load<TextureProvider>(directory);

	// �e�N�X�`�����ǂݍ��߂Ă��邩���m�F����
	if (!handle->IsValid())
	{
		std::cout << directory << "�e�N�X�`���ǂݍ��ݎ��s" << std::endl;
		_skeletalMesh->mMaterials.emplace_back(material);
		return;
	}

	material.mTexture = handle->Get<Texture>();
	_skeletalMesh->mMaterials.emplace_back(material);
}

void SkeletalMeshProvider::LoadBoneData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, aiBone** _aiBones, const size_t _boneNum) const
{	
	// BindPose�s���������
	for (size_t bone_i = 0; bone_i < _boneNum; bone_i++)
	{
		std::string boneName = _aiBones[bone_i]->mName.C_Str();
		if (!_skeletalMesh->mBoneMap[boneName].lock())
		{
			continue;
		}
		_skeletalMesh->mBoneMap[boneName].lock()->mBindPoseMatrix = ConvAiMatrix(_aiBones[bone_i]->mOffsetMatrix);
	}
}

void SkeletalMeshProvider::LoadNode(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiNode* _rootNode) const
{
	std::shared_ptr<BoneAsset> boneAsset = std::make_shared<BoneAsset>();
	ReadNode(boneAsset, *_rootNode);
	_skeletalMesh->mRootBone = boneAsset;

	// Map�ɓo�^����
	RegisterBoneMapAndSetBoneIndex(_skeletalMesh, _skeletalMesh->mRootBone);
}

void SkeletalMeshProvider::ReadNode(std::shared_ptr<BoneAsset>& _boneAsset, const aiNode& _aiNode) const
{
	_boneAsset->mBoneName = _aiNode.mName.C_Str();
	_boneAsset->mTransformationMatrix = ConvAiMatrix(_aiNode.mTransformation);

	// �q�{�[���̐����Ɛe�̃Z�b�g
	size_t childNum = _aiNode.mNumChildren;
	_boneAsset->mChildBones.resize(childNum);
	for (size_t bone_i = 0; std::shared_ptr<BoneAsset>& child : _boneAsset->mChildBones)
	{
		child = std::make_shared<BoneAsset>();
		child->mParentBone = _boneAsset;

		// �q�{�[�����Ȃ��Ȃ�܂ōċN����
		ReadNode(child,*_aiNode.mChildren[bone_i]);
		bone_i++;
	}
}

void SkeletalMeshProvider::RegisterBoneMapAndSetBoneIndex(std::shared_ptr<SkeletalMeshAsset>& _skeletalMeshAsset, const std::shared_ptr<BoneAsset>& _boneAsset) const
{
	// �C���f�b�N�X�̃Z�b�g
	_boneAsset->mIndex = _skeletalMeshAsset->mBoneMap.size();
	bool success = _skeletalMeshAsset->mBoneMap.try_emplace(_boneAsset->mBoneName, _boneAsset).second;
	if (!success)
	{
		_skeletalMeshAsset->mBoneMap[_boneAsset->mBoneName] = _boneAsset;
		std::cout << "�o�^�ς݃{�[��" << _boneAsset->mBoneName << std::endl;
	}

	// �q�{�[����o�^���邽�߂ɍċN����
	for (std::shared_ptr<BoneAsset>& child : _boneAsset->mChildBones)
	{
		RegisterBoneMapAndSetBoneIndex(_skeletalMeshAsset, child);
	}
}

DirectX::SimpleMath::Matrix SkeletalMeshProvider::ConvAiMatrix(const aiMatrix4x4& _aiMatrix) const noexcept
{
	DXSimpleMath::Matrix matrix;

	// �e�v�f�����ւ��āA�E��n���獶��n�ɕϊ�
	matrix._11 = _aiMatrix.a1;
	matrix._12 = _aiMatrix.a2;
	matrix._13 = _aiMatrix.a3;
	matrix._14 = _aiMatrix.a4;
	matrix._21 = _aiMatrix.b1;
	matrix._22 = _aiMatrix.b2;
	matrix._23 = _aiMatrix.b3;
	matrix._24 = _aiMatrix.b4;
	matrix._31 = _aiMatrix.c1;
	matrix._32 = _aiMatrix.c2;
	matrix._33 = _aiMatrix.c3;
	matrix._34 = _aiMatrix.c4;
	matrix._41 = _aiMatrix.d1;
	matrix._42 = _aiMatrix.d2;
	matrix._43 = _aiMatrix.d3;
	matrix._44 = _aiMatrix.d4;
	matrix = matrix.Transpose();

	return matrix;
}

void SkeletalMeshProvider::Setting()
{
	// �����Ȃ�
}

