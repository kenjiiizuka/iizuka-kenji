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

	// ���O��������
	logger.WriteLog("AttackGene RiskType");
	// �U���s����]������
	EvaluateAttack(_blackboard);

	// ���݂̈�`�q�̃��X�N�^�C�v�ƖڕW�̃��X�N�^�C�v�̍��������
	// �����̍��v��]���l�ɂ���
	mGoalAchievement = std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn]);
	mGoalAchievement = 1 - (mGoalAchievement / 4.0f);

	mbIsEvaluated = true;

	// �S�[���l�ƌ��݂̒l�����O�ɏ�������
	{
		// �S�[���̒l
		logger.WriteLog("GoalRatio");
		float value = mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn];
		logger.WriteLog("AttackAction_HighRisk_HighReturn : " + std::to_string(value));

		value = mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn];
		logger.WriteLog("AttackAction_HighRisk_LowReturn : " + std::to_string(value));

		value = mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn];
		logger.WriteLog("AttackAction_LowRisk_HighReturn : " + std::to_string(value));

		value = mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn];
		logger.WriteLog("AttackAction_LowRisk_LowReturn : " + std::to_string(value));

		// ���݂̔䗦
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
	// ��`���Đݒ肳�ꂽ�U����`�q�̃��X�N�^�C�v�̊��������߂�
	size_t actionNum = mAttackGenes.size();
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn, actionNum);
	CalucRiskTypeRatio(GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn, actionNum);

	// ���݂̕]���l�����߂�	
	mGoalAchievement = std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn]);
	mGoalAchievement += std::abs(mActionRiskTypeTargetRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn] - mCurrentRiskTypeRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn]);
	mGoalAchievement = 1 - (mGoalAchievement / 4.0f);
}

void Situation::EvaluateAttack(std::shared_ptr<BlackBoard> _blackboard)
{
	size_t actionNum = mAttackGenes.size();
	std::vector<uint32_t> actionExecuteCounts(actionNum); // �s���̎��s��
	std::vector<float> inflictedDamages(actionNum);      // ���̐퓬�ŗ^�����_���[�W
	std::vector<float> takenDamageDPS(actionNum);        // ���s���ɂ�������U���̂c�o�r

	// �]���ɕK�v�ȃf�[�^�̎擾
	for (size_t index = 0; index < actionNum; index++)
	{
		actionExecuteCounts[index] = mAttackGenes[index]->GetExecuteCount();
		inflictedDamages[index] = mAttackGenes[index]->GetAveragedDamageInflicted();
		takenDamageDPS[index] = mAttackGenes[index]->GetAveragedDamageTakenExecution() / mAttackGenes[index]->GetAveragedExecutionTime();
	}

	uint32_t maxExecuteCount = *std::max_element(actionExecuteCounts.begin(), actionExecuteCounts.end()); // ��ԑ������s���ꂽ�񐔂��擾
	float maxInflictedDamage = *std::max_element(inflictedDamages.begin(), inflictedDamages.end());     // ��ԍ����^�����_���[�W
	float maxTakenDPS = *std::max_element(takenDamageDPS.begin(), takenDamageDPS.end());                // �ő�c�o�r

	for (size_t index = 0; index < actionNum; index++)
	{
		// �]��1 ���̍U�����v���C���[�ɑ΂��ėL���Ȃ̂�
		float effectiveness = maxInflictedDamage == 0 ? 0 : inflictedDamages[index] / maxInflictedDamage;
		mAttackGenes[index]->SetEffectivenessToPlayer(effectiveness);
		// �]��2 ���̍U���̓v���C���[�ɂǂ̒��x�Ώ�����Ă��邩
		float receptivity = maxTakenDPS == 0 ? 0 : takenDamageDPS[index] / maxTakenDPS;
		mAttackGenes[index]->SetReceptivityToPlayer(receptivity);
		// �]�����ڂ��炱�̍U�����v���C���[�ɂƂ��Ăǂ̂悤�ȍU���Ȃ̂���]������
		mAttackGenes[index]->Evaluate(_blackboard, mAttackEvaluationThreshold);
	}

	// �eRiskType������Situation�ɐݒ肳�ꂽ�ڕW�Ƃǂꂾ�������Ă��邩�𔻒f����
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
	// BlackBoard�̏�񂩂獡��Situation���K���Ă��邩�𔻒f����
	return true;
	// return mSituationSuitable(_blackBoard);
}

