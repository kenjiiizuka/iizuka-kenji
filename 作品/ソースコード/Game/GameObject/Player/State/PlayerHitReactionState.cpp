//------------- INCLUDES --------------
#include "PlayerHitReactionState.h"
#include "../Player.h"
#include "../Animation/PlayerAnimationInstance.h"
#include "../Animation/Notify/PlayerInputAbleNotifyState.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"


PlayerHitReactionState::PlayerHitReactionState(Player* _player)
	:PlayerStateContext(_player)
{
	// 処理なし
}

PlayerHitReactionState::~PlayerHitReactionState()
{
	// 処理なし
}

void PlayerHitReactionState::Entry()
{
	mbIsInputAble = false;
}

void PlayerHitReactionState::Update()
{
	// アニメーションが再生されているかを確認する
	// 再生されていない、終了する場合は入力可能にして処理終了
	if (CheckAnimationEnd())
	{
		mbIsInputAble = true;
		mbNeedTransitionState = true;
		return;
	}

	// ヒットリアクションアニメーションについている通知から入力可能かを判断する
	//	mbIsInputAble = CheckInputAble();
}

bool PlayerHitReactionState::CheckInputAble() const
{
	std::shared_ptr<AnimationInstance> animInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	std::shared_ptr<SkeletalMeshAnimationClip> animClip = animInstance->GetAnimationPlayer()->GetPlayAnimation().lock();
	return animClip->GetAnimnotifyState<PlayerInputAbleNotifyState>()->IsInputAble();	
}

bool PlayerHitReactionState::CheckAnimationEnd() const
{
	std::shared_ptr<AnimationInstance> animInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	std::shared_ptr<AnimationPlayer> animPlayer = animInstance->GetAnimationPlayer();
	return  (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame());
}
