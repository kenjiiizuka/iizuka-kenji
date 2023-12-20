/**
* @file PlayerStepNotifyState.h
* @brief PlayerStepNotifyState�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ----------
#include "../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"

//-------- �O���錾 ---------
class CapsuleCollisionComponent;

/**
* @class PlayerStepNotifyState
* @brief �v���C���[�̃X�e�b�v���ɓG�̍U���Ƃ̓����蔻��������ʒm�X�e�[�g
*/
class PlayerStepNotifyState : public AnimationNotifyState
{
public:
	/**
	* �R���X�g���N�^
	*
	* @param SkeletalMeshAnimation* (_attachAnimation) �A�^�b�`�����A�j���[�V����
	* @param float (_attachStartFrame) �A�^�b�`����t���[���̊J�n
	* @param float (_attachEndFrame) �A�^�b�`����t���[���̏I��
	*/
	PlayerStepNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

	/**
	* �f�X�g���N�^
	*/
	~PlayerStepNotifyState();

private:
	/** �v���C���[�̃R���W���� */
	std::weak_ptr<CapsuleCollisionComponent> mPlayerCollision;

public:
	/**
�@�@* @fn�@NotifyBegin
�@�@* @brief �ʒm�̊J�n����
�@�@* @return void
�@�@*/
	void NotifyBegin() override;

	/**
	* @fn NotifyEnd
	* @brief �ʒm�̏I������
	* @return void
	*/
	void NotifyEnd() override;
};

