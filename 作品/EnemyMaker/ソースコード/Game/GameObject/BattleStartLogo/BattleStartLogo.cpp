//-------- INCLUDES ---------
#include "BattleStartLogo.h"
#include "../../Component/SpriteComponent/AnimationSpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../../Utility/MathLibrary.h"

BattleStartLogo::BattleStartLogo()
	: mbIsAnimationFinish(false)
{
	// ˆ—‚È‚µ
}

BattleStartLogo::~BattleStartLogo()
{
	// ˆ—‚È‚µ
}

void BattleStartLogo::Init()
{
	std::shared_ptr<AnimationSpriteComponent> sprite = AddComponent<AnimationSpriteComponent>();
	sprite->Init({ 310,30 }, { 600,600 });

	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Start.png");
	if (texture->IsValid())
	{
		sprite->SetMaterialTexture(texture->Get<Texture>());
	}
	
	sprite->SetMaterialDiffuse({ 1.0f,1.0f,1.0f,1.0f });
	sprite->SetupAnimationTable(8,7);
	sprite->PlayAnimation();
	mSprite = sprite;
}

void BattleStartLogo::Update(const double _deltaTime)
{
	if (!mSprite.lock()->IsPlay())
	{
		mbIsAnimationFinish = true;
		mSprite.lock()->SetVisible(false);
	}
}
