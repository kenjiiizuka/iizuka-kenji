/**
* @file EffekseerTestScene.h
* @brief EffekseerTestSceneクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "Scene.h"

/**
* class EffekseerTestScene
* @brief エフェクシア導入テストシーン
*/
class EffekseerTestScene : public Scene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

	std::weak_ptr<class EffectComponent> effectComp;

};

