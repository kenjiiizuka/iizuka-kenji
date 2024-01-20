//----------- INCLUDES -----------
#include "BearAIController.h"
#include "../../EnemyBase.h"
#include "../../AIBase/EnemyActionSelector.h"
#include "../../AIBase/EnemyActionProcessor.h"
#include "BearGeneticAlgorithm.h"
#include<memory>

BearAIController::BearAIController(EnemyBase* _controlledEnemy)
	: EnemyAIController(_controlledEnemy)
{
	// 処理なし
}

void BearAIController::Init()
{
	//セレクター、プロセッサー 遺伝学習クラスの作成
	mActionProcessor = std::make_shared<EnemyActionProcessor>();
	mActionSelector = std::make_shared<EnemyActionSelector>(mBlackBoard);
 	mGeneticAlgorithm = std::make_shared<BearGeneticAlgorithm>(mBlackBoard);
	EnemyAIController::Init();
}

void BearAIController::Update()
{
	EnemyAIController::Update();
}
