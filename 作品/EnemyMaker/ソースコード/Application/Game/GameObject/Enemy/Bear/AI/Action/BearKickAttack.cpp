//-------------- INCLUDES -------------
#include "BearKickAttack.h"
#include "../../../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../../../Resource/Skeleton.h"
#include "../../../../../Resource/Bone.h"
#include "../../../EnemyBase.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../../AIBase/BlackBoard.h"
#include "../../../../../Resource/SkeletalMeshAnimationClip.h"
#include "../../../EnemyAttackCollisionAttachNotifyState.h"
#include "../../../AIBase/Sensor/EnemyAttackHitSensor.h"

// 名前空間エイリアス
namespace DXSimpleMath = DirectX::SimpleMath;

BearKickAttack::BearKickAttack(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(BearKickAttack).name();
	mAttackID = BearEnemyAttackData::Kick;
}

void BearKickAttack::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行回数の加算と配列の拡張しているので呼び出す
	BearAttackAction::BeginActionExecution(_enemy);	
	
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName,1.0f,0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult BearKickAttack::UpdateActionExecution()
{
	// 攻撃用のコリジョンをセンサーにセットする アニメーション通知ないで生成しているコリジョンなのでマイフレームセットするようにする
	std::shared_ptr<SkeletalMeshAnimationClip> kickClip = mAnimInstance.lock()->GetAnimationClipByName("Kick");
	std::weak_ptr<EnemyAttackCapsuleCollisionComponent> attackCollision = kickClip->GetAnimnotifyState<EnemyAttackCollisionAttachNotifyState>()->GetAttackCollision();
	mHitSensor->SetCollision(attackCollision);


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

void BearKickAttack::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool BearKickAttack::IsExecuteAble()
{	
	return BearAttackAction::IsExecuteAble();
}

void BearKickAttack::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<BearKickAttack>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
