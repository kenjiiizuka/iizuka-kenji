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
	// 処理なし
}

SkeletalMesh::~SkeletalMesh()
{
	// 処理なし
	mVisualEntity.reset();
}

void SkeletalMesh::Initialize(const std::string& _filePath)
{
	// アセットの読み込み
	mAssetHandle = AssetManager::GetInstance().Load<SkeletalMeshProvider>(_filePath);

	// アセットが使えるかチェック
	if (!mAssetHandle->IsValid())
	{
		std::cout << _filePath << "は使えません" << std::endl;
		return;
	}

	// アセット取得
	SkeletalMeshAsset skeletalMeshAsset = mAssetHandle->Get<SkeletalMeshAsset>();

	// ルートボーンアセットがあればスケルトンを生成する
	std::weak_ptr<BoneAsset> rootBoneAsset = skeletalMeshAsset.GetRootBoneAsset();
	if (!rootBoneAsset.lock())
	{
		std::cout << _filePath << "ボーンがありません" << std::endl;
		return;
	}
	mSkeleton = std::make_shared<Skeleton>();
	mSkeleton->Initialize(rootBoneAsset.lock());

	// 描画用オブジェクトの生成
	CreateVisualEntity();
	// レンダリングマネージャーのオブジェクト層に登録
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

	// 頂点、インデックス、マテリアルデータを取得
	std::vector<std::vector<SkeletalMeshAsset::Vertex>> verticesData = skeletalMeshAsset.GetVertices();
	std::vector<std::vector<uint32_t>> indicesData = skeletalMeshAsset.GetIndices();
	std::vector<VisualEntityData::Material> materials = skeletalMeshAsset.GetMaterials();

	// メッシュの数を取得する
	size_t numMesh = verticesData.size();
	
	// メッシュの数分VisualEntityDataを生成する	
	std::vector<std::shared_ptr<VisualEntityData>> entityData(numMesh);
	for (size_t mesh_i = 0; std::shared_ptr<VisualEntityData>&data : entityData)
	{	
		// 頂点バッファ作成のために頂点データを確保する
		SkeletalMeshAsset::Vertex* vertices;
		vertices = new SkeletalMeshAsset::Vertex[verticesData[mesh_i].size()];

		// 頂点データを代入する
		for (size_t vertices_i = 0; vertices_i < verticesData[mesh_i].size(); vertices_i++)
		{
			vertices[vertices_i] = verticesData[mesh_i][vertices_i];
		}
		// 頂点データをstd::shared<void>型に代入
		std::shared_ptr<void> vertexData(
			vertices,
			[](void* data) {delete[] static_cast<SkeletalMeshAsset::Vertex*>(data); }
		);

	    // インデックスバッファを作成するためにデータを確保する
		uint32_t* indices;
		size_t indexNum = indicesData[mesh_i].size();
		indices = new uint32_t[indexNum];

		// 頂点データを代入する
		for (size_t indices_i = 0; indices_i < indicesData[mesh_i].size(); indices_i++)
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
		desc.mVertexCount =  static_cast<uint32_t>(verticesData[mesh_i].size());
		desc.mVertexTypeByteSize = sizeof(SkeletalMeshAsset::Vertex);
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
	std::shared_ptr<SkeletalMeshVertexShader> vertexShader = mVisualEntity->MakeVertexShader<SkeletalMeshVertexShader>();
	vertexShader->SetSkeletalMesh(mSkeleton);
	mVisualEntity->MakePixelShader<LightPixelShader>();
}

void SkeletalMesh::CalucWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix)
{
	mWorldMatrix =  MathLibrary::MakeWorldMatrix(mTransform);
	mWorldMatrix *= _worldMatrix;
	// ワールドトランスフォームを計算
	MathLibrary::DecomposeMatrix(mWorldMatrix, mWorldTransform);
}
