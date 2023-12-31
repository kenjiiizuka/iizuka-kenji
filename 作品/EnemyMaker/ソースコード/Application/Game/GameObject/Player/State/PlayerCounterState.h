/**
* @file PlayerCounterState.h
* @brief PlayerCounterStateクラスの定義
*/

#pragma once

//---------- INCLUDES ---------
#include "PlayerStateContext.h"

/**
* @class PlayerCounterState
* @brief プレイヤーのカウンター攻撃ステート
*/
class PlayerCounterState : public PlayerStateContext
{
public:
	/**
	* コンストラクタ
	* 
	* @param Player* (_player)
	*/
	PlayerCounterState(Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerCounterState();

private:
	/** 初回フレームを示す */
	bool mbFirstFrame;

public:
	/**
	* @fn Entry
	* @brief ステートの開始処理
	* @return void
	*/
	void Entry() override;

	/**
	* @fn Update
	* @brief 更新処理
	*/
	void Update() override;

};

