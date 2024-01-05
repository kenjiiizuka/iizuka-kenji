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
	// 処理なし
}

StaticMesh::~StaticMesh()
{
	// 処理なし
}

void StaticMesh::Initialize(const std::string& _filePath)
{
	// アセットの読み込み
	mAssetHandle = AssetManager::GetInstance().Load<StaticMeshProvider>(_filePath);

	// アセットが使えるかチェック
	if (!mAssetHandle->IsValid())
	{
		std::cout << _filePath << "は使えません" << std::endl;
		return;
	}

	// 描画用オブジェクトの作成
	CreateVisualEntity();

	// レンダリングマネージャーのオブジェクト層に登録
	RendererManager::GetInstance().RegisterEntity(mVisualEntity, RendererInf::Layer_Object);
}

void StaticMesh::Draw()
{
	mVisualEntity->SetWorldMatrix(mWorldMatrix);
}

void StaticMesh::CreateVisualEntity()
{
	// アセットの取得
	StaticMeshAsset staticMeshAsset = mAssetHandle->Get<StaticMeshAsset>();

	// 頂点データ、インデックス、マテリアルデータを取得
	std::vector<std::vector<StaticMeshAsset::Vertex>> verticesData = staticMeshAsset.GetVertices();
	std::vector<std::vector<uint32_t>> indicesData = staticMeshAsset.GetIndices();
	std::vector<VisualEntityData::Material> materials = staticMeshAsset.GetMaterials();

	// メッシュの数を取得する
	size_t numMesh = verticesData.size();

	// メッシュの数分VisualEntityDataを生成する	
	std::vector<std::shared_ptr<VisualEntityData>> entityData(numMesh);
	for (size_t mesh_i = 0; std::shared_ptr<VisualEntityData>&data : entityData)
	{
		// 頂点バッファ作成のために頂点データを確保する
		StaticMeshAsset::Vertex* vertices;

		size_t vertexDataSize = verticesData[mesh_i].size();
		vertices = new StaticMeshAsset::Vertex[vertexDataSize];

		// 頂点データを代入する
		for (size_t vertices_i = 0; vertices_i < vertexDataSize; vertices_i++)
		{
			vertices[vertices_i] = verticesData[mesh_i][vertices_i];
		}
		// 頂点データをstd::shared<void>型に代入
		std::shared_ptr<void> vertexData(
			vertices,
			[](void* data) {delete[] static_cast<StaticMeshAsset::Vertex*>(data); }
		);

		// インデックスバッファを作成するためにデータを確保する
		uint32_t* indices;
		size_t indexNum = indicesData[mesh_i].size();
		indices = new uint32_t[indexNum];

		// インデックスデータを代入する
		for (size_t indices_i = 0; indices_i < indexNum; indices_i++)
		{
			indices[indices_i] = indicesData[mesh_i][indices_i];
		}

		// インデックスデータをstd::shared<void>型に代入

		std::shared_ptr<void> indexData(
			indices,
			[](void* data) {delete[] static_cast<uint32_t*>(data); }
		);

		// VisualEntityData作成の為に必要な情報をセットする
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

		// VisualEntityDataの作成
		entityData[mesh_i] = (std::make_shared<VisualEntityData>(desc));

		// マテリアルのセット
		entityData[mesh_i]->SetMaterial(materials[mesh_i]);

		mesh_i++;
	}

	// 描画用オブジェクトの生成
	mVisualEntity = std::make_shared<VisualEntity>(entityData);

	// シェーダーの作成
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
	// ワールド空間のトランスフォームを計算
	MathLibrary::DecomposeMatrix(mWorldMatrix, mWorldTransform);
}