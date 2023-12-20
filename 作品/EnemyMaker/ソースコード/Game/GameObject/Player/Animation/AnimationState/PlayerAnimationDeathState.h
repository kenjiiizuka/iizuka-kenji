/**
* @file PlayerAnimationDeathState.h
* @brief PlayerAnimationDeathState�N���X�̒�`
*/


#pragma once

//---------- INCLUDES -----------
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"

/**
* @class PlayerAnimationDeathState
* @brief �v���C���[�̎��S���A�j���[�V�����X�e�[�g
*/
class PlayerAnimationDeathState : public AnimationStateContext
{
public:
	/**
	* �R���X�g���N�^
	*
	* @param[in] AnimationInstance* (_animInstance)
	*/
	PlayerAnimationDeathState(AnimationInstance* _animInstance);

	/**
	* �f�X�g���N�^
	*/
	~PlayerAnimationDeathState();

public:
	/**
	 * @fn Entry
	 * @brief �X�e�[�g�̊J�n����
	 * @return void
	*/
	void Entry() override;
};

