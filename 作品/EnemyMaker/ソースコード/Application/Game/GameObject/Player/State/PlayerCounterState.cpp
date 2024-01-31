//---------- INCLUDES ----------
#include "PlayerCounterState.h"
#include "../Player.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"
#include "../Weapon/PlayerWeapon.h"

PlayerCounterState::PlayerCounterState(Player* _player)
	: PlayerStateContext(_player)
	, mbFirstFrame(false)
	, mCollisionSizeChangeFrame(6)
	, mbChangeCollisionSize(false)
{
	// 処理なし
}

PlayerCounterState::~PlayerCounterState()
{
	// 処理なし
}

void PlayerCounterState::Entry()
{
	mbIsInputAble = false;
	mbChangeCollisionSize = false;

	// カウンター攻撃にセットする
	PlayerAttack attack = mPlayer->GetAttackData().lock()->GetAttack(PlayerData::AttackID_Counter);
	mPlayer->SetCurrentAttack(attack);	
}

void PlayerCounterState::Update()
{
	if (mbFirstFrame)
	{
		mbFirstFrame = false;
		return;
	}

	std::shared_ptr<AnimationInstance> animIns = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	std::shared_ptr<AnimationPlayer> animPlayer = animIns->GetAnimationPlayer();

	// カウンターアニメーションの再生フレーム指定されたフレーム以上で、コリジョンのサイズを変更前なら、当たり判定を大きくする
	if (mCollisionSizeChangeFrame <= animPlayer->GetPlayAnimation().lock()->GetCurrentPlayTime() && !mbChangeCollisionSize)
	{
		// 武器の当たり判定を大きくする
		mPlayer->GetWeapon().lock()->SetCapsuleCollisionSize(6.0f, 2.0f);
		mbChangeCollisionSize = true;
	}

	// カウンターアニメーションが終了しているかを確認する
	if (animPlayer->IsEndOnNextFrame() || !animPlayer->IsPlay())
	{
		mbNeedTransitionState = true;
		mbIsInputAble = true;

		// 当たり判定のサイズを通常のサイズに戻す
		mPlayer->GetWeapon().lock()->SetDefaultCapsuleCollisionSize();
	}
}
