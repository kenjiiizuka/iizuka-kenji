/**
* @file SkeletalMeshAnimationProvider
* @brief SkeletalMeshAnimationProviderクラスの定義
*/

#pragma once

//----------- INCLUDES ---------------
#include "../IAssetProvider.h"


/**
* @class SkeletalMeshAnimationProvider
* @brief スケルタルメッシュアニメーションの読み込みをするクラス
*/
class SkeletalMeshAnimationProvider final :  public IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SkeletalMeshAnimationProvider();

	/**
	* デストラクタ
	*/
	~SkeletalMeshAnimationProvider();

public:	
	/**
	 * @fn Load
	 * @brief バイナリファイルを読み込む処理
	 * @param const std::string& (_filePath)
	 * @return std::shared_ptr<IAsset>
	*/
	std::shared_ptr<IAsset> Load(const std::string& _filePath) const override;

	/**
	 * @fn GetProviderType
	 * @brief プロバイターのTypeを返す
	 * @detail typeidを使用してプロバイターの型を返している
	 * @return std::type_info プロバイダーの型
	*/
	inline virtual const std::type_info& GetProviderType() const override;

protected:
	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	void Setting();
	
};

//--------- INLINES ---------

inline const std::type_info& SkeletalMeshAnimationProvider::GetProviderType() const
{
	return typeid(SkeletalMeshAnimationProvider);
}


