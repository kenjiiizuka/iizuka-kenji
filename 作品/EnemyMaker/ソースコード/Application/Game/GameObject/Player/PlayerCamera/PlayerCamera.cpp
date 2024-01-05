//-------- INCLUDES --------
#include "PlayerCamera.h"
#include "../Player.h"
#include "../../../Component/TransformComponent/TransformComponent.h"
#include "../../../../System/InputSystem/XInput.h"
#include "../../../../Utility/MathLibrary.h"
#include "../../../Scene/SceneManager.h"

using namespace DirectX::SimpleMath;

PlayerCamera::PlayerCamera()
	: mDistanceToPlayer(23.5f)
	, mMoveInterpSpeed(4.0f)
	, mFixFoucusHeight(8.0f)
	, mMoveHorizontalRadius(0.04f)
	, mMoveVerticaRadius(0.02f)
	, bVerticalInverse(false)
	, bHorizontalInverse(false)
	, mbResetPosition(false)
	, mResetElapsedTime(0.0f)
	, mResetTime(0.2f)
	, mState(CameraState::State_Free)
{
	// 処理なし
}

void PlayerCamera::Init(std::weak_ptr<Player> _plyer)
{
	mPlayer = _plyer;
	mPlayerTransform = _plyer.lock()->GetComponent<TransformComponent>();

	// 初期位置としてプレイヤーの後ろにカメラを設置する
	Vector3 playerPos = mPlayerTransform.lock()->GetPosition();
	Vector3 newCameraPos = playerPos + (-mPlayerTransform.lock()->GetForwardVector() * mDistanceToPlayer);
	newCameraPos.y += 10;
	mTransform.lock()->SetPosition(newCameraPos);

	// 注視点の設定
	Vector3 newTargetPos = playerPos;
	newTargetPos.y += mFixFoucusHeight;
	mFocusPosition = newTargetPos;

	// 基準となるプレイヤーへのベクトルを保存
	mInitToPlayerVector = newCameraPos - playerPos;
	mInitToPlayerVector.Normalize();
}

void PlayerCamera::Update(const double _deltaTime)
{
	// カメラ位置の設定
	CalcuPosition();

	// 回転の制御
	ControlRotation(_deltaTime);

	// 基底クラスの更新処理実行
	Camera::Update(_deltaTime);
}


void PlayerCamera::CalcuFocusPosition()
{
	// カメラ位置の設定
	Vector3 mPlayerPos = mPlayerTransform.lock()->GetPosition();
	Vector3 newTargetPos = mPlayerPos;
	newTargetPos.y += mFixFoucusHeight;
	mFocusPosition = newTargetPos;
}

void PlayerCamera::PositionReset(const double _deltaTime)
{
	// 初期位置まで補間する
	Quaternion targetQuat;
	Vector3 targetRotation = mPlayerTransform.lock()->GetRotation();
	targetRotation.x = mTransform.lock()->GetRotation().x;
	MathLibrary::ConvRotationToQuaternion(targetRotation, targetQuat);

	Quaternion cameraQuat;
	MathLibrary::ConvRotationToQuaternion(mTransform.lock()->GetRotation(), cameraQuat);

	// 補間に使用する比率を求める
	float t = MathLibrary::Clamp01(static_cast<float>(mResetElapsedTime / mResetTime));

	// 補間
	Quaternion newQuaternion = Quaternion::Lerp(cameraQuat, targetQuat, t);

	// 回転のセット
	mTransform.lock()->SetRotation(newQuaternion.ToEuler());

	// 経過時間を加算
	mResetElapsedTime += _deltaTime;
}

void PlayerCamera::ControlRotation(const double _deltaTime)
{
	if (XInput::GetPadTrigger(Pad::LeftBack))
	{
		mbResetPosition = true;
		mResetElapsedTime = 0.0f;
	}

	// カメラ位置リセット処理
	if (mbResetPosition)
	{
		// 位置リセット処理
		PositionReset(_deltaTime);

		// カメラリセット処理の終了チェック
		mbResetPosition = !(mResetElapsedTime >= mResetTime);

		return;
	}

	// 回転の処理	
	// 操作の反転処理
	float verticalAddRadius = bVerticalInverse ? mMoveVerticaRadius : mMoveVerticaRadius * -1;
	float horizonAddRadius = bHorizontalInverse ? mMoveHorizontalRadius * -1 : mMoveHorizontalRadius;

	// 回転量を計算
	Vector2 moveRotation = XInput::GetPadRightStick() * Vector2(horizonAddRadius, verticalAddRadius);
	mTransform.lock()->AddRotation({ moveRotation.y, moveRotation.x, 0 });

	// 最大の回転量を超えていないか確認する
	CheckRotationLimit();
}

void PlayerCamera::CheckRotationLimit()
{
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
}

void PlayerCamera::CalcuPosition()
{
	Vector3 mPlayerPos = mPlayerTransform.lock()->GetPosition();
	Vector3 camRotation = mTransform.lock()->GetRotation();
	Vector3 playerToCameraVector = MathLibrary::RotateVector(mInitToPlayerVector, camRotation);
	Vector3 newCameraPos = mPlayerPos + (playerToCameraVector * mDistanceToPlayer);
	mTransform.lock()->SetPosition(newCameraPos);
}

void PlayerCamera::SetPlayer(std::weak_ptr<Player> _player)
{
	mPlayer = _player;
}
