//-------- INCLUDES --------
#include "WinLogo.h"
#include "../../Component/SpriteComponent/AnimationSpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../GameObject/BlackPanel/BlackPanel.h"
#include "../../../Utility/MathLibrary.h"

WinLogo::WinLogo()
	: mbIsFinishAnimation(false)
{
	// �����Ȃ�
}

WinLogo::~WinLogo()
{
	// �����Ȃ�
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
	// �p�l���̕�Ԃ��I�����Ă��邩���m�F����
	if (!mPanel.lock()->IsInterpFinish())
	{
		mSprite.lock()->PlayAnimation();
		return;
	}

	// ��Ԃ��I�����Ă����珟�����S���o��
	mSprite.lock()->SetMaterialDiffuse({ 1.0,1.0f,1.0f,1.0f });
	mbIsFinishAnimation = !mSprite.lock()->IsPlay();
}

