/**
* @file PlayerWeaponCollisionActiveNotifyState.h
* @brief PlayerWeaponCollisionActiveNotifyState�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ---------
#include "../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"

//-------- �O���錾 --------
class PlayerAttackCapsuleCollisionComponent;

/**
* @class PlayerWeaponCollisionActiveNotifyState
* @brief �v���C���[�̕���̃R���W�����̃I���I�t��؂�Ԃ��ʒm�X�e�[�g
* @detail �v���C���[��p�̒ʒm�X�e�[�g�ɂȂ��Ă���̂ŁA���̃I�u�W�F�N�g�ɂ̓A�^�b�`���Ȃ��悤��
*/
class PlayerWeaponCollisionActiveNotifyState : public AnimationNotifyState
{
public:
	/**
	 * �R���X�g���N�^
	 *
	 * @param[in] SkeletalMeshAnimation* (_attachAnimation) �A�^�b�`�����A�j���[�V����
	 * @param[in] float (_attachStartFrame) �A�^�b�`����t���[���̊J�n
	 * @param[in] float (_attachEndFrame) �A�^�b�`����t���[���̏I��
	*/
	PlayerWeaponCollisionActiveNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

	/**
	* �f�X�g���N�^
	*/
	~PlayerWeaponCollisionActiveNotifyState();

private:
	/** �v���C���[�̕���̃R���W���� */
	std::weak_ptr<PlayerAttackCapsuleCollisionComponent> mPlayerWeaponCollision;

public:
	/**
	* @fn NotifyBegin
	* @brief �ʒm�J�n����
	* @detail �v���C���[�̕���̃R���W�������擾���邵�A�R���W�������I���ɂ���
	*/
	void NotifyBegin() override;

	/**
	* @fn NotifyEnd
	* @brief �ʒm�I������
	* @detail �v���C���[�̕���̃R���W�������I�t�ɂ���
	*/
	void NotifyEnd() override;
};

