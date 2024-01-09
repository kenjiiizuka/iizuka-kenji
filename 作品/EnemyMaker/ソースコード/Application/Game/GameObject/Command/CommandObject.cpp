//----------- INCLUDES -----------
#include "CommandObject.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"

CommandObject::CommandObject()
{
	// �����Ȃ�
}

CommandObject::~CommandObject()
{
	// �����Ȃ�
}

void CommandObject::Init(const DirectX::SimpleMath::Vector2 _pos, const DirectX::SimpleMath::Vector2 _size, std::string_view _filePath)
{
	// �X�v���C�g�R���|�[�l���g�̃Z�b�g
	std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
	sprite->Init(_pos,_size);

	// �e�N�X�`���̃Z�b�g
	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>(_filePath.data());
	if (texture->IsValid())
	{
		sprite->SetMaterialTexture(texture->Get<Texture>());
	}

	mCommandSprite = sprite;
}

