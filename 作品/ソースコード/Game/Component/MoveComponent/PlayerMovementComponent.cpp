//----------- INCLUDES ------------
#include "PlayerMovementComponent.h"
#include "../../../Utility/MathLibrary.h"
#include "../../Component/TransformComponent/TransformComponent.h"
#include "../../../ImGui/ImGuiUtility.h"

using namespace DirectX::SimpleMath;

PlayerMovementComponent::PlayerMovementComponent()
	: mAcceleration(5.0f)
	, mbMoveInput(false)
	, mMoveElapsedTime(0.0f)
	, mTimeToMaxSpeed(1.5f)
	, mCurrentSpeed(0.0f)
	, mCurrentTargetSpeed(0.0f)
	, mFaceDirectionInterpSpeed(0.0f)
	, mMaxSpeed(0.0f)
{
	// 処理なし
}

PlayerMovementComponent::~PlayerMovementComponent()
{
	// 処理なし
}

void PlayerMovementComponent::Update(const double _deltaTime)
{
	float deltaTime = static_cast<float>(_deltaTime);

	if (mbMoveInput) 
	{	
		Movement(deltaTime);
	}
	else
	{
		Deceleration(deltaTime);
	}

	//ImGui::Begin("PlayerMove");
	//ImGuiUtility::GetInstance().DragFloat("Acceleration", mAcceleration, 1.0f, 10.0f);
	//ImGui::End();

	mbMoveInput = false;
}

void PlayerMovementComponent::Deceleration(const float _deltaTime)
{
	// 経過時間を減算 速度を遅くするため
	mMoveElapsedTime -= 0.1f;
	mMoveElapsedTime = MathLibrary::Clamp(mMoveElapsedTime, 0.0f, mTimeToMaxSpeed);

	// 移動速度を求める　減速は加速を考慮しない 
	mCurrentSpeed = mMaxSpeed * MathLibrary::Clamp01(mMoveElapsedTime / mTimeToMaxSpeed);

	// 実際の移動量を求める
	mCurrentVelocity = mStickDirection * mCurrentSpeed;

	// 座標移動
	mOwnerTransform.lock()->AddPosition(mCurrentVelocity * _deltaTime);
}

void PlayerMovementComponent::FaceDirection(const float _deltaTime)
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
	Vector3 newRotation = MathLibrary::LerpQuaternion(currentQuaternion, targetQuaternion, _deltaTime , mFaceDirectionInterpSpeed);
	newRotation.x = 0;
	newRotation.z = 0;
	mOwnerTransform.lock()->SetRotation(newRotation);
}

void PlayerMovementComponent::Movement(const float _deltaTime)
{
	// 移動方向に向ける
	FaceDirection(_deltaTime);

	// 現在の速度を求める
	mCurrentSpeed = mMaxSpeed * MathLibrary::Clamp01(mMoveElapsedTime / mTimeToMaxSpeed) * mAcceleration;
	mCurrentSpeed = MathLibrary::Clamp(mCurrentSpeed, 0.0f, mMaxSpeed);

	// 実際の移動量を求める
	mCurrentVelocity = mStickDirection * mCurrentSpeed;

	// 座標移動
	mOwnerTransform.lock()->AddPosition(mCurrentVelocity * _deltaTime);

	// 経過時間を加算
	mMoveElapsedTime += _deltaTime;
	mMoveElapsedTime = MathLibrary::Clamp(mMoveElapsedTime, 0.0f, mTimeToMaxSpeed * 1.5f);
}

void PlayerMovementComponent::AddMovementInput(const DirectX::SimpleMath::Vector3 _stickDirection)
{
	mbMoveInput = true;
	mStickDirection = _stickDirection;

	// 入力されているスティックの倒れているベクトルから現在の移動速度を求める
	float stickDirectionLength = _stickDirection.Length();
	// 目標の速度
	mCurrentTargetSpeed = mMaxSpeed * MathLibrary::Clamp01(stickDirectionLength / 1.0f);	
}

void PlayerMovementComponent::MoveStop()
{
	mCurrentSpeed = 0.0f;
	mCurrentVelocity = Vector3::Zero;
	mCurrentTargetSpeed = 0.0f;
	mMoveElapsedTime = 0.0f;
	mbMoveInput = false;
}



