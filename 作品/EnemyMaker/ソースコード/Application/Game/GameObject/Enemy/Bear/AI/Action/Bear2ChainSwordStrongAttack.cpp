//------------ INCLUDES ----------
#include "Bear2ChainSwordStrongAttack.h"
#include "../../../EnemyBase.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../../AIBase/BlackBoard.h"

namespace DXSimpleMath = DirectX::SimpleMath;

Bear2ChainSwordStrongAttack::Bear2ChainSwordStrongAttack(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(Bear2ChainSwordStrongAttack).name();
	mAttackID = BearEnemyAttackData::DoubleSlash_Strong;
}

void Bear2ChainSwordStrongAttack::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName,1.0f,0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult Bear2ChainSwordStrongAttack::UpdateActionExecution()
{
	// 親クラス内で時間の計測をしているので呼び出す
	BearAttackAction::UpdateActionExecution();

	// 追従処理
	if (GetCurrentAnimationSection() == "FollowStart")
	{
		FollowRotation();
	}

	// アニメーションの終了判定があれば成功を返す、それ以外は実行中
	std::shared_ptr<AnimationPlayer> animPlayer = mAnimInstance.lock()->GetAnimationPlayer();
	if (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame())
	{
		return EnemyActionResult::Succeeded;
	}
	return EnemyActionResult::InProgress;
}

void Bear2ChainSwordStrongAttack::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool Bear2ChainSwordStrongAttack::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

void Bear2ChainSwordStrongAttack::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<Bear2ChainSwordStrongAttack>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
