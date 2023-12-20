//---------- INCLUDES ------------
#include "PlayerStepState.h"
#include "../Player.h"
#include "../Animation/PlayerAnimationInstance.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../../Utility/MathLibrary.h"
#include "../Animation/Notify/PlayerInputAbleNotifyState.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"


PlayerStepState::PlayerStepState(Player* _player)
	: PlayerStateContext(_player)
{
	// �����Ȃ�
}

PlayerStepState::~PlayerStepState()
{
	// �����Ȃ�
}

void PlayerStepState::Entry()
{
	mbIsInputAble = false;

	// ���O�ɍs���Ă����v���C���[�̍U�����擾
	PlayerAttack attack = mPlayer->GetPrevAttack();

	// �U�����Ă��Ȃ���Βʏ�X�e�b�v
	if (attack.mAttackID == PlayerData::AttackID_NoAttack)
	{
		mPlayer->SetStepAnimationClipName("Roll");
		mPlayer->SetStepAnimationInterpStartTime(8.0f);
		mPlayer->SetIdleRunInterpTime(mPlayer->GetStepToIdleRunInterpTime());
		return;
	}

	// �v���C���[�̉E�����x�N�g���ƍ��X�e�B�b�N�̓|��Ă���������擾
	DirectX::SimpleMath::Vector3 rotation = mPlayer->GetComponent<TransformComponent>()->GetRotation();	
	DirectX::SimpleMath::Vector3 right = MathLibrary::GetRightVector(rotation);
	DirectX::SimpleMath::Vector3 controllerLStickDirection = mPlayer->GetCameraAlignedLStickDirection();
	controllerLStickDirection.Normalize();

	// �E�����x�N�g���ƃX�e�B�b�N�̓|��Ă�������œ��ς��Ƃ荶�E�ǂ���̃X�e�b�v�����邩���肷��
	float dot = right.Dot(controllerLStickDirection);
	
	// �E�X�e�b�v
	if (MathLibrary::InRange(dot, 0.75f, 1.0f))
	{
		// �g�p����X�e�b�v�A�j���[�V�����N���b�v���̃Z�b�g
		mPlayer->SetStepAnimationClipName(attack.mRightStepAnimationClipName);  
		// ��Ԃɂ����鎞�Ԃ̃Z�b�g
		mPlayer->SetStepAnimationInterpTime(attack.mAnimationInterp.mRightStepInterpTime);
		// ��Ԑ�ʒu�̃Z�b�g
		mPlayer->SetStepAnimationInterpStartTime(attack.mAnimationInterp.mRightStepInterpStartTime);
		// Idle�ւ̕�Ԃɂ����鎞�Ԃ̃Z�b�g
		mPlayer->SetIdleRunInterpTime(mPlayer->GetRightStepToIdleRunInterpTime());
	}
	// ���X�e�b�v
	else if (MathLibrary::InRange(dot, -1.0f, -0.75f))
	{
		// �g�p����X�e�b�v�A�j���[�V�����N���b�v���̃Z�b�g
		mPlayer->SetStepAnimationClipName(attack.mLeftStepAnimationClipName);
		// ��Ԃɂ����鎞�Ԃ̃Z�b�g
		mPlayer->SetStepAnimationInterpTime(attack.mAnimationInterp.mLeftStepInterpTime);
		// ��Ԑ�ʒu�̃Z�b�g
		mPlayer->SetStepAnimationInterpStartTime(attack.mAnimationInterp.mLeftStepInterpStartTime);
		// Idle�ւ̕�Ԃɂ����鎞�Ԃ̃Z�b�g
		mPlayer->SetIdleRunInterpTime(mPlayer->GetLeftStepToIdleRunInterpTime());
	}
	// �ʏ�X�e�b�v
	else
	{
		// �g�p����X�e�b�v�A�j���[�V�����N���b�v���̃Z�b�g
		mPlayer->SetStepAnimationInterpStartTime(attack.mAnimationInterp.mStepInterpStartTime);
		// ��Ԃɂ����鎞�Ԃ̃Z�b�g
		mPlayer->SetStepAnimationInterpTime(attack.mAnimationInterp.mStepInterpTime);
		// ��Ԑ�ʒu�̃Z�b�g
		mPlayer->SetStepAnimationClipName(attack.mStepAnimationClipName);
		// Idle�ւ̕�Ԃɂ����鎞�Ԃ̃Z�b�g
		mPlayer->SetIdleRunInterpTime(mPlayer->GetStepToIdleRunInterpTime());
	}
}

void PlayerStepState::Update()
{
	if (CheckAnimationEnd())
	{
		mbIsInputAble = true;
		mbNeedTransitionState = true;
		return;
	}

	mbIsInputAble = CheckInputAble();
}

bool PlayerStepState::CheckAnimationEnd()
{
	std::shared_ptr<AnimationPlayer> animPlayer = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance()->GetAnimationPlayer();
	return (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame());
}

bool PlayerStepState::CheckInputAble() const
{
	std::shared_ptr<AnimationInstance> animationInstance = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();

	// �A�j���[�V�������Đ�����Ă��邩���m�F
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
