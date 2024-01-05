//---------- INCLUDES ---------
#include "PlayerGuardState.h"
#include "../Player.h"
#include "../../../Component/PlayerInputComponent/PlayerInputContollerComponent.h"
#include "../../../Component/MoveComponent/PlayerMovementComponent.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../Resource/SkeletalMeshAnimationClip.h"

PlayerGuardState::PlayerGuardState(Player* _player)
	: PlayerStateContext(_player)
	, mGuardStartElapsedTime(0.0f)
	, mJustGuardSuccessTime(0.3f)
	, mbGuardEnd(false)
{
	// �����Ȃ�
}

PlayerGuardState::~PlayerGuardState()
{
	// �����Ȃ�
}

void PlayerGuardState::Entry()
{
	mbIsInputAble = false;
	mInputController = mPlayer->GetComponent<PlayerInputControllerComponent>();
	mPlayer->SetGuardInput(true);
}

void PlayerGuardState::Update()
{
	// ���͂��I�����Ă���΁A�X�e�[�g�̏I���J�ڂ̔��f������@
	if (mbGuardEnd)
	{
		// �A�j���[�V�������I�����Ă���΃X�e�[�g��ύX����
		if (CheckGuardAnimationFinish())
		{
			mbIsInputAble = true;
			mbNeedTransitionState = true;
		}
		
		// �ړ����͂�����ΏI��
		if (XInput::IsLeftStickInputAble())
		{
			DirectX::SimpleMath::Vector3 direction = mPlayer->GetCameraAlignedLStickDirection();
			mPlayer->GetComponent<PlayerMovementComponent>()->AddMovementInput(direction);
			mbIsInputAble = true;
			mbNeedTransitionState = true;
		}
	}

	// �K�[�h�̓��͂��I���Ă��邩���m�F����
	if (!mInputController.lock()->IsInput(PlayerInputControllerComponent::Operation_Guard))
	{
		mbGuardEnd = true;
		mbIsInputAble = true;
		mPlayer->SetGuardInput(false);
	}

	mGuardStartElapsedTime += mPlayer->GetCustomDeltaTime();
}

void PlayerGuardState::Exit()
{
	mPlayer->SetGuardInput(false);
}

bool PlayerGuardState::CheckGuardAnimationFinish()
{
	std::shared_ptr<AnimationPlayer> animPlayer = mPlayer->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance()->GetAnimationPlayer();
	return (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame());
}

PlayerData::GuardResult PlayerGuardState::CheckGuard(const DirectX::SimpleMath::Vector3 _attackPosition) const noexcept
{
	std::shared_ptr<TransformComponent> playerTrans = mPlayer->GetComponent<TransformComponent>();

	// �v���C���[����U���ʒu�ւ̒P�ʃx�N�g�����v�Z
	DirectX::SimpleMath::Vector3 toAttack = _attackPosition - playerTrans->GetPosition();
	toAttack.Normalize();

	// �U�������ƃv���C���[�̑O�����x�N�g���̓��ς��A�K�[�h�\�͈͂𒴂��Ă��Ȃ����𔻒f����
	float dot = playerTrans->GetForwardVector().Dot(toAttack);

	// ����180�x�K�[�h�\
	if (dot >= 0.0)
	{
		// �W���X�K�ł��Ă��邩�̊m�F
		if (mGuardStartElapsedTime <= mJustGuardSuccessTime)
		{
			return PlayerData::GuardResult::Result_JustGuard;
		}

		// �ʏ�K�[�h
		return PlayerData::GuardResult::Result_Guard;
	}

	// �K�[�h���s
	return PlayerData::GuardResult::Result_Faild;
}

