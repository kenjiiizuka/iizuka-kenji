/**
* @file PlayerData.h
* @brief プレイヤーに必要な列挙型やなどを定義したファイル
*/


#pragma once

//----------- INCLUDES ----------------
#include <string>
#include <vector>
#include "../CrossCharacterData.h"


/**
* @namespace
* @brief プレイヤーに使用する列挙型を定義している
* @detail 配列の添え字として使用したい列挙型を名前衝突を防ぐために名前空間内に定義しています
*/
namespace PlayerData
{
	/** プレイヤーの攻撃 */
	enum AttackID : uint8_t
	{	
		AttackID_NoAttack = 0,  /**< 攻撃なし,していない */
		AttackID_Y1,            /**< Yボタン 1 */
		AttackID_Y2,            /**< Yボタン 2 */
		AttackID_Y3,            /**< Yボタン 3 */
		AttackID_Y4,            /**< Yボタン 4 */
		AttackID_B1,            /**< Bボタン 1 */
		AttackID_B2,            /**< Bボタン 2 */
		AttackID_B2_2,          /**< Bボタン パターン２ */
		AttackID_B3,            /**< Bボタン 3 */
		AttackID_Max,           /**< 攻撃最大数 */	
	};	

	/**
	* @enum PlayerBehaviorState
	* @brief プレイヤーのステートを表した列挙型
	*/
	enum PlayerBehaviorState : uint8_t
	{
		State_Attack      = 0, /**< 攻撃 */
		State_Step        = 1, /**< ステップ回避 */
		State_HitReaction = 2, /**< ヒットリアクション中 */
		State_IdleMove    = 3, /**< 待機、移動*/
		State_Death       = 4  /**< 死亡 */
	};
}



/**
* @struct PlayerAttackCollision
* @brief プレイヤーの攻撃のコリジョンの情報を持つ構造体
* @detail コリジョンの発生タイミングと発生回数を持つ
*/
struct PlayerAttackCollision
{
	uint8_t mCollisionOccurrence;                                  /**< コリジョンの発生回数 */
	std::vector<std::pair<uint16_t, uint16_t>> mCollisionFrames;   /**< コリジョン発生ごとの発生タイミング */

	/**
	* デフォルトコンストラクタ
	*/
	PlayerAttackCollision();
};

/**
* @struct PlayerNextAnimationClipInterpTime
* @detail プレイヤーの攻撃の次のアニメーションの補間開始位置の時間
*/
struct PlayerNextAnimationClipInterp
{
	float mYAttackInterpStartTime;             /**< 次のY攻撃の補間開始位置 */
	float mBAttackInterpStartTime;             /**< 次のB攻撃の補間開始位置 */
	float mStepInterpStartTime;                /**< ステップの補間開始位置 */
	float mRightStepInterpStartTime;           /**< 右ステップの補間開始位置 */
	float mLeftStepInterpStartTime;            /**< 左ステップの補間開始位置 */
	float mYAttackInterpTime;                  /**< 次のY攻撃への補間にかける時間 */
	float mBAttackInterpTime;                  /**< 次のB攻撃への補間にかける時間 */
	float mStepInterpTime;                     /**< ステップへの補間にかける時間 */
	float mLeftStepInterpTime;                 /**< 左ステップへの補間にかける時間 */
	float mRightStepInterpTime;                /**< 右ステップへの補間にかける時間 */
	float mIdleMoveInterpTime;                 /**< アイドルへの補間にかける時間 */

	/**
	 * デフォルトコンストラクタ
	*/
	PlayerNextAnimationClipInterp();
};

/**
* @struct PlayerAttack
* @brief プレイヤーの攻撃の情報を持つ構造体
* @detail コンボ、ダメージ、当たり判定の発生回数、発生タイミング、使用するアニメーションクリップの名前
*/
struct PlayerAttack
{
	PlayerData::AttackID mAttackID;                      /**< 攻撃ID */
	PlayerData::AttackID mNextY;                         /**< 次のYボタンの攻撃のID */
	PlayerData::AttackID mNextB;                         /**< 次のBボタンの攻撃のID */
	std::string mAnimationClipName;                          /**< 使用するアニメーションクリップ */
	std::string mLeftStepAnimationClipName;                  /**< 左ステップアニメーションクリップの名前 */
	std::string mRightStepAnimationClipName;                 /**< 右ステップアニメーションクリップの名前 */
	std::string mStepAnimationClipName;                      /**< ステップアニメーションクリップの名前 */
	PlayerAttackCollision mCollision;                        /**< コリジョンの情報 */
	PlayerNextAnimationClipInterp mAnimationInterp; /**< アニメーション補間開始位置 */
	std::pair<uint16_t, uint16_t> mInputAbleFrame;           /**< 入力受付フレーム */
	float mDamage;                                           /**< この攻撃のダメージ */

	/**
	* 攻撃の情報をすべて設定できるコンストラクタ
	*
	* @param[in] PlayerAttackID (_id) この攻撃のID
	* @param[in] PlayerAttackID (_nextComboID)
	* @param[in] float (_damage) この攻撃の攻撃力
	*/
	PlayerAttack(PlayerData::AttackID _id, PlayerData::AttackID _nextY, PlayerData::AttackID _nextB, PlayerData::AttackID _nextRB, float _damage);

	/**
	* 値の初期化
	*/
	PlayerAttack();
};

/** プレイヤーのステート */
enum class PlayerState : uint16_t
{
	Pulled,     /**< 抜刀中ステート */
	Attack,     /**< 攻撃中ステート */
	HitReaction /**< ヒットリアクションステート */
};
