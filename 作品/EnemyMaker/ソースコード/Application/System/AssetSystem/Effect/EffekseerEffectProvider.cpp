//----------- INCLUDES -----------
#include "EffekseerEffectProvider.h"
#include "../../Effekseer/EffectSystem.h"
#include "EffekseerEffect.h"
#include <filesystem>

EffekseerEffectProvider::EffekseerEffectProvider()
{
	// 処理なし
}

EffekseerEffectProvider::~EffekseerEffectProvider()
{
	// 処理なし
}

void EffekseerEffectProvider::Setting()
{
	// 処理なし
}

std::shared_ptr<IAsset> EffekseerEffectProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<EffekseerEffect> effect = std::make_shared<EffekseerEffect>();

	// マネージャーの取得
	Effekseer::ManagerRef effekseerManager = EffectSystem::GetInstance().GetEffekseerManager();

	// エフェクトの読み込み
	std::filesystem::path filePath = _filePath;
	effect->mEffect = Effekseer::Effect::Create(effekseerManager, filePath.u16string().c_str());

	// 読み込みチェック
	if (effect->mEffect == nullptr)
	{
		std::cout << "エフェクト読み込み失敗" << _filePath << std::endl;
		return std::shared_ptr<IAsset>();
	}

	return effect;
}
