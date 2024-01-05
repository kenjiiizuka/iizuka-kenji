//---------- INCLUDES ------------
#include "PlayerAnimationInstance.h"
#include "../Player.h"
#include "../../../Component/MoveComponent/PlayerMovementComponent.h"
#include "../../../../Utility/Debug.h"
#include "../../../Component/SkeletalMeshComponent/AnimationStateContext.h"
#include "AnimationState/PlayerAnimationPulledState.h"
#include "AnimationState/PlayerAnimationAttackState.h"
#include "Notify/PlayerInputAbleNotifyState.h"
#include "AnimationState/PlayerAnimationRollState.h"
#include "AnimationState/PlayerAnimationHitReactionState.h"
#include "AnimationState/PlayerAnimationDeathState.h"
#include "AnimationState/PlayerAnimationGuardState.h"
#include "Notify/PlayerWeaponCollisionActiveNotifyState.h"
#include "Notify/PlayerStepNotifyState.h"
#include "../../../Resource/BlendAnimationClip.h"
#include "../../../../System/Logger/Logger.h"
#include "../../../Component/EffectComponent/PlayEffectNotify.h"
#include "Notify/PlayerHitReactionBigNotifyState.h"
using namespace PlayerData;

PlayerAnimationInstance::PlayerAnimationInstance()
	: mPlayer(nullptr)
	, mMainState(PlayerAnimationState::Idle)
	, bPlayAttackAnimation(false)
	, bIsPlayRollAnimation(false)
	, mPlayerAttackState(AttackID_NoAttack)
	, mHitReactionNames({ "Hit_Small","Hit_Big" })
{
	// 処理なし
}

void PlayerAnimationInstance::AnimationInit()
{	
	mPlayer = static_cast<Player*>(GetOwner());
	if (!mPlayer)
	{
		Cout<std::string>("キャストに失敗  PlayerAnimationInstance.cpp AnimationInit");
	}

	// 使用するアニメーションクリップの読み込み
	LoadUseAnimationClips();

	// 通知ステートの設定
	SetupNotify();
	
	// アニメーションクリップの設定
	SetupAnimationClip();
	
	// 納刀Idleアニメーションから開始
	mStateContext = TransitionContext<PlayerAnimationPulledState>();
	mStateContext->Entry();
}

void PlayerAnimationInstance::AnimationUpdate()
{
	mPlayerAttackState = mPlayer->GetCurrentAttackID();
	AnimationInstance::AnimationUpdate();	
}

void PlayerAnimationInstance::MainStateMachine()
{
	// ステートコンテキストのステートマシン処理
	mStateContext->StateMachine();

	// ステートによってコンテキストを切り替える
	switch (mMainState)
	{
	case PlayerAnimationState::Idle:
	{	
		// ステップステートに遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToStep();

		// 死亡ステートに遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToDeath();

		// ヒットリアクションステートへ遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToHitReaction();

		// 攻撃ステートへの遷移
		CheckTransitionToAttack();

		// ガードステートに遷移する
		CheckTransitionToGuard();

		break;
	}
	case PlayerAnimationState::Attack:
	{
		// 攻撃が終了したら抜刀ステートに戻る
		if (std::static_pointer_cast<PlayerAnimationAttackState>(mStateContext)->IsAttackEnd())
		{
			mMainState = PlayerAnimationState::Idle;
			mStateContext = TransitionContext<PlayerAnimationPulledState>();
			mStateContext->Entry();
			bPlayAttackAnimation = false;
		}
	
		// ステップステートに遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToStep();
		
		// 死亡ステートに遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToDeath();

		// ヒットリアクションステートへ遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToHitReaction();

		// ガードステートに遷移する
		CheckTransitionToGuard();

		break;
	}
	// 回避
	case PlayerAnimationState::Step:
	{
		// ステップアニメーション終了時にIdleへ遷移する	
		if (mPlayer->GetBehaviorState() == PlayerData::PlayerBehaviorState::State_IdleMove)
		{
			TransitionIdle();
			bIsPlayRollAnimation = false;
		}
		else if (mStateContext->IsNeedTransition())
		{
			TransitionIdle();
			bIsPlayRollAnimation = false;
		}

		// ヒットリアクションステートへ遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToHitReaction();

		// 死亡ステートに遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToDeath();

		// 攻撃ステートへの遷移
		CheckTransitionToAttack();

		// ガードステートに遷移する
		CheckTransitionToGuard();

		break;
	}
	case PlayerAnimationState::HitReaction:
	{
		// ヒットリアクションアニメーション終了時にIdleへ遷移する
		if (mStateContext->IsNeedTransition())
		{
			TransitionIdle();
		}
		// ステップアニメーション終了時にIdleへ遷移する	
		else if (mPlayer->GetBehaviorState() == PlayerData::PlayerBehaviorState::State_IdleMove)
		{
			TransitionIdle();
			bIsPlayRollAnimation = false;
		}
		break;
	}

	case PlayerAnimationState::Guard:
	{
		if (mStateContext->IsNeedTransition())
		{
			TransitionIdle();
		}
		else if (mPlayer->GetBehaviorState() == PlayerData::PlayerBehaviorState::State_IdleMove)
		{
			TransitionIdle();
		}

		// ヒットリアクションステートへ遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToHitReaction();

		// ステップステートに遷移するか確認 条件を満たしていれば遷移
		CheckTransitionToStep();

		// 攻撃ステートへの遷移
		CheckTransitionToAttack();

		break;
	}		
	}
}

