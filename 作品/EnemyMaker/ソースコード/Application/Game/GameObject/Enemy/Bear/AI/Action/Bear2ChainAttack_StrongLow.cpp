//---------- INCLUDES -----------
#include "Bear2ChainAttack_StrongLow.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../BearEnemy.h"
#include "../../../../../../Utility/MathLibrary.h"
#include "../../../AIBase/BlackBoard.h"

Bear2ChainAttack_StrongLow::Bear2ChainAttack_StrongLow(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(Bear2ChainAttack_StrongLow).name();
	mAttackID = BearEnemyAttackData::DoubleSlash_StrongLow;
}

Bear2ChainAttack_StrongLow::~Bear2ChainAttack_StrongLow()
{
	// 処理なし
}

void Bear2ChainAttack_StrongLow::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName, 1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult Bear2ChainAttack_StrongLow::UpdateActionExecution()
{
	// 名前空間省略
	using namespace DirectX::SimpleMath;

	// 親クラス内で時間の計測をしているので呼び出す
	BearAttackAction::UpdateActionExecution();
		
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

void Bear2ChainAttack_StrongLow::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool Bear2ChainAttack_StrongLow::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

void Bear2ChainAttack_StrongLow::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<Bear2ChainAttack_StrongLow>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
