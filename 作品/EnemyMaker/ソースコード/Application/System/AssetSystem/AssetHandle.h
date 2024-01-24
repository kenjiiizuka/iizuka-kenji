/**
* @file AssetHandle.h
* @brief AssetHandleクラスの定義
*/

#pragma once

//-------- INCLUDES ---------
#include <memory>


//-------- 前方宣言 ---------
class IAsset;
class IAssetProvider;

/**
* @class AssetHandle
* @brief アセットのポインタをラップする
*/
class AssetHandle
{
	/**--------------------------------------------------------------------------------------
	* アセットプロバイダーからのみハンドルにアセットのポインタを持たせたいのでフレンド指定
	* ゲッターを用意すると、ハンドルに新しいポインタをセットされてしまう
	*/
	friend IAssetProvider;

public:
	/**
	* デフォルトコンストラクタ
	*/
	AssetHandle();

	/**
	* デフォルトデストラクタ
	*/
	~AssetHandle();
	
private:
	/** アセットへのポインタ */
	std::weak_ptr<IAsset> mAsset;

	/** アセットをロードしたプロバイダー */
	IAssetProvider* mOwnerProvider;

public:
	/**
	* @fn IsValid
	* @brief このハンドルが指しているアセットが使用可能か返す
	* @return bool true 使用可能　false : 使用不可
	*/
	inline bool IsValid() const;

	/**
	* @fn Get
	* @brief アセットへの参照を返す
	*/
	template<class AssetType>
	inline AssetType& Get();
	
	/**
	* @fn Get
	* @brief アセットへの参照を返す
	*/
	inline IAsset& Get();

};

//----------- INLINES -----------

inline bool AssetHandle::IsValid() const
{
	if (mAsset.lock())
	{
		return true;
	}
	return false;
}

template<class AssetType>
inline AssetType& AssetHandle::Get()
{
	AssetType& asset = *std::dynamic_pointer_cast<AssetType>(mAsset.lock());
	return asset;
}

inline IAsset& AssetHandle::Get()
{
	return *mAsset.lock();
}
