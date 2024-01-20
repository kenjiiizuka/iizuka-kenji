/**
* @file  EnemyData.h
* @brief エネミーに使用する列挙型や構造体を定義したファイル
*/

#pragma once

//----------- INCLUDES ------------
#include <stdint.h>
#include <string>
#include <vector>
#include "../CrossCharacterData.h"

/** エネミーのステータスに関数するパラメーターを保持したデータ */
struct EnemyStatus
{
	float mCurrentHp; /**< 現在の体力 */
	float mMaxHp;     /**< 最大体力 */

	/*
	* 値の初期化
	*/
	EnemyStatus();

	/**
	 * @fn GetCurrentHpRatio
	 * @brief 現在のHPの割合を返す関数
	 * @return float 現在のHPの割合
	*/
	inline float GetCurrentHpRatio();
};


inline float EnemyStatus::GetCurrentHpRatio()
{
	return mCurrentHp / mMaxHp;
}


/**
* @struct EnemyAttackExecutionConditions
* @brief 攻撃の実行条件データをもつ構造体
*/
struct EnemyAttackExecutionConditions
{
	/**
	* デフォルトコンストラクタ
	*/
	EnemyAttackExecutionConditions();
	
	uint8_t mExecuteCheckCircleNum;   /** 実行判定用円の数 */	
	std::vector<float> mCircleRadius; /** 実行判定円の長さ */	
	std::vector<float> mAngle;        /** 実行円を出す位置へのエネミーからみた角度 */	
	std::vector<float> mDistance;     /** 実行円を出す位置までの距離 */
};

/**
* @struct EnemyAttack
* @brief 敵の攻撃のデータを持つ構造体
*/
struct EnemyAttack
{
	/**
	* デフォルトコンストラクタ 
	*/
	EnemyAttack();

	/**
	* コンストラクタ
	* 
	* @param const std::string&                            (_animClipName)
	* @param const uint8_t&                                (_collisionOccurrence)
	* @param const std::vector<float>&                     (_damagePerCollision)
	* @param const std:vector<CrossCharacter::HitReaction> (_hitReactionPerCollision)
	*/
	EnemyAttack(const std::string& _animClipName, const uint8_t& _collisionOccurrence, const std::vector<float> _damagePerCollision, const std::vector<CrossCharacter::HitReaction> _hitReactionPerCollision);

	std::string mAnimationClipName;                                    /**< この攻撃に使用するアニメーションクリップの名前 */
	uint8_t mCollisionOccurrence;                                      /**< コリジョンの発生回数 */
	std::vector<float> mDamagePerCollision;                            /**< コリジョンごとのダメージ */
	std::vector<CrossCharacter::HitReaction> mHitReactionPerCollision; /**< コリジョンごとのヒットリアクション */
	std::vector<std::pair<uint16_t, uint16_t>> mCollisionFrames;       /**< コリジョンごとのコリジョンの発生のフレーム間 std::pair<startFrame, endFrame> */
	EnemyAttackExecutionConditions mExecutionCondition;                /**< この攻撃の実行条件 */
	float mToIdleRunInterpTime;                                        /**< この攻撃からIdleRunアニメーションへの補間にかける時間 */	
};




