//----------- INCLUDES ---------
#include "PlayerStateController.h"

PlayerStateController::PlayerStateController(std::shared_ptr<PlayerStateObserver> _observer, Player* _player)
	: mObserver(_observer)
	, mPlayer(_player)
	, mbNeedTransitionState(false)
{
	// �����Ȃ�
}

PlayerStateController::~PlayerStateController()
{
	// �����Ȃ�
}

void PlayerStateController::UpdateState()
{
	if (!mCurrentState)
	{
		return;
	}

	//�X�e�[�g�̍X�V
	mCurrentState->Update();
}

