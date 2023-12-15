/**
* @file PlayerWeaponCollisionActiveNotifyState.h
* @brief PlayerWeaponCollisionActiveNotifyStateクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include "../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"

//-------- 前方宣言 --------
class PlayerAttackCapsuleCollisionComponent;

/**
* @class PlayerWeaponCollisionActiveNotifyState
* @brief プレイヤーの武器のコリジョンのオンオフを切り返す通知ステート
* @detail プレイヤー専用の通知ステートになっているので、他のオブジェクトにはアタッチしないように
*/
class PlayerWeaponCollisionActiveNotifyState : public AnimationNotifyState
{
public:
	/**
	 * コンストラクタ
	 *
	 * @param[in] SkeletalMeshAnimation* (_attachAnimation) アタッチされるアニメーション
	 * @param[in] float (_attachStartFrame) アタッチするフレームの開始
	 * @param[in] float (_attachEndFrame) アタッチするフレームの終了
	*/
	PlayerWeaponCollisionActiveNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

	/**
	* デストラクタ
	*/
	~PlayerWeaponCollisionActiveNotifyState();

private:
	/** プレイヤーの武器のコリジョン */
	std::weak_ptr<PlayerAttackCapsuleCollisionComponent> mPlayerWeaponCollision;

public:
	/**
	* @fn NotifyBegin
	* @brief 通知開始処理
	* @detail プレイヤーの武器のコリジョンを取得するし、コリジョンをオンにする
	*/
	void NotifyBegin() override;

	/**
	* @fn NotifyEnd
	* @brief 通知終了処理
	* @detail プレイヤーの武器のコリジョンをオフにする
	*/
	void NotifyEnd() override;
};

