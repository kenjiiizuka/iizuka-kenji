/**
* @file BearRoarAttack.h
* @brief BearRoarAttackクラスの定義
*/

#pragma once

//---------- INCLUDES ---------
#include "BearAttackAction.h"

//-------- 前方宣言 ---------
class AnimationInstance;

/**
* @class BearRoarAttack
* @brief 熊の敵の威嚇攻撃
*/
class BearRoarAttack : public BearAttackAction
{
public:
	/**
	* 引数ありコンストラクタ
	*
	* @param std::shared_ptr<BlackBoard> (_blackBoard)
	*/
	BearRoarAttack(std::shared_ptr<BlackBoard> _blackBoard);

public:
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
	virtual EnemyActionResult UpdateActionExecution();

	/**
	 * @fn EndActionExecution
	 * @brief 行動の終了処理
	 * @return void
	*/
	virtual void EndActionExecution();

	/**
	 * @fn IsExecuteAble
	 * @brief この行動を実行可能かを判断する関数
	 * @return bool true : 実行可能 false 実行不可
	*/
	virtual bool IsExecuteAble();

	/**
	 * @fn DuplicateFromSelfType
	 * @brief 自身と同じ型を引数で渡された値に新たに生成する
	 * @param std::shared_ptr<EnemyAttackAction>& (_destination)
	 * @return void
	*/
	virtual void DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination);
};

