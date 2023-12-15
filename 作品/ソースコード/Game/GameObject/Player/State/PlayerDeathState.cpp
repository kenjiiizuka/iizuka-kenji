#include "PlayerDeathState.h"

PlayerDeathState::PlayerDeathState(Player* _player)
	: PlayerStateContext(_player)
{
	// ˆ—‚È‚µ
}

PlayerDeathState::~PlayerDeathState()
{
	// ˆ—‚È‚µ
}

void PlayerDeathState::Entry()
{
	mbIsInputAble = false;
	mbNeedTransitionState = false;
}


