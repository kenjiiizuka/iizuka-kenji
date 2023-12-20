/**
* @file PlayerDeathState.h
* @brief PlayerDeathState�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ---------
#include "PlayerStateContext.h"

/**
* @class PlayerDeathState
* @brief �v���C���[�̎��S�X�e�[�g
*/
class PlayerDeathState : public PlayerStateContext
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param Player* (_player)
	*/
	PlayerDeathState(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerDeathState();

public:
	/**
	* @fn Entry
	* @brief �X�e�[�g�J�n����
	*/
	void Entry() override;
};

