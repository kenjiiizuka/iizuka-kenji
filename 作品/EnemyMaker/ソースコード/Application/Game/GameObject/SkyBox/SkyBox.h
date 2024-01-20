/**
* @file SkyBox
* @brief SkyBoxクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include "../GameObject.h"

/**
* @class SkyBox
* @brief SkyBoxオブジェクト
*/
class SkyBox : public GameObject
{
public:
	/**
	* コンストラクタ
	*/
	SkyBox();

	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	void Init() override;
};

