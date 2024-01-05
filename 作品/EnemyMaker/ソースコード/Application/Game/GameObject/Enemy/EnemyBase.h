/**
* @file  EnemyBase.h
* @brief EnemyBaseクラスの定義 エネミーに使う構造体などの定義がされている
*/

#pragma once

//--------- INCLUDES ----------
#include <list>
#include <mutex>
#include "../GameObject.h"
#include "../ObjectInterface/IDamageAble.h"
#include "EnemyData.h"


//---------- 前方宣言 ----------
class AnimationInstance;
class SkeletalMeshComponent;
class CharacterMovementComponent;
class EnemyAIComponent;
class HpBer;
class IEnemyAttackData;

/**
* @class EnemyBase
* @brief すべての敵の基底クラス
*/
class EnemyBase : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	EnemyBase();

private:
	/** 戦闘開始しているか判断するフラグ */
	bool mbBattleStart;

protected:
	/** ステータス構造体 */
	EnemyStatus mStatus;

	/** 攻撃データ */
	std::shared_ptr<IEnemyAttackData> mAttackData;

	/** スケルタルメッシュ */
	std::weak_ptr<SkeletalMeshComponent> mMesh;

	/** 移動コンポーネント */
	std::weak_ptr<CharacterMovementComponent> mCharacterMoveComp;

	/** AIコンポーネント */
	std::weak_ptr<EnemyAIComponent> mAIComponent;

	/** HPゲージ */
	std::weak_ptr<HpBer> mHpBer;

	/** 死亡フラグ */
	bool mbDeath;

	/** 怯み値 この値が最大値を超えていれば怯む */
	float mFlinch;

	/** 怯み値の最大値 */
	float mMaxFlinch;

	/** 怯み値減少速度 */
	float mFlinchDecreaseSpeed;

	/** 減少開始までにかかる時間 */
	float mFlinchDecreaseDelayTime;

	/** 怯みの上昇率 */
	float mFlinchUpRate;

	/** ダメージを受けてからの経過時間 */
	double mTakenDamageElapsedTime;

public:
	/**
	 * @fn Init
	 * @brief 初期化処理　必要なコンポーネントの追加
	 * @return void
	*/
	void Init();

	/**
	 * @fn Update
	 * @brief 更新処理
	 * @return void
	*/
	void Update(const double _deltaTime) override;

protected:
	/**
	* @fn SetupSkeletalMesh
	* @brief スケルタルメッシュの準備をする関数
	* @param const std::string& (_filePath)
	* @return void
	*/
	void SetupSkeletalMesh(const std::string& _filePath);

private:
	/**
	 * @fn Dead
	 * @brief 死亡した時の処理
	 * @return void
	*/
	void Dead();

	/**
	* @fn DecreaseFlinch
	* @brief 怯み値を時間経過で減少させていく関数
	* @param const double (_deltaTime)
	* @return void
	*/
	void DecreaseFlinch(const double deltaTime);

public:
	/**
	 * @fn TakenDamage
	 * @brief ダメージを受け取る関数
	 * @param const float (_damage) ダメージ
	 * @param const DirectX::SimpleMath::Vector3 (_hitPosition)
	 * @return void
	*/
	void TakenDamage(const float _damage , const DirectX::SimpleMath::Vector3 _hitPosition);

	/**
	* @fn BattleStart
	* @brief 戦闘開始をする関数
	* @return void
	*/
	void BattleStart() noexcept;

	/**
	* @fn BattleEnd
	* @brief 戦闘終了関数
	* @return void
	*/
	void BattleEnd() noexcept;

	/**
	 * @fn GetAnimationInstance
	 * @brief アニムインスタンスを取得する関数
	 * @return std::shared_ptr<AnimationInstance>
	*/
	std::shared_ptr<AnimationInstance> GetAnimationInstance();

	/**
	 * @fn GetStatus
	 * @brief ステータスのゲッター
	 * @return EnemyStatus ステータス
	*/
	inline EnemyStatus GetStatus() const;

	/**
	* @fn GetAttackData
	* @brief 攻撃データを返す
	* @return std::weak_ptr<IEnemyAttackData> 攻撃のデータ
	*/
	inline std::weak_ptr<IEnemyAttackData> GetAttackData() const noexcept;

	/**
	* @fn IsAlive
	* @brief 生存しているかを返す
	* @return bool true 生存している false 生存していない
	*/
	inline bool IsAlive() const noexcept;

	/**
	* @fn IsFlinch
	* @brief 怯み値がたまっていればtrueを返す
	* @return bool 
	*/
	inline bool IsFlinch() const noexcept;

	/**
	* @fn ResetFlinch
	* @brief 怯み値をリセットする
	* @detail 怯みアニメーション終了後にリセットするための関数
	*         リセットごとに、最大怯み値を上げる
	* @return void
	*/
	inline void ResetFlinch() noexcept;

};

//----------------- INLINES ----------------------

inline EnemyStatus EnemyBase::GetStatus() const
{
	return mStatus;
}

inline std::weak_ptr<IEnemyAttackData> EnemyBase::GetAttackData() const noexcept
{
	return mAttackData;
}

inline bool EnemyBase::IsAlive() const noexcept
{
	return mStatus.mCurrentHp > 0;
}

inline bool EnemyBase::IsFlinch() const noexcept
{
	return (mFlinch >= mMaxFlinch);
}

inline void EnemyBase::ResetFlinch() noexcept
{
	mFlinch = 0;
	mMaxFlinch += mMaxFlinch * mFlinchUpRate;
}
