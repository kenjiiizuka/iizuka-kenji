/**
* @file DecisionEvaluator.h
* @brief DecisionEvaluatorクラスの定義
*/
#pragma once

//--------- INCLUDES ---------
#include <vector>
#include <memory>
#include "GeneticInfomation.h"

//--------- 前方宣言 --------
class Situation;
class BlackBoard;

/**
* @class DecisionEvaluator
* @brief 意思決定データを評価する機能を持つ
*/
class DecisionEvaluator final
{
public:
	/**
	* 値の初期化
	*/
	DecisionEvaluator(std::shared_ptr<BlackBoard> _blackboard);

private:
	/** ブラックボード */
	std::shared_ptr<BlackBoard> mBlackBoard;

public:
	/**
	 * @fn EvaluateGenetics
	 * @brief 評価関数
	 * @param std::shared_ptr<BlackBoard> (_blackboard) 
	 * @param std::vector<std::shared_ptr<Gene>>& (_genes)
	 * @param const size_t (evoluteIndex) 評価したい遺伝子の添え字
	 * @return void
	*/
	void EvaluateGenetics(std::shared_ptr<BlackBoard> _blackboard, std::vector<std::shared_ptr<Gene>>& _genes, const size_t evaluateIndex);

private:
	/**
	* @fn AdaptationEvaluation
	* @brief 遺伝子の評価を他の遺伝子に適応する
	* @detail 評価し、分類分けされた攻撃を他の遺伝子の同じ攻撃遺伝子に割り振る
	* @param std::vector<std::shared_ptr<Gene>>& (_genes)
	* @param const size_t (_index)
	* @return void
	*/
	void AdaptationEvaluation(std::vector<std::shared_ptr<Gene>>& _genes, const size_t _index);

	/**
	* @fn AdaptationEvaluationToSituation
	* @brief 状況遺伝子に評価を適応する
	* @detail 評価によって分類が変わった攻撃遺伝子の情報を適応している
	* @param std::shared_ptr<Gene>& (_adaptGene) 適応先遺伝子
	* @param std::shared_ptr<Gene>& (_adaptBaseGene) 適応元遺伝子
	* @return void
	*/
	void AdaptationEvaluationToSituation(std::shared_ptr<Gene>& _adaptGene, std::shared_ptr<Gene>& _adaptBaseGene);

	/**
	* @fn AdaptAttackGene
	* @brief 攻撃遺伝子に評価を適応する
	* @param AttackGenes& (_adaptAttackGenes)
	* @param AttackGenes& (_adaptBaseAttackGenes)
	* @return void
	*/
	void AdaptAttackGene(AttackGenes& _adaptAttackGenes, AttackGenes& _adaptBaseAttackGenes);
};


