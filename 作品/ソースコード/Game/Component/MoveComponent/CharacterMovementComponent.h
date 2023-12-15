/**
 * @file CharacterMovementComponent.h
 * @brief CharacterMovementComponentクラスの定義
 */

#pragma once

//--------- INCLUDES ----------
#include <SimpleMath.h>
#include "MoveComponent.h"

//-------- 前方宣言 ----------
class TransformComponent;

/**
* @class CharacterMovementComponent
* @brief CharacterMovementComponentクラスの定義
*/
class CharacterMovementComponent : public MoveComponent
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	CharacterMovementComponent();

	/**
	* デストラクタ
	*/
	~CharacterMovementComponent();

private:
	/** 最高速度 */
	float mMaxWalkSpeed;

	/** 初速 */
	float mInitSpeed;

	/** 最大加速度 */
	float mMaxAcceleration;

	/** 現在のスピード */
	DirectX::SimpleMath::Vector3 mCurrentVelocity;	

	/** 移動方向 */
	DirectX::SimpleMath::Vector3 mDirection;

	/** 初速 */
	DirectX::SimpleMath::Vector3 mInitVelocity;

	/** 移動始めてからの経過時間 */
	double mMoveElapsedTime;
	
	/** 今動いているか */
	bool bIsMoving;

	/** 移動の入力があったか */
	bool bIsMoveInput;

	/** 移動方向に回転を向けるか */
	bool bIsFaceDirection;

	/** 移動方向に回転向ける際の補間速度 */
	float mFaceDirectionInterpSpeed;

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
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime);
	
protected:
	/**
	* @fn FaceDirection
	* @brief 移動方向に回転を向ける
	* @return void
	*/
	void FaceDirection();
	
	/**
	* @fn Deceleration
	* @brief 減速の処理
	* @param const float (_deltaTime)
	* @return void
	*/
	virtual void Deceleration(const float deltaTime);

public:
	/**
	* @fn AddMovementInput
	* @brief 移動入力関数
	* @detail 与えられた移動方向ベクトルと、スケーリング値から初速を求める
	* @param const DirectX::SimpleMath::Vector3 (_direction)
	* @param float (_scaleValue)
	* @return void
	*/
	void AddMovementInput(DirectX::SimpleMath::Vector3 _direction, float _scaleValue = 1.0f);
	
	/**
	* @fn SetMaxAcceleration
	* @brief 最大加速度のセッター
	* @param const float (_maxAcceleration)
	* @return void
	*/
	inline void SetMaxAcceleration(const float _maxAcceleration);
	
	/**
	* @fn SetFaceDirectionInterpSpeed
	* @brief 移動方向にむく補間速度のセッター
	* @param const float (_interpSpeed)
	* @return void
	*/
	inline void SetFaceDirectionInterpSpeed(const float _interpSpeed);

	/**
	* @fn GetCurrentVelocity
	* @brief 現在の移動速度を返す
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetCurrentVelocity() const noexcept;

	/**
	* @fn SetMaxWalkSpeed
	* @brief 最大移動速度のセッター
	* @param const float (_maxWalkSpeed)
	* @return void
	*/
	inline void SetMaxWalkSpeed(const float _maxWalkSpeed) noexcept;

	/**
	* @fn GetMaxWalkSpeed
	* @brief 最大移動速度のゲッター
	* @return float
	*/
	inline float GetMaxWalkSpeed() const noexcept;

	/**
	* @fn GetFaceDirectionInterpSpeed
	* @brief 進行方向を向く補間速度のゲッター
	* @return float
	*/
	inline float GetFaceDirectionInterpSpeed() const noexcept;

};

//---------- INLINES ----------

inline void CharacterMovementComponent::SetMaxAcceleration(const float _maxAcceleration)
{
	mMaxAcceleration = _maxAcceleration;
}

inline void CharacterMovementComponent::SetFaceDirectionInterpSpeed(const float _interpSpeed)
{
	mFaceDirectionInterpSpeed = _interpSpeed;
}

inline DirectX::SimpleMath::Vector3 CharacterMovementComponent::GetCurrentVelocity() const noexcept
{
	return mCurrentVelocity;
}

inline void CharacterMovementComponent::SetMaxWalkSpeed(const float _maxWalkSpeed) noexcept
{
	mMaxWalkSpeed = _maxWalkSpeed;
}

inline float CharacterMovementComponent::GetMaxWalkSpeed() const noexcept
{
	return mMaxWalkSpeed;
}

inline float CharacterMovementComponent::GetFaceDirectionInterpSpeed() const noexcept
{
	return mFaceDirectionInterpSpeed;
}