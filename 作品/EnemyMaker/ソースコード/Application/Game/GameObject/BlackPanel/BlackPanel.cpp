//--------- INCLUDES ----------
#include "BlackPanel.h"
#include "../../Component/SpriteComponent/SliderSpriteComponent.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"

BlackPanel::BlackPanel()
	: mAlpha(0.0f)
	, mAlphaInterpTime(1.0f)
	, mCurrentAlphaInterpTime(0.0f)
	, mbInterp(false)
{
	// 処理なし
}

BlackPanel::~BlackPanel()
{
	// 処理なし
}

void BlackPanel::Init()
{
	std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
	sprite->Init({ 0.0f,0.0f }, { 1280.0f, 720.0f });
	mSprite = sprite;

	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Black.png");
	if (texture->IsValid())
	{
		sprite->SetMaterialTexture(texture->Get<Texture>());
	}
}

void BlackPanel::Update(const double _deltaTime)
{
	if (!mbInterp)
	{
		return;
	}
	
	// α値を1.0に向けて補間する
	mAlpha = 1.0f * MathLibrary::Clamp01(mCurrentAlphaInterpTime / mAlphaInterpTime);
	mSprite.lock()->SetMaterialDiffuse({ 1.0f,1.0f,1.0f,mAlpha });
	mCurrentAlphaInterpTime += static_cast<float>(_deltaTime);	

	// 補間終了判定
	mbInterp = !IsInterpFinish();
}

void BlackPanel::InterpStart(const float _interpTime) noexcept
{
	mbInterp = 1.0f;
	mAlpha = 0.0f;
	mCurrentAlphaInterpTime = 0.0f;
	mAlphaInterpTime = _interpTime;
}


