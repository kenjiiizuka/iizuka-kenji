//-------- INCLUDES ---------
#include "EffectComponent.h"
#include "../../../System/AssetSystem/Effect/EffectAssetInclude.h"
#include "../../../System/Effekseer/EffectSystem.h"

EffectComponent::EffectComponent()
	: mEffectHandle(0)
{
	// ˆ—‚È‚µ
}

EffectComponent::~EffectComponent()
{
	// ˆ—‚È‚µ
}

void EffectComponent::Init(std::string_view _filePath)
{
	// “Ç‚İ‚İ
	mAssetHandle = AssetManager::GetInstance().Load<EffekseerEffectProvider>(_filePath.data());
	// “Ç‚İ‚İ‚Å‚«‚Ä‚¢‚é‚©‚ğŠm”F
	if (!mAssetHandle->IsValid())
	{
		return;
	}
}

void EffectComponent::PlayEffect(const DirectX::SimpleMath::Vector3 _playPosition)
{
	Effekseer::ManagerRef manager = EffectSystem::GetInstance().GetEffekseerManager();
	mEffectHandle = manager->Play(mAssetHandle->Get<EffekseerEffect>().GetEffect(), _playPosition.x, _playPosition.y, _playPosition.z);
}
