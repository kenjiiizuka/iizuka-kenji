//-------- INCLUDES --------
#include "XInput.h"
#include "../../Utility/Debug.h"
#include "../../Utility/MathLibrary.h"
#include "../FPSController/FPSController.h"

//-------- LIB --------
#pragma comment (lib, "xinput.lib")

DWORD XInput::mControllerIndex = 0;
XINPUT_STATE XInput::mXInputState = {};
std::array<bool, (size_t)Pad::Max> XInput::mPadState = {};
std::array<bool, (size_t)Pad::Max> XInput::mOldPadState = {};
std::array<WORD, (size_t)Pad::Max> XInput::mPadID = {};
XINPUT_VIBRATION XInput::mVibration = {};
const float XInput::mMaxStickThumb = 32767.f;
float XInput::mVibrationTime = 0;
bool XInput::mbVibration = false;
float XInput::mElapsedVibrationTime = 0;
WORD XInput::mMaxVibration = 65535;

using namespace DirectX::SimpleMath;

void XInput::Init()
{
	mPadID[Pad::A] = XINPUT_GAMEPAD_A;
	mPadID[Pad::B] = XINPUT_GAMEPAD_B;
	mPadID[Pad::X] = XINPUT_GAMEPAD_X;
	mPadID[Pad::Y] = XINPUT_GAMEPAD_Y;
	mPadID[Pad::Up] = XINPUT_GAMEPAD_DPAD_UP;
	mPadID[Pad::Down] = XINPUT_GAMEPAD_DPAD_DOWN;
	mPadID[Pad::Left] = XINPUT_GAMEPAD_DPAD_LEFT;
	mPadID[Pad::Right] = XINPUT_GAMEPAD_DPAD_RIGHT;
	mPadID[Pad::Back] = XINPUT_GAMEPAD_START;
	mPadID[Pad::Start] = XINPUT_GAMEPAD_BACK;
	mPadID[Pad::LeftThumb] = XINPUT_GAMEPAD_LEFT_THUMB;
	mPadID[Pad::RightThumb] = XINPUT_GAMEPAD_RIGHT_THUMB;
	mPadID[Pad::LeftBack] = XINPUT_GAMEPAD_LEFT_SHOULDER;
	mPadID[Pad::RightBack] = XINPUT_GAMEPAD_RIGHT_SHOULDER;
	mPadID[Pad::LeftTrigger] = 0;  
	mPadID[Pad::RightTrigger] = 0; 

	DWORD result = XInputGetState(mControllerIndex, &mXInputState);
	if (result == ERROR_SUCCESS)
	{		
		CheckPressedPadButtons();
		Cout<std::string>("Controller接続完了");
	}
	else
	{
		Cout<std::string>("Controllerに接続できていません");
	}	
}

void XInput::Update()
{
	mOldPadState = mPadState; // 前フレームの押下情報として保存
	DWORD result = XInputGetState(mControllerIndex, &mXInputState);
	if (result == ERROR_SUCCESS)
	{	
		CheckPressedPadButtons();

		// トリガーボタンがおされているか確認
		mPadState[LeftTrigger] = mXInputState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		mPadState[RightTrigger] = mXInputState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;	
	}

	// 振動の処理をする
	if (mbVibration)
	{
		VibrationUpdate();
	}

}

void XInput::CheckPressedPadButtons()
{	
	for (UINT i = 0; i < Pad::LeftTrigger; i++)
	{
		mPadState[i] = mXInputState.Gamepad.wButtons & mPadID[i];
	}	
}

void XInput::VibrationUpdate()
{	
	XInputSetState(mControllerIndex, &mVibration);

	// 経過時間を加算
	mElapsedVibrationTime += FPSController::GetDeltaTimeFloat();

	// 振動終了処理
	if (mElapsedVibrationTime >= mVibrationTime)
	{
		mbVibration = false;
		mVibration = {};
		XInputSetState(mControllerIndex, &mVibration);
	}
}

bool XInput::GetPadPress(Pad _button)
{
	return mPadState[_button];
}

void XInput::Vibration(const float _vibrationTime, const float _leftMotorPower, const float _rightMotorPower)
{
	mElapsedVibrationTime = 0.0f;
	mVibrationTime = _vibrationTime;
	mVibration.wLeftMotorSpeed = static_cast<WORD>(_leftMotorPower);
	mVibration.wRightMotorSpeed = static_cast<WORD>(_rightMotorPower);
	mbVibration = true;
}

bool XInput::GetPadTrigger(Pad _button)
{
	return mPadState[_button] && !mOldPadState[_button];
}

bool XInput::GetPressAnyKey()
{
	for (bool button : mPadState)
	{
		if (button)
		{
			return true;
		}
	}
	return false;
}

bool XInput::IsLeftStickInputAble()
{
	if ((mXInputState.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		mXInputState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(mXInputState.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			mXInputState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		return false;
	}
	return true;
}

DirectX::SimpleMath::Vector2 XInput::GetPadRightStick()
{
	if ((mXInputState.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		mXInputState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(mXInputState.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			mXInputState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		return Vector2::Zero;
	}

	Vector2 stick;
	stick.x = MathLibrary::ClampMinus1Plus1(static_cast<float>(mXInputState.Gamepad.sThumbRX) / mMaxStickThumb);
	stick.y = MathLibrary::ClampMinus1Plus1(static_cast<float>(mXInputState.Gamepad.sThumbRY) / mMaxStickThumb);
	return stick;
}

DirectX::SimpleMath::Vector2 XInput::GetPadLeftStick()
{
	if ((mXInputState.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		mXInputState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(mXInputState.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			mXInputState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		return Vector2::Zero;
	}

	Vector2 stick;
	stick.x = MathLibrary::ClampMinus1Plus1(static_cast<float>(mXInputState.Gamepad.sThumbLX) / mMaxStickThumb);
	stick.y = MathLibrary::ClampMinus1Plus1(static_cast<float>(mXInputState.Gamepad.sThumbLY) / mMaxStickThumb);
	return stick;
}

DirectX::SimpleMath::Vector3 XInput::GetPadLeftStickRotation()
{
	Vector2 stick = GetPadLeftStick();
	float stickRadian = MathLibrary::Atan2(stick.y, stick.x);	
	Cout<float>(stickRadian);
	return Vector3(0, stickRadian, 0);
}
