/**
* @file PlayerMovementComponent.h
* @brief PlayerMovementComponentクラスの定義
* 
*/

#pragma once

//--------- INCLUDES ---------
#include "MoveComponent.h"
#include <SimpleMath.h>

/**
* @class PlayerMovementComponent
* @brief プレイヤーの移動コンポーネント
*/
class PlayerMovementComponent : public MoveComponent
{
public:
	/**
	* コンストラクタ
	*/
	PlayerMovementComponent();

	/**
	* デストラクタ
	*/
	~PlayerMovementComponent();

private:	
	/** 移動入力があるか */
	bool mbMoveInput;

	/** 加速度 */
	float mAcceleration;

	/** 最大速度の達するまでの時間 */
	float mTimeToMaxSpeed;

	/** 移動開始してからの経過時間 */
	float mMoveElapsedTime;

	/** 最大移動速度 */
	float mMaxSpeed;

	/** 現在の目標の速度 */
	float mCurrentTargetSpeed;

	/** 現在の移動速度 */
	float mCurrentSpeed;

	/** スティックの倒れている方向 */
	DirectX::SimpleMath::Vector3 mStickDirection;

	/** 減速開始した時の移動速度 */
	DirectX::SimpleMath::Vector3 mDecelerationStartVelocity;

	/** 移動方向に向く補間速度 */
	float mFaceDirectionInterpSpeed;

	/** 現在の移動量 */
	DirectX::SimpleMath::Vector3 mCurrentVelocity;

public:
	/**
	* @fn Update
	* @brief 更新処理
	* @detail 移動の入力があれば速度をさいだい速度まで補間し
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override; 

private:
	/**
	* @fn Deceleration
	* @brief 減速の処理
	* @param const float (_deltaTime)
	* @return void
	*/
	void Deceleration(const float deltaTime);

	/**
	* @fn FaceDirection
	* @brief 移動方向に回転を向ける
	* @param const float (_deltaTime)
	* @return void
	*/
	void FaceDirection(const float _deltaTime);

	/**
	* @fn Movement
	* @brief 移動処理
	* @param const float (_deltaTime)
	* @return void 
	*/
	void Movement(const float _deltaTime);

public:
	/**
	* @fn AddMovementInput
	* @brief 移動入力関数
	* @param const DirectX::SimpleMath::Vector3 (_stickDirection) スティックの倒れている方向ベクトル
	* @return void
	*/
	void AddMovementInput(const DirectX::SimpleMath::Vector3 _stickDirection);

	/**
	* @fn MoveStop
	* @brief 移動を停止する関数
	* @return void
	*/
	void MoveStop();

	/**
	* @fn SetMaxSpeed
	* @brief 最大移動速度のセッター
	* @param const float (_maxSpeed)
	* @return void
	*/
	inline void SetMaxSpeed(const float _maxSpeed) noexcept;

	/**
	* @fn SetFaceDirectionInterpSpeed
	* @brief 移動方向にむく補間速度のセッター
	* @param const float (_interpSpeed)
	* @return void
	*/
	inline void SetFaceDirectionInterpSpeed(const float _interpSpeed);

	/**
	* @fn GetMaxSpeed
	* @brief 最大速度を返す
	* @return float 
	*/
	inline float GetMaxSpeed() const noexcept;

	/**
	* @fn GetCurrentVelocity
	* @brief 現在の移動速度を返す
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetCurrentVelocity() const noexcept;
};

//------------- INLINES ------------

inline void PlayerMovementComponent::SetMaxSpeed(const float _maxSpeed) noexcept
{
	mMaxSpeed = _maxSpeed;
}

inline void PlayerMovementComponent::SetFaceDirectionInterpSpeed(const float _interpSpeed)
{
	mFaceDirectionInterpSpeed = _interpSpeed;
}

inline float PlayerMovementComponent::GetMaxSpeed() const noexcept
{
	return mMaxSpeed;
}

inline DirectX::SimpleMath::Vector3 PlayerMovementComponent::GetCurrentVelocity() const noexcept
{
	return mCurrentVelocity;
}
