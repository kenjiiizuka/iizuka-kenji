/**
* @file PlayerHpBer.h
* @brief PlayerHpBerクラスの定義
*/

#pragma once

//-------- INCLUDES --------
#include "../../HpBer/HpBer.h"

/**
* @class PlayerHpBer
* @ brief プレイヤーのHPバー
*/
class PlayerHpBer : public HpBer
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	PlayerHpBer();

	/**
	* デストラクタ
	*/
	~PlayerHpBer();

private:

	/**
	* @fn InitSprite
	* @brief 使用するスプライトの初期化
	* @return void
	*/
	void InitSprite() override;
};

