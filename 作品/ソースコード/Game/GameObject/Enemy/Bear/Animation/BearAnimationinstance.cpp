#include "BearAnimationinstance.h"
#include "AnimationState/BearIdle_RunState.h"
#include "../BearEnemy.h"
#include "../BearEnemyAttackData.h"
#include "../Animation/Notify/BearWeaponCollisionActiveNotifyState.h"
#include "../../EnemyAttackCollisionAttachNotifyState.h"
#include "../../../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"
#include "../../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../../Component/MoveComponent/CharacterMovementComponent.h"
#include "../../../../Resource/BlendAnimationClip.h"
#include "../../../../../System/AnimationSystem/AnimationPlayer.h"
#include "../../../../GameObject/Camera/CameraShakeNotify.h"



BearAnimationInstance::BearAnimationInstance()
	: mbIsAttackAction(false)
	, mbIsMoveAction(false)
	, mEnemy(nullptr)	
	, mState(BearEnemyAnimationState::Idle_Run)
	, mToIdleRunInterpTime(0.0f)
{
	// 処理なし
}

BearAnimationInstance::~BearAnimationInstance()
{
	// 処理なし
}

void BearAnimationInstance::AnimationInit()
{
	mEnemy = static_cast<BearEnemy*>(GetOwner());

	// 攻撃データの取得
	std::shared_ptr<BearEnemyAttackData> attackData = std::static_pointer_cast<BearEnemyAttackData>(mEnemy->GetAttackData().lock());

	// 使用するアニメーションの読み込み
	LoadUseAnimationClips();

	// アニメーションの設定
	SetupAnimationClips();

	// アニメーション通知の設定
	SetupNotifies();
	
	
	// アニメーションの開始ステートの生成
	mStateContext = std::make_shared<BearIdle_RunState>(this);
	mStateContext->Entry();
	mState = BearEnemyAnimationState::Idle_Run;
}

void BearAnimationInstance::MainStateMachine()
{	
	switch (mState)
	{
	case BearEnemyAnimationState::Idle_Run:
		// 攻撃するなら攻撃ステートに遷移
		if(mbIsAttackAction)
		{
			mState = BearEnemyAnimationState::Attack;
		}

		if (mbIsMoveAction)
		{
			mState = BearEnemyAnimationState::Move;
		}
	
		// Hpが0以下なら死亡アニメーションに遷移
		if (mEnemy->GetStatus().mCurrentHp <= 0)
		{
			mState = BearEnemyAnimationState::Death;
			AnimationPlaySetting setting = 0;
			setting |= AnimationInf::AnimationPlayType::PlayType_LastFrameFreesze;
			PlayAnimationClip("Death");
		}
	
		break;
	case BearEnemyAnimationState::Attack:
	
		// IdleRunステートに移動
		if (!mbIsAttackAction)
		{
		 	mStateContext = TransitionContext<BearIdle_RunState>();
		 	mStateContext->Entry();
		 	mState = BearEnemyAnimationState::Idle_Run;
		}
	
		// Hpが0以下なら死亡アニメーションに遷移
		if (mEnemy->GetStatus().mCurrentHp <= 0)
		{
			mState = BearEnemyAnimationState::Death;
			AnimationPlaySetting setting = 0;
			setting |= AnimationInf::AnimationPlayType::PlayType_LastFrameFreesze;
			PlayAnimationClip("Death");
		}

		// 攻撃アニメーションが終了したらIdleに行く
		if (!mAnimPlayer.lock()->IsPlay())
		{
			mStateContext = TransitionContext<BearIdle_RunState>();
			mStateContext->Entry();
			mState = BearEnemyAnimationState::Idle_Run;
		}

		break;

	case BearEnemyAnimationState::Move:

		if (!mbIsMoveAction)
		{
			mStateContext = TransitionContext<BearIdle_RunState>();
			mStateContext->Entry();
			mState = BearEnemyAnimationState::Idle_Run;
		}

		// Hpが0以下なら死亡アニメーションに遷移
		if (mEnemy->GetStatus().mCurrentHp <= 0)
		{
			mState = BearEnemyAnimationState::Death;
			AnimationPlaySetting setting = 0;
			setting |= AnimationInf::AnimationPlayType::PlayType_LastFrameFreesze;
			PlayAnimationClip("Death");
		}

		break;

	case BearEnemyAnimationState::Death:
		// 死亡しているのでどのステートにも遷移しない

		break;
	}
}

