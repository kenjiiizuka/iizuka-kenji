/**
* @file MoveComponent.h
* @brief MoveComponentクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "../Component.h"

//--------- 前方宣言 --------
class TransformComponent;

/**
* @class MoveComponent
* @brief オブジェクトの移動をするコンポーネント
* @detail オーナーのトランスフォームコンポーネントを動かしている
*/
class MoveComponent : public Component
{
public:
	/**
	* コンストラクタ
	*/
	MoveComponent();

	/**
	* デストラクタ
	*/
	~MoveComponent();

protected:
	/** 移動速度 */
	float mMoveSpeed;

	/** 回転速度 */
	float mRotationSpeed;
	
	/** オーナーのトランスフォームコンポーネント */
	std::weak_ptr<TransformComponent> mOwnerTransform;

public:		
	/**
	* @fn Init
	* @brief 初期化処理
	*/
	void Init() override;
	
	/**
	* @fn MoveForward
	* @brief オーナーオブジェクトを前にすすませる
	* @detail 設定されたMoveSpeedと_scaleValueを乗算して移動量を求めている
	*         deltaTimeは関数内で乗算している
	* @param const float (_scaleValue)
	* @return void
	*/
	virtual void MoveForward(const float _scaleValue);

	/**
	* @fn MoveRight
	* @brief オーナーオブジェクトを右にすすませる
	* @detail 設定されたMoveSpeedと_scaleValueを乗算して移動量を求めている
	*         deltaTimeは関数内で乗算している
	* @param const float (_scaleValue)
	* @return void
	*/
	virtual void MoveRight(const float _scaleValue);

	/**
	* @fn MoveRight
	* @brief オーナーオブジェクトを上にすすませる
	* @detail 設定されたMoveSpeedと_scaleValueを乗算して移動量を求めている
	*         deltaTimeは関数内で乗算している
	* @param const float (_scaleValue)
	* @return void
	*/
	virtual void MoveUp(const float _scaleValue);

	/**
    * @fn RotationYaw
    * @brief オーナーオブジェクトをYaw軸回転させる
    * @detail 設定されたRotationSpeedと_scaleValueを乗算して回転量を求めている
    *         deltaTimeは関数内で乗算している
    * @param const float (_scaleValue)
    * @return void
    */
	void RotationYaw(const float _scaleValue);

	/**
	* @fn RotationPitch
	* @brief オーナーオブジェクトをPitch軸回転させる
	* @detail 設定されたRotationSpeedと_scaleValueを乗算して回転量を求めている
	*         deltaTimeは関数内で乗算している
	* @param const float (_scaleValue)
	* @return void
	*/
	void RotationPitch(const float _scaleValue);

	/**
	* @fn RotationRoll
	* @brief オーナーオブジェクトをRoll軸回転させる
	* @detail 設定されたRotationSpeedと_scaleValueを乗算して回転量を求めている
	*         deltaTimeは関数内で乗算している
	* @param const float (_scaleValue)
	* @return void
	*/
	void RotationRoll(const float _scaleValue);

	/**
	* @fn SetMoveSpeed
	* @brief 移動速度のセッター
	* @param const float (_speed)
	* @return void
	*/
	inline void SetMoveSpeed(const float _speed) noexcept;

	/**
	* @fn SetRotSpeed
	* @brief 回転速度のセッター
	* @param const float (_speed)
	* @return void
	*/
	inline void SetRotSpeed(const float _speed) noexcept;

	/**
	* @fn GetModeSpeed
	* @brief スピートのゲッター
	* @return float 移動速度
	*/
	inline float GetMoveSpeed() const noexcept;

};

//----------- INLINES ------------

inline void MoveComponent::SetMoveSpeed(const float _speed) noexcept
{
	mMoveSpeed = _speed;
}

inline void MoveComponent::SetRotSpeed(const float _speed) noexcept
{
	mRotationSpeed = _speed;
}

inline float MoveComponent::GetMoveSpeed() const noexcept
{
	return mMoveSpeed;
}
