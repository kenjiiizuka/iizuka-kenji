/**
* @file  BearMoveAction.h
* @brief BearMoveActionクラスの定義をしている
*/


#pragma once


//------------- INCLUDES -------------
#include "../../../AIBase/GeneticAlgorithm/Gene/EnemyMoveAction.h"


//------------- 前方宣言 -------------
class EnemyBase;
class CharacterMovementComponent;


/**
* @class BearMoveAction
* @brief 熊の敵の移動するクラス
* @details プレイヤーに向かって移動をする。また途中で中断可能
*/
class BearMoveAction : public EnemyMoveAction
{
public:
	/**
	* 引数ありコンストラクタ
	*
	* @param std::shared_ptr<BlackBoard> (_blackBoard)
	*/
	BearMoveAction(std::shared_ptr<BlackBoard> _blackBoard);

private:	
	/** 移動コンポーネント */
	std::weak_ptr<CharacterMovementComponent> mMoveComp;

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
	 * @fn IsValidAction
	 * @brief この行動が有効かどうかを返す
	 * @return bool true : 有効 false 無効
	*/
	virtual bool IsValidAction();

	/**
	 * @fn DuplicateFromSelfType
	 * @brief 自身と同じ型の実体を生成する
	 * @param std::shared_ptr<EnemyMoveAction>& (_output) 生成先
	 * @return void
	*/
	void DuplicateFromSelfType(std::shared_ptr<EnemyMoveAction>& _output) override;

};

