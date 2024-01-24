//------------- INCLUDES -----------
#include "EnemyActionProcessor.h"
#include "GeneticAlgorithm/Gene/EnemyAction.h"
#include "GeneticAlgorithm/GeneticAlgorithmDebugger.h"
#include "GeneticAlgorithm/Gene/EnemyAttackAction.h"
#include "GeneticAlgorithm/Gene/EnemyMoveAction.h"

EnemyActionProcessor::EnemyActionProcessor()
	: mbIsActionInitialized(false)
	, mActionResult(EnemyActionResult::InProgress)
	, mbIsExecuteAction(false)
	, mbIsFinishAction(false)
{
}

void EnemyActionProcessor::Update(EnemyBase* _enemy)
{
	if (!mCurrentAction)
	{
		mbIsFinishAction = false;
		return;
	}

	// 行動の初期処理をする
	if (!mbIsActionInitialized) 
	{
		mbIsExecuteAction = true;
		mCurrentAction->BeginActionExecution(_enemy);
		mbIsActionInitialized = true;
	}

	// 行動の更新処理
	mActionResult = mCurrentAction->UpdateActionExecution();

	// 行動の終了処理
	if (mActionResult == EnemyActionResult::Failed || mActionResult == EnemyActionResult::Succeeded)
	{
		mCurrentAction->EndActionExecution();
		mbIsActionInitialized = false;
		mbIsExecuteAction = false;
		mbIsFinishAction = true;
		// 現在の行動を解放
		mCurrentAction.reset();
	}
}

