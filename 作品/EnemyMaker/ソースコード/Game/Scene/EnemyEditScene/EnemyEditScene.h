/**
* @file EnemyEditScene.h
* @brief EnemyEditSceneクラスの定義
*/

#pragma once

//----------- INCLUDES --------------
#include "../Scene.h"
#include "../../GameObject/Enemy/BearEnemyEditor.h"

/**
* @class EnemyEditScene
* @brief エネミーを編集するシーン
*/
class EnemyEditScene : public Scene
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	EnemyEditScene();

	/**
	* デストラクタ
	*/
	~EnemyEditScene();

private:
	/** 熊の敵のエディター */
	std::shared_ptr<BearEnemyEditor> mEditor;

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

	/**
	* @fn Uninitialize
	* @brief 終了処理
	* @return void
	*/
	void Uninitialize() override;

};

