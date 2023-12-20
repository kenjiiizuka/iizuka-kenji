#include "PlayerAttackState.h"
#include "../PlayerAttackData.h"
#include "../Player.h"
#include "../Animation/Notify/PlayerInputAbleNotifyState.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../Component/PlayerInputComponent/PlayerInputContollerComponent.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"
#include "../../../../System/InputSystem/XInput.h"

PlayerAttackState::PlayerAttackState(Player* _player)
	: PlayerStateContext(_player)
{
	// �����Ȃ�
}

PlayerAttackState::~PlayerAttackState()
{
	// �����Ȃ�
}

void PlayerAttackState::Entry()
{
	// ���͕s��Ԃɂ���
	mbIsInputAble = false;

	// �U���f�[�^���擾����
	mAttackData = mPlayer->GetAttackData();

	// �C���v�b�g�R���g���[���[���擾����
	std::shared_ptr<PlayerInputControllerComponent> inputController = mPlayer->GetControllerComponent().lock();
	
	// �v���C���[�̂���U�����Z�b�g����
	PlayerAttack attack;
	if (inputController->GetTrigger(PlayerInputControllerComponent::Operation_AttackB))
	{
		attack = mAttackData.lock()->GetNextBAttackInformation(PlayerData::AttackID_NoAttack);
	}
	else if (inputController->GetTrigger(PlayerInputControllerComponent::Operation_AttackY))
	{
		attack = mAttackData.lock()->GetNextYAttackInformation(PlayerData::AttackID_NoAttack);
	}
	mPlayer->SetCurrentAttack(attack);
	mPlayer->SetNextAttackInterpTime(0.0f);
	mPlayer->SetNextAttackInterpStartTime(0.0f);
	mPlayer->SetIdleRunInterpTime(attack.mAnimationInterp.mIdleMoveInterpTime);

	mInputController = inputController;
}

void PlayerAttackState::Update()
{
	// �U���A�j���[�V�������I���Ă��Ȃ������m�F
	// �I���Ă���΍U�����Ă��Ȃ���Ԃ��Z�b�g���ă��^�[��
	if(CheckAttackAnimationEnd())
	{
		mbIsInputAble = true;
		mbNeedTransitionState = true;
		return;
	}

	// ���͉\���𔻒f
	mbIsInputAble = CheckInputAble();

	// ���͉\�Ȃ�R���{�̏���������
	if (mbIsInputAble)
	{
		Comb();
	}
}

void PlayerAttackState::Exit()
{
	PlayerAttack noAttack = mAttackData.lock()->GetAttack(PlayerData::AttackID_NoAttack);
	mPlayer->SetAttackAble(true);
	mPlayer->SetCurrentAttack(noAttack);
	mPlayer->SetNextAttackInterpTime(0.0f);
}

bool PlayerAttackState::CheckAttackAnimationEnd()
{
	std::shared_ptr<AnimationInstance> animationInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	std::shared_ptr<AnimationPlayer> animPlayer = animationInstance->GetAnimationPlayer();
	
	// �Đ�����Ă��Ȃ��A���̃t���[���ŏI������ꍇ��true��Ԃ�
	return (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame());	
}

bool PlayerAttackState::CheckInputAble()
{
	std::shared_ptr<AnimationInstance> animationInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();

	// �A�j���[�V�������Đ�����Ă��邩���m�F�@�Đ�����Ă��Ȃ�������true
	std::shared_ptr<SkeletalMeshAnimationClip> animClip = animationInstance->GetAnimationPlayer()->GetPlayAnimation().lock();
	if (!animClip)
	{
		return true;
	}
	
	// �ʒm�����Ă��邩�m�F���ĂȂ���Γ��͕s��
	std::shared_ptr<PlayerInputAbleNotifyState> notify = animClip->GetAnimnotifyState<PlayerInputAbleNotifyState>();
	if (!notify)
	{
		return false;
	}

	// �ʒm������Βʒm������͉\�����󂯎��
	return notify->IsInputAble();
}

void PlayerAttackState::Comb()
{
	// ���͂�����Ύ��̍U���̏����擾����
	PlayerData::AttackID currentAttackID = mPlayer->GetCurrentAttackID();	

	std::shared_ptr<PlayerInputControllerComponent> inputController = mInputController.lock();

	// �{�^���̓��͂ɍ��킹�čU���̃f�[�^���Z�b�g����
	if (inputController->GetTrigger(PlayerInputControllerComponent::Operation_AttackY))
	{
		// ���̍U�����Ȃ���΍U���s�ɂ���
		PlayerData::AttackID nextY = mAttackData.lock()->GetAttack(currentAttackID).mNextY;
		if (nextY == PlayerData::AttackID_NoAttack)
		{
			mPlayer->SetAttackAble(false);
			return;
		}

		// ���̍U���̐ݒ�
		PlayerAttack attack = mAttackData.lock()->GetNextYAttackInformation(currentAttackID);
		mPlayer->SetCurrentAttack(attack);
 
		// ���O�̍U�����擾
		PlayerAttack prevAttack = mPlayer->GetPrevAttack();

		// ���̃A�j���[�V�����܂ŕ�Ԃɂ����鎞�Ԃ�ݒ� 
		mPlayer->SetNextAttackInterpTime(prevAttack.mAnimationInterp.mYAttackInterpTime);

		mPlayer->SetNextAttackInterpStartTime(prevAttack.mAnimationInterp.mYAttackInterpStartTime);

		// �A�C�h���ւ̕�Ԃɂ����鎞�Ԃ̃Z�b�g
		mPlayer->SetIdleRunInterpTime(attack.mAnimationInterp.mIdleMoveInterpTime);
	}
	else if (inputController->GetTrigger(PlayerInputControllerComponent::Operation_AttackB))
	{
		// ���̍U�����Ȃ���΍U���s�ɂ���
		PlayerData::AttackID nextB = mAttackData.lock()->GetAttack(currentAttackID).mNextB;
		if (nextB == PlayerData::AttackID_NoAttack)
		{
			mPlayer->SetAttackAble(false);
			return;
		}

		// ���̍U���̐ݒ�
		PlayerAttack attack = mAttackData.lock()->GetNextBAttackInformation(currentAttackID);
		mPlayer->SetCurrentAttack(attack);

		PlayerAttack prevAttack = mPlayer->GetPrevAttack();

		// ���̃A�j���[�V�����܂ŕ�Ԃɂ����鎞�Ԃ�ݒ� 
		mPlayer->SetNextAttackInterpTime(prevAttack.mAnimationInterp.mBAttackInterpTime);

		// ���ɃA�j���[�V�����̕�ԊJ�n�ʒu�̐ݒ�
		mPlayer->SetNextAttackInterpStartTime(prevAttack.mAnimationInterp.mBAttackInterpStartTime);

		// �A�C�h���ւ̕�Ԃɂ����鎞�Ԃ̃Z�b�g
		mPlayer->SetIdleRunInterpTime(attack.mAnimationInterp.mIdleMoveInterpTime);
	}	
}
