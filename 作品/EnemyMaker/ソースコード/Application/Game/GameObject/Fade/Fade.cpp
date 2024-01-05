//-------- INCLUDES ---------
#include "Fade.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"

Fade::Fade()
	: mFadeState(Fade_None)
	, mAlpha(1.0f)
	, mFadeSpeed(2.0f)
{
	// �����Ȃ�
}

Fade::~Fade()
{
	// �����Ȃ�
}

void Fade::Init()
{
	std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
	sprite->Init({ 0.0f,0.0f }, { 1280.0f,720.0f });

	std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/texture/Title/TitleLayer1.png");
	if (texture->IsValid())
	{
		sprite->SetMaterialTexture(texture->Get<Texture>());
	}
	
	sprite->SetMaterialDiffuse({ 0.0f,0.0f,0.0f,1.0f });
	mFadeSprite = sprite;
}

void Fade::Update(const double _deltaTime)
{
	// None�ȊO�̎��̂ݏ���������
	if (mFadeState != Fade_None)
	{
		mFadeUpdate(_deltaTime);
	}
}

void Fade::FadeInUpdate(const double _deltaTime)
{
	mAlpha -= mFadeSpeed * static_cast<float>(_deltaTime);
	mFadeSprite.lock()->SetMaterialDiffuse({ 0.0f,0.0f,0.0f,mAlpha });

	// �t�F�[�h���I�����Ă��邩���m�F����
	if (mAlpha <= 0.0f)
	{
		mFadeState = Fade_None;
		mFadeSprite.lock()->SetVisible(false);
	}
}

void Fade::FadeOutUpdate(const double _deltaTime)
{
	mAlpha += mFadeSpeed * static_cast<float>(_deltaTime);
	mFadeSprite.lock()->SetMaterialDiffuse({ 0.0f,0.0f,0.0f,mAlpha });

	// �t�F�[�h���I�����Ă��邩���m�F����
	if (mAlpha >= 1.0f)
	{
		mFadeState = Fade_None;
	}
}
