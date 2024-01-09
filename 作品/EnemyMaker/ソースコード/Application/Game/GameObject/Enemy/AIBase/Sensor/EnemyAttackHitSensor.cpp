//---------- INCLUDES -----------
#include "EnemyAttackHitSensor.h"
#include "../../../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"
#include "../../../Player/Player.h"

EnemyAttackHitSensor::EnemyAttackHitSensor()
	: mbIsHit(false)
	, mDamage(0)
{
	// 処理なし
}

EnemyAttackHitSensor::~EnemyAttackHitSensor()
{
	// 処理なし
}

void EnemyAttackHitSensor::Init()
{
	// 当たっていない状態がデフォルト
	mbIsHit = false;
	mDamage = 0;
}

void EnemyAttackHitSensor::Update()
{
	mbIsHit = false;
	mDamage = 0;

	// コリジョンがセットされているかを判断する
	if (mAttackCollisions.size() == 0)
	{
		return;
	}
	
	// プレイヤーに当たっているコリジョンがないか確認する
	for (std::weak_ptr<EnemyAttackCapsuleCollisionComponent> collision : mAttackCollisions)
	{
		// 参照が有効なのかを確認する　無効ならスキップ
		if (!collision.lock())
		{
			continue;
		}

		std::shared_ptr<EnemyAttackCapsuleCollisionComponent> validCollision = collision.lock();

		// 何かに当たっているのかを判断する 当たっていなかったらスキップ
		if (!validCollision->IsCurrentHit())
		{
			continue;
		}

		// プレイヤーにしかあたらないコリジョンなのでダメージをそのまま加算する
		mbIsHit = true;
		mDamage = validCollision->GetDamage();
	}
}