//---------- INCLUDES ----------
#include <iostream>
#include "MoveComponent.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../../System/FPSController/FPSController.h"
#include "../../../Utility/Debug.h"

using namespace DirectX::SimpleMath;

MoveComponent::MoveComponent()
	: mMoveSpeed(10.f)
	, mRotationSpeed(1.0f)
{
	// ˆ—‚È‚µ
}

MoveComponent::~MoveComponent()
{
	// ˆ—‚È‚µ
}

void MoveComponent::Init()
{
	mOwnerTransform = mOwner->GetComponent<TransformComponent>();
}


void MoveComponent::MoveForward(const float _scaleValue)
{
	Vector3 direction = mOwnerTransform.lock()->GetForwardVector() * _scaleValue;
	Vector3 addvec = (direction * mMoveSpeed * static_cast<float>(FPSController::GetDeltaTime()));	
	Vector3 newPos = mOwnerTransform.lock()->GetPosition() + addvec;

	mOwnerTransform.lock()->SetPosition(newPos);
}

void MoveComponent::MoveRight(const float _scaleValue)
{
	Vector3 direction = mOwnerTransform.lock()->GetRightVector() * _scaleValue;
	Vector3 newPos = mOwnerTransform.lock()->GetPosition() + direction * mMoveSpeed * static_cast<float>(FPSController::GetDeltaTime());
	mOwnerTransform.lock()->SetPosition(newPos);
}


void MoveComponent::MoveUp(const float _scaleValue)
{
	Vector3 direction = mOwnerTransform.lock()->GetUpVector() * _scaleValue;
	Vector3 newPos = mOwnerTransform.lock()->GetPosition() + direction * mMoveSpeed * static_cast<float>(FPSController::GetDeltaTime());
	mOwnerTransform.lock()->SetPosition(newPos);
}

void MoveComponent::RotationYaw(const float _scaleValue)
{
	mOwnerTransform.lock()->AddRotation(Vector3(0.0f, (_scaleValue * mRotationSpeed) * static_cast<float>(FPSController::GetDeltaTime()), 0.0f));
}

void MoveComponent::RotationPitch(const float _scaleValue)
{
	mOwnerTransform.lock()->AddRotation(Vector3((_scaleValue * mRotationSpeed) * static_cast<float>(FPSController::GetDeltaTime()), 0.0, 0.0f));
}

void MoveComponent::RotationRoll(const float _scaleValue)
{
	mOwnerTransform.lock()->AddRotation(Vector3(0.0, 0.0f, (_scaleValue * mRotationSpeed) * static_cast<float>(FPSController::GetDeltaTime())));
}