void BearAnimationInstance::LoadUseAnimationClips()
{	
	// 攻撃データの取得
	std::shared_ptr<BearEnemyAttackData> attackData = std::static_pointer_cast<BearEnemyAttackData>(mEnemy->GetAttackData().lock());

	// アニメーションの読み込み
	LoadAnimationClip("assets/Enemy/Animation/Idle.fbx", "Idle");
	LoadAnimationClip("assets/Enemy/Animation/Death.fbx", "Death");
	LoadAnimationClip("assets/Enemy/Animation/Run.fbx", "Run");

	// 攻撃アニメーションの読み込み
	// 腕薙ぎ払い
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/Swiping.fbx",
		attackData->GetAttack(BearEnemyAttackData::ArmSmash).mAnimationClipName
	);

	// 武器振り弱
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/Slash_Weak.fbx",
		attackData->GetAttack(BearEnemyAttackData::ArmUpperSmash).mAnimationClipName
	);

	// 武器3連撃
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/ComboAttack.fbx",
		attackData->GetAttack(BearEnemyAttackData::TripleSlash).mAnimationClipName
	);

	// ジャンプ切り
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/JumpSlash.fbx",
		attackData->GetAttack(BearEnemyAttackData::JumpSlash).mAnimationClipName
	);

	// 武器振り下ろし
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/Downward.fbx",
		attackData->GetAttack(BearEnemyAttackData::DownwardSlash).mAnimationClipName
	);

	// 武器2連撃
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/2ChainAttack.fbx",
		attackData->GetAttack(BearEnemyAttackData::DoubleSlash).mAnimationClipName
	);

	// 武器2連撃 強
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/2ChainAttack_Strong.fbx",
		attackData->GetAttack(BearEnemyAttackData::DoubleSlash_Strong).mAnimationClipName
	);

	// 蹴り攻撃
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/Kick.fbx",
		attackData->GetAttack(BearEnemyAttackData::Kick).mAnimationClipName
	);


	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/RoarAttack.fbx",
		"RoarAttack"
	);

	// 武器振り上げ
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/SwordWingUp.fbx",
		attackData->GetAttack(BearEnemyAttackData::UpwardSlash).mAnimationClipName
	);

	// 後ろに武器を振って、前に武器を叩きつける攻撃
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/360Attack.fbx",
		attackData->GetAttack(BearEnemyAttackData::BackAndFrontSlash).mAnimationClipName
	);

	// 武器を振りおろし 強
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/DownwardStrong.fbx",
		attackData->GetAttack(BearEnemyAttackData::DownwardSlashStrong).mAnimationClipName
	);

	// 武器をを二連続で振る 強 低い
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/2ChainAttack_StrongLow.fbx",
		attackData->GetAttack(BearEnemyAttackData::DoubleSlash_StrongLow).mAnimationClipName
	);

	// 切り下がり
	LoadAnimationClip
	(
		"assets/Enemy/Animation/Attack/BackJumpSlash.fbx",
		attackData->GetAttack(BearEnemyAttackData::BackJumpSlash).mAnimationClipName
	);

	// 右振り向きアニメーション
	LoadAnimationClip("assets/Enemy/Animation/TurnRight90.fbx", "TurnRight");

	// 左振り向きアニメーション
	LoadAnimationClip("assets/Enemy/Animation/TurnLeft90.fbx", "TurnLeft");

	mAnimationClips["IdleToRun"] = std::make_shared<BlendAnimationClip>(mAnimationClips["Idle"], mAnimationClips["Run"], 20.0f, 0.0f, 0.0f);
	
}

