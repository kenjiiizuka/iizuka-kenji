//---------- INCLUDES ---------
#include "StaticMeshObject.h"
#include "../../Component/StaticMeshComponent/StaticMeshComponent.h"
#include "../../Component/StaticMeshComponent/StaticMesh.h"
#include "../../../System/RendererSystem/Shader/VertexShader/OutlineLightVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/OutlinePixelShader.h"

StaticMeshObject::StaticMeshObject()
{
	// èàóùÇ»Çµ
}

StaticMeshObject::~StaticMeshObject()
{
	// èàóùÇ»Çµ
}

void StaticMeshObject::Init(std::string_view _filePath)
{
	std::shared_ptr<StaticMeshComponent> mesh = AddComponent<StaticMeshComponent>();
	mesh->Load(_filePath.data());
	std::shared_ptr<StaticMesh> staticMesh = mesh->GetStaticMesh();
	staticMesh->AddVertexShader<OutlineLightVertexShader>()->SetOutlineThickness(0.4f);
	staticMesh->AddPixelShader<OutlinePixelShader>();
	staticMesh->SwapShader();
	staticMesh->SetDrawType(DrawType::Draw_SolidFront, 0);
	staticMesh->SetDrawType(DrawType::Draw_SolidBack, 1);
}

void StaticMeshObject::Update(const double _deltaTime)
{
	DirectX::SimpleMath::Matrix worldMatrix = GetComponent<TransformComponent>()->CalucWorldMatrix(DirectX::SimpleMath::Matrix::Identity);
	GetComponent<StaticMeshComponent>()->GetStaticMesh()->SetWorldMatrix(worldMatrix);
}
