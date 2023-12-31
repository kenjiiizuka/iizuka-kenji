//---------- INCLUDES ------------
#include "AnimationTestObject.h"
#include "AnimationInstanceTest.h"

AnimationTestObject::AnimationTestObject()
{
	// 処理なし
}

AnimationTestObject::~AnimationTestObject()
{
	// 処理なし
}

void AnimationTestObject::Init()
{
	std::shared_ptr<SkeletalMeshComponent> skeletalMesh = AddComponent<SkeletalMeshComponent>();
	
	// モデル読み込み
	skeletalMesh->Load("assets/Enemy/Model/Bear.fbx");
	skeletalMesh->SetScale(0.06f);
	skeletalMesh->SetRotation({ 0.0f, 3.14f,0.0f });
	skeletalMesh->CreateAnimInstance<AnimationInstanceTest>();
	SetRotation({ 0.0f,3.14f,0.0f });
}
