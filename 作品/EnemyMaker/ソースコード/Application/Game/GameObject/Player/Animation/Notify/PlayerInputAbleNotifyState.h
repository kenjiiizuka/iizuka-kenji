/**
* @file  PlayerComboAbleNotifyState.h
* @brief このステートがアタッチされているフレーム間は入力受付可能にするクラス
*/

#pragma once

//-------- INCLUDES ----------
#include "../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"


/**
* @class PlayerInputAbleNotifyState
* @brief プレイヤー用のアニメーション設定されたフレームの間trueを返すクラス
*/
class PlayerInputAbleNotifyState : public AnimationNotifyState
{
public:
	/**
	* 値の初期化
	 *
	 * @param[in] SkeletalMeshAnimation* (_attachAnimation) アタッチされるアニメーション
	 * @param[in] uint16_t (_attachStartFrame) アタッチするフレームの開始
	 * @param[in] uint16_t (_attachEndFrame) アタッチするフレームの終了
	*/
	PlayerInputAbleNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

private:
	/** コンボ可能フラグ */
	bool bInputAble;

public:
	/**
　　 * @fn　NotifyInit
　　 * @brief 通知の初期処理
　　 * @return void
　　*/
	void NotifyInit() override;

	/**
	 * @fn　NotifyBegin
	 * @brief コンボ可にする
	 * @return void
	*/
	void NotifyBegin() override;

	/**
	 * @fn　NotifyEnd
	 * @brief コンボ不可にする
	 * @return void
	*/
	void NotifyEnd() override;

	/**
     * @fn　IsCombAble
     * @brief コンボ可能かを返す
     * @return bool
    */
	bool IsInputAble() { return bInputAble; }
};

