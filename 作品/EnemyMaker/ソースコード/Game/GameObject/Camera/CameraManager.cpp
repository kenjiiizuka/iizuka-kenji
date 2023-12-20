#include "CameraManager.h"
#include "DebugCamera.h"
#include "../../../System/InputSystem/Input.h"
#include "Camera2D.h"

void CameraManager::Init()
{
	// デフォルトでデバッグカメラを生成しメインカメラにする
	mMainCamera = CreateCamera<DebugCamera>("DebugCamera");
	
	m2DCamera = std::make_shared<Camera2D>();
}

void CameraManager::Update(const double _deltaTime)
{
	Debug();
	mMainCamera->UpdateBase(_deltaTime);
}

void CameraManager::Draw()
{
	mMainCamera->DrawBase(DirectX::SimpleMath::Matrix::Identity);
}

void CameraManager::Uninit()
{
	for (std::pair<std::string, std::shared_ptr<Camera>> pair : mpCameraList) {
		pair.second->UninitBase();
	}
	mpCameraList.clear();
}

void CameraManager::Debug()
{
#if defined(DEBUG) || defined(_DEBUG)	
	if (Input::GetKeyTrigger(VK_F2)) {
		if (bDebug) {
			SetMainCamera(mOldCameraName);
		}
		else {
			mOldCameraName = mMainCameraName;
			SetMainCamera("DebugCamera");
		}
		bDebug = !bDebug;
	}
#endif
}
