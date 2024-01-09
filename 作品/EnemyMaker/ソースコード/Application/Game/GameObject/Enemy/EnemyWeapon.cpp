//----------- INCLUDES ------------
#include "EnemyWeapon.h"
#include "../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../ImGui/ImGuiUtility.h"

void EnemyWeapon::Init(const std::string& _filePath, std::shared_ptr<Bone> _attachBone, std::shared_ptr<SkeletalMesh> _skeletalMesh)
{
	Weapon::Init(_filePath, _attachBone, _skeletalMesh);

	// コリジョンの生成
	mCollisionOffsetTransform = { {0.0f,65.0f,0.0f},{1.0f,1.0f,1.0f},{0.0f,0.0,0.0f} };
	float capsuleHeight = 5.5f;
	float capsuleRadius = 2.5f;
	mAttackCollision = AddComponent<EnemyAttackCapsuleCollisionComponent>();
	mAttackCollision.lock()->Init(capsuleHeight, capsuleRadius, 50.0f, CrossCharacter::HitReaction_Small);
	mAttackCollision.lock()->SetOffSetTransform(mCollisionOffsetTransform);
	CollisionTypes collisionTypes;
	collisionTypes[Collision::Channel_Player] = Collision::Type_Overlap;
	collisionTypes[Collision::Channel_Enemy] = Collision::Type_None;
	collisionTypes[Collision::Channel_EnemyAttack] = Collision::Type_None;
	collisionTypes[Collision::Channel_Movable] = Collision::Type_None;
	collisionTypes[Collision::Channel_Static] = Collision::Type_None;
	mAttackCollision.lock()->SetCollisionTypes(collisionTypes);

	mAttackCollision.lock()->SetDebugDraw(true);
}

void EnemyWeapon::SetCollisonActive(bool _active)
{
	mAttackCollision.lock()->SetActiveCollision(_active);
}

void EnemyWeapon::SetDamage(float _damage)
{
	mAttackCollision.lock()->SetDamage(_damage);
}

