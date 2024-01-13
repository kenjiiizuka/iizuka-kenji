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
	// 処理なし
}

PlayerHitStopComponent::~PlayerHitStopComponent()
{
	// 処理なし
}

void PlayerHitStopComponent::HitStop()
{	
	std::shared_ptr<AnimationPlayer> animPlayer = mOwner->GetComponent<SkeletalMeshComponent>()->GetAnimationPlayer().lock();
	if (!animPlayer)
	{
		return;
	}

	// カメラ振動
	SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->ShakeMainCamera({ 0.2f,0.2f }, 0.1f);

	// -1.7フレームスキップする
	animPlayer->SkipAnimationFrame(-(mHitStopSecondWeight * mDamage));
}