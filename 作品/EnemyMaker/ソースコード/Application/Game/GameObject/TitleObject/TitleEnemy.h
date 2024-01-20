/**
* @file TitleEnemy.h
* @brief TitleEnemyクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include "../GameObject.h"

/**
* @class TitleEnemy
* @brief タイトル用のエネミー
*/
class TitleEnemy : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	TitleEnemy();

	/**
	* デストラクタ
	*/
	~TitleEnemy();

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;
};

