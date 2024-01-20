#pragma once

//--------- INCLUDES -------
#include "../GameObject.h"

//------- 前方宣言 --------
class PlaneComponent;

/**
* @fn PlaneObject
* @brief 板ポリオブジェクト
*/
class PlaneObject : public GameObject
{
private:
	
	/** プレーンコンポーネント */
	std::weak_ptr<PlaneComponent> mPlane;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @param const std::string& (_textureFilePath) 使用するテクスチャのファイルパス
	* @param float (_size) 板ポリのサイズ
	* @param bool (_isLighting) ライティングするかしないか
	* @return void
	*/
	void Init(const std::string& _textureFilePaht, float _size, bool _isLighting = true);

	/**
	* @fn Draw
	* @brief 描画処理
	* @return void
	*/
	void Draw() override;
};

