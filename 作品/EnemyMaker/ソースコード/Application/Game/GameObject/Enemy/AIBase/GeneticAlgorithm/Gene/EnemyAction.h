﻿#pragma once

//---------- INCLUDES -----------
#include <memory>
#include "../../EnemyAIData.h"
#include "DecisionData.h"
/**
* @file  EnemyAction.h
* @brief EnemyActionクラスの定義
*/

// 前方宣言
class EnemyBase;
class BlackBoard;

/** エネミーの行動クラス */
class EnemyAction : public DecisionData
{
public:
	EnemyAction(std::shared_ptr<BlackBoard> _blackBoard);
	virtual ~EnemyAction() {};

private:
	/** アクション変更可能フラグ */
	bool mbCanChange;

	/** この行動の実行回数 */
	uint32_t mExecuteCount;

	float mSuitable;

protected:
	/** この行動をするEnemy */
	EnemyBase* mEnemy;

	/** ブラックボード */
	std::shared_ptr<BlackBoard> mBlackBoard;
	
public:
	/**
	 * @fn Evaluate
	 * @brief このすべての評価項目を評価する関数
	 * @return void
	*/
	void Evaluate(std::shared_ptr<BlackBoard> _blackboard) override {};
	
	/**
	 * @fn BeginActionExecution
	 * @brief 行動の開始処理
	 * @return void
	*/
	virtual void BeginActionExecution(EnemyBase* _enemy);

	/**
	 * @fn UpdateActionExecution
	 * @brief 行動の更新処理
	 * @return EnemyActionResult
	*/
	virtual EnemyActionResult UpdateActionExecution() = 0;

	/**
	 * @fn EndActionExecution
	 * @brief 行動の終了処理
	 * @return void
	*/
	virtual void EndActionExecution() = 0;

	/**
	 * @fn IsExecuteAble
	 * @brief この行動を実行可能かを判断する関数
	 * @return bool true : 実行可能 false 実行不可
	*/
	virtual bool IsExecuteAble()  { return true; }

	/**
	 * @fn IsValidAction
	 * @brief この行動が有効かどうかを返す
	 * @return bool true : 有効 false 無効
	*/
	virtual bool IsValidAction()  { return true; }

	/**
	 * @fn GetExecuteCount
	 * @brief この行動を実行した回数
	 * @return void
	*/
	inline uint32_t GetExecuteCount() const noexcept;

	/**
	* @fn SetExecuteCount
	* @brief 実行した回数をセットする
	* @param uint16_t (_executeCount)
	* @return 
	*/
	inline void SetExecuteCount(uint32_t _executeCount) noexcept;

	/**
	 * @fn SetEnemy
	 * @brief この行動をするエネミーをセットする
	 * @param EnemyBase* (_enemy)
	 * @return void
	*/
	inline void SetEnemy(EnemyBase* _enemy);

	/**
	* @fn SetSuitable
	* @brief 状況遺伝子に適しているのかのセッター
	* @param const float (_suitable)
	* @return void
	*/
	inline void SetSuitable(const float _suitable) noexcept;

	/**
	* @fn GetSuitable
	* @brief 状況遺伝子に適しているかを返す
	* @return float
	*/
	inline float GetSuitable() const noexcept;
};

//----------------- INLINES -------------------------

inline uint32_t EnemyAction::GetExecuteCount() const noexcept
{
	return mExecuteCount;
}

inline void EnemyAction::SetExecuteCount(uint32_t _executeCount) noexcept
{
	mExecuteCount = _executeCount;
}

inline void EnemyAction::SetEnemy(EnemyBase* _enemy)
{
	mEnemy = _enemy;
}

inline void EnemyAction::SetSuitable(const float _suitable) noexcept
{
	mSuitable = _suitable;
}

inline float EnemyAction::GetSuitable() const noexcept
{
	return mSuitable;
}
