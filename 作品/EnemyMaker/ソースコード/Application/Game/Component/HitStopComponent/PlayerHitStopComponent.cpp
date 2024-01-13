//--------- INCLUDES ----------
#include "PlayerHitStopComponent.h"
#include "../../../Utility/MathLibrary.h"
#include "../../GameObject/GameObject.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../GameObject/Camera/CameraIncludes.h"

PlayerHitStopComponent::PlayerHitStopComponent()
	: mDamage(0.0f)
	, mHitStopSecondWeight(0.09f)
{
	// �����Ȃ�
}

PlayerHitStopComponent::~PlayerHitStopComponent()
{
	// �����Ȃ�
}

void PlayerHitStopComponent::HitStop()
{	
	std::shared_ptr<AnimationPlayer> animPlayer = mOwner->GetComponent<SkeletalMeshComponent>()->GetAnimationPlayer().lock();
	if (!animPlayer)
	{
		return;
	}

	// �J�����U��
	SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->ShakeMainCamera({ 0.2f,0.2f }, 0.1f);

	// -1.7�t���[���X�L�b�v����
	animPlayer->SkipAnimationFrame(-(mHitStopSecondWeight * mDamage));
}