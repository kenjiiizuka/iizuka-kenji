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
#include "../../../Utility/MathLibrary.h"
#include "../DamageUI/DamageUI.h"

EnemyBase::EnemyBase()
	: mStatus({})
    , mbDeath(false)
	, mbBattleStart(false)
	, mFlinch(0)
	, mMaxFlinch(100)
	, mTakenDamageElapsedTime(0.0f)
	, mFlinchDecreaseDelayTime(2.0f)
	, mFlinchDecreaseSpeed(1.0f)
	, mFlinchUpRate(1.5f)
{
	// 処理なし
}

void EnemyBase::Init()
{
	mAIComponent = AddComponent<EnemyAIComponent>();
	mMesh = AddComponent<SkeletalMeshComponent>();
	mHpBer = AddChildObject<HpBer>();
	mHpBer.lock()->Init(mStatus.mMaxHp, mStatus.mCurrentHp, { 240,50 }, { 800, 30 });
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
	
	// 怯み値を減少させる
	DecreaseFlinch(_deltaTime);

	// ダメージを受けてからの経過時間を加算
	mTakenDamageElapsedTime += _deltaTime;

	//ImGui::Begin("Enemy");
	//ImGui::InputFloat("Flinch", &mFlinch);
	//ImGui::InputFloat("MaxFlinch", &mMaxFlinch);
	//ImGui::End();
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
	skeletalMesh->SetDrawType(CullType::Draw_SolidFront, 0);
	skeletalMesh->SetDrawType(CullType::Draw_SolidBack, 1);
}

void EnemyBase::Dead()
{
	mAIComponent.lock()->StopAI();
}

void EnemyBase::DecreaseFlinch(const double _deltaTime)
{
	// 怯み現象までのDelay時間を超えていなければ減少させない
	if (!(mTakenDamageElapsedTime >= mFlinchDecreaseDelayTime))
	{
		return;
	}
	mFlinch -= static_cast<float>(_deltaTime) * mFlinchDecreaseSpeed;

	mFlinch = MathLibrary::Clamp(mFlinch, 0.0f, mMaxFlinch);
}

void EnemyBase::TakenDamage(const float _damage, const DirectX::SimpleMath::Vector3 _hitPosition)
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
	mAIComponent.lock()->SetTakenDamage(_damage);

	// 怯み値を加算
	mFlinch += _damage;

	// ダメージを受けてからの経過時間をリセット
	mTakenDamageElapsedTime = 0.0f;

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
