//------------- INCLUDES ------------
#include "CharacterMovementComponent.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../../System/FPSController/FPSController.h"
#include "../../../Utility/MathLibrary.h"

using namespace DirectX::SimpleMath;

CharacterMovementComponent::CharacterMovementComponent()
	: bIsMoving(false)
	, bIsMoveInput(false)
	, bIsFaceDirection(true)
	, mMaxAcceleration(2000.f)
	, mMaxWalkSpeed(5.f)
	, mInitSpeed(10.f)
	, mMoveElapsedTime(0.f)
	, mFaceDirectionInterpSpeed(3.0f)
{
	// 処理なし
}

CharacterMovementComponent::~CharacterMovementComponent()
{
	// 処理なし
}

void CharacterMovementComponent::Init()
{
	MoveComponent::Init();
	mCurrentVelocity = Vector3::Zero;
	mInitVelocity = Vector3::Zero;
}

void CharacterMovementComponent::Update(const double _deltaTime)
{
	// 移動しているか判断	
	bIsMoving = mCurrentVelocity != Vector3::Zero;

	float deltaTime = static_cast<float>(_deltaTime);

	// 減速の処理
	if (!bIsMoveInput)
	{	
		Deceleration(deltaTime);
		bIsMoveInput = false;
		return;
	}
	
	mMoveElapsedTime += FPSController::GetDeltaTime();

	// 移動処理
	// Ownerの向きを移動方向に合わせる
	if (bIsFaceDirection)
	{
		FaceDirection();
	}

	mOwnerTransform.lock()->AddPosition(mCurrentVelocity * deltaTime);	
	bIsMoveInput = false;
}

void CharacterMovementComponent::FaceDirection()
{
	// 移動していなかったら
	if (MathLibrary::VectorIsZero(mCurrentVelocity))
	{
		return;
	}

	const Vector3 rotation = mOwnerTransform.lock()->GetRotation();
	Vector3 targetRotation = MathLibrary::Conv_VectorToRotation(mCurrentVelocity); // Velocityから移動方向への回転を求める
	Quaternion currentQuaternion = Quaternion::CreateFromYawPitchRoll(rotation);
	Quaternion targetQuaternion = Quaternion::CreateFromYawPitchRoll(targetRotation);
	Vector3 newRotation = MathLibrary::LerpQuaternion(currentQuaternion, targetQuaternion, static_cast<float>(FPSController::GetDeltaTime()), mFaceDirectionInterpSpeed);
	newRotation.x = 0;
	newRotation.z = 0;
	mOwnerTransform.lock()->SetRotation(newRotation);
}

void CharacterMovementComponent::Deceleration(const float _deltaTime)
{
	mCurrentVelocity = Vector3::Zero;
	mInitVelocity = Vector3::Zero;
}

void CharacterMovementComponent::AddMovementInput(DirectX::SimpleMath::Vector3 _direction, float _scaleValue)
{
	bIsMoveInput = true;
	if (bIsMoving)
	{
		float speed =  static_cast<float>((mInitVelocity.Length() * mMoveElapsedTime) + mMaxAcceleration * pow(mMoveElapsedTime, 2.0f) / 2.0f);
		speed = speed > mMaxWalkSpeed ? mMaxWalkSpeed : speed;
		mCurrentVelocity = _direction * speed;
	}
	else
	{
		mInitVelocity = mInitSpeed * (_direction) * _scaleValue; // 初速を求め、現在の速度にする
		mCurrentVelocity = mInitVelocity;
	}
}