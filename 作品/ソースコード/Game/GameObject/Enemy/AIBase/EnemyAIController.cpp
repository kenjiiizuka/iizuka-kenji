#include "EnemyAIController.h"
#include "EnemyActionSelector.h"
#include "EnemyActionProcessor.h"
#include "BlackBoard.h"
#include "../EnemyBase.h"
#include "../../../../Manager.h"
#include "../../../Scene/Scene.h"
#include "../../Player/Player.h"
#include "GeneticAlgorithm/EnemyGeneticAlgorithm.h"
#include "GeneticAlgorithm/Gene/Gene.h"
#include "GeneticAlgorithm/Gene/EnemyAttackAction.h"
#include "GeneticAlgorithm/Gene/EnemyMoveAction.h"
#include "../../../Scene/SceneManager.h"
#include "../../../../ImGui/ImGuiUtility.h"

using namespace DirectX::SimpleMath;

EnemyAIController::EnemyAIController(EnemyBase* _controlledEnemy)
	: mControlledEnemy(_controlledEnemy)
	, mbRunAI(false)
{
	mBlackBoard = std::make_shared<BlackBoard>();
}

void EnemyAIController::Init()
{
	// HPのデータをBlackBoardに書き込む
	mBlackBoard->SetValue<float>(mControlledEnemy->GetStatus().mMaxHp, "MaxHP");
	// 遺伝学習の準備
	mGeneticAlgorithm->Init();
	
	// 生成した遺伝子に操作(遺伝子の持ち主となる)するエネミーのポインタを渡す
	std::shared_ptr<Gene> genetic = mGeneticAlgorithm->GetGene();
	std::vector<std::shared_ptr<Situation>> situations = genetic->GetSituations();
	for (std::shared_ptr<Situation> situation : situations)
	{
		AttackGenes attackGenes = situation->GetAttackGenes();
		for (std::shared_ptr<EnemyAttackAction> attackGene : attackGenes)
		{
			attackGene->SetEnemy(mControlledEnemy);
		}
		MoveGenes moveGenes = situation->GetMoveGenes();

		for (std::shared_ptr<EnemyMoveAction> moveGene : moveGenes)
		{
			moveGene->SetEnemy(mControlledEnemy);
		}
	}

	// 遺伝子をセレクターに渡す
	mActionSelector->SetGene(genetic);
}

void EnemyAIController::Update()
{
	if (!mbRunAI)
	{
		return;
	}

	std::weak_ptr<Scene> currentScene = SceneManager::GetInstance().GetCurrentScene();
	std::shared_ptr<Player> target = currentScene.lock()->GetGameObject<Player>(ELayer::ObjectLayer);
	// ブラックボードに必要なデータを書き込み	
	mBlackBoard->SetValue<EnemyBase*>(mControlledEnemy,"OwnerEnemy");

	Vector3 targetPosition = target->GetComponent<TransformComponent>()->GetPosition();
	Vector3 enemyPosition = mControlledEnemy->GetComponent<TransformComponent>()->GetPosition();
	Vector3 vectorToTarget = targetPosition - enemyPosition;
	mBlackBoard->SetValue<Vector3>(vectorToTarget, "VectorToTarget");	
	mBlackBoard->SetValue<Vector3>(targetPosition, "TargetPosition");

	
	// 行動を実行していなければ行動を選択する
	if (mActionProcessor->IsActionSettable())
	{
	   mActionSelector->Update();
	   mActionProcessor->SetExecutionAction(mActionSelector->GetSelectAction());
	}
	// セットされている行動を実行
	mActionProcessor->Update(mControlledEnemy);
}

void EnemyAIController::StopController()
{
	// すでにとまっていたら処理しない
	if (!mbRunAI)
	{
		return;
	}
	mbRunAI = false;
	
	// 操作をとめたタイミングで遺伝学習の終了処理をする
	GeneticAlgorithmEnd();
}

void EnemyAIController::RunController()
{
	mbRunAI = true;
}

void EnemyAIController::GeneticAlgorithmEnd()
{
	mGeneticAlgorithm->Evaluate();
	mGeneticAlgorithm->GenerateGenetic();
	mGeneticAlgorithm->GeneSave();
}

void EnemyAIController::SetTakenDamageToCurrentExecuteAttackAction(const float _takenDamage)
{
	// 現在している行動を取得
	std::weak_ptr<EnemyAction> action = mActionProcessor->GetCurrentExecutionAction();

	// なにも実行されていないこともあるのでチェックする
	if (!action.lock())
	{
		return;
	}
	
	// 攻撃行動にダイナミックキャスト
	std::shared_ptr<EnemyAttackAction> attackAction = std::dynamic_pointer_cast<EnemyAttackAction>(action.lock());

	// キャストに成功しているかを確認する
	if (!attackAction)
	{
		return;
	}

	// 実行中にくらったダメージとして追加する
	attackAction->AddDamageTakenDuringExecution(_takenDamage);
}

