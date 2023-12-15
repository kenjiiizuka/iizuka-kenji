/**
* @file PlayerStepNotifyState.h
* @brief PlayerStepNotifyStateクラスの定義
*/

#pragma once

//----------- INCLUDES ----------
#include "../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"

//-------- 前方宣言 ---------
class CapsuleCollisionComponent;

/**
* @class PlayerStepNotifyState
* @brief プレイヤーのステップ中に敵の攻撃との当たり判定を消す通知ステート
*/
class PlayerStepNotifyState : public AnimationNotifyState
{
public:
	/**
	* コンストラクタ
	*
	* @param SkeletalMeshAnimation* (_attachAnimation) アタッチされるアニメーション
	* @param float (_attachStartFrame) アタッチするフレームの開始
	* @param float (_attachEndFrame) アタッチするフレームの終了
	*/
	PlayerStepNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

	/**
	* デストラクタ
	*/
	~PlayerStepNotifyState();

private:
	/** プレイヤーのコリジョン */
	std::weak_ptr<CapsuleCollisionComponent> mPlayerCollision;

public:
	/**
　　* @fn　NotifyBegin
　　* @brief 通知の開始処理
　　* @return void
　　*/
	void NotifyBegin() override;

	/**
	* @fn NotifyEnd
	* @brief 通知の終了処理
	* @return void
	*/
	void NotifyEnd() override;
};