void BearAnimationInstance::SetupNotifies()
{
	// 攻撃データの取得
	std::shared_ptr<BearEnemyAttackData> attackData = std::static_pointer_cast<BearEnemyAttackData>(mEnemy->GetAttackData().lock());

	// 武器を使用した攻撃
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::JumpSlash));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::DoubleSlash));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::DoubleSlash_Strong));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::TripleSlash));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::DownwardSlash));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::UpwardSlash));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::BackAndFrontSlash));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::DoubleSlash_StrongLow));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::DownwardSlashStrong));
	SettingAttackNotifyState(attackData->GetAttack(BearEnemyAttackData::BackJumpSlash));

	// 攻撃に当たり判定発生通知ステート追加
	SettingCollisionAttachNotifyState(attackData->GetAttack(BearEnemyAttackData::ArmSmash), "mixamorig:LeftForeArm", 4.0f, 3.0f);
	SettingCollisionAttachNotifyState(attackData->GetAttack(BearEnemyAttackData::Kick), "mixamorig:RightToeBase", 1.0f, 1.5f);
	SettingCollisionAttachNotifyState(attackData->GetAttack(BearEnemyAttackData::ArmUpperSmash), "mixamorig:LeftForeArm", 4.0f, 3.0f);

	// 画面振動あり攻撃
	SettingCameraShakeNotify(110, attackData->GetAttack(BearEnemyAttackData::JumpSlash), 0.3f, { 0.2f,1.0f });
	SettingCameraShakeNotify(152, attackData->GetAttack(BearEnemyAttackData::BackAndFrontSlash), 0.3f, { 0.1f,0.6f });
}

void BearAnimationInstance::SetupAnimationClips()
{
	// 攻撃データの取得
	std::shared_ptr<BearEnemyAttackData> attackData = std::static_pointer_cast<BearEnemyAttackData>(mEnemy->GetAttackData().lock());

	mAnimationClips["IdleToRun"]->SetLoop(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::JumpSlash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::ArmSmash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::TripleSlash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::DownwardSlash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::DoubleSlash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::DoubleSlash_Strong).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::UpwardSlash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::DoubleSlash_StrongLow).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::ArmUpperSmash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::BackAndFrontSlash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips[attackData->GetAttack(BearEnemyAttackData::BackJumpSlash).mAnimationClipName]->SetSynchroPosition(true);
	mAnimationClips["RoarAttack"]->SetSynchroPosition(true);
	mAnimationClips["TurnRight"]->SetSynchroRotation(true);
	mAnimationClips["TurnLeft"]->SetSynchroRotation(true);
}

void BearAnimationInstance::SettingAttackNotifyState(const EnemyAttack& _attackInformation)
{
	// 発生するコリジョンの数だけ通知を追加する
	for (size_t notify_i = 0; notify_i < _attackInformation.mCollisionOccurrence; notify_i++)
	{
		std::shared_ptr<BearWeaponCollisionActiveNotifyState> notifyState;
		notifyState = mAnimationClips[_attackInformation.mAnimationClipName]->AddAnimationNotifyState
			<BearWeaponCollisionActiveNotifyState>
			(
				_attackInformation.mCollisionFrames[notify_i].first,
				_attackInformation.mCollisionFrames[notify_i].second
			);
		notifyState->SetDamage(_attackInformation.mDamagePerCollision[notify_i]);
		notifyState->SetHitReaction(_attackInformation.mHitReactionPerCollision[notify_i]);
	}	
}

void BearAnimationInstance::SettingCollisionAttachNotifyState(const EnemyAttack& _attack, std::string_view _boneName, const float _height, const float _radius)
{
	for (size_t notify_i = 0; notify_i < _attack.mCollisionOccurrence; notify_i++)
	{
		std::shared_ptr<EnemyAttackCollisionAttachNotifyState> notifyState;
		notifyState = mAnimationClips[_attack.mAnimationClipName]->AddAnimationNotifyState
			<EnemyAttackCollisionAttachNotifyState>
			(
				_attack.mCollisionFrames[notify_i].first,
				_attack.mCollisionFrames[notify_i].second
			);
		notifyState->SetDamage(_attack.mDamagePerCollision[notify_i]);
		notifyState->SetCapsuleHeight(_height);
		notifyState->SetCapsuleRadius(_radius);
		notifyState->SetAttachBoneName(_boneName.data());
	}
}

void BearAnimationInstance::SettingCameraShakeNotify(const uint16_t _attachFrame, const EnemyAttack& _attack, const float _shakeTime, const DirectX::SimpleMath::Vector2 _shakeVector, const uint8_t _shakeLevel)
{
	std::shared_ptr<CameraShakeNotify> notify;
	notify = mAnimationClips[_attack.mAnimationClipName]->AddAnimationNotify<CameraShakeNotify>(_attachFrame);
	notify->SetShakeLevel(_shakeLevel);
	notify->SetShakeTime(_shakeTime);
	notify->SetShakeVector(_shakeVector);
}