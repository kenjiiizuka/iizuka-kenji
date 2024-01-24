//------------ INCLUDES ----------
#include "EnemyAction.h"
#include "../../../../../../System/FPSController/FPSController.h"

EnemyAction::EnemyAction(std::shared_ptr<BlackBoard> _blackBoard)
	: mbCanChange(false)
	, mBlackBoard(_blackBoard)
	, mEnemy(nullptr)
	, mExecuteCount(0)
	, mSuitable(0.0f)
	, mActionType(EnemyActionType::None)
{
}

void EnemyAction::BeginActionExecution(EnemyBase* _enemy)
{
	// 実行回数を加算
	mExecuteCount++;
}

