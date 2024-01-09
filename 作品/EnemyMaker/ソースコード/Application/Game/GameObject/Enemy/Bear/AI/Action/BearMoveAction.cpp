//------------- INCLUDES --------------
#include "BearMoveAction.h"
#include "../../../../../Component/MoveComponent/CharacterMovementComponent.h"
#include "../../../AIBase/BlackBoard.h"
#include "../../../EnemyBase.h"


using namespace DirectX::SimpleMath;

BearMoveAction::BearMoveAction(std::shared_ptr<BlackBoard> _blackBoard)
	: EnemyMoveAction(_blackBoard)
{
	mTypeName = typeid(BearMoveAction).name();
}

void BearMoveAction::BeginActionExecution(EnemyBase* _enemy)
{
	mEnemy = _enemy;
	mMoveComp = mEnemy->GetComponent<CharacterMovementComponent>();
}

EnemyActionResult BearMoveAction::UpdateActionExecution()
{
	Vector3 vectorToTarget = mBlackBoard->GetValue<Vector3>("VectorToTarget");
	float toPlayerDistance = vectorToTarget.Length();
	if (toPlayerDistance >= 7.0)
	{
		vectorToTarget.Normalize();
		mMoveComp.lock()->AddMovementInput(vectorToTarget);
		return EnemyActionResult::CanChange;
	}
	else
	{
		return EnemyActionResult::Succeeded;
	}
}

void BearMoveAction::EndActionExecution()
{
}

bool BearMoveAction::IsExecuteAble()
{			
	Vector3 targetPosition = mBlackBoard->GetValue<Vector3>("TargetPosition");
	Vector3 enemyPos = mEnemy->GetComponent<TransformComponent>()->GetPosition();

	float distance = (targetPosition - enemyPos).Length();	
	return distance > 8.0f;
}

bool BearMoveAction::IsValidAction()
{
	return true;
}

void BearMoveAction::DuplicateFromSelfType(std::shared_ptr<EnemyMoveAction>& _output)
{
	_output = std::make_shared<BearMoveAction>(mBlackBoard);
}
