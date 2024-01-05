//-------- INCLUDES ---------
#include "EffectComponent.h"
#include "../../../System/AssetSystem/Effect/EffectAssetInclude.h"
#include "../../../System/Effekseer/EffectSystem.h"
#include "../../../Utility/MathLibrary.h"

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

void EffectComponent::PlayEffect(const DirectX::SimpleMath::Vector3 _playPosition, const DirectX::SimpleMath::Vector3 _scale, const float _angle, const DirectX::SimpleMath::Vector3 _axis)
{
	Effekseer::ManagerRef manager = EffectSystem::GetInstance().GetEffekseerManager();
	mEffectHandle = manager->Play(mAssetHandle->Get<EffekseerEffect>().GetEffect(), _playPosition.x, _playPosition.y, _playPosition.z);
	manager->SetRotation(mEffectHandle, { _axis.x, _axis.y, _axis.z }, _angle);
	manager->SetScale(mEffectHandle, _scale.x, _scale.y, _scale.z);
}
