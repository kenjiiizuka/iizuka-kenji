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
	// �����Ȃ�
}

HitStopComponent::~HitStopComponent()
{
	// �����Ȃ�
}

void HitStopComponent::HitStop(const double _stopPower, const double _stopSeconds, const double _defaultTimeDilation)
{
	mHitStopSeconds = _stopSeconds;
	mElapsedStopTime = 0.0;
	mOwnerDefaultTimeDilation = _defaultTimeDilation;

	// �^�C���_�C���[�V������ݒ肷��
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

	// �o�ߎ��Ԃ��v������ 
	// �����̒l���g���Ă��Ȃ��̂́ATimeDilation�̉e�����󂯂��l�����琳��Ɍo�ߎ��Ԃ𑪂邱�Ƃ��ł��Ȃ�����
	mElapsedStopTime += FPSController::GetDeltaTime();

	if (mElapsedStopTime >= mHitStopSeconds)
	{
		mbStop = false;
		mOwner->SetTimeDilation(mOwnerDefaultTimeDilation);
	}
}
