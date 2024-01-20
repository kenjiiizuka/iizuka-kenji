/**
* @file Situation.h
* @brief Situationクラスの定義
*/

#pragma once

//----------- INCLUDES -----------
#include <functional>
#include "DecisionData.h"
#include "../GeneticInfomation.h"

//----------- 前方宣言 ------------
class EnemyAttackAction;
class EnemyMoveAction;
class BlackBoard;

/**
* @class Situation
* @brief 状況遺伝子 意思決定する際の特定の状況を表す
*/
class Situation final : public DecisionData 
{
public:
	/**
	* コンストラクタ
	*/
	Situation();

private:	
	/** このSituationが目標とする攻撃のリスクタイプの比率 */
	SituationRiskTypeRatio mActionRiskTypeTargetRatio;

	/** 現在の攻撃のリスクタイプの比率 */
	SituationRiskTypeRatio mCurrentRiskTypeRatio;

	/** このシチュエーションの攻撃の評価値を高いか低いかを分ける閾値 */
	AttackEvaluationThreshold mAttackEvaluationThreshold;

	/** このシチュエーションの移動の評価値を高いか低いかを分ける閾値 */
	MoveEvaluationThreshold mMoveEvaluationThreshold;

	/** 攻撃遺伝子 */
	AttackGenes mAttackGenes;

	/** 移動遺伝子 */
	MoveGenes mMoveGenes;

	/** ゴールにどれだけ近いか　評価値 */
	float mGoalAchievement;

	/** 評価済みかどうか */
	bool mbIsEvaluated;

	/** このSituationが現在の状況に適してるかを判断する関数 */
	std::function<bool(std::shared_ptr<BlackBoard>)> mSituationSuitable;

public:
	/**
	 * @fn Evaluate
	 * @brief この状況で取りうる行動の評価をして、その評価の合計値を求める
	 * @return void 
	*/
	void Evaluate(std::shared_ptr<BlackBoard> _blackboard) override;

	/**
	* @fn InheritedInitialize
	* @brief 遺伝して生成された場合の初期化処理
	* @detail 持っている遺伝子のリスクタイプを計算する
	* @return void
	*/
	void CalculateAllRiskTypeRatio();

private:
	/**
	 * @fn EvaluateAttack
	 * @brief 攻撃の評価をする
	 * @return void
	*/
	void EvaluateAttack(std::shared_ptr<BlackBoard> _blackboard);

	/**
	 * @fn CountRiskType
	 * @brief 指定されたリスクタイプの攻撃の数を返す
	 * @return size_t
	*/
	size_t CountRiskType(const GeneticAlgorithmInf::AttackActionRiskType _riskType);

	/**
	* @fn CalucRiskTypeRatio
	* @brief リスクタイプの数の比率を計算する
	* @param const GeneticAlgorithmInf::AttackActionRiskType (_riskType)
	* @param const size_t (_actionNum)
	* @return void
	*/
	void CalucRiskTypeRatio(const GeneticAlgorithmInf::AttackActionRiskType _riskType, const size_t _actionNum);

public:
	/**
	 * @fn GetTotalActionEvaluation
	 * @brief この状況の行動すべての評価の合計を返す
	 * @return float
	*/
	inline float GetGoalAchievement() const;

	/**
	* @fn GetActionRiskTypeTargetRatio
	* @brief 目標のリスクタイプの割合を返す
	* return SituationRiskTypeRatio
	*/
	inline SituationRiskTypeRatio GetRiskTypeTargetRatio() const noexcept;

	/**
	* @fn GetCurrentRiskTypeRatio
	* @brief 現在のリスクタイプの比率を返す
	* @return SituationRiskTypeRatio
	*/
	inline SituationRiskTypeRatio GetCurrentRiskTypeRatio() const noexcept;

	/**
	* @fn GetAttackEvaluationThreshold
	* @brief 各攻撃の評価を高いか低いかを判断する値を返す
	* return AttackEvaluationThreshold
	*/
	inline AttackEvaluationThreshold GetAttackEvaluationThreshold() const noexcept;

	/**
	* @fn GetMoveEvaluationThreshold
	* @brief 各移動の評価を高いか低いかを判断する値を返す
	* return AttackEvaluationThreshold
	*/
	inline MoveEvaluationThreshold GetMoveEvaluationThreshold() const noexcept;

	/**
	 * @fn GetTotalActionEvaluation
	 * @brief この状況の行動すべての評価の合計をセットする
	 * @param const float (_evaluation)
	 * @return void
	*/
	inline void SetGoalAchievement(const float _evaluation) noexcept;

	/**
	* @fn GetActionRiskTypeTargetRatio
	* @brief 目標のリスクタイプの割合をセットする
	* @param const SituationRiskTypeRatio&
	* @return void
	*/
	inline void SetActionRiskTypeTargetRatio(const SituationRiskTypeRatio& _riskRatio) noexcept;

