//----------- INCLUDES ----------
#include "PlayerStateContext.h"

PlayerStateContext::PlayerStateContext(Player* _player)
	: mPlayer(_player)
	, mbIsInputAble(false)
	, mbNeedTransitionState(false)
{
	// 処理なし
}

PlayerStateContext::~PlayerStateContext()
{
	// 処理なし
}