void PlayerAnimationInstance::SetupNotify()
{
	// 攻撃データの取得
	std::shared_ptr<PlayerAttackData> attackData = mPlayer->GetAttackData().lock();

	// 0番目 AttackID_NoAttackは攻撃していない状態なのでアニメーションがないため AttackID_Y1からスタート
	for (uint16_t attack_i = AttackID_Y1; attack_i < AttackID_Max; attack_i++)
	{
		PlayerAttack attack = attackData->GetAttack(static_cast<AttackID>(attack_i));
		AttachCollisionActiveNotify(attack.mAnimationClipName, attack.mCollision);
		AttachInputAbleActiveNotify(attack.mAnimationClipName, attack.mInputAbleFrame);
	}
	mAnimationClips["Hit_Small"]->AddAnimationNotifyState<PlayerInputAbleNotifyState>(60, 108);

	// ステップアニメーションにコリジョンオフ用の通知ステートを設定
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_Y1));
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_Y2));
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_Y3));
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_Y4));
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_B3));
	mAnimationClips[attackData->GetAttack(PlayerData::AttackID_B3).mStepAnimationClipName]->AddAnimationNotifyState<PlayerStepNotifyState>(11, 18);

	// ヒットリアクションに吹っ飛び通知を付ける
	float blowEndFrame = GetAnimationClipByName(mHitReactionNames[CrossCharacter::HitReaction_Big])->GetDuration();
	GetAnimationClipByName(mHitReactionNames[CrossCharacter::HitReaction_Big])->AddAnimationNotifyState<PlayerHitReactionBigNotifyState>(0, static_cast<uint16_t>(blowEndFrame));

	// エフェクトを発生通知を付ける
	AttachEffectNotify
	(
		attackData->GetAttack(PlayerData::AttackID_Counter).mAnimationClipName,
		0,
		"assets/Player/Effect/CounterAttack.efkefc",
		{0.0f,5.0f,0.0f},
		{2.0f,2.0f,2.0f}
	);
}

void PlayerAnimationInstance::AttachStepNotify(const PlayerAttack& _attack)
{
	// コリジョンオブ通知ステート追加
	mAnimationClips[_attack.mStepAnimationClipName]->AddAnimationNotifyState<PlayerStepNotifyState>(11, 18);
	mAnimationClips[_attack.mLeftStepAnimationClipName]->AddAnimationNotifyState<PlayerStepNotifyState>(5, 12);
	mAnimationClips[_attack.mRightStepAnimationClipName]->AddAnimationNotifyState<PlayerStepNotifyState>(5, 12);

	// 入力可能通知ステート追加
	mAnimationClips[_attack.mStepAnimationClipName]->AddAnimationNotifyState<PlayerInputAbleNotifyState>(43, 65);
	mAnimationClips[_attack.mLeftStepAnimationClipName]->AddAnimationNotifyState<PlayerInputAbleNotifyState>(27, 40);
	mAnimationClips[_attack.mRightStepAnimationClipName]->AddAnimationNotifyState<PlayerInputAbleNotifyState>(27, 40);
}

