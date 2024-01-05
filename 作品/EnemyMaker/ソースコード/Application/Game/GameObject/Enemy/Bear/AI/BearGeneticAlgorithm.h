#pragma once
#include "../../AIBase/GeneticAlgorithm/EnemyGeneticAlgorithm.h"

class BearGeneticAlgorithm : public EnemyGeneticAlgorithm
{
public:
	/**
	* 値の初期化
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

