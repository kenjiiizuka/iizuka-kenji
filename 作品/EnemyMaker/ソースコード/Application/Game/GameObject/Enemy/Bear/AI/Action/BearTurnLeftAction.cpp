//------------ INCLUDES ------------
#include "BearTurnLeftAction.h"
#include "../../../../../../Utility/MathLibrary.h"
#include "../../../EnemyBase.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../AIBase/BlackBoard.h"
#include "../../../../../../Utility/DetectorUtility.h"

// 名前空間エイリアス 
namespace DXSimpleMath = DirectX::SimpleMath;


BearTurnLeftAction::BearTurnLeftAction(std::shared_ptr<BlackBoard> _blackBoard)
	: EnemyMoveAction(_blackBoard)
{
	mTypeName = typeid(BearTurnLeftAction).name();
}

void BearTurnLeftAction::BeginActionExecution(EnemyBase* _enemy)
{	
	// ターンアニメーションを再生する
	mAnimInstance = mEnemy->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	mAnimInstance.lock()->PlayAnimationClip("TurnLeft",1.0f, 0.2f); // アニメーションクリップ名 , 再生速度、補間する秒数

	std::static_pointer_cast<BearAnimationInstance>(mAnimInstance.lock())->SetMove(true);

}

EnemyActionResult BearTurnLeftAction::UpdateActionExecution()
{
	// アニメーションが終了するなら成功を返
	std::shared_ptr<AnimationPlayer> animPlayer = mAnimInstance.lock()->GetAnimationPlayer();
	if (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame())
	{
		return EnemyActionResult::Succeeded;
	}

	// アニメーション中なら処理中を返す
	return EnemyActionResult::InProgress;
}

void BearTurnLeftAction::EndActionExecution()
{
	std::static_pointer_cast<BearAnimationInstance>(mAnimInstance.lock())->SetMove(false);
}

bool BearTurnLeftAction::IsExecuteAble()
{
	// 自身の左側に扇型を出して、その範囲プレイヤー居れば振り向く

	std::shared_ptr<TransformComponent> transform = mEnemy->GetComponent<TransformComponent>();
	
	// 扇形の始点
	DXSimpleMath::Vector3 enemyPos = transform->GetPosition();

	// 扇型の終点を設定
	// 左斜め後ろを終点にするために、BackとLeftベクトルのハーフベクトルにLeftベクトルを加算
	DXSimpleMath::Vector3 leftVector = -MathLibrary::GetRightVector(transform->GetRotation());
	DXSimpleMath::Vector3 backVector = -MathLibrary::GetForwardVector(transform->GetRotation());
	DXSimpleMath::Vector3 toEndPointVector = backVector + leftVector;
	DXSimpleMath::Vector3 sectorEndPos = enemyPos + (toEndPointVector * 100.0f);
	float sectorDegree = 70.0f;

	DXSimpleMath::Vector3 playerPos = mBlackBoard->GetValue<DXSimpleMath::Vector3>("TargetPosition");

	return DetectorUtility::IsPositionInSector2D
	(
		{ playerPos.x, playerPos.z },
		{ enemyPos.x, enemyPos.z },
		{ sectorEndPos.x, sectorEndPos.z },
		sectorDegree,
		{1,1,0,1}
	);
}

bool BearTurnLeftAction::IsValidAction()
{
	return true;
}

void BearTurnLeftAction::DuplicateFromSelfType(std::shared_ptr<EnemyMoveAction>& _output)
{
	_output = std::make_shared<BearTurnLeftAction>(mBlackBoard);
}
