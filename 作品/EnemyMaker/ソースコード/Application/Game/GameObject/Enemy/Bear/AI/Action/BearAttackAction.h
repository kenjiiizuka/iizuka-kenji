#pragma once
/**
* @file BearAttackAction.h
* @brief BearAttackActionクラスの定義
*/

//---------- INCLUDES -----------
#include "../../../AIBase/GeneticAlgorithm/Gene/EnemyAttackAction.h"
#include "../../BearEnemyAttackData.h"

//--------- 前方宣言 ------------
class BearAnimationInstance;
class BearEnemy;
class EnemyWeapon;

/**
* @class BearAttackAction
* @brief 熊の敵の攻撃行動の基底クラス
* @detail 熊の敵の攻撃行動の共通処理をまとめるために定義した
*         このクラスを生成してい使用することはない
*/
class BearAttackAction : public EnemyAttackAction
{
public:
	/**
	* コンストラクタ
	* 
	* @param  std::shared_ptr<BlackBoard> (_blackBoard)
	*/
	BearAttackAction(std::shared_ptr<BlackBoard> _blackBoard);

protected:
	/** この行動をするエネミーのアニメーションインスタンス */
	std::weak_ptr<BearAnimationInstance> mAnimInstance;

	/** この行動をする熊の敵 */
	BearEnemy* mBearEnemy;

	/** 敵の持っている武器 */
	std::weak_ptr<EnemyWeapon> mWeapon;

	/** 再生するアニメーションクリップの名前 */
	std::string mAnimationClipName;

public:
	/**
	 * @fn BeginActionExecution
	 * @brief 行動の開始処理
	 * @return void
	*/
	virtual void BeginActionExecution(EnemyBase* _enemy);

	/**
	 * @fn EndActionExecution
	 * @brief 行動の終了処理
	 * @return void
	*/
	virtual void EndActionExecution();

	/**
	* @fn IsExecuteAble
	* @brief 攻撃が実行可能かを判断する関数
	* @return bool true 実行可能 false 実行不可
	*/
	virtual bool IsExecuteAble() override;

};

