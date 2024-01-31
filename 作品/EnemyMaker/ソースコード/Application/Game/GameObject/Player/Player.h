/**
* @file  Player.h
* @brief Playerクラスの定義、そのほかプレイヤーに使う構造体なども定義されている
*/

#pragma once

//------------ INCLUDES -------------
#include <array>
#include <string>
#include "PlayerAttackData.h"
#include "../GameObject.h"
#include "PlayerStateObserver.h"
#include "PlayerStateController.h"

//----------- 前方宣言 ---------------
class PlayerMovementComponent;
class CapsuleCollisionComponent;
class PlayerWeapon;
class PlayerAnimationInstance;
class SkeletalMeshComponent;
class PrimitiveComponent;
class PlayerHitStopComponent;
class PlayerHpBer;
class PlayerInputControllerComponent;
class AudioComponent;
class EffectComponent;

/**
* @class Player
* @brief このゲームのプレイヤークラス
*/
class Player : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	Player();

	/**
	* デストラクタ
	*/
	~Player();

private:
	/** 戦闘開始フラグ */
	bool mbBattleStart;

	/** 最大体力 */
	float mMaxHp;

	/** 現在の体力 */
	float mCurrentHp;

	/** プレイヤーの状態を監視するオブザーバー */
	std::shared_ptr<PlayerStateObserver> mStateObserver;

	/** プレイヤーステートを切り替え、現在ステートの処理をするクラス */
	std::shared_ptr<PlayerStateController> mStateController;

	/** CharacterMoveComponentへの参照 */
	std::weak_ptr<PlayerMovementComponent> mMoveComp;

	/** SkeletalMeshComponentへの参照 */
	std::weak_ptr<SkeletalMeshComponent> mMeshComp;

	/** このプレイヤーの持っている武器の参照 */
 	std::weak_ptr<PlayerWeapon> mWeapon;

	/** ヒットストップコンポーネント */
	std::weak_ptr<PlayerHitStopComponent> mHitStopComp;

	/** カプセルコリジョンコンポーネント */
	std::weak_ptr<CapsuleCollisionComponent> mCollisionComp;

	/** アニメーションインスタンス */
	std::weak_ptr<PlayerAnimationInstance> mAnimInstance;

	/** HPバー */
	std::weak_ptr<PlayerHpBer> mHpBer;

	/** プレイヤーの入力を管理するコンポーネント */
	std::weak_ptr<PlayerInputControllerComponent> mInputController;

	/** ジャストガードした時の効果音 */
	std::weak_ptr<AudioComponent> mJustGuardAudio;

	/** ガードした時の効果音 */
	std::weak_ptr<AudioComponent> mGuardAudio;

	/** ガード時のエフェクト */
	std::weak_ptr<EffectComponent> mGuardEffect;

	/** ジャストガード時のエフェクト */
	std::weak_ptr<EffectComponent> mJustGuardEffect;

	/** 死亡しているかを判断する */
	bool mbIsDeath;

	/** カプセルコリジョンのオフセットトランスフォーム */
	Transform mCapsuleCollisionOffSet;

	/** カプセルコリジョンの半径 */
	float mCapsuleCollisionRadius;

	/** カプセルコリジョンの高さ */
	float mCapsuleCollisionHeight;

	/** カメラの方向に基づいた左スティックの倒れている方向 */
	DirectX::SimpleMath::Vector3 mCameraAlignedLStickDirection;

	/** ヒットリアクション */
	CrossCharacter::HitReaction mHitReaction;

	/** 攻撃情報 */
	std::shared_ptr<PlayerAttackData> mAttackData;

	/** 現在している攻撃 */
	PlayerAttack mCurrentAttack;

	/** 最後にした攻撃 */
	PlayerAttack mPrevAttack;

	/** Bボタン攻撃フラグ */
	bool mbIsBAttack;

	/** Yボタン攻撃フラグ */
	bool mbIsYAttack;

	/** 攻撃可能かを示すフラグ最後の攻撃が入力可能 */
	bool mbIsAbleAttack;

	/** ガード中の入力が続いているか */
	bool mbIsGuardInput;

	/** ジャストガードしてからカウンター可能時間 */
	double mCounterAbleTime;

	/** ジャストガードをしてからの経過時間 */
	double mJustGuardElapsedTime;

	/** プレイヤー現在の行動 */
	PlayerData::PlayerBehaviorState mBehavior;

	/** ダメージを受けた際の吹っ飛び方向 */
	DirectX::SimpleMath::Vector3 mBlowVector;

