#include "PlayerDeathState.h"

PlayerDeathState::PlayerDeathState(Player* _player)
	: PlayerStateContext(_player)
{
	// 処理なし
}

PlayerDeathState::~PlayerDeathState()
{
	// 処理なし
}

void PlayerDeathState::Entry()
{
	mbIsInputAble = false;
	mbNeedTransitionState = false;
}


