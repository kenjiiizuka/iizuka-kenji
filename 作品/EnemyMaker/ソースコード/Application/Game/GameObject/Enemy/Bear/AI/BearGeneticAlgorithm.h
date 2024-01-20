/**
* @file BearGeneticAlgorithm.h
* @brief BearGeneticAlgorithmクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include "../../AIBase/GeneticAlgorithm/EnemyGeneticAlgorithm.h"

/**
* @class BearGeneticAlgorithm
* @brief 熊の敵用遺伝学習クラス 
* @detail 遺伝子の型を設定する処理をしている
*/
class BearGeneticAlgorithm : public EnemyGeneticAlgorithm
{
public:
	/**
	* コンストラクタ
	* 
	* @param std::shared_ptr<BlackBoard>& (_blackboard) ブラックボード
	*/
	BearGeneticAlgorithm(std::shared_ptr<BlackBoard>& _blackboard);

private:	
	/**
	 * @fn SetupAttackGeneType
	 * @brief 生成する攻撃、移動遺伝子の型判別用変数の生成
	 * @return void
	*/
	virtual void SetupGeneType() override;
};

