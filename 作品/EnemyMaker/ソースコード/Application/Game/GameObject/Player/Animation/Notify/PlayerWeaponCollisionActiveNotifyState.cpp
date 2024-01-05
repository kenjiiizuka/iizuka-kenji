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
	// 処理なし
}

PlayerWeaponCollisionActiveNotifyState::~PlayerWeaponCollisionActiveNotifyState()
{
	// 処理なし
}

void PlayerWeaponCollisionActiveNotifyState::NotifyBegin()
{
	// プレイヤーの武器のコリジョンを取得
	Player* player =  static_cast<Player*>(mSkeletalMesh.lock()->GetOwnerObject());
	mPlayerWeaponCollision = player->GetWeapon().lock()->GetComponent<PlayerAttackCapsuleCollisionComponent>();
	// 攻撃オンにする
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


