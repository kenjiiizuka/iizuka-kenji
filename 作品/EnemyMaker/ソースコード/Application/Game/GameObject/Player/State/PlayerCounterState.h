/**
* @file PlayerCounterState.h
* @brief PlayerCounterState�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ---------
#include "PlayerStateContext.h"

/**
* @class PlayerCounterState
* @brief �v���C���[�̃J�E���^�[�U���X�e�[�g
*/
class PlayerCounterState : public PlayerStateContext
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param Player* (_player)
	*/
	PlayerCounterState(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerCounterState();

private:
	/** ����t���[�������� */
	bool mbFirstFrame;

	/** �����蔻��̃T�C�Y��ύX������ */
	bool mbChangeCollisionSize;

	/** �R���W�����̑傫����ύX����t���[�� */
	uint8_t mCollisionSizeChangeFrame;

public:
	/**
	* @fn Entry
	* @brief �X�e�[�g�̊J�n����
	* @return void
	*/
	void Entry() override;

	/**
	* @fn Update
	* @brief �X�V����
	*/
	void Update() override;

};

