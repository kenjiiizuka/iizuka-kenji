#include "DecisionEvaluator.h"
#include "Gene/Gene.h"
#include "../../../../../Utility/MathLibrary.h"
#include "GeneticInfomation.h"
#include "../GeneticAlgorithm/Gene/EnemyAttackAction.h"

DecisionEvaluator::DecisionEvaluator(std::shared_ptr<BlackBoard> _blackboard)
	: mBlackBoard(_blackboard)
{
}

void DecisionEvaluator::EvaluateGenetics(std::shared_ptr<BlackBoard> _blackboard, std::vector<std::shared_ptr<Gene>>& _genes, const size_t _evaluateIndex)
{
	// 遺伝子の評価
	_genes[_evaluateIndex]->Evaluate(_blackboard);
	AdaptationEvaluation(_genes, _evaluateIndex);
}

void DecisionEvaluator::AdaptationEvaluation(std::vector<std::shared_ptr<Gene>>& _genes, const size_t _index)
{
	for (size_t gene_i = 0; std::shared_ptr<Gene>& adaptGene : _genes)
	{
		// 適応元と同じならスキップ
		if (gene_i == _index)
		{
			gene_i++;
			continue;
		}
		// 状況遺伝子に評価値を適応
		AdaptationEvaluationToSituation(adaptGene, _genes[_index]);
		gene_i++;
	}
}

void DecisionEvaluator::AdaptationEvaluationToSituation(std::shared_ptr<Gene>& _adaptGene, std::shared_ptr<Gene>& _adaptBaseGene)
{
	std::vector<std::shared_ptr<Situation>> adaptSituations = _adaptGene->GetSituations();
	std::vector<std::shared_ptr<Situation>> adaptBaseSituations = _adaptBaseGene->GetSituations();

	// 評価によって分類されたことを適応する
	for (size_t situation_i = 0; std::shared_ptr<Situation>& adaptSituation : adaptSituations)
	{
	 	AttackGenes adaptAttackGene = adaptSituation->GetAttackGenes();
		AttackGenes adaptBaseAttackGene = adaptBaseSituations[situation_i]->GetAttackGenes();
		AdaptAttackGene(adaptAttackGene, adaptBaseAttackGene);
		adaptSituation->CalculateAllRiskTypeRatio();
		situation_i++;
	}

}

void DecisionEvaluator::AdaptAttackGene(AttackGenes& _adaptAttackGenes, AttackGenes& _adaptBaseAttackGenes)
{
	// 名前照合して一致する攻撃に評価を適応する
	for (std::shared_ptr<EnemyAttackAction> adaptBaseAttack : _adaptBaseAttackGenes)
	{
		for (std::string baseName = adaptBaseAttack->GetTypeName() ;std::shared_ptr<EnemyAttackAction> adaptAttack : _adaptAttackGenes)
		{
			if (baseName == adaptAttack->GetTypeName())
			{
				adaptAttack->SetAttackActionRiskType(adaptBaseAttack->GetAttackActionRiskType());
			}
		}
	}
}

