#pragma once // インクルードガード

/**
* @file EnemyAttackHitSensor.h
* @brief EnemyAttackHitSensorクラスの定義
*/

//-------- INCLUDES ---------
#include <memory>
#include <vector>

//-------- 前方宣言 ---------
class EnemyAttackCapsuleCollisionComponent; // エネミーの攻撃用当たり判定クラス

/**
* @class EnemyAttackHitSensor
* @brief エネミーの攻撃が当たったか当たっていないかを観察して結果を持つ
* @detail 渡されたエネミーの攻撃コリジョンを観察し、プレイヤーに当たっているかを判断する
*         コリジョンは複数でも可能で、その際はどれか一つが当たっていれば当たっていることなる
*/
class EnemyAttackHitSensor final
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	EnemyAttackHitSensor();

	/**
	* デフォルトデストラクタ
	*/
	~EnemyAttackHitSensor();

private:
	/** 実行している攻撃の当たり判定 */
	std::vector<std::weak_ptr<EnemyAttackCapsuleCollisionComponent>> mAttackCollisions;
	
	/** ヒットしているか */
	bool mbIsHit;

	/** ヒットしたコリジョンのダメージ */
	float mDamage;

public:
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @return void
	*/
	void Init();

	/**
	 * @fn Update
	 * @brief 更新処理
	 * @detail セットされている当たり判定を観察し、当たっているかを判断する
	 * @return void
	*/
	void Update();

	/**
	 * @fn SetCollision
	 * @brief 観察したいコリジョンを複数セットする関数
	 * @param const std::vector<std::weak_ptr<EnemyAttackCapsuleCollisionComponent>> _attackCollisions
	 * @return void
	*/
	inline void SetCollision(const std::vector<std::weak_ptr<EnemyAttackCapsuleCollisionComponent>> _attackCollisions);

	/**
	 * @fn SetCollision
	 * @brief 観察したいコリジョンをセットする関数
	 * @param const std::weak_ptr<EnemyAttackCapsuleCollisionComponent> _attackCollision
	 * @return void
	*/
	inline void SetCollision(const std::weak_ptr<EnemyAttackCapsuleCollisionComponent> _attackCollision);

	/**
	 * @fn IsCollisionHit
	 * @brief 攻撃がヒットしたかを返す
	 * @return bool true ヒット false ヒットしていない
	*/
	inline bool IsCollisionHit() const noexcept;

	/**
	 * @fn GetHitDamage
	 * @brief ヒットしたコリジョンのダメージを返す
	 * @return float
	*/
	inline float GetHitDamage() const noexcept;

};

//---------- INLINES ---------
inline void EnemyAttackHitSensor::SetCollision(const std::vector<std::weak_ptr<EnemyAttackCapsuleCollisionComponent>> _attackCollisions)
{
	mAttackCollisions = _attackCollisions;
}

inline void EnemyAttackHitSensor::SetCollision(const std::weak_ptr<EnemyAttackCapsuleCollisionComponent> _attackCollision)
{
	// 複数すでにセットされている場合のためにクリアする
	mAttackCollisions.clear();
	mAttackCollisions.push_back(_attackCollision);
}

inline bool EnemyAttackHitSensor::IsCollisionHit() const noexcept
{
	return mbIsHit;
}

inline float EnemyAttackHitSensor::GetHitDamage() const noexcept
{
	return mDamage;
}
