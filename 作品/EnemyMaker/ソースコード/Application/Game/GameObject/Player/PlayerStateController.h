/**
* @file PlayerStateSwitcher.h
* @brief PlayerStateSwitcherクラスの定義
*/

#pragma once
//----------- INCLUDES -----------
#include <memory>
#include "State/PlayerStateContext.h"

//----------- 前方宣言 -----------
class Player;
class PlayerStateObserver;

//---------- コンセプト -----------
template<class PlayerState>
concept DerivedPlayerState = std::derived_from<PlayerState, PlayerStateContext>;

/**
* @class PlayerStateSwitcher
* @brief プレイヤーのステートを切り替えるクラス
* @detail プレイヤーを監視するクラスから通知をもらい、ステートを切り替える
*/
class PlayerStateController
{
public:
	/**
	* コンストラクタ
	* 
	* @param std::shared_ptr<PlayerStateObserver> (_observer)
	* @param Player*                              (_player)
	*/
	PlayerStateController(std::shared_ptr<PlayerStateObserver> _observer, Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerStateController();

private:
	/** プレイヤーと通知管理クラスを監視するオブザーバー */
	std::weak_ptr<PlayerStateObserver> mObserver;

	/** プレイヤー */
	Player* mPlayer;

	/** 現在のステート */
	std::shared_ptr<PlayerStateContext> mCurrentState;

	/** ステートの遷移が必要なことをしめす */
	bool mbNeedTransitionState;

public:
	/**
	* @fn UpdateState
	* @brief 更新処理
	* @detail 現在のステートの更新処理をする
	* @return void
	*/
	void UpdateState();

	/**
	* @fn SwitchState
	* @brief ステート切り替え関数
	* @detail コンセプトでPlayerStateContextクラスを継承したクラスのみ指定可能にしている
	*         新しいステートを生成し、Entryを実行している
	* @return void
	*/
	template<DerivedPlayerState PlayerState>
	inline void SwitchState();

	/**
	* @fn IsInputAble
	* @brief 現在のステートはコントローラーからの入力を受け付けるかを返す
	* @return bool true 入力可 false 入力不可
	*/
	inline bool IsInputAble() const noexcept;

	/**
	* @fn IsNeedTransition
	* @brief 遷移が必要なのかを返す
	* @return bool
	*/
	inline bool IsNeedTransition() const noexcept;

	/**
	* @fn GetState
	* @brief 現在のステートを返す
	* @return std::weak_ptr<PlayerStateContext>
	*/
	inline std::weak_ptr<PlayerStateContext> GetState() const noexcept;

};

//---------- INLINES ----------

template<DerivedPlayerState PlayerState>
inline void PlayerStateController::SwitchState()
{
	if (mCurrentState)
	{
		mCurrentState->Exit();
		mCurrentState.reset();
	}	
	mCurrentState = std::make_shared<PlayerState>(mPlayer);
	mCurrentState->Entry();
}

inline bool PlayerStateController::IsInputAble() const noexcept
{
	// ステートがあれば、そのステートの入力可、不可を返す ステートがなければ 入力可能を返す
	return mCurrentState ? mCurrentState->IsInputAble() : true;
}

inline bool PlayerStateController::IsNeedTransition() const noexcept
{
	return mCurrentState ? mCurrentState->IsNeedTransition() : true;
}

inline std::weak_ptr<PlayerStateContext> PlayerStateController::GetState() const noexcept
{
	return mCurrentState;
}
