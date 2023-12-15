#include "IAssetProvider.h"
#include "AssetHandle.h"

std::shared_ptr<AssetHandle> IAssetProvider::Provide(const std::string& _filePath)
{
	// �L���b�V���}�b�v����A�Z�b�g���擾
	std::shared_ptr<IAsset> asset = GetAssetFromCacheMap(_filePath);

	// �A�Z�b�g���Ȃ���Γǂݍ���
	if (!asset)
	{
		asset = LoadBase(_filePath);
	}

	// �A�Z�b�g�n���h���̍쐬
	std::shared_ptr<AssetHandle> newHandle = std::make_shared<AssetHandle>();
	// �A�Z�b�g�ƃv���o�C�_�[�̓o�^
	newHandle->mAsset = asset;
	newHandle->mOwnerProvider = this;
	return newHandle;
}

std::shared_ptr<IAsset> IAssetProvider::LoadBase(const std::string& _filePath)
{
	// �A�Z�b�g�̓ǂݍ���
	std::shared_ptr<IAsset> asset = Load(_filePath);

	// �A�Z�b�g���ǂݍ��߂Ă�����L���b�V���}�b�v�ɓo�^
	if (asset)
	{
		AddCacheMap(_filePath, asset);
	}
	return asset;
}
