#include "EnemyData.h"

EnemyAttack::EnemyAttack()
	: mCollisionOccurrence(0)
{
	// 処理なし
}

EnemyAttack::EnemyAttack(const std::string& _animClipName, const uint8_t& _collisionOccurrence, const std::vector<float> _damagePerCollision, const std::vector<CrossCharacter::HitReaction> _hitReactionPerCollision)
	: mAnimationClipName(_animClipName)
	, mCollisionOccurrence(_collisionOccurrence)
	, mDamagePerCollision(_damagePerCollision)
	, mHitReactionPerCollision(_hitReactionPerCollision)
{
	// 処理なし
}

EnemyStatus::EnemyStatus()
	:mMaxHp(100.f)
	, mCurrentHp(100.f)
{
	// 処理なし
}

EnemyAttackExecutionConditions::EnemyAttackExecutionConditions()
	: mExecuteCheckCircleNum(0)
{
	// 処理なし
}
