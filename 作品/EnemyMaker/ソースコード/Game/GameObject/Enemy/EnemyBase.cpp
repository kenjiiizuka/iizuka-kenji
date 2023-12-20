//---------- INCLUDES ------------
#include "EnemyBase.h"
#include "AIBase/EnemyAIController.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Component/AIComponent/EnemyAIComponent.h"
#include "../HpBer/HpBer.h"
#include "AIBase/GeneticAlgorithm/GeneticAlgorithmDebugger.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../System/RendererSystem/Shader/VertexShader/OutlineSkeletalMeshVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/OutlinePixelShader.h"

EnemyBase::EnemyBase()
	: mStatus({})
    , mbDeath(false)
	, mbBattleStart(false)
{
	// 処理なし
}

void EnemyBase::Init()
{
	mAIComponent = AddComponent<EnemyAIComponent>();
	mMesh = AddComponent<SkeletalMeshComponent>();
	mHpBer = AddChildObject<HpBer>();
	mHpBer.lock()->Init(mStatus.mMaxHp, mStatus.mCurrentHp, { 240,50 }, { 800, 30 });
	// mTransform.lock()->SetPosition({ 100.0f,0.0f,100.0f });
}

void EnemyBase::Update(const double _deltaTime)
{		
	if (!mbBattleStart)
	{
		return;
	}

	// HpがゼロになっているかなっていたらAIを止める
	if (mStatus.mCurrentHp <= 0 && !mbDeath)
	{
		mbDeath = true;
		Dead();
	}

	GeneticAlgorithmDebugger::GetInstance().DisplayGeneticDebug();

	/*ImGui::Begin("Enemy");
	if (ImGui::Button("Death"))
	{
		TakenDamage(mStatus.mMaxHp);
	}
	ImGui::End();*/
}

void EnemyBase::SetupSkeletalMesh(const std::string& _filePath)
{
	std::shared_ptr<SkeletalMeshComponent> mesh = mMesh.lock();
	mesh->Load(_filePath);
	mesh->SetScale(0.08f);
	mesh->SetRotation({ 0.0f, 3.14f,0.0f });
	
	std::shared_ptr<SkeletalMesh> skeletalMesh = mesh->GetSkeletalMesh().lock();
	std::shared_ptr<OutlineSkeletalMeshVertexShader> outlineShader = skeletalMesh->AddVertexShader<OutlineSkeletalMeshVertexShader>();
	outlineShader->SetSkeleton(skeletalMesh->GetSkeleton().lock());
	skeletalMesh->AddPixelShader<OutlinePixelShader>();
	skeletalMesh->SwapShader();
	skeletalMesh->SetDrawType(DrawType::Draw_SolidFront, 0);
	skeletalMesh->SetDrawType(DrawType::Draw_SolidBack, 1);
}

void EnemyBase::Dead()
{
	mAIComponent.lock()->StopAI();
}

void EnemyBase::TakenDamage(float _damage)
{
	// Hpを減算する
	mStatus.mCurrentHp -= _damage;
	if (mStatus.mCurrentHp <= 0)
	{
		mStatus.mCurrentHp = 0;
	}

	// HPバーに現在の体力をセットする
	mHpBer.lock()->SetCurrentHp(mStatus.mCurrentHp);
	
	// 攻撃実行中にくらったダメージとして追加する関数
	// 攻撃していない場合などは追加されないようになっている
//	mAIController->SetTakenDamageToCurrentExecuteAttackAction(_damage);
	mAIComponent.lock()->SetTakenDamage(_damage);
}

std::shared_ptr<AnimationInstance> EnemyBase::GetAnimationInstance()
{
	return mMesh.lock()->GetAnimationInstance();
}

void EnemyBase::BattleStart() noexcept
{
	mbBattleStart = true;
	mAIComponent.lock()->RunAI();
}

void EnemyBase::BattleEnd() noexcept
{
	mbBattleStart = false;

	
	mAIComponent.lock()->StopAI();
}
