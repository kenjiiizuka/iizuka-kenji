/**
* @file PlayerGuardState.h
* @brief PlayerGuardStateクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "PlayerStateContext.h"
#include <SimpleMath.h>
#include <memory>

//---------- 前方宣言 ----------
class PlayerInputControllerComponent;

/**
* @class PlayerGuardState
* @brief プレイヤーのガードステート
*/
class PlayerGuardState : public PlayerStateContext
{
public:
	/**
	* コンストラクタ
	*
	* @param Player* (_player)
	*/
	PlayerGuardState(Player* _player);

	/**
	* デストラクタ
	*/
	~PlayerGuardState();

private:
	/** プレイヤーの入力制御コンポーネント */
	std::weak_ptr<PlayerInputControllerComponent> mInputController;

	/** ガード開始してからの経過時間 */
	double mGuardStartElapsedTime;

	/** ジャスガ成功時間 */
	double mJustGuardSuccessTime;

	/** ガードの入力がなくなったかを示す */
	bool mbGuardEnd;

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

	/**
	* @fn Exit
	* @brief ステートの終了処理
	* @return void
	*/
	void Exit() override;

private:
	/**
	* @fn CheckGuardAnimationFinish
	* @brief ガードアニメーションが終了しているかを確認する 
	* @bool
	*/
	bool CheckGuardAnimationFinish();

public:
	/**
	* @fn CheckGuard
	* @brief ガードの結果を判断する関数
	* @detail ガード中に振れた攻撃の当たり判定の位置をがプレイヤーに対してガード可能位置にいるかを判断する
	* @return PlayerData::GuardResult
	*/
	PlayerData::GuardResult CheckGuard(const DirectX::SimpleMath::Vector3 _attackPosition) const noexcept;

};

