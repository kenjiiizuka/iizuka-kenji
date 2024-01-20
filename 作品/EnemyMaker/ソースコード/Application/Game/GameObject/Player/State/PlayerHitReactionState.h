/**
* @file PlayerHitReactionState.h
* @brief PlayerHitReactionState�N���X�̒�`
*/
#pragma once

//----------- INCLUDES ----------
#include "PlayerStateContext.h"

/**
* @class PlayerHitReactionState
* @brief �v���C���[�̃q�b�g���A�N�V�����X�e�[�g
*/
class PlayerHitReactionState : public PlayerStateContext
{
public:
	/**
	* �R���X�g���N�^
	*
	* @param Player* (_player)
	*/
	PlayerHitReactionState(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerHitReactionState();

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

private:
	/**
	* @fn CheckAnimationEnd
	* @brief �q�b�g���A�N�V�����̃A�j���[�V�������I�����Ă��邩���m�F����
	* @return true �I�����Ă��� false �I�����Ă��Ȃ�
	*/
	bool CheckAnimationEnd() const;

	/**
	* @fn CheckInputAble
	* @brief ���͉\�����m�F����
	* @detail �q�b�g���A�N�V�����A�j���[�V�����ɂ��Ă���PlayerInputAbleNotifyState������͉\�����󂯎��
	* @return bool true �\ false �s�\
	*/
	bool CheckInputAble() const;

};
