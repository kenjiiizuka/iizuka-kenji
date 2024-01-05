/**
* @file PlayerAttackState.h
* @brief PlayerAttackStateクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include <memory>
#include "PlayerStateContext.h"

//---------- 前方宣言 ----------
class PlayerAttackData;
class PlayerInputControllerComponent;

/**
* @class PlayerAttackState
* @brief プレイヤーの攻撃ステート
* @detail コンボ継続の処理と、入力可能タイミングの判断をしている
*/
class PlayerAttackState : public PlayerStateContext
{
public:
	/**
	* コンストラクタ
	*
	* @param Player* (_player)
	*/
	PlayerAttackState(Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerAttackState();

private:
	/** プレイヤーの攻撃データ */
	std::weak_ptr<PlayerAttackData> mAttackData;

	/** プレイヤーのインプットコントローラー */
	std::weak_ptr<PlayerInputControllerComponent> mInputController;

	/** ステートが開始したフレームであること示す */
	bool mbEntryFrame;

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
	* @return void
	*/
	void Update() override;

	/**
	* @fn Exit
	* @brief ステートの終了処理
	* @return void
	*/
	virtual void Exit() override;

private:
	/**
	* @fn CheckAttackAnimationEnd
	* @brief 攻撃アニメーションの再生が終っているかを確認する
	* @return bool true 終っている false 終っていない
	*/
	bool CheckAttackAnimationEnd();

	/**
	* @fn CheckInputAble
	* @brief 入力可能かを確認する
	* @detail 再生されている攻撃アニメーションについているPlayerInputAbleNotifyStateクラスから入力可能かを判断する
	* @return bool true 入力可能 false 入力不可
	*/
	bool CheckInputAble();

	/**
	* @fn Comb
	* @brief コンボ継続処理
	* @detail コントローラーから攻撃ボタンの入力があればコンボを継続する
	* @return void
	*/
	void Comb();

};

