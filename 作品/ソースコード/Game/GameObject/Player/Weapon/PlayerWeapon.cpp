#include "PlayerWeapon.h"
#include "../Player.h"
#include "../../Enemy/EnemyBase.h"
#include "../../../Component/TransformComponent/TransformComponent.h"
#include "../../../Component/CollisionComponent/PlayerAttackCapsuleCollisionComponent.h"
#include "../../../../System/InputSystem/Input.h"
#include "../../../../System/FPSController/FPSController.h"
#include "../../../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"
#include "../../../Component/HitStopComponent/PlayerHitStopComponent.h"
#include "../../../Component/AudioComponent/AudioComponent.h"
#include "../../../Component/EffectComponent/EffectComponent.h"

PlayerWeapon::PlayerWeapon()
	: mPlayer(nullptr)
	, mCapsuleHeight(2.7f)
	, mCapsuleRadius(0.7f)
{
	// �����Ȃ�
}

void PlayerWeapon::Init(const std::string& _filePath, std::shared_ptr<Bone> _attachBone, std::shared_ptr<SkeletalMesh> _skeletalMesh)
{	
	Weapon::Init(_filePath, _attachBone, _skeletalMesh);

	mPlayer = static_cast<Player*>(mParent);

	// �����蔻��̐ݒ�
	mCollisionOffsetTransform = Transform({ 0.f,87.0f,0 }, { 1,1,1 }, { 0,0,0 });
	std::shared_ptr<PlayerAttackCapsuleCollisionComponent> collision = AddComponent<PlayerAttackCapsuleCollisionComponent>();
	collision->Init(mCapsuleHeight,mCapsuleRadius, 0.0f);
	collision->SetOffSetTransform(mCollisionOffsetTransform);

	// �����蔻��̃��C���[�ݒ�
	collision->SetCollisionChannel(Collision::Channel_PlayerAttack);
	CollisionTypes collisionTypes;
	collisionTypes[Collision::Channel_Player] = Collision::Type_None;
	collisionTypes[Collision::Channel_Enemy] = Collision::Type_Overlap;
	collisionTypes[Collision::Channel_EnemyAttack] = Collision::Type_None;
	collisionTypes[Collision::Channel_Movable] = Collision::Type_None;
	collisionTypes[Collision::Channel_Static] = Collision::Type_None;
	collision->SetCollisionTypes(collisionTypes);

	mCapsuleCollision = collision;

	std::shared_ptr<EffectComponent> hitEffect = AddComponent<EffectComponent>();
	hitEffect->Init("assets/Effect/HitEffect/HitEffect.efkefc");
	mHitEffect = hitEffect;


	std::shared_ptr<AudioComponent> hitSE = AddComponent<AudioComponent>();
	hitSE->Init("assets/Player/Audio/Hit.wav");
	mHitSE = hitSE;
}

void PlayerWeapon::Update(const double _deltaTime)
{
	Weapon::Update(_deltaTime);
}

void PlayerWeapon::BeginHit(GameObject* _hitObject, PrimitiveComponent* _hitComp)
{
	// �R���W�����������ɂȂ��Ă���Ώ������Ȃ�
	if (!mCapsuleCollision.lock()->IsActiveCollision())
	{
		return;
	}

	// �q�b�g�G�t�F�N�g
	mHitEffect.lock()->PlayEffect(_hitComp->GetTransform().mPosition);
	mPlayer->GetHitStopComponent().lock()->HitStop();

	// �G�l�~�[�Ȃ�_���[�W��`����
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(_hitObject);
	if (!enemy)
	{
		return;
	}
	float damage = mPlayer->GetCurrentAttackDamage();

	// �G�Ƀ_���[�W��^����
	enemy->TakenDamage(damage);
	
	// �A���œ����邱�Ƃ�h�����߂ɃR���W�������I�t�ɂ���
	mCapsuleCollision.lock()->SetActiveCollision(false);

	// ���������u�Ԃɉ���炷
	Transform trans = _hitComp->GetTransform();
	// mHitSE.lock()->PlaySound3D(trans.mPosition,trans.mRotation, 1.0f);
	mHitSE.lock()->PlaySound2D(0.2f);
}

