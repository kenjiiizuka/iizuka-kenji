/**
* @file PlayerIdleMoveState.h
* @brief PlayerIdleMoveState�N���X�̒�`
*/
#pragma once

//--------- INCLUDES ----------
#include <memory>
#include "PlayerStateContext.h"

//--------- �O���錾 ---------
class PlayerMovementComponent;


/**
* @class PlayerIdleMoveState
* @brief �v���C���[�̑ҋ@�ړ��X�e�[�g
*/
class PlayerIdleMoveState : public PlayerStateContext
{
public:
	/**
	* �R���X�g���N�^
	*
	* @param Player* (_player)
	*/
	PlayerIdleMoveState(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerIdleMoveState();

private:
	/** �v���C���[�̃��[�u�R���|�[�l���g */
	std::weak_ptr<PlayerMovementComponent> mMoveComp;

public:
	/**
	* @fn Entry
	* @brief �X�e�[�g�J�n����
	*/
	void Entry() override;

	/**
	* @fn Exit
	* @brief �X�e�[�g�I�͏���
	* @return void
	*/
	void Exit() override;

	/**
	* @fn Update
	* @brief �X�V����
	*/
	void Update() override;

};

