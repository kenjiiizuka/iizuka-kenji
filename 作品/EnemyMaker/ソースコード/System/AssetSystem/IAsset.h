#pragma once
/**
* @file IAsset.h
* @brief IAssetクラスの定義
*/

//--------- INCLUDES --------
#include <typeinfo>

/**
* @class IAsset
* @brief アセットのインターフェースクラス
*/
class IAsset
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	IAsset()
	{
		// 処理なし
	}

	/**
	* デフォルトデストラクタ
	*/
	virtual ~IAsset()
	{
		// 処理なし
	}

public:
	/**
	* @fn GetAssetType
	* @brief アセットのタイプを返す
	* @detail typeidを使用して型判別をしている
	* @return const std::type_info& 
	*/
	inline virtual const std::type_info& GetAssetType() const noexcept = 0;

};

