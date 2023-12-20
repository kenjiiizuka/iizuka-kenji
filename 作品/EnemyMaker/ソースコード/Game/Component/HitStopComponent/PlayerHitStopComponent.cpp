//--------- INCLUDES ----------
#include "PlayerHitStopComponent.h"
#include "../../../Utility/MathLibrary.h"
#include "../../GameObject/GameObject.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../ImGui/ImGuiUtility.h"

PlayerHitStopComponent::PlayerHitStopComponent()
	: mMaxDamage(30.0f)
	, mDamage(0.0f)
	, mMaxHitStopSeconds(0.064)
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

	// -1.7フレームスキップする
	animPlayer->SkipAnimationFrame(-1.7f);
}