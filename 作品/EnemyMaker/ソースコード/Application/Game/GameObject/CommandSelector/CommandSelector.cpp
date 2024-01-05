//---------- INCLUDES ----------
#include "CommandSelector.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../GameObject/Command/CommandObject.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../Component/AudioComponent/AudioComponent.h"

CommandSelector::CommandSelector()
	: mCurrentChoiceID(NoSelect)
	, mSelectButton(Pad::A)
{
	// 処理なし
}

CommandSelector::~CommandSelector()
{
	// 処理なし
}

void CommandSelector::Init()
{
	std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
	sprite->Init({ 0.0f,0.0f }, { 319.0f, 226.0f });

	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/Title/Select.png");
	if (texture->IsValid())
	{
		sprite->SetMaterialTexture(texture->Get<Texture>());
	}

	mCursorSprite = sprite;

	// 決定SE
	{
		std::shared_ptr<AudioComponent> audio = AddComponent<AudioComponent>();
		audio->Init("assets/Title/Audio/select.wav");
		mSelectSE = audio;
	}

	// カーソル移動SE
	{
		std::shared_ptr<AudioComponent> audio = AddComponent<AudioComponent>();
		audio->Init("assets/Title/Audio/Cursormove.wav");
		mCursorMoveSE = audio;
	}
}

void CommandSelector::Update(const double _deltaTime)
{
	float leftStickY = XInput::GetPadLeftStick().y;

	if (XInput::GetPadTrigger(Pad::Down) || leftStickY < 0)
	{
		// カーソルを一つ下に移動
		MoveCursor(static_cast<CommandSelector::ID>(mCurrentChoiceID + 1));
	}
	else if (XInput::GetPadTrigger(Pad::Up) || leftStickY > 0)
	{
		// カーソルを一つ上に移動
		MoveCursor(static_cast<CommandSelector::ID>(mCurrentChoiceID - 1));
	}
}

void CommandSelector::MoveCursor(const ID _id)
{
	// カーソルがある場合のみ
	std::shared_ptr<SpriteComponent> cursor = mCursorSprite.lock();
	if (!cursor)
	{
		return;
	}

	// 指定されたIDがコマンドの数より大きくないか確認
	if (_id >= mCommands.size())
	{
		return;
	}

	DirectX::SimpleMath::Vector2 position = mCommands[_id].lock()->GetCommandSprite().lock()->GetPosition();
	cursor->SetPositionAndMapVertices(position);

	// 現在選択しているIDの設定
	mCurrentChoiceID = _id;

	// SE再生
	mCursorMoveSE.lock()->PlaySound2D();
}

void CommandSelector::AddCommand(const std::shared_ptr<CommandObject> _command)
{
	mCommands.emplace_back(_command);
}

void CommandSelector::ResetCursorPosition()
{
	// カーソルがある場合のみ
	std::shared_ptr<SpriteComponent> cursor = mCursorSprite.lock();
	if (!cursor)
	{
		return;
	}

	// コマンド一つでもある場合のみ
	if (mCommands.size() < 0)
	{
		return;
	}
	MoveCursor(CommandSelector::NoSelect);
}

CommandSelector::ID CommandSelector::GetSelectCommandID() const noexcept
{
	if (XInput::GetPadTrigger(mSelectButton))
	{
		mSelectSE.lock()->PlaySound2D();
		// 0はなにも選ばれていないことを示しているので + 1 している
		return static_cast<CommandSelector::ID>(mCurrentChoiceID + 1);
	}
	return CommandSelector::NoSelect;
}
