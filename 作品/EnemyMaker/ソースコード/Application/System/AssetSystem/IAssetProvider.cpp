#include "IAssetProvider.h"
#include "AssetHandle.h"

std::shared_ptr<AssetHandle> IAssetProvider::Provide(const std::string& _filePath)
{
	// キャッシュマップからアセットを取得
	std::shared_ptr<IAsset> asset = GetAssetFromCacheMap(_filePath);

	// アセットがなければ読み込む
	if (!asset)
	{
		asset = LoadBase(_filePath);
	}

	// アセットハンドルの作成
	std::shared_ptr<AssetHandle> newHandle = std::make_shared<AssetHandle>();
	// アセットとプロバイダーの登録
	newHandle->mAsset = asset;
	newHandle->mOwnerProvider = this;
	return newHandle;
}

std::shared_ptr<IAsset> IAssetProvider::LoadBase(const std::string& _filePath)
{
	// アセットの読み込み
	std::shared_ptr<IAsset> asset = Load(_filePath);

	// アセットが読み込めていたらキャッシュマップに登録
	if (asset)
	{
		AddCacheMap(_filePath, asset);
	}
	return asset;
}
