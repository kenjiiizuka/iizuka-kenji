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
	// 処理なし
}

StaticMeshProvider::~StaticMeshProvider()
{
	// 処理なし
}


std::shared_ptr<IAsset> StaticMeshProvider::Load(const std::string& _filePath) const
{
	// インポートセッティング
	int flag = 0;
	flag |= aiProcess_Triangulate;           // 三角形ポリゴンにする
	flag |= aiProcess_JoinIdenticalVertices; // 同じ頂点を結合
	flag |= aiProcess_FlipUVs;               // UV反転機能
	flag |= aiProcess_PreTransformVertices;
	// flag |= aiProcess_MakeLeftHanded;

	//読み込み
	Assimp::Importer importer{};
	const aiScene* aiScene = importer.ReadFile(_filePath, aiProcess_ConvertToLeftHanded | flag);

	// 読み込み出来ているかチェック
	if (!aiScene)
	{
		std::cout << _filePath << "の読み込みに失敗しました" << std::endl;
		return std::shared_ptr<StaticMeshAsset>();
	}

	// メッシュデータがあるか確認する
	if (!aiScene->HasMeshes())
	{
		std::cout << _filePath << "にはメッシュデータはありません" << std::endl;
		return std::shared_ptr<StaticMeshAsset>();
	}

	std::shared_ptr<StaticMeshAsset> staticMeshAsset = std::make_shared<StaticMeshAsset>();

	// メッシュの数だけ読み込む
	for (size_t mesh_i = 0; mesh_i < aiScene->mNumMeshes; mesh_i++)
	{
		LoadVertexData(staticMeshAsset, *aiScene->mMeshes[mesh_i]);
		LoadMaterialData(staticMeshAsset, *aiScene->mMaterials[mesh_i], _filePath);
	}

	return staticMeshAsset;
}

void StaticMeshProvider::Setting()
{
	// 処理なし
}

void StaticMeshProvider::LoadVertexData(std::shared_ptr<StaticMeshAsset>& _staticMeshAsset, const aiMesh& _aiMesh) const
{
	// 頂点データの読み取り
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

	// インデックスデータの読み込み
	uint32_t indexNum = _aiMesh.mNumFaces * 3; // 3は三角ポリゴンなので, ポリゴン× 1ポリゴンの頂点数
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
	// マテリアルの作成
	VisualEntityData::Material material;

	// ディフューズの読み込み
	aiColor3D diffuse = { 1.0f,1.0f,1.0f };
	if (_aiMaterial.Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
	{
		material.mDiffuse = { diffuse.r, diffuse.g,diffuse.b ,1.0 };
	}

	// アンビエント読み込み
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

	// テクスチャの読み込み
	// テクスチャがあるか確認 なければマテリアルを追加してリターン
	aiString aiPathOrigin;
	if (_aiMaterial.Get(AI_MATKEY_TEXTURE_DIFFUSE(0), aiPathOrigin) != AI_SUCCESS)
	{
		material.TextureEnable = false;
		_staticMesh->mMaterials.emplace_back(material);
		return;
	}

	std::string pathOrigin = aiPathOrigin.C_Str();
	// テクスチャのファイル名を取得
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

	// モデルと同じ階層にパスを設定
	std::string directory = _filePath;
	directory = directory.substr(0, directory.find_last_of('/') + 1);
	directory += textureFileName;

	// テクスチャ読み込み
	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>(directory);	
	if (texture->IsValid())
	{
		material.mTexture = texture->Get<Texture>();
	}

	_staticMesh->mMaterials.emplace_back(material);
}