//----------- INCLUDES -----------
#include "EnemyAIComponent.h"
#include "../../GameObject/Enemy/AIBase/EnemyAIController.h"

EnemyAIComponent::EnemyAIComponent()
	:mbRunAI(false)
{
	// ˆ—‚È‚µ
}

EnemyAIComponent::~EnemyAIComponent()
{
	// ˆ—‚È‚µ
}

void EnemyAIComponent::ControllerInitialize()
{
	mAIController->Init();
}

void EnemyAIComponent::Update(const double _deltaTime)
{
	mAIController->Update();
}

void EnemyAIComponent::StopAI()
{
	mAIController->StopController();
}

void EnemyAIComponent::RunAI()
{
	mAIController->RunController();
}

void EnemyAIComponent::SetTakenDamage(const float _takenDamage)
{
	mAIController->SetTakenDamageToCurrentExecuteAttackAction(_takenDamage);
}