void PlayerAnimationInstance::AttachCollisionActiveNotify(const std::string& _clipName, const PlayerAttackCollision& _collisionInf)
{
	// アニメーションクリップが存在する確認
	std::shared_ptr<SkeletalMeshAnimationClip> clip = GetAnimationClipByName(_clipName);
	if (!clip)
	{
		return;
	}

	for (const std::pair<uint16_t, uint16_t>& attachFrame : _collisionInf.mCollisionFrames)
	{
		clip->AddAnimationNotifyState
			<PlayerWeaponCollisionActiveNotifyState>
			(
				attachFrame.first,
				attachFrame.second
			);
	}	
}

void PlayerAnimationInstance::AttachInputAbleActiveNotify(const std::string& _clipName, const std::pair<uint16_t, uint16_t>& _attachFrame)
{
	// アニメーションクリップが存在する確認
	std::shared_ptr<SkeletalMeshAnimationClip> clip = GetAnimationClipByName(_clipName);
	if (!clip)
	{
		return;
	}

	clip->AddAnimationNotifyState
		<PlayerInputAbleNotifyState>
		(
			_attachFrame.first,
			_attachFrame.second
		);
}

void PlayerAnimationInstance::TransitionIdle()
{	
	mMainState = PlayerAnimationState::Idle;
	mStateContext = TransitionContext<PlayerAnimationPulledState>();
	mStateContext->Entry();	

	Logger::GetInstance().WriteLog("[Transition] To Pulled",1);
}

void PlayerAnimationInstance::CheckTransitionToDeath()
{
	if (mPlayer->IsDeath())
	{
		TransitionToDeath();
	}
}

void PlayerAnimationInstance::CheckTransitionToHitReaction()
{
	if (mPlayer->IsInHitReaction())
	{
		TransitionToHitReaction();
	}
}

void PlayerAnimationInstance::CheckTransitionToGuard()
{
	if (mPlayer->GetBehaviorState() == PlayerBehaviorState::State_Guard)
	{
		mStateContext = TransitionContext<PlayerAnimationGuardState>();
		mStateContext->Entry();
		mMainState = PlayerAnimationState::Guard;
	}
}

void PlayerAnimationInstance::CheckTransitionToAttack()
{
	// 攻撃ステートへの遷移
	if (mPlayerAttackState != AttackID_NoAttack)
	{
		TransitionToAttack();
	}
}

void PlayerAnimationInstance::TransitionToAttack()
{
	mMainState = PlayerAnimationState::Attack;
	mStateContext = TransitionContext<PlayerAnimationAttackState>();
	std::static_pointer_cast<PlayerAnimationAttackState>(mStateContext)->Entry(mPlayerAttackState);
	bPlayAttackAnimation = true;
}

void PlayerAnimationInstance::TransitionToDeath()
{
	mStateContext = TransitionContext<PlayerAnimationDeathState>();
	mStateContext->Entry();
	mMainState = PlayerAnimationState::Death;

	Logger::GetInstance().WriteLog("[Transition] To Death",1);
}

void PlayerAnimationInstance::TransitionToRoll()
{
	mStateContext = TransitionContext<PlayerAnimationRollState>();
	mStateContext->Entry();
	mMainState = PlayerAnimationState::Step;
	bIsPlayRollAnimation = true;

	Logger::GetInstance().WriteLog("[Transition] To Step",1);
}

void PlayerAnimationInstance::CheckTransitionToStep()
{
	if (mPlayer->IsRolling())
	{
		TransitionToRoll();
	}
}

void PlayerAnimationInstance::TransitionToHitReaction()
{
	mStateContext = TransitionContext<PlayerAnimationHitReactionState>();
	std::static_pointer_cast<PlayerAnimationHitReactionState>(mStateContext)->Entry(mHitReactionNames[mPlayer->GetHitReaction()]);
	mMainState = PlayerAnimationState::HitReaction;

	Logger::GetInstance().WriteLog("[Transition] To HitReaction",1);
}

