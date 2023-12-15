/**
* @file CameraShakeNotify.h
* @brief CameraShakeNotify�N���X�̒�`
*/

#pragma once

//-------- INCLUDES ----------
#include "../../Component/SkeletalMeshComponent/AnimationNotify.h"
#include <SimpleMath.h>

/**
* @class CameraShakeNotify
* @brief �J�����U���p�ʒm�X�e�[�g
*/
class CameraShakeNotify : public AnimationNotify
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	* 
	* @param SkeletalMeshAnimationClip* (_attachAnimation)
	* @param float (_attachFrame)
	*/
	CameraShakeNotify(SkeletalMeshAnimationClip* _attachAnimation, float _attachFrame);

	/**
	* �f�X�g���N�^
	*/
	~CameraShakeNotify();

private:
	/** �U������ */
	float mShakeTime;

	/** �U���̋��� */
	uint8_t mShakeLevel;

	/** �U���œ����ő�̃x�N�g�� */
	DirectX::SimpleMath::Vector2 mShakeVector;

public:
	/**
�@�@ * @fn�@NotifyUpdate
�@�@ * @brief �ʒm�̍X�V����
     * @detail �J�����U�����������s����
�@�@ * @return void
�@�@*/
	virtual void NotifyUpdate();

	/**
	* @fn SetShakeTime
	* @brief �U�����Ԃ̃Z�b�^�[
	* @param const float (_shakeTime)
	* @return void
	*/
	inline void SetShakeTime(const float _shakeTime) noexcept;

	/**
	* @fn SetShakeLevel
	* @brief �U���̋����̐ݒ�
	* @param const uint8_t (_level)
	* @return void
	*/
	inline void SetShakeLevel(const uint8_t _level) noexcept;

	/**
	* @fn SetShakeVector
	* @brief �J�����̐U���x�N�g���̃Z�b�^�[
	* @param const DirectX::SimpleMath::Vector2 (_shakeVector)
	* @return void
	*/
	inline void SetShakeVector(const DirectX::SimpleMath::Vector2 _shakeVector) noexcept;

	/**
	* @fn SetShakeTime
	* @brief �U�����Ԃ̃Q�b�^�[
	* @return float
	*/
	inline float GetShakeTime() const noexcept;

	/**
	* @fn SetShakeLevel
	* @brief �U���̋����̃Q�b�^�[
	* @return uint8_t
	*/
	inline uint8_t GetShakeLevel() const noexcept;

	/**
	* @fn SetShakeVector
	* @brief �J�����̐U���x�N�g���̃Q�b�^�[
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
