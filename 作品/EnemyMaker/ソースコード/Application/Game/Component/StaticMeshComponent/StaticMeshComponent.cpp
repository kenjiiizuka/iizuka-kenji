//---------- INCLUDES ----------
#include "StaticMeshComponent.h"
#include "StaticMesh.h"
#include "../../../System/RendererSystem/Shader/VertexShader/VertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/PixelShader.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../../Utility/MathLibrary.h"

//------------ NAMESPACEALIAS -------------
namespace DXSimpleMath = DirectX::SimpleMath;

StaticMeshComponent::StaticMeshComponent() 
{
	// 処理なし
}

StaticMeshComponent::~StaticMeshComponent()
{
	// 処理なし
}

void StaticMeshComponent::Load(const std::string& _filepath)
{
	mStaticMesh = std::make_shared<StaticMesh>();
	mStaticMesh->Initialize(_filepath);
	mStaticMesh->SetOwnerObject(mOwner);
}

void StaticMeshComponent::Update(const double _deltaTime)
{
	CalucStaticMeshWorldMatrix();
}

void StaticMeshComponent::Draw()
{
	mStaticMesh->Draw();
}

void StaticMeshComponent::CalucStaticMeshWorldMatrix()
{
	// SkeletalMeshの位置を計算する
	DXSimpleMath::Matrix ownerWorldMatrix = mOwner->GetComponent<TransformComponent>()->CalucWorldMatrix(DXSimpleMath::Matrix::Identity);
	DXSimpleMath::Matrix worldMatrix = MathLibrary::MakeWorldMatrix(mTransform);
	mStaticMesh->CalucWorldMatrix(worldMatrix * ownerWorldMatrix);
}