void PlayerAnimationInstance::LoadUseAnimationClips()
{
	// 抜刀中アニメーション
	LoadAnimationClip("assets/Player/Animation/PulledRun.fbx", "PulledRun");
	LoadAnimationClip("assets/Player/Animation/Idle.fbx", "PulledIdle");

	// 死亡アニメーション
	LoadAnimationClip("assets/Player/Animation/Death.fbx", "Death");

	// 攻撃データの取得
	std::shared_ptr<PlayerAttackData> attackData = mPlayer->GetAttackData().lock();

	// アニメーションの読み込み	
	// フロントステップ
	LoadAnimationClip("assets/Player/Animation/Frontstep.fbx", "Roll");

	LoadAnimationClip(
		"assets/Player/Animation/Frontstep_Y2.fbx",
		attackData->GetAttack(AttackID_Y2).mStepAnimationClipName
	);
	
	LoadAnimationClip(
		"assets/Player/Animation/Frontstep_Y3.fbx",
		attackData->GetAttack(AttackID_Y3).mStepAnimationClipName
	);

	LoadAnimationClip(
		"assets/Player/Animation/Frontstep_Y4.fbx",
		attackData->GetAttack(AttackID_Y4).mStepAnimationClipName
	);

	LoadAnimationClip(
		"assets/Player/Animation/Frontstep_B3.fbx",
		attackData->GetAttack(AttackID_B3).mStepAnimationClipName
	);

	// レフトステップ
	LoadAnimationClip("assets/Player/Animation/Leftstep.fbx", "LeftStep");

	LoadAnimationClip(
		"assets/Player/Animation/Leftstep_Y2.fbx",
		attackData->GetAttack(AttackID_Y2).mLeftStepAnimationClipName
	);

	LoadAnimationClip(
		"assets/Player/Animation/Leftstep_Y3.fbx",
		attackData->GetAttack(AttackID_Y3).mLeftStepAnimationClipName
	);

	LoadAnimationClip(
		"assets/Player/Animation/Leftstep_Y4.fbx",
		attackData->GetAttack(AttackID_Y4).mLeftStepAnimationClipName
	);

	LoadAnimationClip(
		"assets/Player/Animation/LeftStepB3.fbx",
		attackData->GetAttack(AttackID_B3).mLeftStepAnimationClipName
	);

	// 右ステップ
	LoadAnimationClip("assets/Player/Animation/Rightstep.fbx", "RightStep");

	LoadAnimationClip(
		"assets/Player/Animation/Rightstep_AC2.fbx",
		attackData->GetAttack(AttackID_Y2).mRightStepAnimationClipName
	);

	LoadAnimationClip(
		"assets/Player/Animation/Rightstep_AC3.fbx",
		attackData->GetAttack(AttackID_Y3).mRightStepAnimationClipName
	);

	LoadAnimationClip(
		"assets/Player/Animation/Rightstep_AC4.fbx",
		attackData->GetAttack(AttackID_Y4).mRightStepAnimationClipName
	);

	LoadAnimationClip(
		"assets/Player/Animation/RightStepB3.fbx",
		attackData->GetAttack(AttackID_B3).mRightStepAnimationClipName
	);

	// 攻撃アニメーション
	// Yボタン
	LoadAnimationClip
	(
		"assets/Player/Animation/Attack_Y1.fbx",
		attackData->GetAttack(AttackID_Y1).mAnimationClipName
	);

	LoadAnimationClip
	(
		"assets/Player/Animation/Attack_Y2.fbx", 
		attackData->GetAttack(AttackID_Y2).mAnimationClipName
	);

	LoadAnimationClip
	(
		"assets/Player/Animation/Attack_Y3.fbx", 
		attackData->GetAttack(AttackID_Y3).mAnimationClipName
	);

	LoadAnimationClip
	(
		"assets/Player/Animation/Attack_Y4.fbx", 
		attackData->GetAttack(AttackID_Y4).mAnimationClipName
	);

	// Bボタン
	LoadAnimationClip
	(
		"assets/Player/Animation/Attack_B1.fbx", 
		attackData->GetAttack(AttackID_B1).mAnimationClipName
	);

	LoadAnimationClip
	(
		"assets/Player/Animation/Attack_B2.fbx", 
		attackData->GetAttack(AttackID_B2).mAnimationClipName
	);

	LoadAnimationClip
	(
		"assets/Player/Animation/Attack_B2_2.fbx", 
		attackData->GetAttack(AttackID_B2_2).mAnimationClipName
	);

	LoadAnimationClip
	(
		"assets/Player/Animation/Attack_B3.fbx", 
		attackData->GetAttack(AttackID_B3).mAnimationClipName
	);

	LoadAnimationClip
	(
		"assets/Player/Animation/Counter.fbx", 
		attackData->GetAttack(AttackID_Counter).mAnimationClipName
	);

	// ヒットリアクション
	LoadAnimationClip("assets/Player/Animation/Hit_Small.fbx", mHitReactionNames[CrossCharacter::HitReaction_Small]);
	LoadAnimationClip("assets/Player/Animation/Hit_Big.fbx", mHitReactionNames[CrossCharacter::HitReaction_Big]);
	// ガードアニメーション読み込み
	LoadAnimationClip("assets/Player/Animation/GuardStart.fbx", "GuardStart");
	LoadAnimationClip("assets/Player/Animation/StopGuarding.fbx", "StopGuard");
	LoadAnimationClip("assets/Player/Animation/Guarding.fbx", "Guarding");
	
	// ブレンドアニメーションクリップの作成
	float maxWalkSpeed = mPlayer->GetComponent<PlayerMovementComponent>()->GetMaxSpeed();
	mAnimationClips["PulledIdleToRun"] = std::make_shared<BlendAnimationClip>(mAnimationClips["PulledIdle"], mAnimationClips["PulledRun"], maxWalkSpeed, 0.0f, 0.0f);
}

