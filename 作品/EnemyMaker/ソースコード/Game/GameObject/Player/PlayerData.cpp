#include "PlayerData.h"

PlayerAttack::PlayerAttack(PlayerData::AttackID _id, PlayerData::AttackID _nextY, PlayerData::AttackID _nextB, PlayerData::AttackID _nextRB, float _damage)
	: mAttackID(_id)
	, mNextY(_nextY)
	, mNextB(_nextB)
	, mDamage(_damage)
	, mAnimationInterp({})
{
	// èàóùÇ»Çµ
}

PlayerAttack::PlayerAttack()
	: mAttackID(PlayerData::AttackID_NoAttack)
	, mNextY(PlayerData::AttackID_Y1)
	, mNextB(PlayerData::AttackID_B1)
	, mDamage(0)
	, mAnimationInterp({})
{
	// èàóùÇ»Çµ
}


PlayerAttackCollision::PlayerAttackCollision()
	: mCollisionOccurrence(0)
{
	// èàóùÇ»Çµ
}

PlayerNextAnimationClipInterp::PlayerNextAnimationClipInterp()
	: mBAttackInterpStartTime(0.0f)
	, mYAttackInterpStartTime(0.0f)
	, mStepInterpStartTime(0.0f)
	, mRightStepInterpStartTime(0.0f)
	, mLeftStepInterpStartTime(0.0f)
	, mBAttackInterpTime(0.0f)
	, mYAttackInterpTime(0.0f)
	, mStepInterpTime(0.0f)
	, mRightStepInterpTime(0.0f)
	, mLeftStepInterpTime(0.0f)
	, mIdleMoveInterpTime(0.0f)
{
	// èàóùÇ»Çµ
}
