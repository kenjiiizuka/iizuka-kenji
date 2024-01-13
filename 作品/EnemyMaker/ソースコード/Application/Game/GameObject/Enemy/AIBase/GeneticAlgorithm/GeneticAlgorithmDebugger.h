/**
* @file GeneticAlgorithmDebugger.h
* @brief GeneticAlgorithmDebuggerクラスの定義
*/


#pragma once

//--------- INCLUDES -----------
#include <memory>
#include <string>
#include <SimpleMath.h>
#include "../../../../../System/Singleton.h"
#include "GeneticInfomation.h"
#include "../GeneticAlgorithm/EnemyGeneticAlgorithm.h"


//--------- 前方宣言 -----------
class EnemyAttackAction;
class EnemyMoveAction;

/**
* @class GeneticAlgorithmDebugger
* @brief 遺伝学習アルゴリズムのデバッガ－
*/
class GeneticAlgorithmDebugger final : public Singleton<GeneticAlgorithmDebugger>
{
   /**----------------------------------------------------------------------------------------------
   * 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
   * クラス外から生成、破棄できないようにするためにフレンド指定する
   ------------------------------------------------------------------------------------------------*/
	friend class Singleton<GeneticAlgorithmDebugger>;

private:
	/**
	 * デフォルトコンストラクタ
	*/
	GeneticAlgorithmDebugger();

	/**
	 * デストラクタ
	*/
	~GeneticAlgorithmDebugger()
	{
		// 処理なし
	}

	/**
	* コピーコンストラクタ
	* コピー禁止のため代入禁止
	*/
	GeneticAlgorithmDebugger(const GeneticAlgorithmDebugger&) = delete;
	
	/**
	* 代入演算子のオーバーロード
	* 代入禁止のため delete指定
	*/
	void operator= (const GeneticAlgorithmDebugger&) = delete;

private:
	/** 遺伝子データ */
	std::vector<std::shared_ptr<Gene>> mGenes;

	/** 表示する遺伝子の添え字 */
	size_t mDisplayGeneticIndex;

	/** 現在使用している遺伝子の添え字 */
	size_t mCurrentGeneIndex;

	/** 今の遺伝子の世代 */
	size_t mGenerationCount;

	/** 攻撃遺伝子の評価値を表示するか */
	bool mbDisplayAttackGeneEvaluation;

	/** 攻撃遺伝子の評価値のためのデータを表示するか */
	bool mbDisplayAttackGeneEvaluationData;

	/** 移動遺伝子の評価値を表示するか */
	bool mbDisplayMoveGeneEvaluation;

	/** 移動遺伝子の評価値のためのデータを表示するか */
	bool mbDisplayMoveGeneEvaluationData;

public:
	/**
	* @fn DisplayGeneticDebug
	* @brief デバッグ用のWindowを描画
	* @return void
	*/
	void DisplayGeneticDebug();

private:
	/**
	* @fn DisplayGenetic
	* @brief 遺伝子の内容を表示する
	* @param const std::shared_ptr<Gene>& (_genetic)
	* @return void
	*/
	void DisplayGenetic(const std::shared_ptr<Gene>& _genetic);

	/**
	* @fn DisplaySituation
	* @brief 状況遺伝子のデータを表示する
	* @param const std::shared_ptr<Gene>& _genetic
	* @return void
	*/
	void DisplaySituation(const std::shared_ptr<Gene>& _genetic);

	/**
	* @fn DisplayAttackGeneEvaluation
	* @brief 攻撃遺伝子の評価値を表示する
	* @param const AttackGenes& (_attackGenes) 評価値をデバッグ表示したい攻撃遺伝子
	* @return void
	*/
	void DisplayAttackGeneEvaluation(const AttackGenes& _attackGenes);

	/**
	* @fn DisplayAttackGeneEvaluationData
	* @brief 攻撃遺伝子を評価するためのデータをデバッグ表示する
	* @param const const AttackGenes& (_attackGenes) 評価値を求めるためのデータを表示したい攻撃遺伝子
	* @return void
	*/
	void DisplayAttackGeneEvaluationData(const AttackGenes& _attackGenes);

	/**
	* @fn DisplayMoveGeneEvaluationData
	* @brief 移動遺伝子を評価するためのデータをデバッグ表示する
	* @param const std::vector<std::weak_ptr<EnemyAttackAction>> (_moveGenes) 評価値を求めるためのデータを表示したい移動遺伝子
	* @return void
	*/
	void DisplayMoveGeneEvaluationData(const MoveGenes& _moveGenes);

public:
	/**
	* @fn SetDisplayGenetic
	* @brief 表示したい遺伝子データをセットする
	* @param const std::vector<Genetic>& (_genetic)
	*/
	inline void SetDisplayGenetic(const std::vector<std::shared_ptr<Gene>>& _genetic) noexcept;

	/**
	* @fn SetCurrentGenerationCount
	* @brief 現在の遺伝子の世代数をセットする
	* @param const size_t (_count)
	* @return void
	*/
	inline void SetCurrentGenerationCount(const size_t _count) noexcept;

	/**
	* @fn SetCurrentGeneIndex
	* @brief 現在使用している遺伝子の添え字
	* @param const size_t& (_index)
	* @return void
	*/
	inline void SetCurrentGeneIndex(const size_t& _index) noexcept;

	/**
	* @fn SetDisplayGeneIndex
	* @brief 表示したい遺伝子の添え字をセットする
	* @param const size_t& (_index)
	* @return void
	*/
	inline void SetDisplayGeneIndex(const size_t& _index) noexcept;

};

//----------- INLINES -------------

inline void GeneticAlgorithmDebugger::SetDisplayGenetic(const std::vector<std::shared_ptr<Gene>>& _genetic) noexcept
{
	mGenes = _genetic;
}

inline void GeneticAlgorithmDebugger::SetCurrentGenerationCount(const size_t _count) noexcept
{
	mGenerationCount = _count;
}

inline void GeneticAlgorithmDebugger::SetCurrentGeneIndex(const size_t& _index) noexcept
{
	mCurrentGeneIndex = _index;
}

inline void GeneticAlgorithmDebugger::SetDisplayGeneIndex(const size_t& _index) noexcept
{
	mDisplayGeneticIndex = _index;
}
