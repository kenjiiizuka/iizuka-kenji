#include "PlayerCamera.h"
#include "../Player.h"
#include "../../../Component/TransformComponent/TransformComponent.h"
#include "../../../../System/InputSystem/XInput.h"
#include "../../../../Utility/MathLibrary.h"

using namespace DirectX::SimpleMath;

PlayerCamera::PlayerCamera()
	: mDistanceToPlayer(23.5f)
	, mMoveInterpSpeed(4.0f)
	, mFixFoucusHeight(8.0f)
	, mMoveHorizontalRadius(0.04f)
	, mMoveVerticaRadius(0.02f)
	, bVerticalInverce(false)
	, bHorizontalInverce(false)
{
	// �����Ȃ�
}

void PlayerCamera::FixInit(std::weak_ptr<Player> _plyer)
{
	mPlayer = _plyer;
	mPlayerTransform = _plyer.lock()->GetComponent<TransformComponent>();

	// �����ʒu�Ƃ��ăv���C���[�̌��ɃJ������ݒu����
	Vector3 playerPos = mPlayerTransform.lock()->GetPosition();
	Vector3 newCameraPos = playerPos + (-mPlayerTransform.lock()->GetForwardVector() * mDistanceToPlayer);
	newCameraPos.y += 6;
	mTransform.lock()->SetPosition(newCameraPos);

	// �����_�̐ݒ�
	Vector3 newTargetPos = playerPos;
	newTargetPos.y += mFixFoucusHeight;
	mFocusPosition = newTargetPos;

	// ��ƂȂ�v���C���[�ւ̃x�N�g����ۑ�
	mInitToPlayerVector = newCameraPos - playerPos;
	mInitToPlayerVector.Normalize();
}

void PlayerCamera::Update(const double _deltaTime)
{
	// �J�����ʒu�̐ݒ�
	Vector3 mPlayerPos = mPlayerTransform.lock()->GetPosition();

	// �x�N�g���̉�]
	Vector3 camRotation = mTransform.lock()->GetRotation();
	Vector3 playerToCameraVector = MathLibrary::RotateVector(mInitToPlayerVector, camRotation);
	Vector3 newCameraPos = mPlayerPos + (playerToCameraVector * mDistanceToPlayer);	
	mTransform.lock()->SetPosition(newCameraPos);

	// ��]�̏���	
	// ����̔��]����
	float verticalAddRadius = bVerticalInverce ? mMoveVerticaRadius : mMoveVerticaRadius * -1;
	float horizonAddRadius = bHorizontalInverce ? mMoveHorizontalRadius * -1 : mMoveHorizontalRadius;
	Vector2 moveRadius = XInput::GetPadRightStick() * Vector2(horizonAddRadius, verticalAddRadius);	
	mTransform.lock()->AddRotation({ moveRadius.y, moveRadius.x, 0 });	 // vertical(Roll)��Y�v�f  horizon(Yaw)��X�v�f
	Vector3 currentRotation = mTransform.lock()->GetRotation();
	if (currentRotation.x > 1.3f)
	{
		currentRotation.x = 1.3f;
		mTransform.lock()->SetRotation(currentRotation);
	}
	else if (currentRotation.x < -0.23f)
	{
		currentRotation.x = -0.23f;
		mTransform.lock()->SetRotation(currentRotation);
	}

	// ���N���X�̍X�V�������s
	Camera::Update(_deltaTime);
}


void PlayerCamera::CalcuFocusPosition()
{
	// �J�����ʒu�̐ݒ�
	Vector3 mPlayerPos = mPlayerTransform.lock()->GetPosition();
	Vector3 newTargetPos = mPlayerPos;
	newTargetPos.y += mFixFoucusHeight;
	mFocusPosition = newTargetPos;
}

void PlayerCamera::SetPlayer(std::weak_ptr<Player> _player)
{
	mPlayer = _player;
}