//---------- 以下アニメーション関連の値 ---------------

	/** 次の攻撃を再生する際の補間にかける時間 */
	float mNextAttackInterpTime;

	/** 次の攻撃のアニメーション開始位置 */
	float mNextAttackInterpStartTime;

	/** 回避アニメーション補間開始位置 */
	float mStepAnimationInterpStartTime;

	/** 回避アニメーションの補間にかける時間 */
	float mStepAnimationInterpTime;

	/** 攻撃からアイドルへの補間にかける時間 */
	float mIdleRunInterpTime;

	/** ステップからアイドルへの補間にかける時間 */
	float mStepToIdleRunInterpTime;

	/** 左ステップからアイドルへの補間にかける時間 */
	float mLeftStepToIdleRunInterpTime;

	/** 右ステップからアイドルへの補間にかける時間 */
	float mRightStepToIdleRunInterpTime;

	/** ステップアニメーションクリップの名前 攻撃ごとに使用するクリップが変えるため */
	std::string mStepAnimationClipName;

//------------------------------------------------------
public:	
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @return void
	*/
	void Init() override;

	/**
	 * @fn Update
	 * @brief 更新処理
	 * @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	 * @fn BeginHit
	 * @brief 何かにあったときの処理
	 * @param GameObject* (_hitObject)        当たったオブジェクト
	 * @param PrimitiveComponent* (_hitComp)  当たったコンポーネント
	 * @return void
	*/
	void BeginHit(GameObject* _hitedObject, PrimitiveComponent* _hitcomp) override;

private:
	/**
	* @fn SetupMoveComponent
	* @brief 移動コンポーネントの追加と設定をする
	* @return void
	*/
	void SetupMoveComponent();

	/**
	* @fn SetupSkeletalMeshComponent
	* @brief スケルタルメッシュコンポーネントの追加と設定をする
	* @return void
	*/
	void SetupSkeletalMeshComponent();

	/**
	* @fn SetupWeapon
	* @brief 武器の追加、設定をする
	* @return void
	*/
	void SetupWeapon();

	/**
	* @fn SetupCollision
	* @brief コリジョンの設定をする
	*/
	void SetupCollision();

	/**
	* @fn SetupAudio
	* @brief プレイヤーが使用するオーディオを読み込む
	* @return void
	*/
	void SetupAudio();

	/**
	* @fn SetupEffect
	* @brief エフェクトの読み込み初期化
	* @return void
	*/
	void SetupEffect();

	/**
	* @fn CheckState
	* @brief ステートを確認する
	* @detail controllerからの入力と、現在のステートからステートが変化するかを確認する
	* @return void
	*/
	void CheckState();

	/**
	* @fn CheckGuard
	* @brief ガードできているかを返す
	* @param const DirectX::SimpleMath::Vector3 (_hitCollisionPos)
	* @param float& (_damage)
	* @return PlayerData::GuardResult true ガード成功 false ガード失敗
	*/
	PlayerData::GuardResult CheckGuard(const DirectX::SimpleMath::Vector3 _hitCollisionPos, float& _damage);

	/**
	* @fn GuardingHit
	* @brief ガード中に攻撃をくらった時の処理
	* @param float& (_damage)                                       ダメージ
	* @param const DirectX::SimpleMath::Vector3 (_hitPosition)      ヒット位置
	* @param const const CrossCharacter::HitReaction (_hitReaction) くらった攻撃のヒットリアクション
	* @return void
	*/
	void GuardingHit(float& _damage, const DirectX::SimpleMath::Vector3 _hitPosition, const CrossCharacter::HitReaction _hitReaction);

	/**
	* @fn IsExecuteStep
	* @brief ステップを実行するか確認する関数
	* @return true ステップ実行 false 実行しない
	*/
	bool IsExecuteStep() const noexcept;

	/**
	* @fn IsExecuteAttack
	* @brief 攻撃を実行するか確認する
	* @detail 攻撃には複数のフラグが存在するので、関数内でフラグを立てています
	* @return true 実行 false 実行しない
	*/
	bool IsExecuteAttack() noexcept;
	
	/**
	* @fn IsExecuteGuard
	* @brief ガードを実行するか確認する
	* @return bool true 実行 false 実行しない
	*/
	bool IsExecuteGuard() const noexcept;

	/**
	* @fn IsExecuteCounter
	* @brief カウンターが実行可能かを確認する
	* @return bool 
	*/
	bool IsExecuteCounter() const noexcept;

	/**
	 * @fn　calculateCameraAlignedStickDirection
	 * @brief スティックの倒れている方向をカメラ向いてる方向に基づいて計算する関数
	 * @return void
	*/
	void CalculateCameraAlignedLStickDirection();

	/**
	 * @fn　TakenDamage
	 * @brief ダメージを受け取る関数
	 * @param float (_damage) ダメージ
	 * @return void
	*/
	void TakenDamage(float _damage);

	/**
	* @fn CheckHP
	* @brief HPがあるかないかの確認
	* @return bool true ある false なし
	*/
	bool CheckHP();

	/**
	* @fn CalcuBlowVector
	* @brief ヒットした位置から吹っ飛び方向を計算する
	* @param const DirectX::SimpleMath::Vector3& (_hitPosition) ヒットした位置
	* @return void
	*/
	void CalcuBlowVector(const DirectX::SimpleMath::Vector3& _hitPosition);

