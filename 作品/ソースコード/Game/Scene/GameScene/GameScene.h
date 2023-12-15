/**
* @file GameScene.h
* @brief GameSceneクラスの定義
*/

#pragma once

//----------- INCLUDES ---------
#include "../Scene.h"
#include "BattleManager.h"

//-------- 前方宣言 --------
class Fade;

/**
* @class GameScene
* @brief ゲームシーン
*/
class GameScene final : public Scene
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	GameScene();

	/**
	* デストラクタ
	*/
	~GameScene();

private:
	/** バトルマネージャー */
	std::shared_ptr<BattleManager> mBattleManager;

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

private:
	/** フェード用のオブジェクト */
	std::weak_ptr<Fade> mFade;

	/** シーン遷移の入力があったか */
	bool mbTransitionScene;
};

