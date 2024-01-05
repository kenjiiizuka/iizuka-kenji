#include "BearRoarAttack.h"
#include "../../../EnemyBase.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../../AIBase/BlackBoard.h"
#include "../../../../../../System/InputSystem/Input.h"

BearRoarAttack::BearRoarAttack(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(BearRoarAttack).name();
}

void BearRoarAttack::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);

	AnimationPlaySetting setting = AnimationInf::AnimationPlayType::PlayType_PositionSynchro;
	mAnimInstance.lock()->PlayAnimationClip("RoarAttack",1.0f,0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult BearRoarAttack::UpdateActionExecution()
{
	// 親クラス内で時間の計測をしているので呼び出す
	BearAttackAction::UpdateActionExecution();

	// アニメーションの終了判定があれば成功を返す、それ以外は実行中
	std::shared_ptr<AnimationPlayer> animPlayer = mAnimInstance.lock()->GetAnimationPlayer();
	if (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame())
	{
		return EnemyActionResult::Succeeded;
	}
	return EnemyActionResult::InProgress;
}

void BearRoarAttack::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool BearRoarAttack::IsExecuteAble()
{
	return Input::GetKeyTrigger('7') && Input::GetKeyPress('A');	
}

void BearRoarAttack::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<BearRoarAttack>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
