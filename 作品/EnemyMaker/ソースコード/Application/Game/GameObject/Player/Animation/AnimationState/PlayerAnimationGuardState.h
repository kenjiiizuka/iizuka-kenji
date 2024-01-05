/**
* @file PlayerAnimationGuardState.h
* @brief PlayerAnimationGuardState�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"

//--------- �O���錾 --------
class Player;

/**
* @fn PlayerAnimationGuardState
* @brief �v���C���[�̃K�[�h�A�j���[�V�����X�e�[�g
*/
class PlayerAnimationGuardState : public AnimationStateContext
{
	/**
	* @enum GuardState
	* @brief �K�[�h�̏�Ԃ�����
	*/
	enum GuardState : uint8_t
	{
		GuardStart = 0, /**< �K�[�h�J�n */
		Guarding,       /**< �K�[�h�� */
		GuardEnd,       /**< �K�[�h�I�� */
	};

public:
	/**
	* �R���X�g���N�^
	*
	* @param AnimationInstance* (_animInstance)
	*/
	PlayerAnimationGuardState(AnimationInstance* _animInstance);

	/**
	* �f�X�g���N�^
	*/
	~PlayerAnimationGuardState();

private:
	/** �K�[�h��� */
	GuardState mGuardState;

	/** �v���C���[ */
	Player* mPlayer;

public:
	/**
	 * @fn Entry
	 * @brief �X�e�[�g�̊J�n����
	 * @return void
	*/
	void Entry() override;

	/**
	 * @fn StateMachine
	 * @brief �X�e�[�g�}�V��
	 * @return void
	*/
	void StateMachine() override;
};

