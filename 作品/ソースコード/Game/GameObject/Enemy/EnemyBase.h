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
class EnemyBase : public GameObject , public IDamageAble
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

public:
	/**
	 * @fn TakenDamage
	 * @brief ダメージを受け取る関数
	 * @param float (_damage) ダメージ
	 * @return void
	*/
	void TakenDamage(float _damage) override;

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
