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
 * @brief XInput�ł̃R���g���[���[�̏�������
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
		Cout<std::string>("Controller�ڑ�����");
	}
	else
	{
		Cout<std::string>("Controller�ɐڑ��ł��Ă��܂���");
	}		
}


/**
 * @fn Update
 * @brief XInput�ł̍X�V���� InputState�̍X�V�A�Ǘ�������
 * @return void
*/
void XInput::Update()
{
	mOldPadState = mPadState; // �O�t���[���̉������Ƃ��ĕۑ�
	DWORD result = XInputGetState(mControllerIndex, &mXInputState);
	if (result == ERROR_SUCCESS)
	{	
		CheckPressedPadButtons();

		// �g���K�[�{�^����������Ă��邩�m�F
		mPadState[LeftTrigger] = mXInputState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		mPadState[RightTrigger] = mXInputState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;	
	}
}


/**
 * @fn CheckPressedButtons
 * @brief ���݂̃{�^���̉��������m�F���A�X�V����֐�
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
 * @brief �����Ŏw�肳�ꂽ�{�^����������Ă邩�擾����֐�
 * @return bool true ������Ă��� : false ������Ă��Ȃ�
*/
bool XInput::GetPadPress(Pad _button)
{
	return mPadState[_button];
}

/**
 * @fn Trigger
 * @brief �����Ŏw�肵���Q�[���p�b�h�{�^���̃g���K�[�擾������֐�
 * @return bool true �����ꂽ(�����ꂽ�u��) : false ������Ă��Ȃ��i�����ꂽ�u�Ԃł͂Ȃ��j
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
 * @brief �Q�[���p�b�h�̉E�X�e�B�b�N�̓|�����擾����
 * @return Vector2 x,y���̒l��Ԃ�
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
 * @brief �Q�[���p�b�h�̍��X�e�B�b�N�̓|�����擾����
 * @return Vector2 x,y���̒l��Ԃ�
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
 * @brief �Q�[���p�b�h�̍��X�e�B�b�N�̓|��Ă���p�x��Ԃ�
 * @return Vector2 x,y���̒l��Ԃ�
*/
DirectX::SimpleMath::Vector3 XInput::GetPadLeftStickRotation()
{
	Vector2 stick = GetPadLeftStick();
	float stickRadian = MathLibrary::Atan2(stick.y, stick.x);	
	Cout<float>(stickRadian);
	return Vector3(0, stickRadian, 0);
}
