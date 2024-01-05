#include "EnemyAttackAction.h"
#include "../../../../../../System/FPSController/FPSController.h"
#include "../../Sensor/EnemyAttackHitSensor.h"
#include "../../../../../../System/Logger/Logger.h"
#include <iostream>


EnemyAttackAction::EnemyAttackAction(std::shared_ptr<BlackBoard> _blackBoard)
	: EnemyAction(_blackBoard)
	, mEffectivenessToPlayer(0.0f)
	, mReceptivityToPlayer(0.0f)
	, mRiskType(GeneticAlgorithmInf::AttackAction_None)
{
	mHitSensor = std::make_shared<EnemyAttackHitSensor>();
	ResizeNumberOfEvaluationItems(3); // 3 攻撃遺伝子の評価項目は３つだから
}

void EnemyAttackAction::Evaluate(std::shared_ptr<BlackBoard> _blackboard)
{
	// オーバーロードされている方を使用してください
}

void EnemyAttackAction::Evaluate(std::shared_ptr<BlackBoard> _blackboard, const AttackEvaluationThreshold& _threshold)
{		
	/// 評価項目2 「プレイヤーに対して有効なのか」が高く、評価項目3 「プレイヤーがこの攻撃をどのくらい対処できるのか」が高い場合
	/// ハイリスクハイリターンの行動
	if (mEffectivenessToPlayer > _threshold[GeneticAlgorithmInf::Attack_Effective] 
		&& mReceptivityToPlayer > _threshold[GeneticAlgorithmInf::Attack_PlayerReceptivity])
	{
		mRiskType = GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn;
	}
	// ロウリスクハイリターン
	else if(mEffectivenessToPlayer > _threshold[GeneticAlgorithmInf::Attack_Effective]
		&& mReceptivityToPlayer < _threshold[GeneticAlgorithmInf::Attack_PlayerReceptivity])
	{
		mRiskType = GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn;
	}
	// ハイリスクロウリターン
	else if (mEffectivenessToPlayer < _threshold[GeneticAlgorithmInf::Attack_Effective]
		 && mReceptivityToPlayer > _threshold[GeneticAlgorithmInf::Attack_PlayerReceptivity])
	{
		mRiskType = GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn;
	}
	// ロウリスクロウリターン
	else
	{
		mRiskType = GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn;
	}

	// ログに自身のリスクタイプと型名を記入
	{
		Logger& logger = Logger::GetInstance();
		// 評価項目値を出力
		logger.WriteLog("EffectivenessToPlayer : " + std::to_string(mEffectivenessToPlayer));
		logger.WriteLog("ReceptivityToPlayer : " + std::to_string(mReceptivityToPlayer));

		std::string riskType = " : ";
		if (mRiskType == GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn)
			riskType += "AttackAction_LowRisk_LowReturn";
		else if (mRiskType == GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn)
			riskType += "AttackAction_HighRisk_LowReturn";
		else if (mRiskType == GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn)
			riskType += "AttackAction_LowRisk_HighReturn";
		else if (mRiskType == GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn)
			riskType += "AttackAction_HighRisk_HighReturn";

		Logger::GetInstance().WriteLog(mTypeName + riskType);
	}
}

void EnemyAttackAction::BeginActionExecution(EnemyBase* _enemy)
{
	// 親クラスで実行カウントを数えているので呼び出す
	EnemyAction::BeginActionExecution(_enemy);

	// 評価に必要な値を保持する配列などのサイズを変更する
	uint32_t executeCount = GetExecuteCount();
	mDamageInflicted.resize(executeCount);
	mDamageTakenDuringExecution.resize(executeCount);
	mExecutionTime.resize(executeCount);
}

EnemyActionResult EnemyAttackAction::UpdateActionExecution()
{
	// 現在の実行数を取得する
	uint32_t executeCount = GetExecuteCount();

	// 実行された回数は添え字として使用するので０以下にならないようにチェックする
	uint32_t executionCount_i = executeCount > 0 ? executeCount - 1 : 0;

	// 攻撃がヒットしたかをチェックするセンサーの更新
	mHitSensor->Update();
	
	// コリジョンが当たっていたらダメージを設定する
	if (mHitSensor->IsCollisionHit())
	{
		mDamageInflicted[executionCount_i] = mHitSensor->GetHitDamage();
	}
	
	// 実行時間を加算する
	mExecutionTime[executionCount_i] += static_cast<float>(FPSController::GetDeltaTime());

	return EnemyActionResult::Succeeded;
}
