//------------- INCLUDES ---------------
#include "BearSwordSwingUpAttack.h"
#include "../../../../../../Utility/MathLibrary.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../../EnemyBase.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../AIBase/BlackBoard.h"

// 名前空間エイリアス
namespace DXSimpleMath = DirectX::SimpleMath;

BearSwordSwingUpAttack::BearSwordSwingUpAttack(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(BearSwordSwingUpAttack).name();
	mAttackID = BearEnemyAttackData::UpwardSlash;
}

void BearSwordSwingUpAttack::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);

	AnimationPlaySetting setting = AnimationInf::AnimationPlayType::PlayType_PositionSynchro;
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName, 1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult BearSwordSwingUpAttack::UpdateActionExecution()
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

void BearSwordSwingUpAttack::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool BearSwordSwingUpAttack::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

void BearSwordSwingUpAttack::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<BearSwordSwingUpAttack>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
