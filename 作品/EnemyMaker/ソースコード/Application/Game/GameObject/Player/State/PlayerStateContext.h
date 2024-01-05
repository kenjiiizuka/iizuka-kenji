/**
* @file PlayerStateContext.h
* @brief PlayerStateContextクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "../PlayerData.h"

//---------- 前方宣言 ----------
class Player;

/**
* @class PlayerStateContext
* @brief プレイヤーの行動をステート管理するためのステートコンテキストクラス
*/
class PlayerStateContext
{
public:
	/**
	* デフォルトコンストラクタ
	* 
	* @param Player* (_player)
	*/
	PlayerStateContext(Player* _player);

	/**
	* デストラクタ
	*/
	virtual ~PlayerStateContext();

protected:
	/** プレイヤー */
	Player* mPlayer;

	/** コントローラーからの入力が可能かを判断する */
	bool mbIsInputAble;

	/** ステートを切り替える必要があることを示すフラグ */
	bool mbNeedTransitionState;

public:
	/**
	* @fn Entry
	* @brief ステートの開始処理
	* @return void
	*/
	virtual void Entry() {};

	/**
	* @fn Update
	* @brief 更新処理
	*/
	virtual void Update() {};

	/**
	* @fn Exit
	* @brief ステートの終了処理
	* @return void
	*/
	virtual void Exit() {};

	/**
	* @fn IsInputAble
	* @brief 入力可能か返す
	* @return bool
	*/
	inline bool IsInputAble() const noexcept; 

	/**
	* @fn IsNeedTransition
	* @brief 遷移が必要なのかを返す
	* @return bool true 必要 false 不必要
	*/
	inline bool IsNeedTransition() const noexcept;

};

//---------- INLINES -----------

inline bool PlayerStateContext::IsInputAble() const noexcept
{
	return mbIsInputAble;
}

inline bool PlayerStateContext::IsNeedTransition() const noexcept
{
	return mbNeedTransitionState;
}