public:
	/**
	* @fn HutReaction
	* @brief デバッグ用のヒットリアクション関数
	* @param CrossCharacter::HitReaction (_hitReaction)
	* @return void
	*/
	void HitReaction_debug(CrossCharacter::HitReaction _hitReaction);

	/**
	* @fn InputAble_debug
	* @brief デバッグ用の入力可能状態ならプレイヤーの色がかわる
	* @return void
	*/
	void InputAble_debug();
	
	/**
	* @fn Recovery_debug
	* @brief デバッグ用の回復関数
	* @return void
	*/
	inline void Recovery_debug();

	/**
	* @fn Counter_debug
	* @brief カウンターをデバッグようにいつでも発動できるようにする処理
	* @return void
	*/
	inline void Counter_debug();

	/**
	* @fn Death_debug
	* @brief デバッグ用の死亡関数
	* @return void
	*/
	void Death_debug();

	

	/**
	* @fn SetCurrentAttack
	* @brief プレイヤーの攻撃のセット
	* @detail PlayerStateContextを継承しているクラスからのみの使用を想定しているそれ以外のクラスからの使用はしないように
	* @param const PlayerAttack& (_attack)
	* @return void
	*/
	inline void SetCurrentAttack(const PlayerAttack& _attack) noexcept;

	/**
	* @fn GetHitStopComponent
	* @brief ヒットストップコンポーネントを返す
	* @return std::weak_ptr<PlayerHitStopComponent>
	*/
	inline std::weak_ptr<PlayerHitStopComponent> GetHitStopComponent() const noexcept;

	/**
	* @fn GetCollisionComponent
	* @brief プレイヤーについているカプセルコリジョンコンポーネントを返す
	* @return std::weak_ptr<CapsuleCollisionComponent> 
	*/
	inline std::weak_ptr<CapsuleCollisionComponent> GetCollisionComponent() const noexcept;

	/**
	* @fn GetAttackData
	* @brief 攻撃データを返す
	* @return std::weak_ptr<PlayerAttackData>　攻撃データ
	*/
	inline std::weak_ptr<PlayerAttackData> GetAttackData() const noexcept;

	/**
	 * @fn　GetCurrentAttack
	 * @brief 現在している攻撃のゲッター
	 * @return PlayerAttackID
	*/
	inline PlayerData::AttackID GetCurrentAttackID() const; 
	
	/**
	* @fn GetCurrentAttack
	* @brief 現在行っている攻撃を取得する
	* @return PlayerAttack
	*/
	inline PlayerAttack GetCurrentAttack() const noexcept;

	/**
	 * @fn　GetCurrentAttackDamage
	 * @brief 現在している攻撃のダメージのゲッター
	 * @return float ダメージ
	*/
	inline float GetCurrentAttackDamage() const;

	/**
	 * @fn　GetWeapon
	 * @brief プレイヤーの武器のゲッター
	 * @return std::weak_ptr<Weapon>　プレイヤーの持っている武器
	*/
	std::weak_ptr<PlayerWeapon> GetWeapon();

	/**
	 * @fn　IsRolling
	 * @brief 回避しているかを返す
	 * @return bool 回避しているか
	*/
	inline bool IsRolling() const;
	
	/**
	 * @fn　IsInHitReaction
	 * @brief ヒットリアクション中なのかを返す
	 * @return bool true ヒットリアクション中 false ヒットリアクションしていない
	*/
	inline bool IsInHitReaction() const;

	/**
	* @fn IsDeath
	* @brief 死亡しているかを返す
	* @return bool true 死亡 false 死亡していない
	*/
	inline bool IsDeath() const noexcept;

	/**
	 * @fn　GetHitReaction
	 * @brief ヒットリアクションを返す
	 * @return HitReaction
	*/
	inline CrossCharacter::HitReaction GetHitReaction() const;

	/**
	* @fn GetRollAnimationInterpTime
	* @brief 回避アニメーションの補間開始位置を返す
	* @return float 回避アニメーションの補間開始位置
	*/
	inline float GetStepAnimationInterpStartTime() const noexcept;

	/**
	* @fn SetStepAnimationInterpTime
	* @brief ステップアニメーションの補間位置のセッター
	* @param const float (_interpTime)
	* @return void
	*/
	inline void SetStepAnimationInterpStartTime(const float _interpTime) noexcept;

	/**
	* @fn GetBehaviorState
	* @brief 現在の行動ステートを返す
	* @return PlayerEntities::PlayerBehaviorState　
	*/
	inline PlayerData::PlayerBehaviorState GetBehaviorState() const noexcept;

	/**
	* @fn IsYAttack
	* @brief Yボタン攻撃をしているのかを返す
	* @return bool true している false していない
	*/
	inline bool IsYAttack() const noexcept;

	/**
	* @fn IsBAttack
	* @brief Bボタン攻撃をしているのかを返す
	* @return true している false していない
	*/
	inline bool IsBAttack() const noexcept;

	/**
	* @fn GetCameraAlignedLStickDirection
	* @brief カメラの向きによって調整されたスティックの倒れている方向を取得する
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetCameraAlignedLStickDirection() const noexcept;

	/**
	* @fn SetBehaviorState
	* @brief プレイヤーの行動ステートをセットする
	* @detail StateObserverからのみ使用を想定しています
	* @return void
	*/
	inline void SetBehaviorState(PlayerData::PlayerBehaviorState _behavior);

	/**
	* @fn GetStepAnimationClipName
	* @brief 使用するステップアニメーションクリップの名前
	* @return std::string ステップアニメーションクリップのなまえ　
	*/
	inline std::string GetStepAnimationClipName() const noexcept;

	/**
	* @fn SetStepAnimationClipName
	* @brief ステップアニメーションクリップの名前をセットする
	* @param const std::string& (_clipName)
	* @return void
	*/
	inline void SetStepAnimationClipName(const std::string& _clipName) noexcept;

	/**
	* @fn BattleStart
	* @brief 戦闘開始関数
	* @return void
	*/
	inline void BattleStart() noexcept;

	/**
	* @fn IsAlive
	* @brief 生存しているかを返す
	* @return bool true 生存している false 生存していない
	*/
	inline bool IsAlive() const noexcept;

	/**
	* @fn SetAttackAble
	* @brief 攻撃可能かをセットする
	* @param const bool (_attackAble)
	* @return void
	*/
	inline void SetAttackAble(const bool _attackAble) noexcept;

	/**
	* @fn SetGuardInput
	* @brief ガードの入力をセットする
	* @param const bool (_guardInput)
	* @return void
	*/
	inline void SetGuardInput(const bool _guardInput) noexcept;

	/**
	* @fn GetGuardInput
	* @brief ガードの入力があるかを返す
	* @return bool 
	*/
	inline bool GetGuardInput() const noexcept;

	/**
	* @fn GetPrevAttack
	* @brief 前回していた攻撃のゲッター
	* @return PlayerAttack
	*/
	inline PlayerAttack GetPrevAttack() const noexcept;

	/**
	* @fn SetNextAttackInterpTime
	* @brief 次に攻撃に補完する際にかける時間のセッター
	* @param const float (_nextInterpTime)
	* @return void
	*/
	inline void SetNextAttackInterpTime(const float _nextInterpTime) noexcept; 

	/**
	* @fn GetNextAttackInterpTime
	* @brief 次に攻撃に補完する際にかける時間のゲッター
	* @return float
	*/
	inline float GetNextAttackInterpTime() const noexcept;

	/**
	* @fn SetStepAnimationInterpTime
	* @brief ステップアニメーションへの補間にかける時間のセッター
	* @param const float (_stepInterpTime)
	* @return void
	*/
	inline void SetStepAnimationInterpTime(const float _stepInterpTime) noexcept;

	/**
	* @fn GetStepAnimationInterpTime
	* @brief ステップアニメーションへの補間にかける時間を返す
	* @return float 
	*/
	inline float GetStepAnimationInterpTime() const noexcept;

	/**
	* @fn SetIdleRunInterpTime
	* @brief 攻撃からIdleRunアニメーションへの補間にかける時間のセッター
	* @param const float (_idleRunInterpTime)
	* @return void
	*/
	inline void SetIdleRunInterpTime(const float _idleRunInterpTime) noexcept;

	/**
	* @fn GetIdleRunInterpTime
	* @brief 攻撃からIdleRunアニメーションへの補間にかける時間のゲッター
	* @return float
	*/
	inline float GetIdleRunInterpTime() const noexcept;

	/**
	* @fn SetStepToIdleRunInterpTime
	* @brief ステップからアイドルランアニメーションへの補間にかける時間のセッター
	* @param (_interpTime)
	* @return void
	*/
	inline void SetStepToIdleRunInterpTime(const float _interpTime) noexcept;

	/**
	* @fn GetSetStepToIdleRunInterpTime
	* @brief ステップからアイドルランアニメーションへの補間にかける時間のゲッター
	* @return float
	*/
	inline float GetStepToIdleRunInterpTime() const noexcept;

	/**
	* @fn SetLeftStepToIdleRunInterpTime
	* @brief 左ステップからアイドルランアニメーションへの補間にかける時間のセッター
	* @param (_interpTime)
	* @return void
	*/
	inline void SetLeftStepToIdleRunInterpTime(const float _interpTime) noexcept;

	/**
	* @fn GetLeftSetStepToIdleRunInterpTime
	* @brief 左ステップからアイドルランアニメーションへの補間にかける時間のゲッター
	* @return float
	*/
	inline float GetLeftStepToIdleRunInterpTime() const noexcept;

	/**
	* @fn SetRightStepToIdleRunInterpTime
	* @brief 右ステップからアイドルランアニメーションへの補間にかける時間のセッター
	* @param (_interpTime)
	* @return void
	*/
	inline void SetRightStepToIdleRunInterpTime(const float _interpTime) noexcept;

	/**
	* @fn GetRightSetStepToIdleRunInterpTime
	* @brief 右ステップからアイドルランアニメーションへの補間にかける時間のゲッター
	* @return float
	*/
	inline float GetRightStepToIdleRunInterpTime() const noexcept;

	/**
	* @fn  SetNextAttackInterpStartTime
	* @brief 次の攻撃の補間開始位置のセッター
	* @param const float (_startTime)
	* @return void
	*/
	inline void SetNextAttackInterpStartTime(const float _startTime) noexcept;

	/**
	* @fn GetNextAttackInterpStartTime
	* @brief 次の攻撃の補間開始位置のゲッター
	* @return float 
	*/
	inline float GetNextAttackInterpStartTime() const noexcept;

	/**
	* @fn GetControllerComponent
	* @brief プレイヤーのインプットコントローラーコンポーネントへの弱参照を返す
	* @return std::weak_ptr<PlayerInputControllerComponent>
	*/
	inline std::weak_ptr<PlayerInputControllerComponent> GetControllerComponent() const noexcept;

	/**
	* @fn GetBlowVector
	* @brief 吹っ飛び方向ベクトルを返す
	* @return void
	*/
	inline DirectX::SimpleMath::Vector3 GetBlowVector() const noexcept;

};

