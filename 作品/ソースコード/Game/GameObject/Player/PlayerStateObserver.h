/**
* @file PlayerStateObserver.h
* @brief PlayerStateObserverクラスの定義
*/

#pragma once

//----------- INCLUDES -----------
#include <memory>
#include "PlayerData.h"

//----------- 前方宣言 -------------
class Player;
class PlayerStateController;

/**
* @class PlayerStateObserver
* @brief プレイヤーの状態を監視し、プレイヤーのステート管理クラスに通知するクラス
*        また、ステート管理クラスの状態によってもステートが変わることがあるので、
*        ステート管理クラスも監視する。ステート管理クラスからステートの変更の必要がでたらステート管理クラスに通知する
*/
class PlayerStateObserver
{
public:
	/**
	* コンストラクタ
	* 
	* @param Player* (_player) 監視対象のプレイヤー
	*/
	PlayerStateObserver(Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerStateObserver();

private:
	/** 監視するプレイヤー */
	Player* mSubjectPlayer;

	/** ステートを切り替えるクラス */
	std::weak_ptr<PlayerStateController> mStateController;

	/** 前フレームのプレイヤーの行動ステート */
	PlayerData::PlayerBehaviorState mPrevBehaviorState;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail 初期ステートとしてIdleMoveに設定する
	* @param const std::shared_ptr<PlayerStateController> (_stateController)
	* @return void
	*/
	void Initialize(const std::shared_ptr<PlayerStateController> _stateController);

	/**
	* @fn Update
	* @brief 更新処理
	* @detail プレイヤーのとステートコントローラーの状態を監視する
	*         ステートコンロトーラーに通知する必要があれば通知する 
	* @return void
	*/
	void Update();

private:
	/**
	* @fn SwitchState
	* @brief ステートコントローラーのステートを切り替える関数
	* @detail 引数で渡されたステートにあったステートコンテキストに切り替える
	* @param const PlayerEntities::PlayerBehaviorState& (_switchState)
	* @return void
	*/
	void SwitchState(const PlayerData::PlayerBehaviorState& _switchState);
};

