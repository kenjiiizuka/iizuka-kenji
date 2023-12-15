#include "XInput.h"
#include "../../Utility/Debug.h"
#include "../../Utility/MathLibrary.h"

//-------- LIB --------
#pragma comment (lib, "xinput.lib")

DWORD XInput::mControllerIndex = 0;
XINPUT_STATE XInput::mXInputState = {};
std::array<bool, (size_t)Pad::Max> XInput::mPadState = {};
std::array<bool, (size_t)Pad::Max> XInput::mOldPadState = {};
std::array<WORD, (size_t)Pad::Max> XInput::mPadID = {};
const float XInput::mMaxStickThumb = 32767.f;

using namespace DirectX::SimpleMath;

/**
 * @fn Init
 * @brief XInputでのコントローラーの初期処理
 * @return void 
*/
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


/**
 * @fn Update
 * @brief XInputでの更新処理 InputStateの更新、管理をする
 * @return void
*/
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
}


/**
 * @fn CheckPressedButtons
 * @brief 現在のボタンの押下情報を確認し、更新する関数
 * @return void
*/
void XInput::CheckPressedPadButtons()
{	
	for (UINT i = 0; i < Pad::LeftTrigger; i++)
	{
		mPadState[i] = mXInputState.Gamepad.wButtons & mPadID[i];
	}	
}

/**
 * @fn Press
 * @brief 引数で指定されたボタンが押されてるか取得する関数
 * @return bool true 押されている : false 押されていない
*/
bool XInput::GetPadPress(Pad _button)
{
	return mPadState[_button];
}

/**
 * @fn Trigger
 * @brief 引数で指定したゲームパッドボタンのトリガー取得をする関数
 * @return bool true 押された(押された瞬間) : false 押されていない（押された瞬間ではない）
*/
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


/**
 * @fn GetPadRightStick
 * @brief ゲームパッドの右スティックの倒れ具合を取得する
 * @return Vector2 x,y軸の値を返す
*/
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

/**
 * @fn GetPadRightStick
 * @brief ゲームパッドの左スティックの倒れ具合を取得する
 * @return Vector2 x,y軸の値を返す
*/
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

/**
 * @fn GetPadLeftStickRotation
 * @brief ゲームパッドの左スティックの倒れている角度を返す
 * @return Vector2 x,y軸の値を返す
*/
DirectX::SimpleMath::Vector3 XInput::GetPadLeftStickRotation()
{
	Vector2 stick = GetPadLeftStick();
	float stickRadian = MathLibrary::Atan2(stick.y, stick.x);	
	Cout<float>(stickRadian);
	return Vector3(0, stickRadian, 0);
}
