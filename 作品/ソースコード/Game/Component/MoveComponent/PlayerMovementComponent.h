/**
* @file PlayerMovementComponent.h
* @brief PlayerMovementComponent�N���X�̒�`
* 
*/

#pragma once

//--------- INCLUDES ---------
#include "MoveComponent.h"
#include <SimpleMath.h>

/**
* @class PlayerMovementComponent
* @brief �v���C���[�̈ړ��R���|�[�l���g
*/
class PlayerMovementComponent : public MoveComponent
{
public:
	/**
	* �R���X�g���N�^
	*/
	PlayerMovementComponent();

	/**
	* �f�X�g���N�^
	*/
	~PlayerMovementComponent();

private:	
	/** �ړ����͂����邩 */
	bool mbMoveInput;

	/** �����x */
	float mAcceleration;

	/** �ő呬�x�̒B����܂ł̎��� */
	float mTimeToMaxSpeed;

	/** �ړ��J�n���Ă���̌o�ߎ��� */
	float mMoveElapsedTime;

	/** �ő�ړ����x */
	float mMaxSpeed;

	/** ���݂̖ڕW�̑��x */
	float mCurrentTargetSpeed;

	/** ���݂̈ړ����x */
	float mCurrentSpeed;

	/** �X�e�B�b�N�̓|��Ă������ */
	DirectX::SimpleMath::Vector3 mStickDirection;

	/** �����J�n�������̈ړ����x */
	DirectX::SimpleMath::Vector3 mDecelerationStartVelocity;

	/** �ړ������Ɍ�����ԑ��x */
	float mFaceDirectionInterpSpeed;

	/** ���݂̈ړ��� */
	DirectX::SimpleMath::Vector3 mCurrentVelocity;

public:
	/**
	* @fn Update
	* @brief �X�V����
	* @detail �ړ��̓��͂�����Α��x�������������x�܂ŕ�Ԃ�
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override; 

private:
	/**
	* @fn Deceleration
	* @brief �����̏���
	* @param const float (_deltaTime)
	* @return void
	*/
	void Deceleration(const float deltaTime);

	/**
	* @fn FaceDirection
	* @brief �ړ������ɉ�]��������
	* @param const float (_deltaTime)
	* @return void
	*/
	void FaceDirection(const float _deltaTime);

	/**
	* @fn Movement
	* @brief �ړ�����
	* @param const float (_deltaTime)
	* @return void 
	*/
	void Movement(const float _deltaTime);

public:
	/**
	* @fn AddMovementInput
	* @brief �ړ����͊֐�
	* @param const DirectX::SimpleMath::Vector3 (_stickDirection) �X�e�B�b�N�̓|��Ă�������x�N�g��
	* @return void
	*/
	void AddMovementInput(const DirectX::SimpleMath::Vector3 _stickDirection);

	/**
	* @fn MoveStop
	* @brief �ړ����~����֐�
	* @return void
	*/
	void MoveStop();

	/**
	* @fn SetMaxSpeed
	* @brief �ő�ړ����x�̃Z�b�^�[
	* @param const float (_maxSpeed)
	* @return void
	*/
	inline void SetMaxSpeed(const float _maxSpeed) noexcept;

	/**
	* @fn SetFaceDirectionInterpSpeed
	* @brief �ړ������ɂނ���ԑ��x�̃Z�b�^�[
	* @param const float (_interpSpeed)
	* @return void
	*/
	inline void SetFaceDirectionInterpSpeed(const float _interpSpeed);

	/**
	* @fn GetMaxSpeed
	* @brief �ő呬�x��Ԃ�
	* @return float 
	*/
	inline float GetMaxSpeed() const noexcept;

	/**
	* @fn GetCurrentVelocity
	* @brief ���݂̈ړ����x��Ԃ�
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
