//----------- INCLUDES ----------
#include "EnemyMoveAction.h"

EnemyMoveAction::EnemyMoveAction(std::shared_ptr<BlackBoard> _blackBoard)
	: EnemyAction(_blackBoard)
{
	ResizeNumberOfEvaluationItems(1); // マジックナンバー 1 移動遺伝子の評価項目は１つだから
	mActionType = EnemyActionType::Move;
}

