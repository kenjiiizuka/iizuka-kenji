//-------- INCLUDES --------
#include "WinLogo.h"
#include "../../Component/SpriteComponent/AnimationSpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../GameObject/BlackPanel/BlackPanel.h"
#include "../../../Utility/MathLibrary.h"

WinLogo::WinLogo()
	: mbIsFinishAnimation(false)
{
	// 処理なし
}

WinLogo::~WinLogo()
{
	// 処理なし
}

void WinLogo::Init()
{
	mPanel = AddChildObject<BlackPanel>();
	mPanel.lock()->InterpStart();

	std::shared_ptr<AnimationSpriteComponent> sprite = AddComponent<AnimationSpriteComponent>();
	sprite->Init({ 370,90 }, { 540,540 });

	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Win.png");
	sprite->SetMaterialTexture(texture->Get<Texture>());

	sprite->SetMaterialDiffuse({ 1.0f,1.0f,1.0f,0.0f });
	sprite->SetupAnimationTable(7, 7);
	mSprite = sprite;
}

void WinLogo::Update(const double _deltaTime)
{
	// パネルの補間が終了しているかを確認する
	if (!mPanel.lock()->IsInterpFinish())
	{
		mSprite.lock()->PlayAnimation();
		return;
	}

	// 補間が終了していたら勝利ロゴを出す
	mSprite.lock()->SetMaterialDiffuse({ 1.0,1.0f,1.0f,1.0f });
	mbIsFinishAnimation = !mSprite.lock()->IsPlay();
}

