//----------- INCLUDES ----------
#include "DebugCamera.h"
#include "../../Component/MoveComponent/MoveComponent.h"
#include "../../../System/InputSystem/Input.h"

using namespace DirectX::SimpleMath;

void DebugCamera::Init()
{
	Camera::Init();
	AddComponent<MoveComponent>();
}

void DebugCamera::Update(const double _deltaTime)
{
	if (Input::GetKeyPress('1'))
	{
		bAnableInput = !bAnableInput;
	}
	
	if (!bAnableInput) 
	{
		return;
	}

	if (Input::GetKeyPress(VK_CONTROL)) {
		RotateMove();
	}
	else {
		Move();
	}	

	Camera::Update(_deltaTime);
}

void DebugCamera::Move()
{
	std::shared_ptr<MoveComponent> moveComp = GetComponent<MoveComponent>();
	moveComp->SetMoveSpeed(20.f);
	moveComp->SetRotSpeed(1.f);
	float scaleValue = 0.0f;
	if (Input::GetKeyPress(VK_SHIFT)) {
		if (Input::GetKeyPress(VK_DOWN)) {
			scaleValue = -1.f;
			moveComp->MoveUp(scaleValue);
		}
		if (Input::GetKeyPress(VK_UP)) {
			scaleValue = 1.f;
			moveComp->MoveUp(scaleValue);
		}
	}
	else {
		if (Input::GetKeyPress(VK_DOWN)) {
			scaleValue = -1.f;
			moveComp->MoveForward(scaleValue);
		}
		if (Input::GetKeyPress(VK_UP)) {
			scaleValue = 1.f;
			moveComp->MoveForward(scaleValue);
		}
	}

	if (Input::GetKeyPress(VK_RIGHT)) {
		scaleValue = 1.0f;
		moveComp->MoveRight(scaleValue);
	}
	if (Input::GetKeyPress(VK_LEFT)) {
		scaleValue = -1.0f;
		moveComp->MoveRight(scaleValue);
	}
}

void DebugCamera::RotateMove()
{
	std::shared_ptr<MoveComponent> moveComp = GetComponent<MoveComponent>();
	float scaleValue = 1;
	if (Input::GetKeyPress(VK_DOWN)) {
		scaleValue = 1.f;
		moveComp->RotationPitch(scaleValue);
	}
	if (Input::GetKeyPress(VK_UP)) {
		scaleValue = -1.f;
		moveComp->RotationPitch(scaleValue);
	}
	if (Input::GetKeyPress(VK_RIGHT)) {
		scaleValue = 1.0f;
		moveComp->RotationYaw(scaleValue);
	}
	if (Input::GetKeyPress(VK_LEFT)) {
		scaleValue = -1.0f;
		moveComp->RotationYaw(scaleValue);
	}
}
