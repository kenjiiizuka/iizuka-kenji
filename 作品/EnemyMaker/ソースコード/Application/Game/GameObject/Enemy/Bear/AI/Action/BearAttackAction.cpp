//---------- INCLUDES -------------
#include "BearAttackAction.h"
#include "../../../AIBase/BlackBoard.h"
#include "../../../EnemyWeapon.h"
#include "../../BearEnemy.h"
#include "../../../AIBase/Sensor/EnemyAttackHitSensor.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/MathLibrary.h"
#include "../../../../../../Utility/DetectorUtility.h"

//------------ NAMESPACEAILAS --------------
using namespace DirectX::SimpleMath;

BearAttackAction::BearAttackAction(std::shared_ptr<BlackBoard> _blackBoard)
	: EnemyAttackAction(_blackBoard)
	, mBearEnemy(nullptr)
{
	// 処理なし
}

void BearAttackAction::BeginActionExecution(EnemyBase* _enemy)
{
	EnemyAttackAction::BeginActionExecution(_enemy);

	// アニメーションインスタンス、敵、武器の参照を取得する
	std::weak_ptr<AnimationInstance> animIns = _enemy->GetAnimationInstance();	
	mAnimInstance = std::static_pointer_cast<BearAnimationInstance>(animIns.lock());
	mBearEnemy = static_cast<BearEnemy*>(mEnemy);
	mWeapon = mBearEnemy->GetWeapon();

	EnemyAttack attack = mBearEnemy->GetAttackData().lock()->GetAttack(mAttackID);

	// 再生するアニメーションクリップの名前を取得する
	mAnimationClipName = attack.mAnimationClipName;
	
	// アイドルアニメーションへの補間速度をセットする
	mAnimInstance.lock()->SetToIdleRunInterpTime(attack.mToIdleRunInterpTime);

	// センサーにコリジョンをセットする
	mHitSensor->SetCollision(mWeapon.lock()->GetAttackCollision());
}

void BearAttackAction::EndActionExecution()
{
	EnemyAttackAction::EndActionExecution();
}

bool BearAttackAction::IsExecuteAble()
{
	if (!mBearEnemy)
	{
		mBearEnemy = static_cast<BearEnemy*>(mEnemy);
	}

	// 実行条件を取得
	EnemyAttackExecutionConditions conditions = mBearEnemy->GetAttackData().lock()->GetAttack(mAttackID).mExecutionCondition;

	 std::shared_ptr<TransformComponent> transform = mBearEnemy->GetComponent<TransformComponent>();
	Vector3 forward = transform->GetForwardVector();
	Vector3 enemyPos = transform->GetPosition();

	// プレイヤーの位置
	Vector3 targetPos = mBlackBoard->GetValue<Vector3>("TargetPosition");
	// デバッグ表示用のカラーを設定 デフォルトは紫
	Vector4 color = {0.7f,0.0f,1.0f,1.0f};
	
	bool isExecute = false;
	for (size_t condition_i = 0; condition_i < conditions.mExecuteCheckCircleNum; condition_i++)
	{
		// 前向きベクトルを回転させ、判定円への方向ベクトルにする
		Vector3 rotation = { 0.0f,conditions.mAngle[condition_i], 0.0f };
		Vector3 toCircleVector = MathLibrary::RotateVector(forward,rotation);

		// 円の位置を求める
		Vector3 circleCenter = toCircleVector * conditions.mDistance[condition_i] + enemyPos;

		// 判定円内に入っているかを確認する
	 	isExecute = DetectorUtility::IsPositionInCircle2D(
			{ targetPos.x, targetPos.z },
			{ circleCenter.x, circleCenter.z },
			conditions.mCircleRadius[condition_i],
			color
			);

		// 実行可能ならtureを返す
		if (isExecute)
			return true;
	}

	return isExecute;
}

