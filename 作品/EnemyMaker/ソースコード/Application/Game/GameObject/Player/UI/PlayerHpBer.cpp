//---------- INCLUDES ----------
#include "PlayerHpBer.h"
#include "../../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../../System/AssetSystem/Texture/TextureAssetInclude.h"

PlayerHpBer::PlayerHpBer()
{
	// 処理なし
}

PlayerHpBer::~PlayerHpBer()
{
	// 処理なし
}

void PlayerHpBer::InitSprite()
{
	// 枠設定
	{
		std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
		sprite->Init(mFramePosition, mFrameSize);
	 	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Frame_a.png");
		sprite->SetMaterialTexture(texture->Get<Texture>());
		mFrameSprite = sprite;
	}

	// ゲージ設定
	{
		mGageSprite = AddComponent<SpriteComponent>();
		mGageSprite.lock()->Init(mGagePosition, mGageSize);		
		std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Gage_a.png");
		mGageSprite.lock()->SetMaterialTexture(texture->Get<Texture>());
		mGageSprite.lock()->SetMaterialDiffuse({ 0.0f,1.0f,0.5f,1.0f });
	}

	// ゲージ消失時のゲージ
	{
		// 常にゲージの右端におく
		DirectX::SimpleMath::Vector2 lostGagePos = mGagePosition + mGageSize;
		mGageLostSprite = AddComponent<SpriteComponent>();
		mGageLostSprite.lock()->Init(lostGagePos, { 0.0,0.0 });
		std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Gage_a.png");
		mGageLostSprite.lock()->SetMaterialTexture(texture->Get<Texture>());
		mGageLostSprite.lock()->SetMaterialDiffuse({ 0.3f,0.0f,0.3f,1.0f });
	}
}