//------------------- INLINES --------------------

inline void Player::Recovery_debug()
{
	mCurrentHp = mMaxHp;
}

inline void Player::Counter_debug()
{
	mJustGuardElapsedTime = 0.0f;
}

inline void  Player::SetCurrentAttack(const PlayerAttack& _attack) noexcept
{
	mPrevAttack = mCurrentAttack;
	mCurrentAttack = _attack;
}

inline std::weak_ptr<PlayerHitStopComponent> Player::GetHitStopComponent() const noexcept
{
	return mHitStopComp;
}

inline std::weak_ptr<CapsuleCollisionComponent> Player::GetCollisionComponent() const noexcept
{
	return mCollisionComp;
}

inline std::weak_ptr<PlayerAttackData> Player::GetAttackData() const noexcept
{
	return mAttackData;
}

inline PlayerData::AttackID Player::GetCurrentAttackID() const
{
	return mCurrentAttack.mAttackID;
}

inline PlayerAttack Player::GetCurrentAttack() const noexcept
{
	return mCurrentAttack;
}

inline float Player::GetCurrentAttackDamage() const
{	
	return mCurrentAttack.mDamage;	
}

inline bool Player::IsRolling() const
{
	return mBehavior == PlayerData::State_Step;
}

inline bool Player::IsInHitReaction() const
{
	return mBehavior == PlayerData::State_HitReaction;
}

