//---------- INCLUDES ----------
#include "PlayerCounterState.h"
#include "../Player.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../Weapon/PlayerWeapon.h"

PlayerCounterState::PlayerCounterState(Player* _player)
	: PlayerStateContext(_player)
	, mbFirstFrame(false)
{
	// �����Ȃ�
}

PlayerCounterState::~PlayerCounterState()
{
	// �����Ȃ�
}

void PlayerCounterState::Entry()
{
	mbIsInputAble = false;

	// �J�E���^�[�U���ɃZ�b�g����
	PlayerAttack attack = mPlayer->GetAttackData().lock()->GetAttack(PlayerData::AttackID_Counter);
	mPlayer->SetCurrentAttack(attack);

	// ����̓����蔻���傫������
	mPlayer->GetWeapon().lock()->SetCapsuleCollisionSize(6.0f,2.0f);

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

	// �J�E���^�[�A�j���[�V�������I�����Ă��邩���m�F����
	if (animPlayer->IsEndOnNextFrame() || !animPlayer->IsPlay())
	{
		mbNeedTransitionState = true;
		mbIsInputAble = true;

		// �����蔻��̃T�C�Y��ʏ�̃T�C�Y�ɖ߂�
		mPlayer->GetWeapon().lock()->SetDefaultCapsuleCollisionSize();
	}
}
