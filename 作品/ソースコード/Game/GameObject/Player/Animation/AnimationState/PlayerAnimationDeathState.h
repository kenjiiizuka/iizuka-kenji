/**
* @file PlayerAnimationDeathState.h
* @brief PlayerAnimationDeathStateクラスの定義
*/


#pragma once

//---------- INCLUDES -----------
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"

/**
* @class PlayerAnimationDeathState
* @brief プレイヤーの死亡時アニメーションステート
*/
class PlayerAnimationDeathState : public AnimationStateContext
{
public:
	/**
	* コンストラクタ
	*
	* @param[in] AnimationInstance* (_animInstance)
	*/
	PlayerAnimationDeathState(AnimationInstance* _animInstance);

	/**
	* デストラクタ
	*/
	~PlayerAnimationDeathState();

public:
	/**
	 * @fn Entry
	 * @brief ステートの開始処理
	 * @return void
	*/
	void Entry() override;
};

