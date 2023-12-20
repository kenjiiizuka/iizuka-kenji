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
	// 処理なし
}

void PlayerWeapon::Init(const std::string& _filePath, std::shared_ptr<Bone> _attachBone, std::shared_ptr<SkeletalMesh> _skeletalMesh)
{	
	Weapon::Init(_filePath, _attachBone, _skeletalMesh);

	mPlayer = static_cast<Player*>(mParent);

	// 当たり判定の設定
	mCollisionOffsetTransform = Transform({ 0.f,87.0f,0 }, { 1,1,1 }, { 0,0,0 });
	std::shared_ptr<PlayerAttackCapsuleCollisionComponent> collision = AddComponent<PlayerAttackCapsuleCollisionComponent>();
	collision->Init(mCapsuleHeight,mCapsuleRadius, 0.0f);
	collision->SetOffSetTransform(mCollisionOffsetTransform);

	// 当たり判定のレイヤー設定
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
	// コリジョンが無効になっていれば処理しない
	if (!mCapsuleCollision.lock()->IsActiveCollision())
	{
		return;
	}

	// ヒットエフェクト
	mHitEffect.lock()->PlayEffect(_hitComp->GetTransform().mPosition);
	mPlayer->GetHitStopComponent().lock()->HitStop();

	// エネミーならダメージを伝える
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(_hitObject);
	if (!enemy)
	{
		return;
	}
	float damage = mPlayer->GetCurrentAttackDamage();

	// 敵にダメージを与える
	enemy->TakenDamage(damage);
	
	// 連続で当たることを防ぐためにコリジョンをオフにする
	mCapsuleCollision.lock()->SetActiveCollision(false);

	// 当たった瞬間に音を鳴らす
	Transform trans = _hitComp->GetTransform();
	// mHitSE.lock()->PlaySound3D(trans.mPosition,trans.mRotation, 1.0f);
	mHitSE.lock()->PlaySound2D(0.2f);
}

