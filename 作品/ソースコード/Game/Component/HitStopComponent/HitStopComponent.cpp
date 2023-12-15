//------------ INCUEDES -----------
#include "HitStopComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../../System/FPSController/FPSController.h"

HitStopComponent::HitStopComponent()
	: mHitStopSeconds(0.0)
	, mElapsedStopTime(0.0)
	, mOwnerDefaultTimeDilation(0.0)
	, mbStop(false)
{
	// 処理なし
}

HitStopComponent::~HitStopComponent()
{
	// 処理なし
}

void HitStopComponent::HitStop(const double _stopPower, const double _stopSeconds, const double _defaultTimeDilation)
{
	mHitStopSeconds = _stopSeconds;
	mElapsedStopTime = 0.0;
	mOwnerDefaultTimeDilation = _defaultTimeDilation;

	// タイムダイレーションを設定する
	double hitStopTimeDilation = (1.0f - _stopPower) * mOwnerDefaultTimeDilation;
	mOwner->SetTimeDilation(hitStopTimeDilation);
	mbStop = true;
}

void HitStopComponent::Update(const double _deltaTime)
{
	if (!mbStop)
	{
		return;
	}

	// 経過時間を計測する 
	// 引数の値を使っていないのは、TimeDilationの影響を受けた値だから正常に経過時間を測ることができないため
	mElapsedStopTime += FPSController::GetDeltaTime();

	if (mElapsedStopTime >= mHitStopSeconds)
	{
		mbStop = false;
		mOwner->SetTimeDilation(mOwnerDefaultTimeDilation);
	}
}
