/**
* @file BearAnimationInstance.h
* @brief BearAnimationInstanceクラスの定義
*/

#pragma once

//------------- INCLUDES ----------
#include "../../EnemyData.h"
#include "../../../../Component/SkeletalMeshComponent/AnimationInstance.h"

//---------- 前方宣言 -----------
class BearEnemy;

/** 熊の敵のアニメーションステート */
enum class BearEnemyAnimationState : uint8_t
{
	Idle_Run,    /**< 待機か走りの状態 */
	Attack,      /**< 攻撃 */
	Move,        /**< 移動 */
	Death,       /**< 死亡 */
	Flinch  /**< ヒットリアクション */
};

/**
* @class BearAnimationInstance
* @brief 熊の敵のアニメーションインスタンス
* @detail アニメーションの制御とアニメーションクリップへの通知付けなどをしている
*/
class BearAnimationInstance : public AnimationInstance
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BearAnimationInstance();

	/**
	* デストラクタ
	*/
	~BearAnimationInstance();

private:
	/** オーナーの熊の敵 */
	BearEnemy* mEnemy;

	/** 攻撃中 */
	bool mbIsAttackAction;

	/** 移動行動中 */
	bool mbIsMoveAction;

	/** アニメーションの現在のステート */
	BearEnemyAnimationState mState;

	/** アイドルランアニメーションへの補間にかける時間 */
	float mToIdleRunInterpTime;

public:
	/**
	 * @fn　AnimationInit
	 * @brief 初期化処理
	 * @return void
	*/
	void AnimationInit() override;

private:
	/**
	 * @fn　MainStateMachine
	 * @brief ステートマシン
	 * @return void
	*/
	void MainStateMachine() override;

	/**
	* @fn LoadClips
	* @brief 使用するアニメーションクリップを読み込む
	* @return void
	*/
	void LoadUseAnimationClips();

	/**
	* @fn CheckTransitionHitReaction
	* @brief 怯み値がたまっていればヒットリアクションに遷移する
	* @return void
	*/
	void CheckTransitionHitReaction();

	/**
	* @fn SetupNotifies
	* @brief アニメーションクリップに通知を設定する
	* @return void
	*/
	void SetupNotifies();

	/**
	* @fn SettingPlayEffectNotify
	* @brief エフェクト再生用の通知をアニメーションに付ける関数
	* @param std::string_view                   (_clipName)
	* @param std::string_view                   (_filePath)
	* @param const float                        (_attachFrame)
	* @param const DirectX::SimpleMath::Vector3 (_offset)
	* @param const DirectX::SimpleMath::Vector3 (_scale)
	* @return void
	*/
	void SettingPlayEffectNotify(std::string_view _clipName, std::string_view _filePath, const float _attachFrame, const DirectX::SimpleMath::Vector3 _offset = {0,0,0}, const DirectX::SimpleMath::Vector3 _sclae = {1,1,1});

	/**
	* @fn SetupAnimationClips
	* @brief アニメーションクリップの設定
	* @detail クリップのループ再生や、同期などの設定をする
	* @return void
	*/
	void SetupAnimationClips();

	/**
	* @fn SettingAttackNotify
	* @brief 武器のコリジョンのオンオフを切り替える通知ステートを設定する関数
	* @param const EnemyAttack& (_attackInformation) 攻撃情報が入った構造体
	* @return void
	*/
	void SettingAttackNotifyState(const EnemyAttack& _attack);

	/**
	* @fn SettingCollisionAttachNotifyState
	* @brief 攻撃用コリジョンをアタッチする通知ステートを設定する関数
	* @param const EnemyAttack& (_attack)
	* @param std::string_view (boneName)
	* @param const float (_height)
	* @param const float (_radius)
	* @return void
	*/
	void SettingCollisionAttachNotifyState(const EnemyAttack& _attack, std::string_view boneName, const float _height, const float _radius);

	/**
	* @fn SettingCameraShakeNotify
	* @brief カメラ振動通知を攻撃アニメーションに付ける関数
	* @param const uint16_t (_attachFrame)
	* @param const EnemyAttack& (_attack)
	* @param const float (_shakeTime)
	* @param const DirectX::SimpleMath::Vector2 (_shakeVector)
	* @param const const uint8_t (_shakeLevel)
	* @return void
	*/
	void SettingCameraShakeNotify(const uint16_t _attachFrame, const EnemyAttack& _attack, const float _shakeTime, const DirectX::SimpleMath::Vector2 _shakeVector, const uint8_t _shakeLevel = 1);

public:
	/**
	 * @fn　SetAttack
	 * @brief 攻撃しているかをセットする
	 * @param const bool (_isAttacking) 攻撃しているか
	 * @return void
	*/
	inline void SetAttack(const bool _isAttacking) noexcept;

	/**
	* @fn SetMove
	* @brief 移動しているかをセットする
	* @param const bool _isMoving
	* @return void
	*/
	inline void SetMove(const bool _isMoving) noexcept;

	/**
	* @fn SetToIdleRunInterpTime
	* @brief アイドルランへの補間にかける時間のセッター
	* @param const float (_interpTime)
	* @return void
	*/
	inline void SetToIdleRunInterpTime(const float _interpTime) noexcept;

	/**
	* @fn GetToIdleRunInterpTime
	* @brief アイドルランへの補間にかける時間のゲッター
	* @return float
	*/
	inline float GetToIdleRunInterpTime()const noexcept;

};

//------------------ INLINES ---------------

inline void BearAnimationInstance::SetAttack(const bool _isAttacking) noexcept
{
	mbIsAttackAction = _isAttacking;
}

inline void BearAnimationInstance::SetMove(const bool _isMoving) noexcept
{
	mbIsMoveAction = _isMoving;
}

inline void BearAnimationInstance::SetToIdleRunInterpTime(const float _interpTime) noexcept
{
	mToIdleRunInterpTime = _interpTime;
}

inline float BearAnimationInstance::GetToIdleRunInterpTime() const noexcept
{
	return mToIdleRunInterpTime;
}


