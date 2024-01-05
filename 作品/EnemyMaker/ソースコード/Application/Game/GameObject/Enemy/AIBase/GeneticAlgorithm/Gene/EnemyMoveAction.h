/**
* @file EnemyMoveAction.h
* @brief EnemyMoveActionクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include <numeric>
#include "EnemyAction.h"

/**
* @class EnemyMoveAction
* @brief エネミーの移動遺伝子クラスの基底
*/
class EnemyMoveAction : public EnemyAction
{
public:
	EnemyMoveAction(std::shared_ptr<BlackBoard> _blackBoard);


private:	
	/** 実行中に受けたダメージ */
	std::vector<float> mDamageTakneExecution;

public:
	/**
	 * @fn DuplicateFromSelfType
	 * @brief 自身と同じ型の実体を生成する
	 * @param std::shared_ptr<EnemyMoveAction>& (_output) 生成先
	 * @return void
	*/
	virtual void DuplicateFromSelfType(std::shared_ptr<EnemyMoveAction>& _output) = 0;

	/**
	 * @fn GetTotalTakenDamage
	 * @brief 実行中に受けた合計ダメージ
	 * @return void
	*/
	inline float GetTotalTakenDamage();
};

//------------------ INLINES -----------------

inline float EnemyMoveAction::GetTotalTakenDamage()
{
	return std::accumulate(mDamageTakneExecution.begin(), mDamageTakneExecution.end(), 0.0f);
}
