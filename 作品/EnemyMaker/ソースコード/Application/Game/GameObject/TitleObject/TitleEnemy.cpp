//---------- INCLUDES ----------
#include "TitleEnemy.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "TitleEnemyAnimationInstance.h"
#include "../../../System/RendererSystem/Shader/VertexShader/OutlineSkeletalMeshVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/OutlinePixelShader.h"


TitleEnemy::TitleEnemy()
{
}

TitleEnemy::~TitleEnemy()
{
}

void TitleEnemy::Init()
{
	std::shared_ptr<SkeletalMeshComponent> skeletalMesh = AddComponent<SkeletalMeshComponent>();
	skeletalMesh->Load("assets/Enemy/Model/Bear.fbx");
	skeletalMesh->CreateAnimInstance<TitleEnemyAnimationInstance>();
	skeletalMesh->SetScale(0.08f);

	std::shared_ptr<SkeletalMesh> mesh = skeletalMesh->GetSkeletalMesh().lock();

	std::shared_ptr<OutlineSkeletalMeshVertexShader> outlineVertexShader = mesh->AddVertexShader<OutlineSkeletalMeshVertexShader>();
	outlineVertexShader->SetSkeleton(mesh->GetSkeleton().lock());
	mesh->AddPixelShader<OutlinePixelShader>();
	mesh->SwapShader();
	mesh->SetDrawType(CullType::Draw_SolidFront, 0);
	mesh->SetDrawType(CullType::Draw_SolidBack, 1);
}

void TitleEnemy::Update(const double _deltaTime)
{

}
