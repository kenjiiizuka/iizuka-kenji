/**
* @file  PlayerAnimationInstance.h
* @brief Playerのアニメーションインスタンス
*/

#pragma once

//---------- INCLUDES ---------
#include <array>
#include "../../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../PlayerData.h"

//--------- 前方宣言 ---------
class Player;
class CharacterMovementComponent;
class AnimationStateContext;

/** プレイヤーアニメーションのステートを表す */
enum class PlayerAnimationState : uint16_t
{
	Idle,        /**< 抜刀状態 */
	Attack,      /**< 攻撃中 */
	Step,        /**< 回避中 */
	HitReaction, /**< ダメージリアクション */
	Guard,       /**< ガード */
	Death        /**< 死亡 */
};

/**
* @class PlayerAnimationInstance
* @brief プレイヤーのアニメーションインスタンス
*        各ステートに合わせてアニメーションを遷移する
*/
class PlayerAnimationInstance : public AnimationInstance
{
public:
	/**
	* コンストラクタ
	*/
	PlayerAnimationInstance();

private:
	/** このアニムインスタを持つプレイヤー */
	Player* mPlayer;

	/** メインステート */
	PlayerAnimationState mMainState;

	/** プレイヤーが現在している攻撃 */
	PlayerData::AttackID mPlayerAttackState;

	/** 攻撃アニメーションが再生されているか */
	bool bPlayAttackAnimation;
	
	/** 回避アニメーションが再生されているか */
	bool bIsPlayRollAnimation;

	/** ヒットリアクションのアニメーションの名前を持つ */
	std::array<std::string, CrossCharacter::HitReaction_Max> mHitReactionNames;
public:
	/**
	 * @fn　AnimationInit
	 * @brief 初期化処理
	 * @return void
	*/
	void AnimationInit() override;
	
	/**
	 * @fn　AnimationUpdate
	 * @brief 初期化処理
	 * @return void
	*/
	void AnimationUpdate() override;

private:
	/**
	 * @fn　MainStateMachine
	 * @brief ステートマシン
	 * @return void
	*/
	void MainStateMachine() override;

	/**
	* @fn SetupNotifyState
	* @brief 通知をアニメーションに設定する
	* @return void
	*/
	void SetupNotify();

	/**
	* @fn AttachStepNotify
	* @brief ステップアニメーションに通知を設定する
	* @detail 攻撃からつながるステップアニメーションの名前を使用してアニメーションクリップを判断
	*         コリジョンオフ用、入力可能判断通知を付ける
	* @param const PlayerAttack& (_attack) 攻撃から派生するステップアニメーションの名前を取得する
	* @return void
	*/
	void AttachStepNotify(const PlayerAttack& _attack);

	/**
	* @fn AttachCollisionActiveNotify
	* @brief 渡された攻撃の情報から対応したアニメーションクリップにコリジョンのオンオフ切り替え通知を付ける
	* @param const std::string&           (_clipName)
	* @param const PlayerAttackCollision& (_collisionInf)
	* @return void
	*/
	void AttachCollisionActiveNotify(const std::string& _clipName, const PlayerAttackCollision& _collisionInf);

	/**
	* @fn AttachInputAbleActiveNotify
	* @brief 指定されたアニメーションクリップに入力受付フレームにする通知を付ける
	* @param const std::string&                   (_clipName)
	* @param const std::pair<uint16_t, uint16_t>& (_attachFrame)
	* @return void
	*/
	void AttachInputAbleActiveNotify(const std::string& _clipName, const std::pair<uint16_t, uint16_t>& _attachFrame);

	/**
	* @fn　SyncState
	* @brief プレイヤーのステートとアニメーションのステートを合わせる関数 納刀抜刀、回避ステートのあとにプレイヤーのステートに合わせるために使う
	* @return void
	*/
	void TransitionIdle();

	/**
	* @fn CheckTransitionToDeath
	* @brief 死亡ステートに移行するかを確認する関数
	* @return void
	*/
	void CheckTransitionToDeath();

	/**
	* @fn CheckTransitionToHitReaction
	* @brief ヒットリアクションステートに移行するかを確認する関数
	* @return void
	*/
	void CheckTransitionToHitReaction();

	/**
	* @fn CheckTransitionToGuard
	* @brief ガードステートに遷移するかを確認し、条件を満たしていれば遷移する関数
	* @return void
	*/
	void CheckTransitionToGuard();

	/**
	* @fn CheckTransitionToAttack
	* @brief 攻撃ステートに遷移するかを確認する関数
	* @return void
	*/
	void CheckTransitionToAttack();

	/**
	* @fn TransitionToAttack
	* @brief 攻撃ステートに遷移する
	* @return void
	*/
	void TransitionToAttack();

	/**
	* @fn TransitionToDeath
	* @brief 死亡ステートに切り替える関数
	* @return void
	*/
	void TransitionToDeath();

	/**
	 * @fn　TransitionToRoll
	 * @brief 現在のステートからRollステートに遷移する
	 * @return void
	*/
	void TransitionToRoll();

	/**
	* @fn CheckTransitionToStep
	* @brief ステップステートへ遷移するかを確認し、遷移条件を満たしていれば遷移する
	* @return void
	*/
	void CheckTransitionToStep();

	/**
	 * @fn　TransitionToHitReaction
	 * @brief 現在のステートからHitReactionステートに遷移する
	 * @return void
	*/
	void TransitionToHitReaction();

	/**
	* @fn LoadUseAnimationClips
	* @brief 使用するアニメーションクリップの読み込み
	* @return void
	*/
	void LoadUseAnimationClips();

	/**
	* @fn SetupAnimationClip
	* @brief アニメーションクリップの設定をする
	* @return void
	*/
	void SetupAnimationClip();

	/**
	* @fn SettingEffectNotify
	* @brief エフェクト再生通知を付ける
	* @param std::string_view (_clipName)
	* @param const float (_attachFrame)
	* @param std::string_view (_filePath)
	* @param const DirectX::SimpleMath::Vector3 (_offset)
	* @param const DirectX::SimpleMath::Vector3 (_scale)
	* @return void
	*/
	void AttachEffectNotify(std::string_view _clipName, const float _attachFrame, std::string_view _filePath, const DirectX::SimpleMath::Vector3 _offset, const DirectX::SimpleMath::Vector3 _scale);

public:
	/**
	 * @fn　GetIsAttack
	 * @brief 現在攻撃アニメーションが再生されているかを返す
	 * @return bool
	*/
	inline bool GetIsAttack();

	/**
	 * @fn　IsRolling
	 * @brief 回避アニメーションが再生されいるかを返す
	 * @return bool
	*/
	inline bool IsRolling();

	/**
	 * @fn　IsHitReaction
	 * @brief ヒットリアクション中か
	 * @return bool
	*/
	inline bool IsHitReaction();
};

//--------------------- INLINES -------------------------

inline bool PlayerAnimationInstance::GetIsAttack()
{
	return bPlayAttackAnimation;
}

inline bool PlayerAnimationInstance::IsRolling()
{
	return bIsPlayRollAnimation;
}

inline bool PlayerAnimationInstance::IsHitReaction()
{
	return (mMainState == PlayerAnimationState::HitReaction);
}