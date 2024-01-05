/**
* @file PlayerTestScene
* @brief PlayerTestScene.h
*/

#pragma once

//---------- INCLUDES -----------
#include "../Scene.h"
#include "../../GameObject/Player/PlayerEditor.h"

/**
* @class PlayerTestScene
* @brief プレイヤーをデバッグ、テストするためのシーン
*/
class PlayerTestScene : public Scene
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
	*/
	void Update() override;

private:
	/** プレイヤーエディター */
	std::shared_ptr<PlayerEditor> mPlayerEditor;


	std::weak_ptr<class EffectComponent> effectComp;
};

