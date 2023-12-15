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
#include "Notify/PlayerWeaponCollisionActiveNotifyState.h"
#include "Notify/PlayerStepNotifyState.h"
#include "../../../Resource/BlendAnimationClip.h"
#include "../../../../System/Logger/Logger.h"

using namespace PlayerData;

PlayerAnimationInstance::PlayerAnimationInstance()
	: mPlayer(nullptr)
	, mMainState(PlayerAnimationState::Idle)
	, bPlayAttackAnimation(false)
	, bIsPlayRollAnimation(false)
	, mPlayerAttackState(AttackID_NoAttack)
	, mHitReactionNames({ "Hit_None", "Hit_Small","Hit_Medium", "Hit_Big" })
{
	// �����Ȃ�
}

void PlayerAnimationInstance::AnimationInit()
{	
	mPlayer = static_cast<Player*>(GetOwner());
	if (!mPlayer)
	{
		Cout<std::string>("�L���X�g�Ɏ��s  PlayerAnimationInstance.cpp AnimationInit");
	}

	// �g�p����A�j���[�V�����N���b�v�̓ǂݍ���
	LoadUseAnimationClips();

	// �ʒm�X�e�[�g�̐ݒ�
	SetupNotifyState();
	
	// �A�j���[�V�����N���b�v�̐ݒ�
	SetupAnimationClip();
	
	// �[��Idle�A�j���[�V��������J�n
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
	// �X�e�[�g�R���e�L�X�g�̃X�e�[�g�}�V������
	mStateContext->StateMachine();

	// �X�e�[�g�ɂ���ăR���e�L�X�g��؂�ւ���
	switch (mMainState)
	{
	case PlayerAnimationState::Idle:
	{	
		// �X�e�b�v�X�e�[�g�ɑJ�ڂ��邩�m�F �����𖞂����Ă���ΑJ��
		CheckTransitionToStep();

		// ���S�X�e�[�g�ɑJ�ڂ��邩�m�F �����𖞂����Ă���ΑJ��
		CheckTransitionToDeath();

		// �q�b�g���A�N�V�����X�e�[�g�֑J�ڂ��邩�m�F �����𖞂����Ă���ΑJ��
		CheckTransitionToHitReaction();

		// �U���X�e�[�g�ւ̑J��
		if (mPlayerAttackState != AttackID_NoAttack)
		{
			mMainState = PlayerAnimationState::Attack;
			mStateContext = TransitionContext<PlayerAnimationAttackState>();
			std::static_pointer_cast<PlayerAnimationAttackState>(mStateContext)->Entry(mPlayerAttackState);
			bPlayAttackAnimation = true;
		}
		break;
	}
	case PlayerAnimationState::Attack:
	{
		// �U�����I�������甲���X�e�[�g�ɖ߂�
		if (std::static_pointer_cast<PlayerAnimationAttackState>(mStateContext)->IsAttackEnd())
		{
			mMainState = PlayerAnimationState::Idle;
			mStateContext = TransitionContext<PlayerAnimationPulledState>();
			mStateContext->Entry();
			bPlayAttackAnimation = false;
		}
	
		// �X�e�b�v�X�e�[�g�ɑJ�ڂ��邩�m�F �����𖞂����Ă���ΑJ��
		CheckTransitionToStep();
		
		// ���S�X�e�[�g�ɑJ�ڂ��邩�m�F �����𖞂����Ă���ΑJ��
		CheckTransitionToDeath();

		// �q�b�g���A�N�V�����X�e�[�g�֑J�ڂ��邩�m�F �����𖞂����Ă���ΑJ��
		CheckTransitionToHitReaction();

		break;
	}
	// ���
	case PlayerAnimationState::Step:
	{
		// �X�e�b�v�A�j���[�V�����I������Idle�֑J�ڂ���
		if (mStateContext->IsNeedTransition())
		{
			TransitionIdle();
			bIsPlayRollAnimation = false;
		}

		// �q�b�g���A�N�V�����X�e�[�g�֑J�ڂ��邩�m�F �����𖞂����Ă���ΑJ��
		CheckTransitionToHitReaction();

		// ���S�X�e�[�g�ɑJ�ڂ��邩�m�F �����𖞂����Ă���ΑJ��
		CheckTransitionToDeath();

		break;
	}
	case PlayerAnimationState::HitReaction:
	{
		// �q�b�g���A�N�V�����A�j���[�V�����I������Idle�֑J�ڂ���
		if (mStateContext->IsNeedTransition())
		{
			TransitionIdle();	
		}
		break;
	}
	}
}

