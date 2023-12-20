//--------- INCLUDES ---------
#include "LoseLogo.h"
#include "../BlackPanel/BlackPanel.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../Utility/MathLibrary.h"
#include "../../Component/SpriteComponent/AnimationSpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"

LoseLogo::LoseLogo()
	: mbIsFinishAnimation(false)
{
	// 処理なし
}

LoseLogo::~LoseLogo()
{
	// 処理なし
}

void LoseLogo::Init()
{
	// パネルの上に敗北ロゴを出すために パネル → ロゴの順で生成する
	mPanel = AddChildObject<BlackPanel>();
	mPanel.lock()->InterpStart();

	std::shared_ptr<AnimationSpriteComponent> sprite = AddComponent<AnimationSpriteComponent>();
	sprite->Init({ 370,90 }, { 540,540 });
	
	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/LoseLogo.png");
	if (texture->IsValid())
	{
		sprite->SetMaterialTexture(texture->Get<Texture>());
	}

	sprite->SetupAnimationTable(7.0f, 7.0f);
	sprite->SetMaterialDiffuse({ 1.0,1.0f,1.0f,0.0f });
	mSprite = sprite;
}

void LoseLogo::Update(const double _deltaTime)
{
	// パネルの補間が終了しているかを確認する
	if (!mPanel.lock()->IsInterpFinish())
	{
		mSprite.lock()->PlayAnimation();	
		return;
	}
	mSprite.lock()->SetMaterialDiffuse({1.0,1.0f,1.0f,1.0f});

	// 補間が終了していたら敗北ロゴを出す
	mbIsFinishAnimation = !mSprite.lock()->IsPlay();
}
