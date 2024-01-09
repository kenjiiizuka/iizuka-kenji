//------------ INCLUDES ------------
#include "Camera.h"
#include "../../Component/MoveComponent/MoveComponent.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../Utility/Debug.h"
#include "../../../System/RendererSystem/Shader/Shader.h"
#include "../../../../main.h"
#include "../../../Utility/MathLibrary.h"

using namespace DirectX::SimpleMath;

DirectX::SimpleMath::Matrix Camera::mViewProjection[2];

Camera::Camera()
	:  mAspectRatio(0.0f)
	, mFarClip(0.0f)
	, mFieldOfView(0.0f)
	, mNearClip(0.0f)
	, mShakeLevel(0)
	, mbShake(false)
	, mShakeTime(0.0f)
	, mElapsedShakeTime(0.0f)
{
	// 処理なし
}

Camera::~Camera()
{
	// 処理なし
}

void Camera::Init()
{
	mTransform.lock()->SetPosition(Vector3(0.0f, 10.0f, -50.0f));
	mFocusPosition = Vector3(0.0f, 0.0f, 0.0f);
	mUpVector = Vector3(0, 1, 0);

	// プロジェクション行列の生成
	mFieldOfView = DirectX::XMConvertToRadians(45.0f);
	mAspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT); // アスペクト比
	mNearClip = 1.0f;  // ニアクリップ
	mFarClip = 1000.f; // ファークリップ

	// プロジェクション行列の作成
	mProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
		mFieldOfView,
		mAspectRatio,
		mNearClip,
		mFarClip
	);

	mViewProjection[1] = mProjectionMatrix.Transpose();
}

void Camera::Update(const double _deltaTime)
{
	CalcuFocusPosition();

	if (mbShake)
	{
		CameraShakeBase();
		mElapsedShakeTime += _deltaTime;
		if (mElapsedShakeTime >= mShakeTime)
		{
			mbShake = false;
		}
	}
}

void Camera::Draw()
{
	// View行列の作成
	mViewMatrix = DirectX::XMMatrixLookAtLH(mTransform.lock()->GetPosition(), mFocusPosition, mUpVector);	
	mViewProjection[0] = mViewMatrix.Transpose();

	Shader::WriteView_ProjectionMatrix(&mViewProjection);
}

void Camera::CameraShake(const uint8_t _shakeLevel, const DirectX::SimpleMath::Vector2 _maxShakeVector, const double _shakeTime)
{
	mbShake = true;
	mShakeLevel = _shakeLevel;
	mShakeTime = _shakeTime;
	mElapsedShakeTime = 0.0f;
	mMaxShakeVector = _maxShakeVector;
}

void Camera::CalcuFocusPosition()
{
	Vector3 lengthVec = mTransform.lock()->GetForwardVector() * 100;
	mFocusPosition = mTransform.lock()->GetPosition() + lengthVec;
}

void Camera::CameraShakeBase()
{
	Vector2 randomVector;
	randomVector.x = MathLibrary::RandomFloatInRange(-mMaxShakeVector.x, mMaxShakeVector.x) * mShakeLevel;
	randomVector.y = MathLibrary::RandomFloatInRange(-mMaxShakeVector.y, mMaxShakeVector.y) * mShakeLevel;
	mTransform.lock()->AddPosition({randomVector.x, randomVector.y,0.0f});
}
