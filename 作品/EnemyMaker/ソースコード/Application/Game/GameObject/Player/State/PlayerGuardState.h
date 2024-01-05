/**
* @file PlayerGuardState.h
* @brief PlayerGuardState�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include "PlayerStateContext.h"
#include <SimpleMath.h>
#include <memory>

//---------- �O���錾 ----------
class PlayerInputControllerComponent;

/**
* @class PlayerGuardState
* @brief �v���C���[�̃K�[�h�X�e�[�g
*/
class PlayerGuardState : public PlayerStateContext
{
public:
	/**
	* �R���X�g���N�^
	*
	* @param Player* (_player)
	*/
	PlayerGuardState(Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerGuardState();

private:
	/** �v���C���[�̓��͐���R���|�[�l���g */
	std::weak_ptr<PlayerInputControllerComponent> mInputController;

	/** �K�[�h�J�n���Ă���̌o�ߎ��� */
	double mGuardStartElapsedTime;

	/** �W���X�K�������� */
	double mJustGuardSuccessTime;

	/** �K�[�h�̓��͂��Ȃ��Ȃ����������� */
	bool mbGuardEnd;

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

	/**
	* @fn Exit
	* @brief �X�e�[�g�̏I������
	* @return void
	*/
	void Exit() override;

private:
	/**
	* @fn CheckGuardAnimationFinish
	* @brief �K�[�h�A�j���[�V�������I�����Ă��邩���m�F���� 
	* @bool
	*/
	bool CheckGuardAnimationFinish();

public:
	/**
	* @fn CheckGuard
	* @brief �K�[�h�̌��ʂ𔻒f����֐�
	* @detail �K�[�h���ɐU�ꂽ�U���̓����蔻��̈ʒu�����v���C���[�ɑ΂��ăK�[�h�\�ʒu�ɂ��邩�𔻒f����
	* @return PlayerData::GuardResult
	*/
	PlayerData::GuardResult CheckGuard(const DirectX::SimpleMath::Vector3 _attackPosition) const noexcept;

};

