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
	// �����Ȃ�
}

PlayerMovementComponent::~PlayerMovementComponent()
{
	// �����Ȃ�
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
	// �o�ߎ��Ԃ����Z ���x��x�����邽��
	mMoveElapsedTime -= 0.1f;
	mMoveElapsedTime = MathLibrary::Clamp(mMoveElapsedTime, 0.0f, mTimeToMaxSpeed);

	// �ړ����x�����߂�@�����͉������l�����Ȃ� 
	mCurrentSpeed = mMaxSpeed * MathLibrary::Clamp01(mMoveElapsedTime / mTimeToMaxSpeed);

	// ���ۂ̈ړ��ʂ����߂�
	mCurrentVelocity = mStickDirection * mCurrentSpeed;

	// ���W�ړ�
	mOwnerTransform.lock()->AddPosition(mCurrentVelocity * _deltaTime);
}

void PlayerMovementComponent::FaceDirection(const float _deltaTime)
{
	// �ړ����Ă��Ȃ�������
	if (MathLibrary::VectorIsZero(mCurrentVelocity))
	{
		return;
	}

	const Vector3 rotation = mOwnerTransform.lock()->GetRotation();
	Vector3 targetRotation = MathLibrary::Conv_VectorToRotation(mCurrentVelocity); // Velocity����ړ������ւ̉�]�����߂�
	Quaternion currentQuaternion = Quaternion::CreateFromYawPitchRoll(rotation);
	Quaternion targetQuaternion = Quaternion::CreateFromYawPitchRoll(targetRotation);
	Vector3 newRotation = MathLibrary::LerpQuaternion(currentQuaternion, targetQuaternion, _deltaTime , mFaceDirectionInterpSpeed);
	newRotation.x = 0;
	newRotation.z = 0;
	mOwnerTransform.lock()->SetRotation(newRotation);
}

void PlayerMovementComponent::Movement(const float _deltaTime)
{
	// �ړ������Ɍ�����
	FaceDirection(_deltaTime);

	// ���݂̑��x�����߂�
	mCurrentSpeed = mMaxSpeed * MathLibrary::Clamp01(mMoveElapsedTime / mTimeToMaxSpeed) * mAcceleration;
	mCurrentSpeed = MathLibrary::Clamp(mCurrentSpeed, 0.0f, mMaxSpeed);

	// ���ۂ̈ړ��ʂ����߂�
	mCurrentVelocity = mStickDirection * mCurrentSpeed;

	// ���W�ړ�
	mOwnerTransform.lock()->AddPosition(mCurrentVelocity * _deltaTime);

	// �o�ߎ��Ԃ����Z
	mMoveElapsedTime += _deltaTime;
	mMoveElapsedTime = MathLibrary::Clamp(mMoveElapsedTime, 0.0f, mTimeToMaxSpeed * 1.5f);
}

void PlayerMovementComponent::AddMovementInput(const DirectX::SimpleMath::Vector3 _stickDirection)
{
	mbMoveInput = true;
	mStickDirection = _stickDirection;

	// ���͂���Ă���X�e�B�b�N�̓|��Ă���x�N�g�����猻�݂̈ړ����x�����߂�
	float stickDirectionLength = _stickDirection.Length();
	// �ڕW�̑��x
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



