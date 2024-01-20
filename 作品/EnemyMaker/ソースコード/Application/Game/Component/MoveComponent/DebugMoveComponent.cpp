//---------- INCLUDES ----------
#include "DebugMoveComponent.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../Utility/Debug.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../../System/FPSController/FPSController.h"

using namespace DirectX::SimpleMath;

void DebugMoveComponent::Move()
{	
	SetMoveSpeed(20.f);
	SetRotSpeed(1.f);
	float scaleValue = 0.0f;
	if (Input::GetKeyPress(VK_SHIFT)) {
		if (Input::GetKeyPress(VK_DOWN)) {
			scaleValue = -1.f;
			MoveUp(scaleValue);
		}
		if (Input::GetKeyPress(VK_UP)) {
			scaleValue = 1.f;
			MoveUp(scaleValue);
		}
	}
	else {
		if (Input::GetKeyPress(VK_DOWN)) {
			scaleValue = -1.f;
			MoveForward(scaleValue);
		}
		if (Input::GetKeyPress(VK_UP)) {
			scaleValue = 1.f;
			MoveForward(scaleValue);
		}
	}

	if (Input::GetKeyPress(VK_RIGHT)) {
		scaleValue = 1.0f;
		MoveRight(scaleValue);
	}
	if (Input::GetKeyPress(VK_LEFT)) {
		scaleValue = -1.0f;
		MoveRight(scaleValue);
	}
}

void DebugMoveComponent::MoveRot()
{
	float scaleValue = 1;
	if (Input::GetKeyPress(VK_DOWN)) 
	{
		scaleValue = 1.f;
		RotationPitch(scaleValue);
	}
	if (Input::GetKeyPress(VK_UP)) 
	{
		scaleValue = -1.f;
		RotationPitch(scaleValue);
	}
	if (Input::GetKeyPress(VK_RIGHT)) 
	{
		scaleValue = 1.0f;
		RotationYaw(scaleValue);
	}
	if (Input::GetKeyPress(VK_LEFT)) 
	{
		scaleValue = -1.0f;
		RotationYaw(scaleValue);
	}
}

void DebugMoveComponent::Update(const double _deltaTime)
{
	if (!Input::GetKeyPress(VK_SPACE)) 
	{
		return;
	}

	if (Input::GetKeyPress(VK_CONTROL)) 
	{
		MoveRot();
	}
	else 
	{
		Move();
	}
}

void DebugMoveComponent::MoveForward(const float _scaleValue)
{
	Vector3 direction = Vector3(0,0,1) * _scaleValue;
	Vector3 addvec = (direction * mMoveSpeed * static_cast<float>(FPSController::GetDeltaTime()));
	Vector3 newPos = mOwnerTransform.lock()->GetPosition() + addvec;
	mOwnerTransform.lock()->SetPosition(newPos);
}

void DebugMoveComponent::MoveRight(const float _scaleValue)
{
	Vector3 direction = Vector3(1,0,0) * _scaleValue;
	Vector3 newPos = mOwnerTransform.lock()->GetPosition() + direction * mMoveSpeed * static_cast<float>(FPSController::GetDeltaTime());
	mOwnerTransform.lock()->SetPosition(newPos);
}

void DebugMoveComponent::MoveUp(const float _scaleValue)
{
	Vector3 direction = Vector3(0,1,0) * _scaleValue;
	Vector3 newPos = mOwnerTransform.lock()->GetPosition() + direction * mMoveSpeed * static_cast<float>(FPSController::GetDeltaTime());
	mOwnerTransform.lock()->SetPosition(newPos);
}
