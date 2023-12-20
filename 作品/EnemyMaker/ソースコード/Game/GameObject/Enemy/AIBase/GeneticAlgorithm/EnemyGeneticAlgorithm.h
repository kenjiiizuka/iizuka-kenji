/**
* @file EnemyGeneticAlgorithm.h
* @brief EnemyGeneticAlgorithmクラスの定義
*/

#pragma once

//----------- INCLUDES ----------
#include "IGeneticAlgorithm.h"

//---------- 前方宣言 -----------
class DecisionEvaluator;
class GeneticDecisionDataGenerator;
class EnemyBase;
class GeneDataSaver;
class GeneDataLoader;
class Gene;

/** エネミーの遺伝学習のプロセスを管理するクラス */
class EnemyGeneticAlgorithm  : public IGeneticAlgorithm
{
public:
	/**
	* コンストラクタ
	* 
	* @param std::shared_ptr<BlackBoard>& (_blackboard)
	*/
	EnemyGeneticAlgorithm(std::shared_ptr<BlackBoard>& _blackboard);

private:
	/** 現在の世代の遺伝子 */
	std::vector<std::shared_ptr<Gene>> mCurrentGenerationGenes;

	/** 何世代目なのか */
	size_t mGenerationCount;

	/** 今の世代の遺伝子の数 */
	size_t mCurrentGenerationGenesSize;

	/** 今の遺伝子でデータを収集した回数（戦闘をして結果がでた回数） */
	size_t mCurrentDataCollectionCount;

	/** 現在データを収集している遺伝子の添え字 */
	size_t mCurrentDataCollectionGene_i;

	/** 評価に必要なデータの収集回数 */
	const size_t mNeedCurrentDataCollectionCont = 1;

	/** 初期の遺伝子を生成する数 */
	const size_t mFirstGenerateGeneNum = 3;

	/** 意思決定データ(遺伝子)の評価をするクラス */
	std::shared_ptr<DecisionEvaluator> mDecisionEvaluator;
	
	/** 意思決定データの生成をするクラス */
	std::shared_ptr<GeneticDecisionDataGenerator> mGenerator;

protected:
	/** ブラックボード */
	std::shared_ptr<BlackBoard> mBlackBoard;

	/** 攻撃遺伝子を生成する際に使用 */
	AttackGenes mAttackGeneTypes;

	/** 移動遺伝を生成する際に使用 */
	MoveGenes mMoveGeneTypes;

	/** 遺伝子データのセーブクラス */
	std::shared_ptr<GeneDataSaver> mGeneDataSaver;

	/** 遺伝子データのロードクラス */
	std::shared_ptr<GeneDataLoader> mGeneDataLoader;

public:
	/**
	 * @fn Init
	 * @brief 初期化関数
	 * @return void
	*/
	void Init() override;

	/**
	 * @fn CreateFirstGeneration
	 * @brief 第一世代の遺伝子を生成する
	 * @return void
	*/
	void GenerateFirstGenes() override;

	/**
	 * @fn Evaluate
	 * @brief 遺伝子の評価関数
	 * @return void
	*/
	void Evaluate() override;

	/**
	 * @fn Evaluate
	 * @brief 遺伝子の評価関数 デバッグ
	 * @return void
	*/
	virtual void DebugEvaluate();

	/**
	 * @fn GeneSave
	 * @brief 遺伝子のセーブ
	 * @return void
	*/
	void GeneSave() override;

	/**
	 * @fn GeneratingNextGeneration
	 * @brief 次の世代の生成関数
	 * @detail 遺伝させるのに十分なデータが集まっていれば遺伝させ次の世代の遺伝子を取得         
	 * @return void
	*/
	void GenerateGenetic() override;

	/**
	* @fn Genetics
	* @brief 遺伝させる
	* @detail 評価し十分データの集まった遺伝子を遺伝させ、次の世代の遺伝子を取得する
	* @return void
	*/
	void Genetics() override;

	/**
	 * @fn GetGenetic
	 * @brief 遺伝子を返す
	 * @detail データ収集に使用する遺伝子を返す
	 * @return std::shared_ptr<Gene>
	*/
	std::shared_ptr<Gene> GetGene() const override;

	/**
	* @fn GetFirstGenerationGeneNum
	* @brief 初期遺伝子を生成する数を返す
	* @return size_t
	*/
	inline size_t GetFirstGenerationGeneNum() const noexcept;

protected:
	/**
	 * @fn SetupAttackGeneType
	 * @brief 生成する攻撃、移動遺伝子の型判別用変数の生成
	 * @detail 継承先で、使用する攻撃、移動遺伝子の型判別用変数を生成
	 *         生成された変数から遺伝や、遺伝子の生成を行う
	 * @return void
	*/
	virtual void SetupGeneType() = 0;
};

//--------------- INLINES -------------------

inline size_t EnemyGeneticAlgorithm::GetFirstGenerationGeneNum() const noexcept
{
	return mFirstGenerateGeneNum;
}