void PlayerAnimationInstance::SetupAnimationClip()
{
	std::shared_ptr<PlayerAttackData> attackData = mPlayer->GetAttackData().lock();

	// 攻撃アニメーションクリップの設定
	for (uint16_t attack_i = AttackID::AttackID_Y1; attack_i < AttackID_Max; attack_i++)
	{
		std::string clipName = attackData->GetAttack(static_cast<AttackID>(attack_i)).mAnimationClipName;

		// アニメーションクリップが存在する確認
		std::shared_ptr<SkeletalMeshAnimationClip> clip = GetAnimationClipByName(clipName);
		if (clip)
		{
			mAnimationClips[clipName]->SetSynchroPosition(true);
		}		
	}

	mAnimationClips["Guarding"]->SetLoop(true);

	mAnimationClips["Roll"]->SetSynchroPosition(true);
	mAnimationClips["RightStep"]->SetSynchroPosition(true);
	mAnimationClips["LeftStep"]->SetSynchroPosition(true);

	mAnimationClips[attackData->GetAttack(AttackID_Y2).mStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y3).mStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y4).mStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_B3).mStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y2).mLeftStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y3).mLeftStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y4).mLeftStepAnimationClipName]->SetSynchroPosition(true);
    mAnimationClips[attackData->GetAttack(AttackID_B3).mLeftStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y2).mRightStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y3).mRightStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y4).mRightStepAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(AttackID_B3).mRightStepAnimationClipName]->SetSynchroPosition(true);

	mAnimationClips["PulledIdleToRun"]->SetLoop(true);

	// ルートからずれた位置から開始するアニメーションの設定
	// 攻撃
	mAnimationClips[attackData->GetAttack(AttackID_Y2).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y3).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y4).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B1).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B2_2).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B3).mAnimationClipName]->SetDisplaced(true);

	// ステップ
	mAnimationClips["Roll"]->SetDisplaced(true);
	mAnimationClips["RightStep"]->SetDisplaced(true);
	mAnimationClips["LeftStep"]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y2).mStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y3).mStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y4).mStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B3).mStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y2).mLeftStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y3).mLeftStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y4).mLeftStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B3).mLeftStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y2).mRightStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y3).mRightStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y4).mRightStepAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B3).mRightStepAnimationClipName]->SetDisplaced(true);
}

void PlayerAnimationInstance::AttachEffectNotify(std::string_view _clipName, const float _attachFrame, std::string_view _filePath, const DirectX::SimpleMath::Vector3 _offset, const DirectX::SimpleMath::Vector3 _scale)
{
	// アニメーションクリップがあるかを確認する
	std::shared_ptr<SkeletalMeshAnimationClip> clip = GetAnimationClipByName(_clipName.data());
	if (!clip)
	{
		return;
	}

	// 通知を付ける
    std::shared_ptr<PlayEffectNotify> notify = clip->AddAnimationNotify<PlayEffectNotify>(_attachFrame);
	notify->SetOffset(_offset);
	notify->SetScale(_scale);
	notify->LoadEffect(_filePath);
}