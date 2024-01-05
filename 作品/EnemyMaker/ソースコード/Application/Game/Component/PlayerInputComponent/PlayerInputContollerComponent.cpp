//---------- INCLUDES ----------
#include "PlayerInputContollerComponent.h"
#include <algorithm>

PlayerInputControllerComponent::PlayerInputControllerComponent()
	: mAllowInputTime(0.16f * 5.0f) // 0.16は1フレームにかかる時間 3はフレーム数
	, mOperationButtons{}
	, mOperationInput({false, false, false})
	, mInputElapsedFrame(0.0f)
{
	// 処理なし
	mOperationButtons[Operation_AttackY] = { Pad::Y, OperationType::OperationType_Trigger };
	mOperationButtons[Operation_AttackB] = { Pad::B, OperationType::OperationType_Trigger };
	mOperationButtons[Operation_Step] = { Pad::A, OperationType::OperationType_Trigger };
	mOperationButtons[Operation_Guard] = { Pad::RightBack, OperationType::OperationType_Press };
	mOperationButtons[Operation_Counter] = { Pad::RightTrigger,OperationType::OperationType_Trigger };
}

PlayerInputControllerComponent::~PlayerInputControllerComponent()
{
	// 処理なし
}

void PlayerInputControllerComponent::Update(const double _deltaTime)
{
	// ボタンが押されているか確認
	for (size_t button_i = 0; Operation operation : mOperationButtons)
	{
		// ボタンが押されていなければ次に行く

		if (operation.second == OperationType_Trigger)
		{
			if (!XInput::GetPadTrigger(operation.first))
			{
				mOperationInput[button_i] = false;
				button_i++;
				continue;
			}
		}
		else
		{
			if (!XInput::GetPadPress(operation.first))
			{
				mOperationInput[button_i] = false;
				button_i++;
				continue;
			}
		}
		
		// ボタンが押されていれば入力経過時間を0にして、入力されたボタンに対応した操作をtrueにする
		mInputElapsedFrame = 0.0f;
		mOperationInput[button_i] = true;
		button_i++;
	}

	// 入力されている操作があるかを確認なければリターン
	bool anyInput = std::any_of(mOperationInput.begin(), mOperationInput.end(), [](bool _element) {return _element; });
	if (!anyInput)
	{
		return;
	}
	
	// 経過時間を加算
	mInputElapsedFrame += static_cast<float>(_deltaTime);

	// 入力許容時間を超えているかをチェック
	// 超えていれば入力をfalseにする
	if (mInputElapsedFrame > mAllowInputTime)
	{
		std::fill(mOperationInput.begin(), mOperationInput.end(), false);
	}
}

