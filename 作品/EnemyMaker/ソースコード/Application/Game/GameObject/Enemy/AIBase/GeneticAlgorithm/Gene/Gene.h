/**
* @file Gene.h
* @brief Geneクラスの定義
*/

#pragma once

//---------- INCLUDES ---------
#include "DecisionData.h"
#include "Situation.h"

/**
* @class Gene
* @brief 遺伝子 状況遺伝子の集合
* @detail 状況遺伝子の数は敵ごとに異なる
*         同じ敵の遺伝子の状況遺伝子の数は遺伝子ごとに同じです　
*/
class Gene : public DecisionData
{
public:
	/**
	* コンストラクタ
	*/
	Gene();

	/**
	* デストラクタ
	*/
	~Gene();

private:
	/** 状況遺伝子 */
	std::vector<std::shared_ptr<Situation>> mSituations;

	/** 評価値 */
	float mEvaluationValue;

public:
	/**
	 * @fn Evaluate
	 * @brief 評価関数
	 * @return void
	*/
	virtual void Evaluate(std::shared_ptr<BlackBoard> _blackboard);

	/**
	* @fn GetSituations
	* @brief 状況遺伝子を返す
	* @return std::vector<std::shared_ptr<Situation>>
	*/
	inline std::vector<std::shared_ptr<Situation>> GetSituations() const noexcept;

	/**
	* @fn AddSituation
	* @brief 状況遺伝子を追加する関数
	* @param std::shared_ptr<Situation> (_situation)
	* @return void
	*/
	inline void AddSituation(std::shared_ptr<Situation> _situation) noexcept;

	/**
	* @fn GetEvaluationValue
	* @brief 評価値を返す関数
	* @return float 評価値
	*/
	inline float GetEvaluationValue() const noexcept;
};

//------------ INLINES ----------

inline std::vector<std::shared_ptr<Situation>> Gene::GetSituations() const noexcept
{
	return mSituations;
}

inline void Gene::AddSituation(std::shared_ptr<Situation> _situation) noexcept
{
	mSituations.emplace_back(_situation);
}

inline float Gene::GetEvaluationValue() const noexcept
{
	return mEvaluationValue;
}
