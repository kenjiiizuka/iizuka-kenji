/**
* @file Camera2D.h
* @brief Camera2Dクラスの定義
*/

#pragma once

//---------- INCLUDES ---------
#include "../GameObject.h"

/**
* @class Camera2D
* @brief 2Dオブジェクトを映すカメラ
*/
class Camera2D : public GameObject
{
public:

	/**
	* @fn Draw
	* @brief 2D描画用のview,projection行列の計算を行う
	* @return void
	*/
	void Draw() override;
};

