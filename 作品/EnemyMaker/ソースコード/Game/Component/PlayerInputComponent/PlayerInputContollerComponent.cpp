//---------- INCLUDES ----------
#include "PlayerInputContollerComponent.h"
#include <algorithm>

PlayerInputControllerComponent::PlayerInputControllerComponent()
	: mAllowInputTime(0.16f * 5.0f) // 0.16��1�t���[���ɂ����鎞�� 3�̓t���[����
	, mOperationButtons({ Pad::Y,Pad::B,Pad::A})
	, mOperationInput({false, false, false})
	, mInputElapsedFrame(0.0f)
{
	// �����Ȃ�
}

PlayerInputControllerComponent::~PlayerInputControllerComponent()
{
	// �����Ȃ�
}

void PlayerInputControllerComponent::Update(const double _deltaTime)
{
	// �{�^����������Ă��邩�m�F
	for (size_t button_i = 0; Pad button : mOperationButtons)
	{
		// �{�^����������Ă��Ȃ���Ύ��ɍs��
		if (!XInput::GetPadTrigger(button))
		{
			mOperationInput[button_i] = false;
			button_i++;
			continue;
		}

		// �{�^����������Ă���Γ��͌o�ߎ��Ԃ�0�ɂ��āA���͂��ꂽ�{�^���ɑΉ����������true�ɂ���
		mInputElapsedFrame = 0.0f;
		mOperationInput[button_i] = true;
		button_i++;
	}

	// ���͂���Ă��鑀�삪���邩���m�F�Ȃ���΃��^�[��
	bool anyInput = std::any_of(mOperationInput.begin(), mOperationInput.end(), [](bool _element) {return _element; });
	if (!anyInput)
	{
		return;
	}
	
	// �o�ߎ��Ԃ����Z
	mInputElapsedFrame += static_cast<float>(_deltaTime);

	// ���͋��e���Ԃ𒴂��Ă��邩���`�F�b�N
	// �����Ă���Γ��͂�false�ɂ���
	if (mInputElapsedFrame > mAllowInputTime)
	{
		std::fill(mOperationInput.begin(), mOperationInput.end(), false);
	}
}

