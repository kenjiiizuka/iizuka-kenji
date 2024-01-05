/**
* @file PlayerAnimationGuardState.h
* @brief PlayerAnimationGuardStateクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"

//--------- 前方宣言 --------
class Player;

/**
* @fn PlayerAnimationGuardState
* @brief プレイヤーのガードアニメーションステート
*/
class PlayerAnimationGuardState : public AnimationStateContext
{
	/**
	* @enum GuardState
	* @brief ガードの状態を示す
	*/
	enum GuardState : uint8_t
	{
		GuardStart = 0, /**< ガード開始 */
		Guarding,       /**< ガード中 */
		GuardEnd,       /**< ガード終了 */
	};

public:
	/**
	* コンストラクタ
	*
	* @param AnimationInstance* (_animInstance)
	*/
	PlayerAnimationGuardState(AnimationInstance* _animInstance);

	/**
	* デストラクタ
	*/
	~PlayerAnimationGuardState();

private:
	/** ガード状態 */
	GuardState mGuardState;

	/** プレイヤー */
	Player* mPlayer;

public:
	/**
	 * @fn Entry
	 * @brief ステートの開始処理
	 * @return void
	*/
	void Entry() override;

	/**
	 * @fn StateMachine
	 * @brief ステートマシン
	 * @return void
	*/
	void StateMachine() override;
};

