#include "Situation.h"
#include "EnemyAction.h"
#include "EnemyAttackAction.h"
#include "EnemyMoveAction.h"
#include "../../BlackBoard.h"
#include "../../../../../../System/Logger/Logger.h"

Situation::Situation()
	: mGoalAchievement(0)
	, mActionRiskTypeTargetRatio({0.3f,0.2f,0.2f,0.3f})
	, mCurrentRiskTypeRatio({})
	, mAttackEvaluationThreshold({0.5f,0.5f,0.5f})
	, mMoveEvaluationThreshold({0.5f,0.5f})
	, mbIsEvaluated(false)
{
}

void Situation::Evaluate(std::shared_ptr<BlackBoard> _blackboard)
{
	Logger& logger = Logger::GetInstance();

	// ログ書き込み
	logger.WriteLog("AttackGene RiskType");
	// 攻撃行動を評価する
	EvaluateAttack(_blackboard);

	// 現在の遺伝子のリスクタイプと目標のリスクタイプの差分を取る
	// 差分の合計を評価値にする
	mGoalAchievement = std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn]);
	mGoalAchievement = 1 - (mGoalAchievement / 4.0f);

	mbIsEvaluated = true;

	// ゴール値と現在の値をログに書き込む
	{
		// ゴールの値
		logger.WriteLog("GoalRatio");
		float value = mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn];
		logger.WriteLog("AttackAction_HighRisk_HighReturn : " + std::to_string(value));

		value = mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn];
		logger.WriteLog("AttackAction_HighRisk_LowReturn : " + std::to_string(value));

		value = mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn];
		logger.WriteLog("AttackAction_LowRisk_HighReturn : " + std::to_string(value));

		value = mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn];
		logger.WriteLog("AttackAction_LowRisk_LowReturn : " + std::to_string(value));

		// 現在の比率
		logger.WriteLog("CurrentRatio");
		value = mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn];
		logger.WriteLog("AttackAction_HighRisk_HighReturn : " + std::to_string(value));

		value = mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn];
		logger.WriteLog("AttackAction_HighRisk_LowReturn : " + std::to_string(value));

		value = mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn];
		logger.WriteLog("AttackAction_LowRisk_HighReturn : " + std::to_string(value));

		value = mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn];
		logger.WriteLog("AttackAction_LowRisk_LowReturn : " + std::to_string(value));

		logger.WriteLog("EvaluationValue : " + std::to_string(mGoalAchievement));
	}
}

void Situation::CalculateAllRiskTypeRatio()
{
	// 遺伝して設定された攻撃遺伝子のリスクタイプの割合を求める
	size_t actionNum = mAttackGenes.size();
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn, actionNum);

	// 現在の評価値を求める	
	mGoalAchievement = std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn]);
	mGoalAchievement = 1 - (mGoalAchievement / 4.0f);
}

void Situation::EvaluateAttack(std::shared_ptr<BlackBoard> _blackboard)
{
	size_t actionNum = mAttackGenes.size();
	std::vector<uint32_t> actionExecuteCounts(actionNum); // 行動の実行回数
	std::vector<float> inflictedDamages(actionNum);      // この戦闘で与えたダメージ
	std::vector<float> takenDamageDPS(actionNum);        // 実行中にくらった攻撃のＤＰＳ

	// 評価に必要なデータの取得
	for (size_t index = 0; index < actionNum; index++)
	{
		actionExecuteCounts[index] = mAttackGenes[index]->GetExecuteCount();
		inflictedDamages[index] = mAttackGenes[index]->GetAveragedDamageInflicted();
		takenDamageDPS[index] = mAttackGenes[index]->GetAveragedDamageTakenExecution() / mAttackGenes[index]->GetAveragedExecutionTime();
	}

	uint32_t maxExecuteCount = *std::max_element(actionExecuteCounts.begin(), actionExecuteCounts.end()); // 一番多く実行された回数を取得
	float maxInflictedDamage = *std::max_element(inflictedDamages.begin(), inflictedDamages.end());     // 一番高い与えたダメージ
	float maxTakenDPS = *std::max_element(takenDamageDPS.begin(), takenDamageDPS.end());                // 最大ＤＰＳ

	for (size_t index = 0; index < actionNum; index++)
	{
		// 評価1 この攻撃がプレイヤーに対して有効なのか
		float effectiveness = maxInflictedDamage == 0 ? 0 : inflictedDamages[index] / maxInflictedDamage;
		mAttackGenes[index]->SetEffectivenessToPlayer(effectiveness);
		// 評価2 この攻撃はプレイヤーにどの程度対処されているか
		float receptivity = maxTakenDPS == 0 ? 0 : takenDamageDPS[index] / maxTakenDPS;
		mAttackGenes[index]->SetReceptivityToPlayer(receptivity);
		// 評価項目からこの攻撃がプレイヤーにとってどのような攻撃なのかを評価する
		mAttackGenes[index]->Evaluate(_blackboard, mAttackEvaluationThreshold);
	}

	// 各RiskTypeがこのSituationに設定された目標とどれだけあっているかを判断する
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn, actionNum);
}

size_t Situation::CountRiskType(const GeneticAlgorithmInf::AttackActionRiskType _riskType)
{
	size_t count = 0;
	for (std::shared_ptr<EnemyAttackAction> attack : mAttackGenes)
	{
		if (_riskType ==  attack->GetAttackActionRiskType())
		{
			count++;
		}
	}
	return count;
}

void Situation::CalucRiskTypeRatio(const GeneticAlgorithmInf::AttackActionRiskType _riskType, const size_t _actionNum)
{
	float highRiskHighReturnNum = static_cast<float>(CountRiskType(_riskType));

	if (highRiskHighReturnNum == 0)
	{
		mCurrentRiskTypeRatio[_riskType] = 0.0f;
	}
	else
	{
		mCurrentRiskTypeRatio[_riskType] = highRiskHighReturnNum / static_cast<float>(_actionNum);
	}
}

bool Situation::IsSituationSuitable(std::shared_ptr<BlackBoard> _blackBoard)
{
	// BlackBoardの情報から今のSituationが適しているかを判断する
	return true;
	// return mSituationSuitable(_blackBoard);
}

