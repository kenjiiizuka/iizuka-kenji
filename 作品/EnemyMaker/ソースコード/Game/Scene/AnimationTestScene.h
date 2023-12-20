/**
* @file AnimationTestScene.h
* @brief AnimationTestSceneクラスの作成
*/

#pragma once

//------------ INCLUDES ------------
#include "Scene.h"

/**
* @fn AnimationTestScene
* @brief アニメーションテスト用のシーン
*/
class AnimationTestScene : public Scene
{
public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @return void
	*/
	void Initialize() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update() override;

};

