/**
* @file GeneticDecisionDataGenerator.h
* @brief GeneticDecisionDataGeneratorクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include <type_traits>
#include "GeneticInfomation.h"
#include "Gene/EnemyAttackAction.h"


//---------- INCLUDES ----------
class EnemyAttackAction;
class Situation;
class BlackBoard;
class Gene;

/**
* @class GeneticDecisionDataGenerator
* @brief 遺伝子を生成するクラス
* @detail 初期遺伝子生成
* 　　　　遺伝させて次世代の遺伝子の生成をする
*/
class GeneticDecisionDataGenerator
{
public:
	/**
	* コンストラクタ
	*/
	GeneticDecisionDataGenerator(std::shared_ptr<BlackBoard> _blackboard);

	/**
	* デストラクタ
	*/
	~GeneticDecisionDataGenerator();

private:
	/** 遺伝子に対応したブラックボード */
	std::shared_ptr<BlackBoard> mBlackboard;

	/** 次世代の遺伝子 */
	std::vector<std::shared_ptr<Gene>> mNextGenerationGenes;

public:	
	/**
	 * @fn GenerateFirstGenetic
	 * @brief 最初の遺伝子をランダムに生成する
	 * @param const AttackGenetic& (_attackGeneType) 
	 * @param const MoveGenes&     (_moveGeneTypes)
	 * @param const size_t         (generateNum)
	 * @return void
	*/
	void GenerateFirstGenetic(const AttackGenes& _attackGeneType, const MoveGenes& _moveGeneTypes, const size_t generateNum);

	/**
	 * @fn Genetics
	 * @brief 今の世代の遺伝子データから次世代の遺伝子を遺伝させて作成する
	 * @param std::vector<std::shared_ptr<Gene>> (_genetic) 遺伝もと遺伝子
	 * @param AttackGenes&                       (_attackGeneTypes) 攻撃遺伝子の型判別よ用の変数
	 * @param MoveGenes&                         (_moveGeneTypes)1  移動遺伝子の型判別用の変数
	 * @return void
	*/
	void Genetics(std::vector<std::shared_ptr<Gene>> _genetic, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes);

private:
	/**
	* @fn SortByEvaluation
	* @brief 評価値の高い順に遺伝子を並べ替える
	* @param const std::vector<Genetic>& (_gene)
	* @return std::vector<Genetic> 並べ替えた遺伝子
	*/
	std::vector<std::shared_ptr<Gene>> SortByEvaluation(const std::vector<std::shared_ptr<Gene>>& _gene);

	/**
	* @fn PassOnGene
	* @brief 渡された遺伝子を遺伝させ、二つの遺伝子を生成する関数
	* @param const std::shared_ptr<Gene>&          (_gene1) 遺伝元遺伝子
	* @param const std::shared_ptr<Gene>&          (_gene2) 遺伝元遺伝子
	* @param std::array<std::shared_ptr<Gene>, 2>& (_newGene) 遺伝で生成された遺伝子
	* @return void
	*/
	void PassOnGene(const std::shared_ptr<Gene>& _gene1, const std::shared_ptr<Gene>& _gene2, std::array<std::shared_ptr<Gene>, 2>& _newGene);

	/**
	* @fn PassOnSituation
	* @brief 状況遺伝子を遺伝させ、二つの状況遺伝子を生成する関数
	* @param const std::shared_ptr<Situation> (_situation1)
	* @param const std::shared_ptr<Situation> (_situation2)
	* @param std::array<std::shared_ptr<Situation>, 2>& (_newSituation)
	* @return void
	*/
	void PassOnSituation(const std::shared_ptr<Situation> _situation1, const std::shared_ptr<Situation> _situation2, std::array<std::shared_ptr<Situation>, 2>& _newSituation);

	/**
	 * @fn CrossoverSinglePointAttackGenetic
	 * @brief 渡されたの攻撃遺伝子を一点交叉で遺伝させる関数
	 * @param const AttackGenes& (_attackGene1) 
	 * @param std::shared_ptr<Situation> (_priorityTwoSituation) 二番目に優先度が高いSituation遺伝子
	 * @return std::array<AttackGenetic,2> 一点交叉により生成された攻撃遺伝子
	*/
	std::array<AttackGenes,2> CrossoverSinglePointAttackGenetic(const AttackGenes& _attackGene1, const AttackGenes& _attackGene2);

	/**
	* @fn DuplicationMoveGenes
	* @brief 渡された状況遺伝子の移動遺伝子を複製する
	* @param std::shared_ptr<Situation> (_situation)
	* @return MoveGenes
	*/
	MoveGenes DuplicationMoveGenesFromSituation(std::shared_ptr<Situation> _situation);

	/**
	* @fn RandomGenerateGene
	* @brief 遺伝子をランダムで生成する
	* @param const AttackGenes& (_attackGeneTypes)
	* @param const MoveGenes&   (_moveGeneTypes)
	* @param std::shared_ptr<Gene>& (_newGene)
	* @void
	*/
	void RandomGenerateGene(const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes, std::shared_ptr<Gene>& _newGene);

	/**
	 * @fn RandomGenerateSituation
	 * @brief 遺伝子(Situation)をランダム生成する
	 * @param const AttackGenetic& (_attackGeneType)
	 * @param const MoveGenes& (_moveGeneTypes)
	 * @param std::shared_ptr<Situation>& (_generatedSituation)
	 * @return void
	*/
	void RandomGenerateSituation(const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes, std::shared_ptr<Situation>& _generatedSituation);

	/**
	 * @fn RandomGenerateAttackGene
	 * @brief 第一引数で指定された遺伝子型からランダムに重複しないように攻撃遺伝子を生成し第二引数に代入する
	 * @param const AttackGenes& (_attackGeneTypes) ランダム生成する際の型を選ぶ候補
	 * @param AttackGenes& (_generatedAttackGenes) 生成された遺伝子を代入する
	 * @return void
	*/
	void RandomGenerateAttackGene(const AttackGenes& _attackGeneTypes, AttackGenes& _generatedAttackGenes);

	/**
	 * @fn RandomGenerateMoveGene
	 * @brief 第一引数で指定された遺伝子型からランダムに重複しないように移動遺伝子を生成し第二引数に代入する
	 * @param const MoveGenes& (_moveGeneTypes) ランダム生成する際の型を選ぶ候補
	 * @param MoveGenes& (_generatedMoveGenes) 生成された遺伝子を代入する
	 * @return void
	*/
	void RandomGenerateMoveGene(const MoveGenes& _moveGeneTypes, MoveGenes& _generatedMoveGenes);

public:
	/**
	 * @fn GetGeneratedNextGenerationGene
	 * @brief 生成した次の世代の遺伝子を返す
	 * @return std::vector<std::shared_ptr<Gene>> 次の世代の遺伝子
	*/
	std::vector<std::shared_ptr<Gene>> GetNextGenerationGene() const;
};

//--------------------- INLINES ----------------------

inline std::vector<std::shared_ptr<Gene>> GeneticDecisionDataGenerator::GetNextGenerationGene() const
{
	return mNextGenerationGenes;
}