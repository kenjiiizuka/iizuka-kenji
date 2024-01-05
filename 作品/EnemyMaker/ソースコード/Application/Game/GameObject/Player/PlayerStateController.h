/**
* @file PlayerStateSwitcher.h
* @brief PlayerStateSwitcher�N���X�̒�`
*/

#pragma once
//----------- INCLUDES -----------
#include <memory>
#include "State/PlayerStateContext.h"

//----------- �O���錾 -----------
class Player;
class PlayerStateObserver;

//---------- �R���Z�v�g -----------
template<class PlayerState>
concept DerivedPlayerState = std::derived_from<PlayerState, PlayerStateContext>;

/**
* @class PlayerStateSwitcher
* @brief �v���C���[�̃X�e�[�g��؂�ւ���N���X
* @detail �v���C���[���Ď�����N���X����ʒm�����炢�A�X�e�[�g��؂�ւ���
*/
class PlayerStateController
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param std::shared_ptr<PlayerStateObserver> (_observer)
	* @param Player*                              (_player)
	*/
	PlayerStateController(std::shared_ptr<PlayerStateObserver> _observer, Player* _player);

	/**
	* �f�X�g���N�^
	*/
	~PlayerStateController();

private:
	/** �v���C���[�ƒʒm�Ǘ��N���X���Ď�����I�u�U�[�o�[ */
	std::weak_ptr<PlayerStateObserver> mObserver;

	/** �v���C���[ */
	Player* mPlayer;

	/** ���݂̃X�e�[�g */
	std::shared_ptr<PlayerStateContext> mCurrentState;

	/** �X�e�[�g�̑J�ڂ��K�v�Ȃ��Ƃ����߂� */
	bool mbNeedTransitionState;

public:
	/**
	* @fn UpdateState
	* @brief �X�V����
	* @detail ���݂̃X�e�[�g�̍X�V����������
	* @return void
	*/
	void UpdateState();

	/**
	* @fn SwitchState
	* @brief �X�e�[�g�؂�ւ��֐�
	* @detail �R���Z�v�g��PlayerStateContext�N���X���p�������N���X�̂ݎw��\�ɂ��Ă���
	*         �V�����X�e�[�g�𐶐����AEntry�����s���Ă���
	* @return void
	*/
	template<DerivedPlayerState PlayerState>
	inline void SwitchState();

	/**
	* @fn IsInputAble
	* @brief ���݂̃X�e�[�g�̓R���g���[���[����̓��͂��󂯕t���邩��Ԃ�
	* @return bool true ���͉� false ���͕s��
	*/
	inline bool IsInputAble() const noexcept;

	/**
	* @fn IsNeedTransition
	* @brief �J�ڂ��K�v�Ȃ̂���Ԃ�
	* @return bool
	*/
	inline bool IsNeedTransition() const noexcept;

	/**
	* @fn GetState
	* @brief ���݂̃X�e�[�g��Ԃ�
	* @return std::weak_ptr<PlayerStateContext>
	*/
	inline std::weak_ptr<PlayerStateContext> GetState() const noexcept;

};

//---------- INLINES ----------

template<DerivedPlayerState PlayerState>
inline void PlayerStateController::SwitchState()
{
	if (mCurrentState)
	{
		mCurrentState->Exit();
		mCurrentState.reset();
	}	
	mCurrentState = std::make_shared<PlayerState>(mPlayer);
	mCurrentState->Entry();
}

inline bool PlayerStateController::IsInputAble() const noexcept
{
	// �X�e�[�g������΁A���̃X�e�[�g�̓��͉A�s��Ԃ� �X�e�[�g���Ȃ���� ���͉\��Ԃ�
	return mCurrentState ? mCurrentState->IsInputAble() : true;
}

inline bool PlayerStateController::IsNeedTransition() const noexcept
{
	return mCurrentState ? mCurrentState->IsNeedTransition() : true;
}

inline std::weak_ptr<PlayerStateContext> PlayerStateController::GetState() const noexcept
{
	return mCurrentState;
}
