/**
* @file BearAIController.h
* @brief BearAIControllerクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include "../../AIBase/EnemyAIController.h"

/**
* @class BearAIController
* @brief 熊の敵の用のAIController
*/
class BearAIController : public EnemyAIController 
{
public:
	/**
	* コンストラクタ
	* 
	* @param EnemyBase* (_controlledEnemy)
	*/
	BearAIController(EnemyBase* _controlledEnemy);

private:
	/**
	 * @fn Init
	 * @brief 初期化処理 セレクターとプロセッサーの生成
	 * @return void
	*/
	void Init() override;

	/**
	 * @fn Update
	 * @brief 更新処理
	 * @return void
	*/
	void Update() override;
};

