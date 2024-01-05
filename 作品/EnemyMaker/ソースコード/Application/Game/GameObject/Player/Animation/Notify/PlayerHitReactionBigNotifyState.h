/**
* @file PlayerHitReactionBigNotifyState.h
* @brief PlayerHitReactionBigNotifyState�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include "../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"
#include <SimpleMath.h>


//---------- �O���錾 ---------
class CurveFloat;
class TransformComponent;

/**
* @class PlayerHitReactionBigNotifyState
* @brief �v���C���[�̃q�b�g���A�N�V������A�j���[�V�����ɂ��킹�ăv���C���[�𓮂������������Ă���
*/
class PlayerHitReactionBigNotifyState : public AnimationNotifyState
{
public:
	/**
	 * �R���X�g���N�^
	 *
	 * @param SkeletalMeshAnimation* (_attachAnimation) �A�^�b�`�����A�j���[�V����
	 * @param float (_attachStartFrame) �A�^�b�`����t���[���̊J�n
	 * @param float (_attachEndFrame) �A�^�b�`����t���[���̏I��
	*/
	PlayerHitReactionBigNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);
	
	/**
	* �f�X�g���N�^
	*/
	~PlayerHitReactionBigNotifyState();

private:
	/** �v���C���[���A�j���[�V�����ɍ��킹�Đ�����΂����߂̃J�[�u */
	std::shared_ptr<CurveFloat> mBlowCurve;

	/** �v���C���[�̃g�����X�t�H�[�� */
	std::weak_ptr<TransformComponent> mPlayerTransform;

	/** �A�j���[�V�������� */
	float mAttachAnimationDuration;

	/** ������ѕ��� */
	DirectX::SimpleMath::Vector3 mBlowVector;

public:
	/**
�@�@ * @fn�@NotifyInit
�@�@ * @brief �ʒm�̏�������
�@�@ * @return void
�@�@*/
	void NotifyInit() override;

	/**
	* @fn NotifyBegin
	* @brief �ʒm�����J�n����
	* @return void
	*/
	void NotifyBegin() override;

	/**
�@�@ * @fn�@NotifyUpdate
�@�@ * @brief �ʒm�̍X�V����
�@�@ * @return void
�@�@*/
	void NotifyUpdate() override;

	/**
	* @fn GetBlowCurve
	* @brief ������т悤�J�[�u��Ԃ�
	* @return std::weak_ptr<CurveFloat>
	*/
	inline std::weak_ptr<CurveFloat> GetBlowCurve() const noexcept;

	/**
	* @fn SetBlowVector
	* @brief ������уx�N�g���̃Z�b�^�[
	* @param const DirectX::SimpleMath::Vector3 (_blowVector)
	* @return void
	*/
	inline void SetBlowVector(const DirectX::SimpleMath::Vector3 _blowVector) noexcept;

};

//---------- INLINES ----------

inline std::weak_ptr<CurveFloat> PlayerHitReactionBigNotifyState::GetBlowCurve() const noexcept
{
	return mBlowCurve;
}

inline void PlayerHitReactionBigNotifyState::SetBlowVector(const DirectX::SimpleMath::Vector3 _blowVector) noexcept
{
	mBlowVector = _blowVector;
	mBlowVector.y = 0.0f;
	mBlowVector.Normalize();
}
