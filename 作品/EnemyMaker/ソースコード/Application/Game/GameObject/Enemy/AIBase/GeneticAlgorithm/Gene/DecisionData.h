/**
* @file DecisionData.h
* @brief DecisionDataクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

//---------- 前方宣言 -----------
class BlackBoard;

/**
* @class DecisionData
* @brief 遺伝子の基底クラス
*/
class DecisionData
{
public:
	/**
	* 値の初期化
	*/
	DecisionData();
	virtual ~DecisionData() {};

private:
	/** 遺伝の優先順位(評価値) */
	float mGeneticPriority;

	/** このデータの戦闘ごとの評価 リストの数が評価項目数 */
	std::vector<std::vector<float>> mEvaluationsPerBattle;

protected:
	/** 自身の型の名前 */
	std::string mTypeName;

	/**
	* @fn ResizeNumberOfEvaluationItems
	* @brief 評価項目数分配列を確保する
	* @param size_t (_itemNum) 遺伝子の評価項目の数
	* @return void
	*/
	inline void ResizeNumberOfEvaluationItems(size_t _itemNum);

	/**
	* @fn GetEvaluationValue
	* @brief 指定した評価値を加絵うs
	* @param size_t (_itemNum) ほしい評価値の添え字
	* @return float 評価値
	*/
	inline float GetEvaluationValue(size_t _item_i) const;

public:
	/**
	 * @fn Evaluate
	 * @brief 評価関数
	 * @return void
	*/
	virtual void Evaluate(std::shared_ptr<BlackBoard> _blackboard) = 0;

	/**
	 * @fn SetEvaluation
	 * @brief 評価の設定関数
	 * @param const float (_evaluation) 新たな評価
	 * @return void
	*/
	inline virtual void AddEvaluation(const float _evaluation, const size_t _evalusateItemNum);

	/**
	 * @fn GetGeneticPriority
	 * @brief この遺伝子の遺伝の優先順位を返す
	 * @return float 評価の平均点
	*/
	inline virtual float GetGeneticPriority();

	/**
	 * @fn SetGeneticPriority
	 * @brief この遺伝子の遺伝の優先順位をセットする
	 * @param const float (_priority)
	 * @return void
	*/
	inline void SetGeneticPriority(const float _priority);

	/**
	 * @fn GetLastBattleEvaluation
	 * @brief 最後の戦闘での評価値を返す
	 * @return float 最後の戦闘での評価値
	*/
	inline float GetLastBattleEvaluation(const size_t _evalusateItemNum) const;

	/**
	 * @fn GetTypeName
	 * @brief 自身の型の名前を返す
	 * @return std::string 
	*/
	inline std::string GetTypeName() const noexcept;
};

//--------------------- INLINES ----------------------

inline void DecisionData::ResizeNumberOfEvaluationItems(size_t _itemNum)
{
	mEvaluationsPerBattle.resize(_itemNum);
}

inline float DecisionData::GetEvaluationValue(size_t _item_i) const
{
	return mEvaluationsPerBattle[_item_i].front();
}

inline void DecisionData::AddEvaluation(const float _evaluation, const size_t _evalusateItemNum)
{
	mEvaluationsPerBattle[_evalusateItemNum].push_back(std::clamp<float>(_evaluation,0,1));
}

inline float DecisionData::GetGeneticPriority()
{
	// 蓄積された評価データの平均を取りそれをこの世代での自身の評価にする
	float total = 0;
	for (std::vector<float> evaluateItem : mEvaluationsPerBattle)
	{
		for (float evaluateValue : evaluateItem)
		{
			total += evaluateValue;
		}
	}
	mGeneticPriority = total / mEvaluationsPerBattle.size();
	return mGeneticPriority;
}

inline void DecisionData::SetGeneticPriority(const float _priority)
{
	mGeneticPriority = _priority;
}

inline float DecisionData::GetLastBattleEvaluation(const size_t _evalusateItemNum) const
{
	return mEvaluationsPerBattle[_evalusateItemNum].front();
}

inline std::string DecisionData::GetTypeName() const noexcept
{
	return mTypeName;
}



