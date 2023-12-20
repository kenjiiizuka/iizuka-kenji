//----------- INCLUDES -----------
#include "Bear2ChainSwordAttack.h"
#include "../../../EnemyBase.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../../AIBase/BlackBoard.h"


namespace DXSimpleMath = DirectX::SimpleMath;

Bear2ChainSwordAttack::Bear2ChainSwordAttack(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(Bear2ChainSwordAttack).name();
	mAttackID = BearEnemyAttackData::DoubleSlash;
}

void Bear2ChainSwordAttack::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);

	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName,1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult Bear2ChainSwordAttack::UpdateActionExecution()
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

void Bear2ChainSwordAttack::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	std::static_pointer_cast<BearAnimationInstance>(mAnimInstance.lock())->SetAttack(false);
}

bool Bear2ChainSwordAttack::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

void Bear2ChainSwordAttack::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<Bear2ChainSwordAttack>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
