#pragma once
#include "../../AIBase/EnemyAIController.h"

/** 熊の敵のAIコントローラー */
class BearAIController : public EnemyAIController 
{
public:
	
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

