//----------- INCLUDES -----------
#include "CameraShakeNotify.h"
#include "CameraManager.h"
#include "Camera.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneManager.h"

CameraShakeNotify::CameraShakeNotify(SkeletalMeshAnimationClip* _attachAnimation, float _attachFrame)
	: AnimationNotify(_attachAnimation, _attachFrame)
	, mShakeTime(0.5f)
	, mShakeLevel(1)
{
	// 処理なし
}

CameraShakeNotify::~CameraShakeNotify()
{
	// 処理なし
}

void CameraShakeNotify::NotifyUpdate()
{
	SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->GetMainCamera()->CameraShake(mShakeLevel, mShakeVector, mShakeTime);
}


