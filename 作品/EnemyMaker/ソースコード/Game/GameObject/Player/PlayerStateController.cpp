//----------- INCLUDES ---------
#include "PlayerStateController.h"

PlayerStateController::PlayerStateController(std::shared_ptr<PlayerStateObserver> _observer, Player* _player)
	: mObserver(_observer)
	, mPlayer(_player)
	, mbNeedTransitionState(false)
{
	// 処理なし
}

PlayerStateController::~PlayerStateController()
{
	// 処理なし
}

void PlayerStateController::UpdateState()
{
	if (!mCurrentState)
	{
		return;
	}

	//ステートの更新
	mCurrentState->Update();
}

