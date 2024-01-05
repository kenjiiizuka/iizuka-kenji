/**
* @file PlayerDeathState.h
* @brief PlayerDeathStateクラスの定義
*/

#pragma once

//----------- INCLUDES ---------
#include "PlayerStateContext.h"

/**
* @class PlayerDeathState
* @brief プレイヤーの死亡ステート
*/
class PlayerDeathState : public PlayerStateContext
{
public:
	/**
	* コンストラクタ
	* 
	* @param Player* (_player)
	*/
	PlayerDeathState(Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerDeathState();

public:
	/**
	* @fn Entry
	* @brief ステート開始処理
	*/
	void Entry() override;
};

