//--------- INCUDES ---------
#include "BearSlashWeak.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/MathLibrary.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../BearEnemy.h"
#include "../../../AIBase/BlackBoard.h"

BearSlashWeak::BearSlashWeak(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(BearSlashWeak).name();
	mAttackID = BearEnemyAttackData::ArmUpperSmash;
}

BearSlashWeak::~BearSlashWeak()
{
	// 処理なし
}

void BearSlashWeak::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName, 1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult BearSlashWeak::UpdateActionExecution()
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

void BearSlashWeak::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool BearSlashWeak::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();	
}

void BearSlashWeak::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<BearSlashWeak>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
