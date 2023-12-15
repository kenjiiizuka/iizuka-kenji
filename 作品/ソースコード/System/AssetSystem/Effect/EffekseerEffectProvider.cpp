//----------- INCLUDES -----------
#include "EffekseerEffectProvider.h"
#include "../../Effekseer/EffectSystem.h"
#include "EffekseerEffect.h"
#include <filesystem>

EffekseerEffectProvider::EffekseerEffectProvider()
{
	// �����Ȃ�
}

EffekseerEffectProvider::~EffekseerEffectProvider()
{
	// �����Ȃ�
}

void EffekseerEffectProvider::Setting()
{
	// �����Ȃ�
}

std::shared_ptr<IAsset> EffekseerEffectProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<EffekseerEffect> effect = std::make_shared<EffekseerEffect>();

	// �}�l�[�W���[�̎擾
	Effekseer::ManagerRef effekseerManager = EffectSystem::GetInstance().GetEffekseerManager();

	// �G�t�F�N�g�̓ǂݍ���
	std::filesystem::path filePath = _filePath;
	effect->mEffect = Effekseer::Effect::Create(effekseerManager, filePath.u16string().c_str());

	// �ǂݍ��݃`�F�b�N
	if (effect->mEffect == nullptr)
	{
		std::cout << "�G�t�F�N�g�ǂݍ��ݎ��s" << _filePath << std::endl;
		return std::shared_ptr<IAsset>();
	}

	return effect;
}
