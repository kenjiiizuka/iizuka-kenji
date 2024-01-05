/**
* @file PlayerStateContext.h
* @brief PlayerStateContext�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include "../PlayerData.h"

//---------- �O���錾 ----------
class Player;

/**
* @class PlayerStateContext
* @brief �v���C���[�̍s�����X�e�[�g�Ǘ����邽�߂̃X�e�[�g�R���e�L�X�g�N���X
*/
class PlayerStateContext
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	* 
	* @param Player* (_player)
	*/
	PlayerStateContext(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	virtual ~PlayerStateContext();

protected:
	/** �v���C���[ */
	Player* mPlayer;

	/** �R���g���[���[����̓��͂��\���𔻒f���� */
	bool mbIsInputAble;

	/** �X�e�[�g��؂�ւ���K�v�����邱�Ƃ������t���O */
	bool mbNeedTransitionState;

public:
	/**
	* @fn Entry
	* @brief �X�e�[�g�̊J�n����
	* @return void
	*/
	virtual void Entry() {};

	/**
	* @fn Update
	* @brief �X�V����
	*/
	virtual void Update() {};

	/**
	* @fn Exit
	* @brief �X�e�[�g�̏I������
	* @return void
	*/
	virtual void Exit() {};

	/**
	* @fn IsInputAble
	* @brief ���͉\���Ԃ�
	* @return bool
	*/
	inline bool IsInputAble() const noexcept; 

	/**
	* @fn IsNeedTransition
	* @brief �J�ڂ��K�v�Ȃ̂���Ԃ�
	* @return bool true �K�v false �s�K�v
	*/
	inline bool IsNeedTransition() const noexcept;

};

//---------- INLINES -----------

inline bool PlayerStateContext::IsInputAble() const noexcept
{
	return mbIsInputAble;
}

inline bool PlayerStateContext::IsNeedTransition() const noexcept
{
	return mbNeedTransitionState;
}
