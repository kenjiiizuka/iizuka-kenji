/**
* @file  PlayerAnimationPulledState.h
* @brief プレイヤーの抜刀状態のアニメーションステートクラス
*/

#pragma once

//--------- INCLUDES --------
#include "../../../../Component/SkeletalMeshComponent/AnimationStateContext.h"
#include <array>

//---------- 前方宣言 ----------
class PlayerMovementComponent;
class BlendAnimationClip;

/**
* @class PlayerAnimationPulledState
* @brief プレイヤーに抜刀状態のアニメーションステート
* @detail プレイヤーの移動速度を取得し、IdleとRunをブレンドしたアニメーションクリップに
*         ブレンド率として速度をセットする
*/
class PlayerAnimationPulledState : public AnimationStateContext
{
public:
    /**
     * 値の初期化
     *
     * @param[in] AnimationInstance* (_animInstance) このステートを持つアニメーションインスタンス
    */
	PlayerAnimationPulledState(AnimationInstance* _animInstance);

private:
    /** Idleから走りのアニメーション */
    std::weak_ptr<BlendAnimationClip> mIdleToRun;

    /** プレイヤーの持つCharacterMovementComponentへの参照 */
    std::weak_ptr<PlayerMovementComponent> mMoveComp;

    /** プレイヤーの現在のスピード */
    float mPlayerSpeed;

public:
    /**
     * @fn　Entry
     * @brief このステートの開始の処理
     * @return void
    */
    void Entry();

    /**
     * @fn　Update
     * @brief 更新処理
     * @return void
    */
    void Update() override; 
};

