/**
* @file BearWeaponCollisionActiveNotifyState.h
* @brief BearWeaponCollisionActiveNotifyState�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include "../../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"
#include "../../../../CrossCharacterData.h"

//--------- �O���錾 ----------
class EnemyAttackCapsuleCollisionComponent;

/**
* @class BearWeaponCollisionActiveNotifyState
* @brief �F�̓G�̕���̃R���W������Active��؂�ւ���ʒm�X�e�[�g
*        �F�̓G��p�̒ʎj�X�e�[�g�Ȃ̂ő��̃I�u�W�F�N�g�ɂ͎g�p�ł��܂���
*/
class BearWeaponCollisionActiveNotifyState : public AnimationNotifyState
{
public:
	/**
	 * �R���X�g���N�^
	 *
	 * @param[in] SkeletalMeshAnimation* (_attachAnimation) �A�^�b�`�����A�j���[�V����
	 * @param[in] float (_attachStartFrame) �A�^�b�`����t���[���̊J�n
	 * @param[in] float (_attachEndFrame) �A�^�b�`����t���[���̏I��
	*/
	BearWeaponCollisionActiveNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

	/**
	* �f�X�g���N�^
	*/
	~BearWeaponCollisionActiveNotifyState();

public:
	/**
�@�@ * @fn�@NotifyBegin
�@�@ * @brief �ʒm�̊J�n����
�@�@ * @return void
�@�@*/
	void NotifyBegin() override;

	/**
	 * @fn�@NotifyEnd
	 * @brief �ʒm�̏I������
	 * @return void
	*/
	void NotifyEnd() override;

private:
	/** �F�̓G�̕���̃R���W���� */
	std::weak_ptr<EnemyAttackCapsuleCollisionComponent> mWeaponCollision;

	/** �_���[�W */
	float mDamage;

	/** �q�b�g���A�N�V���� */
	CrossCharacter::HitReaction mHitReaction;

public:
	/**
	* @fn SetDamage
	* @brief �R���W�����̃_���[�W��ݒ肷��
	* @param const float _damage
	* @return void
	*/
	inline void SetDamage(const float _damage);

	/**
	* @fn SetHitReaction
	* @brief �q�b�g���A�N�V�������Z�b�g����
	* @param const CrossCharacter::HitReaction (_hitReaction)
	* @return void
	*/
	inline void SetHitReaction(const CrossCharacter::HitReaction _hitReaction);
};

//---------- INLINES ----------

inline void BearWeaponCollisionActiveNotifyState::SetDamage(const float _damage)
{
	mDamage = _damage;
}

inline void BearWeaponCollisionActiveNotifyState::SetHitReaction(const CrossCharacter::HitReaction _hitReaction)
{
	mHitReaction = _hitReaction;
}
