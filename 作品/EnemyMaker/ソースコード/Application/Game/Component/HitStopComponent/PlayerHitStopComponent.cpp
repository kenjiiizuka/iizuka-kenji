//--------- INCLUDES ----------
#include "PlayerHitStopComponent.h"
#include "../../../Utility/MathLibrary.h"
#include "../../GameObject/GameObject.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../GameObject/Camera/CameraIncludes.h"
#include "../../../ImGui/ImGuiUtility.h"

PlayerHitStopComponent::PlayerHitStopComponent()
	: mDamage(0.0f)
	, mHitStopSkipSecondWeight(0.09f)
	, mHitStopSecondWeight(0.002f)
	, mStopAnimationSecond(0.0f)
{
	// 処理なし
}

PlayerHitStopComponent::~PlayerHitStopComponent()
{
	// 処理なし
}

void PlayerHitStopComponent::Update(const double _deltaTime)
{

	ImGui::Begin("PlayerHitStop");
	ImGui::InputFloat("StopWeight", &mHitStopSecondWeight);
	ImGui::InputFloat("SkipWeight", &mHitStopSkipSecondWeight);
	ImGui::End();

	// アニメーション停止時間が0以下なら処理しない
	if (!mbStop)
	{
		return;
	}

	// 時間計測
	mStopAnimationSecond -= _deltaTime;

	// 停止時間がまだ残っていれば処理しない
	if (mStopAnimationSecond > 0)
	{
		return;
	}

	// アニメーションプレイヤーを取得
	std::shared_ptr<AnimationPlayer> animPlayer = mOwner->GetComponent<SkeletalMeshComponent>()->GetAnimationPlayer().lock();
	if (!animPlayer)
	{
		return;
	}

	// アニメーションを再生する
	animPlayer->ResumeAnimation();
	mbStop = false;
}

void PlayerHitStopComponent::HitStop(const bool _isCounter)
{	
	std::shared_ptr<AnimationPlayer> animPlayer = mOwner->GetComponent<SkeletalMeshComponent>()->GetAnimationPlayer().lock();
	if (!animPlayer)
	{
		return;
	}

	// カメラ振動
	SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->ShakeMainCamera({ 0.2f,0.2f }, 0.1f);

	// カウンター出ない場合のみアニメーションをスキップする
	if (!_isCounter)
	{
		// フレームをスキップする
		animPlayer->SkipAnimationFrame(-(mHitStopSkipSecondWeight * mDamage));
	}
	// 指定されたフレームだけ止める アニメーションを止める
	mStopAnimationSecond = mHitStopSecondWeight * mDamage;

	// アニメーション停止
	animPlayer->StopAnimation();

	mbStop = true;
}
