/**
* @file PlayerStepState.h
* @brief PlayerStepState�N���X�̒�`
*/

#pragma once

//--------- INCLUDES --------
#include "PlayerStateContext.h"

/**
* @class PlayerStepState
* @brief �v���C���[�̃X�e�b�v�X�e�[�g
*/
class PlayerStepState : public PlayerStateContext
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param Player* (_player)
	*/
	PlayerStepState(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerStepState();

private:
	/** ����̃t���[�����𔻒f���� */
	bool mbFirstFrame;

public:
	/**
	* @fn Entry
	* @brief �X�e�[�g�J�n����
	*/
	void Entry() override;

	/**
	* @fn Update
	* @brief �X�V����
	*/
	void Update() override;

private:
	/**
	* @fn CheckAnimationEnd
	* @brief �A�j���[�V�������I�����Ă��邩�m�F����
	* @return bool true �I�� false �I�����Ă��Ȃ�
	*/
	bool CheckAnimationEnd();

	/**
	* @fn CheckInputAble
	* @brief ���͉\�Ȃ̂��𔻒f����
	* @return bool true ���͉\ false ���͕s��
	*/
	bool CheckInputAble() const;

};

