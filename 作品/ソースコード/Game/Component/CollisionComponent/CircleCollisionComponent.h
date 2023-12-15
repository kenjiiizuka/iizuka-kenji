/**
* @file RingCollisionComponent.h
* @brief RingCollisionComponent�N���X�̒�`
*/

#pragma once

//------------ INCLUDES -------------
#include "PrimitiveComponent.h"

/**
* @class RingCollisionComponent
* @brief �����O��̃R���W�����N���X
*/
class RingCollisionComponent : public PrimitiveComponent
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	RingCollisionComponent();

	/**
	* �f�X�g���N�^
	*/
	~RingCollisionComponent();

private:
	/** �����O�̓����̔��a */
	float mRadius;	

public:
	
	void Update(const double _deltaTime) override;

	/**
	* @fn GetRadius
	* @brief �����O�̔��a��Ԃ�
	* @return float 
	*/
	inline float GetRadius() const noexcept;

	/**
	* @fn SetRadius
	* @brief �����O�̔��a�̃Z�b�^�[
	* @param const float (_radius)
	* @return void
	*/
	inline void SetRadius(const float _radius) noexcept;
};

//-------------- INLINES -------------

inline float RingCollisionComponent::GetRadius() const noexcept
{
	return mRadius;
}

inline void RingCollisionComponent::SetRadius(const float _radius) noexcept
{
	mRadius = _radius;
}
