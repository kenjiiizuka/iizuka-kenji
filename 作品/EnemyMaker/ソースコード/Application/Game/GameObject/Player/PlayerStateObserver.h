/**
* @file PlayerStateObserver.h
* @brief PlayerStateObserver�N���X�̒�`
*/

#pragma once

//----------- INCLUDES -----------
#include <memory>
#include "PlayerData.h"

//----------- �O���錾 -------------
class Player;
class PlayerStateController;

/**
* @class PlayerStateObserver
* @brief �v���C���[�̏�Ԃ��Ď����A�v���C���[�̃X�e�[�g�Ǘ��N���X�ɒʒm����N���X
*        �܂��A�X�e�[�g�Ǘ��N���X�̏�Ԃɂ���Ă��X�e�[�g���ς�邱�Ƃ�����̂ŁA
*        �X�e�[�g�Ǘ��N���X���Ď�����B�X�e�[�g�Ǘ��N���X����X�e�[�g�̕ύX�̕K�v���ł���X�e�[�g�Ǘ��N���X�ɒʒm����
*/
class PlayerStateObserver
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param Player* (_player) �Ď��Ώۂ̃v���C���[
	*/
	PlayerStateObserver(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerStateObserver();

private:
	/** �Ď�����v���C���[ */
	Player* mSubjectPlayer;

	/** �X�e�[�g��؂�ւ���N���X */
	std::weak_ptr<PlayerStateController> mStateController;

	/** �O�t���[���̃v���C���[�̍s���X�e�[�g */
	PlayerData::PlayerBehaviorState mPrevBehaviorState;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail �����X�e�[�g�Ƃ���IdleMove�ɐݒ肷��
	* @param const std::shared_ptr<PlayerStateController> (_stateController)
	* @return void
	*/
	void Initialize(const std::shared_ptr<PlayerStateController> _stateController);

	/**
	* @fn Update
	* @brief �X�V����
	* @detail �v���C���[�̂ƃX�e�[�g�R���g���[���[�̏�Ԃ��Ď�����
	*         �X�e�[�g�R�����g�[���[�ɒʒm����K�v������Βʒm���� 
	* @return void
	*/
	void Update();

private:
	/**
	* @fn SwitchState
	* @brief �X�e�[�g�R���g���[���[�̃X�e�[�g��؂�ւ���֐�
	* @detail �����œn���ꂽ�X�e�[�g�ɂ������X�e�[�g�R���e�L�X�g�ɐ؂�ւ���
	* @param const PlayerEntities::PlayerBehaviorState& (_switchState)
	* @return void
	*/
	void SwitchState(const PlayerData::PlayerBehaviorState& _switchState);
};

