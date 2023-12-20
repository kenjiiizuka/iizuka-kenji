/**
* @file  EnemyActionProcessor.h
* @brief EnemyActionProcessorクラス定義
*/

#pragma once

//----------- INCLUDES ------------
#include <type_traits>
#include <memory>
#include "EnemyAIData.h"


//------- 前方宣言 ---------
class EnemyAction;
class EnemyBase;

/**
* @class EnemyActionProcessor
* @brief 敵の行動を実行するクラス
* @detail 実行したい行動をセットし、セットされた行動を実行している
*         実行中に新たに行動をせっとしたら、実行中の行動が他の行動に遷移可能なら変更される
*/
class EnemyActionProcessor
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	EnemyActionProcessor();

private:
	/** 初期化処理をする必要があるか */
	bool mbIsActionInitialized;
	
	/** 何か行動を実行中か */
	bool mbIsExecuteAction;

	/** 行動が終了したフレームにtrueになる */
	bool mbIsFinishAction;

	/** エネミーの行動の結果 */
	EnemyActionResult mActionResult;

protected:	
	/** 現在している行動 */
	std::shared_ptr<EnemyAction> mCurrentAction;

public:
	/**
	 * @fn Update
	 * @brief 更新処理
	 * @return void
	*/
	virtual void Update(EnemyBase* _enemy);

public:
	/**
	 * @fn SetExecutionAction
	 * @brief 実行するアクションのセット
	 * @param std::shared_ptr<EnemyAction> (_action) 
	 * @return void
	*/
	inline void SetExecutionAction(std::shared_ptr<EnemyAction> _action);

	/**
     * @fn GetCurrentExecutionAction
	 * @brief 現在実行しているアクションの取得
	 * @return std::weak_ptr<EnemyAction>
	*/
	inline std::weak_ptr<EnemyAction> GetCurrentExecutionAction() const;

	/**
	* @fn IsFinishAction
	* @brief 行動実行中なのかを返す
	* @return bool true 実行中 : false 実行していない
	*/
	inline bool IsExecutingAction() const noexcept;

	/**
	* @fn IsActionSettable
	* @brief 行動をセット可能か返す
	* @return bool true 可能 false 不可能
	*/
	inline bool IsActionSettable() const noexcept;

	/**
	* @fn IsFinishAction
	* @brief 攻撃が終了したこと返す
	* @detail 攻撃が終了したフレームのみtrueを返しています
	* @return bool  true 終了 false 終了していない
	*/
	inline bool IsFinishAction() const noexcept;
};

//------------------- INLINES --------------------

inline void EnemyActionProcessor::SetExecutionAction(std::shared_ptr<EnemyAction> _action)
{
	// アクションを実行していなかったらセット可能
	if (!mbIsExecuteAction)
	{
		mCurrentAction = _action;
	}
	// アクションの変更可能かつ、実行中なら変更可能
	else if (mActionResult == EnemyActionResult::CanChange)
	{
		mbIsActionInitialized = false;
		mCurrentAction = _action;
	}
}

inline std::weak_ptr<EnemyAction> EnemyActionProcessor::GetCurrentExecutionAction() const
{
	return mCurrentAction;
}

inline bool EnemyActionProcessor::IsExecutingAction() const noexcept
{
	return mbIsExecuteAction;
}

inline bool EnemyActionProcessor::IsActionSettable() const noexcept
{
	// 攻撃を実行していないか、実行中の行動が切り替え可能ならばtrue
	return !mbIsExecuteAction || mActionResult == EnemyActionResult::CanChange;
}

inline bool EnemyActionProcessor::IsFinishAction() const noexcept
{
	return mbIsFinishAction;
}
