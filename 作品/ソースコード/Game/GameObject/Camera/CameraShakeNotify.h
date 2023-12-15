/**
* @file CameraShakeNotify.h
* @brief CameraShakeNotifyクラスの定義
*/

#pragma once

//-------- INCLUDES ----------
#include "../../Component/SkeletalMeshComponent/AnimationNotify.h"
#include <SimpleMath.h>

/**
* @class CameraShakeNotify
* @brief カメラ振動用通知ステート
*/
class CameraShakeNotify : public AnimationNotify
{
public:
	/**
	* デフォルトコンストラクタ
	* 
	* @param SkeletalMeshAnimationClip* (_attachAnimation)
	* @param float (_attachFrame)
	*/
	CameraShakeNotify(SkeletalMeshAnimationClip* _attachAnimation, float _attachFrame);

	/**
	* デストラクタ
	*/
	~CameraShakeNotify();

private:
	/** 振動時間 */
	float mShakeTime;

	/** 振動の強さ */
	uint8_t mShakeLevel;

	/** 振動で動く最大のベクトル */
	DirectX::SimpleMath::Vector2 mShakeVector;

public:
	/**
　　 * @fn　NotifyUpdate
　　 * @brief 通知の更新処理
     * @detail カメラ振動処理を実行する
　　 * @return void
　　*/
	virtual void NotifyUpdate();

	/**
	* @fn SetShakeTime
	* @brief 振動時間のセッター
	* @param const float (_shakeTime)
	* @return void
	*/
	inline void SetShakeTime(const float _shakeTime) noexcept;

	/**
	* @fn SetShakeLevel
	* @brief 振動の強さの設定
	* @param const uint8_t (_level)
	* @return void
	*/
	inline void SetShakeLevel(const uint8_t _level) noexcept;

	/**
	* @fn SetShakeVector
	* @brief カメラの振動ベクトルのセッター
	* @param const DirectX::SimpleMath::Vector2 (_shakeVector)
	* @return void
	*/
	inline void SetShakeVector(const DirectX::SimpleMath::Vector2 _shakeVector) noexcept;

	/**
	* @fn SetShakeTime
	* @brief 振動時間のゲッター
	* @return float
	*/
	inline float GetShakeTime() const noexcept;

	/**
	* @fn SetShakeLevel
	* @brief 振動の強さのゲッター
	* @return uint8_t
	*/
	inline uint8_t GetShakeLevel() const noexcept;

	/**
	* @fn SetShakeVector
	* @brief カメラの振動ベクトルのゲッター
	* @return DirectX::SimpleMath::Vector2
	*/
	inline DirectX::SimpleMath::Vector2 GetShakeVector()const noexcept;

};

//----------- INLINES -----------

inline void CameraShakeNotify::SetShakeTime(const float _shakeTime) noexcept
{
	mShakeTime = _shakeTime;
}

inline void CameraShakeNotify::SetShakeLevel(const uint8_t _level) noexcept
{
	mShakeLevel = _level;
}

inline void CameraShakeNotify::SetShakeVector(const DirectX::SimpleMath::Vector2 _shakeVector) noexcept
{
	mShakeVector = _shakeVector;
}

inline float CameraShakeNotify::GetShakeTime() const noexcept
{
	return mShakeTime;
}

inline uint8_t CameraShakeNotify::GetShakeLevel() const noexcept
{
	return mShakeLevel;
}

inline DirectX::SimpleMath::Vector2 CameraShakeNotify::GetShakeVector() const noexcept
{
	return mShakeVector;
}