inline bool Player::IsDeath() const noexcept
{
	return mbIsDeath;
}

inline CrossCharacter::HitReaction Player::GetHitReaction() const
{
	return mHitReaction;
}

inline float Player::GetStepAnimationInterpStartTime() const noexcept
{
	return mStepAnimationInterpStartTime;
}

inline void Player::SetStepAnimationInterpStartTime(const float _interpTime) noexcept
{
	mStepAnimationInterpStartTime = _interpTime;
}

inline PlayerData::PlayerBehaviorState Player::GetBehaviorState() const noexcept
{
	return mBehavior;
}

inline bool Player::IsYAttack() const noexcept
{
	return mbIsYAttack;
}

inline bool Player::IsBAttack() const noexcept
{
	return mbIsBAttack;
}

inline DirectX::SimpleMath::Vector3 Player::GetCameraAlignedLStickDirection() const noexcept
{
	return mCameraAlignedLStickDirection;
}

inline void Player::SetBehaviorState(PlayerData::PlayerBehaviorState _behavior)
{
	mBehavior = _behavior;
}

inline std::string Player::GetStepAnimationClipName() const noexcept
{
	return mStepAnimationClipName;
}

inline void Player::SetStepAnimationClipName(const std::string& _clipName) noexcept
{
	mStepAnimationClipName = _clipName;
}

