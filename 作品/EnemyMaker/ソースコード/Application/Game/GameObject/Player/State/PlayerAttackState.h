/**
* @file PlayerAttackState.h
* @brief PlayerAttackState�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include <memory>
#include "PlayerStateContext.h"

//---------- �O���錾 ----------
class PlayerAttackData;
class PlayerInputControllerComponent;

/**
* @class PlayerAttackState
* @brief �v���C���[�̍U���X�e�[�g
* @detail �R���{�p���̏����ƁA���͉\�^�C�~���O�̔��f�����Ă���
*/
class PlayerAttackState : public PlayerStateContext
{
public:
	/**
	* �R���X�g���N�^
	*
	* @param Player* (_player)
	*/
	PlayerAttackState(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerAttackState();

private:
	/** �v���C���[�̍U���f�[�^ */
	std::weak_ptr<PlayerAttackData> mAttackData;

	/** �v���C���[�̃C���v�b�g�R���g���[���[ */
	std::weak_ptr<PlayerInputControllerComponent> mInputController;

	/** �X�e�[�g���J�n�����t���[���ł��邱�Ǝ��� */
	bool mbEntryFrame;

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
	* @return void
	*/
	void Update() override;

	/**
	* @fn Exit
	* @brief �X�e�[�g�̏I������
	* @return void
	*/
	virtual void Exit() override;

private:
	/**
	* @fn CheckAttackAnimationEnd
	* @brief �U���A�j���[�V�����̍Đ����I���Ă��邩���m�F����
	* @return bool true �I���Ă��� false �I���Ă��Ȃ�
	*/
	bool CheckAttackAnimationEnd();

	/**
	* @fn CheckInputAble
	* @brief ���͉\�����m�F����
	* @detail �Đ�����Ă���U���A�j���[�V�����ɂ��Ă���PlayerInputAbleNotifyState�N���X������͉\���𔻒f����
	* @return bool true ���͉\ false ���͕s��
	*/
	bool CheckInputAble();

	/**
	* @fn Comb
	* @brief �R���{�p������
	* @detail �R���g���[���[����U���{�^���̓��͂�����΃R���{���p������
	* @return void
	*/
	void Comb();

};

