//---------- INCLUDES ----------
#include "Bear2ChinaBackAndFront.h"
#include "../../Animation/BearAnimationinstance.h"

Bear2ChinaBackAndFront::Bear2ChinaBackAndFront(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(Bear2ChinaBackAndFront).name();
	mAttackID = BearEnemyAttackData::BackAndFrontSlash;
}

Bear2ChinaBackAndFront::~Bear2ChinaBackAndFront()
{
	// 処理なし
}

void Bear2ChinaBackAndFront::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName, 1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult Bear2ChinaBackAndFront::UpdateActionExecution()
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

void Bear2ChinaBackAndFront::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool Bear2ChinaBackAndFront::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

void Bear2ChinaBackAndFront::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<Bear2ChinaBackAndFront>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