inline void Player::BattleStart() noexcept
{
	mbBattleStart = true;
}

inline bool Player::IsAlive() const noexcept
{
	return mCurrentHp > 0;
}

inline void Player::SetAttackAble(const bool _attackAble) noexcept
{
	mbIsAbleAttack = _attackAble;
}

inline void Player::SetGuardInput(const bool _guardInput) noexcept
{
	mbIsGuardInput = _guardInput;
}

inline bool Player::GetGuardInput() const noexcept
{
	return mbIsGuardInput;
}

inline PlayerAttack Player::GetPrevAttack() const noexcept
{
	return mPrevAttack;
}

inline void Player::SetNextAttackInterpTime(const float _nextInterpTime) noexcept
{
	mNextAttackInterpTime = _nextInterpTime;
}

inline float Player::GetNextAttackInterpTime() const noexcept
{
	return mNextAttackInterpTime;
}

inline void Player::SetStepAnimationInterpTime(const float _stepInterpTime) noexcept
{
	mStepAnimationInterpTime = _stepInterpTime;
}

inline float Player::GetStepAnimationInterpTime() const noexcept
{
	return mStepAnimationInterpTime;
}

inline void Player::SetIdleRunInterpTime(const float _idleRunInterpTime) noexcept
{
	mIdleRunInterpTime = _idleRunInterpTime;
}

inline float Player::GetIdleRunInterpTime() const noexcept
{
	return mIdleRunInterpTime;
}

inline void Player::SetStepToIdleRunInterpTime(const float _interpTime) noexcept
{
	mStepToIdleRunInterpTime = _interpTime;
}

inline float Player::GetStepToIdleRunInterpTime() const noexcept
{
	return mStepToIdleRunInterpTime;
}

inline void Player::SetLeftStepToIdleRunInterpTime(const float _interpTime) noexcept
{
	mLeftStepToIdleRunInterpTime = _interpTime;
}

inline float Player::GetLeftStepToIdleRunInterpTime() const noexcept
{
	return mLeftStepToIdleRunInterpTime;
}

inline void Player::SetRightStepToIdleRunInterpTime(const float _interpTime) noexcept
{
	mRightStepToIdleRunInterpTime = _interpTime;
}

inline float Player::GetRightStepToIdleRunInterpTime() const noexcept
{
	return mRightStepToIdleRunInterpTime;
}

inline void Player::SetNextAttackInterpStartTime(const float _startTime) noexcept
{
	mNextAttackInterpStartTime = _startTime;
}

inline float Player::GetNextAttackInterpStartTime() const noexcept
{
	return mNextAttackInterpStartTime;
}

inline std::weak_ptr<PlayerInputControllerComponent> Player::GetControllerComponent() const noexcept
{
	return mInputController;
}

inline DirectX::SimpleMath::Vector3 Player::GetBlowVector() const noexcept
{
	return mBlowVector;
}
