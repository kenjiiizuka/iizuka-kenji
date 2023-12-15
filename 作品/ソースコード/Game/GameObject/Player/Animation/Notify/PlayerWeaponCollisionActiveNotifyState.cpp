//---------- INCLUDES ----------
#include "PlayerWeaponCollisionActiveNotifyState.h"
#include "../../Player.h"
#include "../../Weapon/PlayerWeapon.h"
#include "../../../../Resource/SkeletalMesh.h"
#include "../../../../Component/CollisionComponent/PlayerAttackCapsuleCollisionComponent.h"


PlayerWeaponCollisionActiveNotifyState::PlayerWeaponCollisionActiveNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(
		_attachAnimation,
		_attachStartFrame, 
		_attachEndFrame
	)
{
	// �����Ȃ�
}

PlayerWeaponCollisionActiveNotifyState::~PlayerWeaponCollisionActiveNotifyState()
{
	// �����Ȃ�
}

void PlayerWeaponCollisionActiveNotifyState::NotifyBegin()
{
	// �v���C���[�̕���̃R���W�������擾
	Player* player =  static_cast<Player*>(mSkeletalMesh.lock()->GetOwnerObject());
	mPlayerWeaponCollision = player->GetWeapon().lock()->GetComponent<PlayerAttackCapsuleCollisionComponent>();
	// �U���I���ɂ���
	mPlayerWeaponCollision.lock()->SetActiveCollision(true);
}

void PlayerWeaponCollisionActiveNotifyState::NotifyEnd()
{
	if (!mPlayerWeaponCollision.lock())
	{
		return;
	}
	mPlayerWeaponCollision.lock()->SetActiveCollision(false);
}


