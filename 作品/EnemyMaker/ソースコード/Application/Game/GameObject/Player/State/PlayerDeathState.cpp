#include "PlayerDeathState.h"

PlayerDeathState::PlayerDeathState(Player* _player)
	: PlayerStateContext(_player)
{
	// �����Ȃ�
}

PlayerDeathState::~PlayerDeathState()
{
	// �����Ȃ�
}

void PlayerDeathState::Entry()
{
	mbIsInputAble = false;
	mbNeedTransitionState = false;
}


