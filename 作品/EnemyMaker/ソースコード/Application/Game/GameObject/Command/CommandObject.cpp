//----------- INCLUDES -----------
#include "CommandObject.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"

CommandObject::CommandObject()
{
	// 処理なし
}

CommandObject::~CommandObject()
{
	// 処理なし
}

void CommandObject::Init(const DirectX::SimpleMath::Vector2 _pos, const DirectX::SimpleMath::Vector2 _size, std::string_view _filePath)
{
	// スプライトコンポーネントのセット
	std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
	sprite->Init(_pos,_size);

	// テクスチャのセット
	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>(_filePath.data());
	if (texture->IsValid())
	{
		sprite->SetMaterialTexture(texture->Get<Texture>());
	}

	mCommandSprite = sprite;
}

