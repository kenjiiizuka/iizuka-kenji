//-------------- INCLUDES -------------
#include "SkeletalMeshComponent.h"
#include "AnimationInstance.h"
#include "../../../Utility/Debug.h"
#include "../../../System/RendererSystem/Shader/Shader.h"
#include "../../GameObject/GameObject.h"
#include "../../../System/AnimationSystem/AnimationPlayer.h"
#include "../../Resource/SkeletalMeshAnimationClip.h"
#include "../../../System/InputSystem/Input.h"
#include "../../Resource/SkeletalMesh.h"
#include "../../Resource/Skeleton.h"
#include "../../../Utility/MathLibrary.h"

//-------------- NAMESPACEAILIAS -------------
namespace DXSimpleMath = DirectX::SimpleMath;

SkeletalMeshComponent::SkeletalMeshComponent()
	: mSkeletalMesh(nullptr)
	, bPlayAnimation(false)
{
	// èàóùÇ»Çµ
}

SkeletalMeshComponent::~SkeletalMeshComponent()
{
	Cout<std::string>("SkeletalMeshComponentÇ™âï˙Ç≥ÇÍÇ‹ÇµÇΩ");
}

void SkeletalMeshComponent::Load(std::string _filePath, bool _flipUV)
{	
	mSkeletalMesh->Initialize(_filePath);	
}

void SkeletalMeshComponent::Init()
{		
	mSkeletalMesh = std::make_shared<SkeletalMesh>();
	mSkeletalMesh->SetOwnerObject(mOwner);
	mAnimPlayer = std::make_shared<AnimationPlayer>();
	CalucSkeletalMeshWorldMatrix();
}

void SkeletalMeshComponent::Update(const double _deltaTime)
{
	if (mAnimInstance)
	{
		mAnimInstance->AnimationUpdate();
	}	
	// SkeletalMeshÇÃà íuÇåvéZÇ∑ÇÈ
	CalucSkeletalMeshWorldMatrix();

	mAnimPlayer->AnimationUpdate(_deltaTime);	
	mSkeletalMesh->Update();
}

void SkeletalMeshComponent::Draw()
{			
	// SkeletalMeshÇÃï`âÊ
	mSkeletalMesh->Draw();
}

std::shared_ptr<AnimationInstance> SkeletalMeshComponent::GetAnimationInstance()
{
	return mAnimInstance;
}

void SkeletalMeshComponent::PlayAnimation(const std::string& _animationName, const float _playRate, const float _blendTime)
{
	mAnimInstance->PlayAnimationClip(_animationName, _playRate, _blendTime);
}

void SkeletalMeshComponent::CalucSkeletalMeshWorldMatrix()
{
	// SkeletalMeshÇÃà íuÇåvéZÇ∑ÇÈ
	DXSimpleMath::Matrix ownerWorldMatrix = mOwner->GetComponent<TransformComponent>()->CalucWorldMatrix(DXSimpleMath::Matrix::Identity);
	DXSimpleMath::Matrix worldMatrix = MathLibrary::MakeWorldMatrix(mTransform);
	mSkeletalMesh->CalucWorldMatrix(worldMatrix * ownerWorldMatrix);
}