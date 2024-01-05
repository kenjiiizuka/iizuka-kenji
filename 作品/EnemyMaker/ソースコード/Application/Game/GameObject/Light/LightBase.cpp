#include "LightBase.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../System/FPSController/FPSController.h"
#include "../../../../main.h"

LightBase::LightBase()
	:mPosition(-49.0f,102.0f,-9.0f)
	, mDiffuse(1.0f,1.0f,1.0f,1.0f)
	, mAmbient(0.3f,0.3f,0.3f,1.0f)
	, mTargetPosition(100,0,100)
{
	CalucDirection();
}

#ifdef _DEBUG
void LightBase::Update(const double _deltaTime)
{
	float speed = 50;
	if(Input::GetKeyPress('L'))
	{
		float deltaTime = static_cast<float>(FPSController::GetDeltaTime());
		if (Input::GetKeyPress('W'))
		{
			mPosition.x += speed * deltaTime;
		}
		if (Input::GetKeyPress('S'))
		{
			mPosition.x -= speed * deltaTime;
		}
		if (Input::GetKeyPress('A'))
		{
			mPosition.z -= speed * deltaTime;
		}
		if (Input::GetKeyPress('D'))
		{
			mPosition.z += speed * deltaTime;
		}
		if (Input::GetKeyPress('Q'))
		{
			mPosition.y += speed * deltaTime;
		}
		if (Input::GetKeyPress('Z'))
		{
			mPosition.y -= speed * deltaTime;
		}

		if (Input::GetKeyPress('G'))
		{
			mAmbient.x -= 1 * deltaTime;
			mAmbient.y -= 1 * deltaTime;
			mAmbient.z -= 1 * deltaTime;

			mAmbient = { 1.0f,1.0f,1.0f,1.0f };
		}
		else if (Input::GetKeyPress('H'))
		{
			mAmbient.x += 1 * deltaTime;
			mAmbient.y += 1 * deltaTime;
			mAmbient.z += 1 * deltaTime;
			mAmbient = { 0.0f,0.0f,0.0f,0.0f };
		}

	}

	CalucDirection();

	//std::cout << "Light Position" << std::endl;
	//std::cout << "X " << mPosition.x << " Y " << mPosition.y << " Z " << mPosition.z << std::endl;
}
#endif // _DEBUG

void LightBase::CalucDirection()
{
	mDirection = mTargetPosition - mPosition;
	//mDirection.Normalize();
}

void LightBase::CalucLightViewMatrix(DirectX::SimpleMath::Matrix& _lightMatrix, DirectX::SimpleMath::Vector3 _targetPos)
{
	_lightMatrix = DirectX::XMMatrixLookAtLH(mPosition, mTargetPosition, {0,1,0});	
}

void LightBase::CalucLightProjectionMatrix(DirectX::SimpleMath::Matrix& _lightMatrix)
{
	// プロジェクション行列の生成
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);
	float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT); // アスペクト比
	float nearPlane = 1.0f;  // ニアクリップ
	float farPlane = 1000.f; // ファークリップ

	_lightMatrix = DirectX::XMMatrixPerspectiveFovLH(
		fieldOfView,
		aspectRatio,
		nearPlane,
		farPlane
	);
}
