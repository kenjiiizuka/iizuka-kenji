//----------- INCLUDES ---------
#include "TitleBackGround.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../Utility/MathLibrary.h"
#include <math.h>
#include "../../../System/FPSController/FPSController.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"

TitleBackGround::TitleBackGround()
{
	// デフォルトコンストラクタ
}

TitleBackGround::~TitleBackGround()
{
	// デストラクタ
}

void TitleBackGround::Init()
{
	// レイヤー1
	{
		std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
		sprite->Init({ 0.0f,0.0f }, { 1280.0f, 720.0f });

		std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/Title/TitleLayer.png");
		if (texture->IsValid())
		{
			sprite->SetMaterialTexture(texture->Get<Texture>());
		}
			
		mLayer1Sprite = sprite;
	}

	// レイヤー2
	{		
		std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
		sprite->Init({ 0.0f,0.0f }, { 1280.0f, 720.0f });
		std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/Title/TitleLayer2.png");
		if (texture->IsValid())
		{
			sprite->SetMaterialTexture(texture->Get<Texture>());
		}
		sprite->SetMaterialDiffuse({ 0.6f,0.0f,0.0f,1.0f });
		mLayer2Emission = { 0.0f,0.0f,0.0f,1.0f };
		sprite->SetMaterialEmission(mLayer2Emission);
		sprite->SetMaterialShininess(0.4f);
		mLayer2Sprite = sprite;
	}

	// レイヤー3
	{
		std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();

		
		sprite->Init({ 160.0f,80.0f }, { 960, 540 });

		std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/Title/TitleLogo.png");
		if (texture->IsValid())
		{
			sprite->SetMaterialTexture(texture->Get<Texture>());
		}
		// sprite->SetMaterialDiffuse({0.7f,0.7f,0.7f,1.0f});
		mTitleLogo = sprite;
	}
}

void TitleBackGround::Update(const double _deltaTime)
{			
	static float prevTime = 0.0f;
	prevTime += static_cast<float>(_deltaTime);
	mLayer2Emission.x = MathLibrary::Clamp01(sin(prevTime));
	if (mLayer2Emission.x > 0.5)
	{
		mLayer2Emission.x = 0.5f;
	}
	mLayer2Sprite.lock()->SetMaterialEmission(mLayer2Emission);
}
