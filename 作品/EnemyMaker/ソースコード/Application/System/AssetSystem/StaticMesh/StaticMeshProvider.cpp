//------------ INCLUDES ------------
#include "StaticMeshProvider.h"
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "StaticMeshProvider.h"
#include "../StaticMesh/StaticMeshAsset.h"
#include "../../AssetSystem/Texture/TextureAssetInclude.h"


//---------- LIBRARY -----------
#ifdef _DEBUG
#pragma comment (lib,"assimp-vc142-mtd.lib")
#else
#pragma comment (lib,"assimp-vc142-mt.lib")
#endif // _DEBUG

//------------- NAMESPACEALIAS ----------------
namespace DXSimpleMath = DirectX::SimpleMath;

StaticMeshProvider::StaticMeshProvider()
{
	// �����Ȃ�
}

StaticMeshProvider::~StaticMeshProvider()
{
	// �����Ȃ�
}


std::shared_ptr<IAsset> StaticMeshProvider::Load(const std::string& _filePath) const
{
	// �C���|�[�g�Z�b�e�B���O
	int flag = 0;
	flag |= aiProcess_Triangulate;           // �O�p�`�|���S���ɂ���
	flag |= aiProcess_JoinIdenticalVertices; // �������_������
	flag |= aiProcess_FlipUVs;               // UV���]�@�\
	flag |= aiProcess_PreTransformVertices;
	// flag |= aiProcess_MakeLeftHanded;

	//�ǂݍ���
	Assimp::Importer importer{};
	const aiScene* aiScene = importer.ReadFile(_filePath, aiProcess_ConvertToLeftHanded | flag);

	// �ǂݍ��ݏo���Ă��邩�`�F�b�N
	if (!aiScene)
	{
		std::cout << _filePath << "�̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		return std::shared_ptr<StaticMeshAsset>();
	}

	// ���b�V���f�[�^�����邩�m�F����
	if (!aiScene->HasMeshes())
	{
		std::cout << _filePath << "�ɂ̓��b�V���f�[�^�͂���܂���" << std::endl;
		return std::shared_ptr<StaticMeshAsset>();
	}

	std::shared_ptr<StaticMeshAsset> staticMeshAsset = std::make_shared<StaticMeshAsset>();

	// ���b�V���̐������ǂݍ���
	for (size_t mesh_i = 0; mesh_i < aiScene->mNumMeshes; mesh_i++)
	{
		LoadVertexData(staticMeshAsset, *aiScene->mMeshes[mesh_i]);
		LoadMaterialData(staticMeshAsset, *aiScene->mMaterials[mesh_i], _filePath);
	}

	return staticMeshAsset;
}

void StaticMeshProvider::Setting()
{
	// �����Ȃ�
}

void StaticMeshProvider::LoadVertexData(std::shared_ptr<StaticMeshAsset>& _staticMeshAsset, const aiMesh& _aiMesh) const
{
	// ���_�f�[�^�̓ǂݎ��
	std::vector<StaticMeshAsset::Vertex> vertices(_aiMesh.mNumVertices);
	for (size_t vertex_i = 0; vertex_i < vertices.size(); vertex_i++)
	{
		aiVector3D pos = _aiMesh.mVertices[vertex_i];
		aiVector3D uv = _aiMesh.HasTextureCoords(0) ? _aiMesh.mTextureCoords[0][vertex_i] : aiVector3D(0.0f, 0.0f, 0.0f);
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

	// �C���f�b�N�X�f�[�^�̓ǂݍ���
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

	_staticMeshAsset->mVertices.emplace_back(vertices);
	_staticMeshAsset->mIndices.emplace_back(indices);
}

void StaticMeshProvider::LoadMaterialData(std::shared_ptr<StaticMeshAsset>& _staticMesh, const aiMaterial& _aiMaterial, const std::string& _filePath) const
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
	// �e�N�X�`�������邩�m�F �Ȃ���΃}�e���A����ǉ����ă��^�[��
	aiString aiPathOrigin;
	if (_aiMaterial.Get(AI_MATKEY_TEXTURE_DIFFUSE(0), aiPathOrigin) != AI_SUCCESS)
	{
		material.TextureEnable = false;
		_staticMesh->mMaterials.emplace_back(material);
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

	// �e�N�X�`���ǂݍ���
	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>(directory);	
	if (texture->IsValid())
	{
		material.mTexture = texture->Get<Texture>();
	}

	_staticMesh->mMaterials.emplace_back(material);
}