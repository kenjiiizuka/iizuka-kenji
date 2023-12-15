/**
* @file  AnimationNotifyState.h
* @brief アニメ－ションの特定のフレーム間で処理をするクラス
*/

#pragma once

//----------- INCLUDES ----------
#include "AnimationNotify.h"

/**
* @class AnimationNotifyState
* @brief アニメーションの特定のフレーム間にアタッチして処理をするクラス
*/
class AnimationNotifyState : public AnimationNotify
{
public:
	/**
	 * コンストラクタ
	 *
	 * @param SkeletalMeshAnimation* (_attachAnimation) アタッチされるアニメーション
	 * @param float (_attachStartFrame) アタッチするフレームの開始
	 * @param float (_attachEndFrame) アタッチするフレームの終了
	*/
	AnimationNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);

private:
	/** 開始のフレーム */
	uint16_t mStartFrame;

	/** 終了フレーム */
	uint16_t mEndFrame;

public:	
	/**
	 * @fn　GetStartFrame
	 * @brief 開始フレームを返す
	 * @return float 開始フレーム
	*/
	uint16_t GetStartFrame() { return mStartFrame; }

	/**
	 * @fn　GetEndFrame
	 * @brief 終了フレームを返す
	 * @return float 終了フレーム
	*/
	uint16_t GetEndFrame() { return mEndFrame; }

	/**
	* @fn SetStartFrame
	* @brief 開始のフレームのセッター
	* @param const uint16_t (_startFrame)
	* @return void
	*/
	inline void SetStartFrame(const uint16_t _startFrame) noexcept;

	/**
	* @fn SetEndFrame
	* @brief 終了のフレームのセッター
	* @param const uint16_t (_endFrame)
	* @return void
	*/
	inline void SetEndFrame(const uint16_t _endFrame) noexcept;
};

//---------- INLINES --------------

inline void AnimationNotifyState::SetStartFrame(const uint16_t _startFrame) noexcept
{
	mStartFrame = _startFrame;
}

inline void AnimationNotifyState::SetEndFrame(const uint16_t _endFrame) noexcept
{
	mEndFrame = _endFrame;
}