	/**
	* @fn SetCurrentRiskTypeRatio
	* @brief リスクタイプの比率をセットする
	* @param const SituationRiskTypeRatio& _riskTypeRatio
	* @return void
	*/
	inline void SetCurrentRiskTypeRatio(const SituationRiskTypeRatio& _riskTypeRatio) noexcept;

	/**
	 * @fn SetAttackEvaluationThreshold
	 * @brief このシチュエーションの攻撃の評価の閾値をセットする
	 * @param AttackEvaluationThreshold (_threshold) 
	 * @return void
	*/
	inline void SetAttackEvaluationThreshold(const AttackEvaluationThreshold& _threshold);

	/**
	 * @fn SetMoveEvaluationThreshold
	 * @brief このシチュエーションの移動の評価の閾値をセットする
	 * @param MoveEvaluationThreshold (_threshold)
	 * @return void
	*/
	inline void SetMoveEvaluationThreshold(const MoveEvaluationThreshold& _threshold);

	/**
	 * @fn GetAttackActions
	 * @brief 攻撃行動を返す
	 * @return AttackGenes 攻撃行動
	*/
	inline AttackGenes GetAttackGenes() const;

	/**
	 * @fn GetAttackActions
	 * @brief 攻撃行動を返す
	 * @return MoveGenes 移動行動
	*/
	inline MoveGenes GetMoveGenes() const;

	/**
	 * @fn IsSituationSuitable
	 * @brief このSituationが今の状況に適しているか判断する
	 * @return bool true 適している false 適していない
	*/
	bool IsSituationSuitable(std::shared_ptr<BlackBoard> _blackBoard);

	/**
	 * @fn SetAttackGenes
	 * @brief 攻撃遺伝子のセッター
	 * @param const AttackGenes& (_attackGenes) 攻撃遺伝子
	 * @return void
	*/
	inline void SetAttackGenes(const AttackGenes& _attackGenes);

	/**
	 * @fn SetMoveGenes
	 * @brief 移動遺伝子のセッター
	 * @param const MoveGenes& (_moveGenes) 移動遺伝子
	 * @return void
	*/
	inline void SetMoveGenes(const MoveGenes& _moveGenes);

	/**
	* @fn IsEvaluated
	* @brief 評価済みかを返す
	* @return bool true : 評価済み false 未評価
	*/
	inline bool IsEvaluated() const noexcept;

	/**
	* @fn SetEvaluated
	* @brief 評価済みかをセットする
	* @param bool (_isEvaluated)
	* @return void 
	*/
	inline void SetEvaluated(bool _isEvaluated) noexcept;
};

//-------------- INLINES -----------------

float Situation::GetGoalAchievement() const
{
	return mGoalAchievement;
}

inline SituationRiskTypeRatio Situation::GetRiskTypeTargetRatio() const noexcept
{
	return mActionRiskTypeTargetRatio;
}

inline SituationRiskTypeRatio Situation::GetCurrentRiskTypeRatio() const noexcept
{
	return mCurrentRiskTypeRatio;
}

inline AttackEvaluationThreshold Situation::GetAttackEvaluationThreshold() const noexcept
{
	return mAttackEvaluationThreshold;
}

inline MoveEvaluationThreshold Situation::GetMoveEvaluationThreshold() const noexcept
{
	return mMoveEvaluationThreshold;
}

inline void Situation::SetGoalAchievement(const float _evaluation) noexcept
{
	mGoalAchievement = _evaluation;
}

inline void Situation::SetActionRiskTypeTargetRatio(const SituationRiskTypeRatio& _riskRatio) noexcept
{
	mActionRiskTypeTargetRatio = _riskRatio;
}

inline void Situation::SetCurrentRiskTypeRatio(const SituationRiskTypeRatio& _riskTypeRatio) noexcept
{
	mCurrentRiskTypeRatio = _riskTypeRatio;
}

inline void Situation::SetAttackEvaluationThreshold(const AttackEvaluationThreshold& _threshold)
{
	mAttackEvaluationThreshold = _threshold;
}

inline void Situation::SetMoveEvaluationThreshold(const MoveEvaluationThreshold& _threshold)
{
	mMoveEvaluationThreshold = _threshold;
}

inline AttackGenes Situation::GetAttackGenes() const
{
	return mAttackGenes;
}

inline MoveGenes Situation::GetMoveGenes() const
{
	return mMoveGenes;
}

inline void Situation::SetAttackGenes(const AttackGenes& _attackGenes)
{
	mAttackGenes = _attackGenes;
}

inline void Situation::SetMoveGenes(const MoveGenes& _moveGenes)
{
	mMoveGenes = _moveGenes;
}

inline bool Situation::IsEvaluated() const noexcept
{
	return mbIsEvaluated;
}

inline void Situation::SetEvaluated(bool _isEvaluated) noexcept
{
	mbIsEvaluated = _isEvaluated;
}
