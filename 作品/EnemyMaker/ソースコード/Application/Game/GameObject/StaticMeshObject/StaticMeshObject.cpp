//---------- INCLUDES ---------
#include "StaticMeshObject.h"
#include "../../Component/StaticMeshComponent/StaticMeshComponent.h"
#include "../../Component/StaticMeshComponent/StaticMesh.h"
#include "../../../System/RendererSystem/Shader/VertexShader/OutlineLightVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/OutlinePixelShader.h"
#include "../../../System/RendererSystem/Shader/GeometryShader/OutlineFrustumCullingGeometryShader.h"
#include "../../../System/RendererSystem/Shader/GeometryShader/FrustumCullingGeometryShader.h"

StaticMeshObject::StaticMeshObject()
{
	// 処理なし
}

StaticMeshObject::~StaticMeshObject()
{
	// 処理なし
}

void StaticMeshObject::Init(std::string_view _filePath)
{
	// StaticMeshComponentの追加 初期化
	std::shared_ptr<StaticMeshComponent> mesh = AddComponent<StaticMeshComponent>();
	mesh->Load(_filePath.data());

	// アウトライン用シェーダーの追加
	std::shared_ptr<StaticMesh> staticMesh = mesh->GetStaticMesh();
	staticMesh->AddVertexShader<OutlineLightVertexShader>()->SetOutlineThickness(0.4f);
	staticMesh->AddPixelShader<OutlinePixelShader>();
	staticMesh->SwapShader();

	// ジオメトリシェーダーの追加
	staticMesh->AddGeometryShader<OutlineFrustumCullingGeometryShader>();
	staticMesh->AddGeometryShader<FrustumCullingGeometryShader>();

	// カリング設定
	staticMesh->SetDrawType(CullType::Draw_SolidFront, 0);
	staticMesh->SetDrawType(CullType::Draw_SolidBack, 1);
}

void StaticMeshObject::Update(const double _deltaTime)
{
	DirectX::SimpleMath::Matrix worldMatrix = GetComponent<TransformComponent>()->CalucWorldMatrix(DirectX::SimpleMath::Matrix::Identity);
	GetComponent<StaticMeshComponent>()->GetStaticMesh()->SetWorldMatrix(worldMatrix);
}