void PlayerAnimationInstance::SetupNotifyState()
{
	// �U���f�[�^�̎擾
	std::shared_ptr<PlayerAttackData> attackData = mPlayer->GetAttackData().lock();

	// 0�Ԗ� AttackID_NoAttack�͍U�����Ă��Ȃ���ԂȂ̂ŃA�j���[�V�������Ȃ����� AttackID_Y1����X�^�[�g
	for (uint16_t attack_i = AttackID_Y1; attack_i < AttackID_Max; attack_i++)
	{
		PlayerAttack attack = attackData->GetAttack(static_cast<AttackID>(attack_i));
		AttachCollisionActiveNotify(attack.mAnimationClipName, attack.mCollision);
		AttachInputAbleActiveNotify(attack.mAnimationClipName, attack.mInputAbleFrame);
	}

	mAnimationClips["Hit_Small"]->AddAnimationNotifyState<PlayerInputAbleNotifyState>(60, 108);

	// �X�e�b�v�A�j���[�V�����ɃR���W�����I�t�p�̒ʒm�X�e�[�g��ݒ�
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_Y1));
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_Y2));
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_Y3));
	AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_Y4));
	// AttachStepNotify(attackData->GetAttack(PlayerData::AttackID_B3));
	mAnimationClips[attackData->GetAttack(PlayerData::AttackID_B3).mStepAnimationClipName]->AddAnimationNotifyState<PlayerStepNotifyState>(11, 18);

}

void PlayerAnimationInstance::AttachStepNotify(const PlayerAttack& _attack)
{
	// �R���W�����I�u�ʒm�X�e�[�g�ǉ�
	mAnimationClips[_attack.mStepAnimationClipName]->AddAnimationNotifyState<PlayerStepNotifyState>(11, 18);
	mAnimationClips[_attack.mLeftStepAnimationClipName]->AddAnimationNotifyState<PlayerStepNotifyState>(5, 12);
	mAnimationClips[_attack.mRightStepAnimationClipName]->AddAnimationNotifyState<PlayerStepNotifyState>(5, 12);

	// ���͉\�ʒm�X�e�[�g�ǉ�
	mAnimationClips[_attack.mStepAnimationClipName]->AddAnimationNotifyState<PlayerInputAbleNotifyState>(43, 65);
	mAnimationClips[_attack.mLeftStepAnimationClipName]->AddAnimationNotifyState<PlayerInputAbleNotifyState>(27, 40);
	mAnimationClips[_attack.mRightStepAnimationClipName]->AddAnimationNotifyState<PlayerInputAbleNotifyState>(27, 40);
}

void PlayerAnimationInstance::AttachCollisionActiveNotify(const std::string& _clipName, const PlayerAttackCollision& _collisionInf)
{
	for (const std::pair<uint16_t, uint16_t>& attachFrame : _collisionInf.mCollisionFrames)
	{
		mAnimationClips[_clipName]->AddAnimationNotifyState
			<PlayerWeaponCollisionActiveNotifyState>
			(
				attachFrame.first,
				attachFrame.second
			);
	}	
}

void PlayerAnimationInstance::AttachInputAbleActiveNotify(const std::string& _clipName, const std::pair<uint16_t, uint16_t>& _attachFrame)
{
	mAnimationClips[_clipName]->AddAnimationNotifyState
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
	// �������A�j���[�V����
	LoadAnimationClip("assets/Player/Animation/PulledRun.fbx", "PulledRun");
	LoadAnimationClip("assets/Player/Animation/Idle.fbx", "PulledIdle");

	// ���S�A�j���[�V����
	LoadAnimationClip("assets/Player/Animation/Death.fbx", "Death");

	// �U���f�[�^�̎擾
	std::shared_ptr<PlayerAttackData> attackData = mPlayer->GetAttackData().lock();

	// �A�j���[�V�����̓ǂݍ���	
	// �t�����g�X�e�b�v
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

	// ���t�g�X�e�b�v
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

	// �E�X�e�b�v
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

	// �U���A�j���[�V����
	// Y�{�^��
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

	// B�{�^��
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

	// �q�b�g���A�N�V����
	LoadAnimationClip("assets/Player/Animation/Hit_Small.fbx", mHitReactionNames[CrossCharacter::HitReaction_Small]);

	// �u�����h�A�j���[�V�����N���b�v�̍쐬
	float maxWalkSpeed = mPlayer->GetComponent<PlayerMovementComponent>()->GetMaxSpeed();
	mAnimationClips["PulledIdleToRun"] = std::make_shared<BlendAnimationClip>(mAnimationClips["PulledIdle"], mAnimationClips["PulledRun"], maxWalkSpeed, 0.0f, 0.0f);
}

void PlayerAnimationInstance::SetupAnimationClip()
{
	std::shared_ptr<PlayerAttackData> attackData = mPlayer->GetAttackData().lock();

	// �U���A�j���[�V�����N���b�v�̐ݒ�
	for (uint16_t attack_i = AttackID::AttackID_Y1; attack_i < AttackID_Max; attack_i++)
	{
		std::string clipName = attackData->GetAttack(static_cast<AttackID>(attack_i)).mAnimationClipName;
		mAnimationClips[clipName]->SetSynchroPosition(true);
	}

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

	// ���[�g���炸�ꂽ�ʒu����J�n����A�j���[�V�����̐ݒ�
	// �U��
	mAnimationClips[attackData->GetAttack(AttackID_Y1).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y2).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y3).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_Y4).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B1).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B2).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B2_2).mAnimationClipName]->SetDisplaced(true);
	mAnimationClips[attackData->GetAttack(AttackID_B3).mAnimationClipName]->SetDisplaced(true);

	// �X�e�b�v
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
