//----------- INCLUDES ----------
#include "PlayerStateContext.h"

PlayerStateContext::PlayerStateContext(Player* _player)
	: mPlayer(_player)
	, mbIsInputAble(false)
	, mbNeedTransitionState(false)
{
	// �����Ȃ�
}

PlayerStateContext::~PlayerStateContext()
{
	// �����Ȃ�
}


