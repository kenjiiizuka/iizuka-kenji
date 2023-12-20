//-------------- INCLUDES ------------
#include "Bear3ChainSwordAttack.h"
#include "../../../EnemyBase.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../../AIBase/BlackBoard.h"

// 名前空間エイリアス
namespace DXSimpleMath = DirectX::SimpleMath;

Bear3ChainSwordAttack::Bear3ChainSwordAttack(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(Bear3ChainSwordAttack).name();
	mAttackID = BearEnemyAttackData::TripleSlash;
}

void Bear3ChainSwordAttack::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);// 親クラスで実行回数の加算と配列の拡張しているので呼び出す

	// アニメーションの再生	
	AnimationPlaySetting setting = 0;
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName,1.0f,0.2f);
	mAnimInstance.lock()->SetAttack(true);

}

EnemyActionResult Bear3ChainSwordAttack::UpdateActionExecution()
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

void Bear3ChainSwordAttack::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool Bear3ChainSwordAttack::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

bool Bear3ChainSwordAttack::IsValidAction()
{
	return true;
}

void Bear3ChainSwordAttack::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<Bear3ChainSwordAttack>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
