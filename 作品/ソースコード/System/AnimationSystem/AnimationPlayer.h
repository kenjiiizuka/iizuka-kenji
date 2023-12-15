/**
* @file  AnimationPlayer.h
* @brief アニメーションを再生するためのクラスの定義
*/

#pragma once

//----------- INCLUDES --------------
#include <vector>
#include <memory>
#include "../AssetSystem/SkeletalMesh/SkeletalMeshAnimationData.h"
#include "../../Game/Component/TransformComponent/Transform.h"
#include "../../Game/Component/SkeletalMeshComponent/AnimationInformation.h"


//----------- 前方宣言 ----------
class SkeletalMeshAnimation;
class SkeletalMesh;
class AnimationInstance;
class SkeletalMeshAnimationClip;
class AnimationSynchronizer;
class InterpSkeletalAnimation;

/**
* @struct AnimationPlayBackData
* @brief アニメーション再生に必要なデータを持つ構造体
*/
struct AnimationPlayBackData
{
	bool mbLoop;                                               /**< ループ再生か */
	bool mbSynchro;                                            /**< アニメーション同期をするか */
	bool mbSynchroNeedInit;                                    /**< アニメーション同期の初期化処理が必要か */
	bool mbInterp;                                             /**< 今のボーンの位置から再生するアニメーションの最初の位置まで補完するか */
	double mCurrentPlayTime;                                   /**< 現在の再生時間 */
	float mPlayRate;                                           /**< 再生速度 */
	float mTickPerSeconds;                                     /**< 1秒に進む値 */
	float mInterpTime;                                         /**< 補間にかける時間 */
	float mElapsedInterpTime;                                  /**< 補間開始からの経過時間 */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;                 /**< アニメーションを適応するスケルタルメッシュ */
	std::weak_ptr<SkeletalMeshAnimationClip> mAnimationClip;   /**< 再生するアニメーションデータ */

	/**
	* デフォルトコンストラクタ
	*/
	AnimationPlayBackData();
};


/**
* @class AnimationPlayer
* @brief 入力としてSkeletalMeshとAnimationClipを貰い、アニメーションデータをスケルタルメッシュに適応する
*/
class AnimationPlayer
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AnimationPlayer();

private:			
	/** 現在アニメーションを再生しているか */
	bool mbIsPlay;

	/** 次のフレームでアニメーションが終ることをしめすフラグ*/
	bool mbEndOnNextFrame;
		
	/** 再生するアニメーションデータ */
	AnimationPlayBackData mAnimPlayBackData;

	/** アニメーション同期をするクラス */
	std::shared_ptr<AnimationSynchronizer> mSynchronizer;

	/** アニメーション補間をするクラス */
	std::shared_ptr<InterpSkeletalAnimation> mAnimationInterp;

public:
	/**
	 * @fn　AnimationUpdate
	 * @brief 更新処理、再生されているアニメーションの通知の処理をする
	 * @return void
	*/
	void AnimationUpdate(const double _deltaTime);
	
private:
	/**
    * @fn StepAnimation
    * @brief アニメーションを進める関数
    * @detail アニメーションの現在の再生時間にあったアニメーションデータをSkeletalMeshに渡している
    * @return void
    */
	void StepAnimation(const double _deltaTime);

	/**
	* @fn InterpBegin
	* @brief アニメーション間の補間の開始処理
	* @param const std::shared_ptr<SkeletalMeshAnimationClip>& (_baseAnimationClip)
	* @param const std::shared_ptr<SkeletalMeshAnimationClip>& (_toAnimationClip)
	* @param const float                                       (_interpTime)
	* @return void
	*/
	void InterpBegin(const std::shared_ptr<SkeletalMeshAnimationClip>& _baseAnimationClip, const float _interpStartAnimationClipTime, const std::shared_ptr<SkeletalMeshAnimationClip> _toAnimationClip, const float _interpTime);

	/**
	* @fn InterpAnimation
	* @brief アニメーション補間処理
	* @return bool true 補間終了 false 補完中
	*/
	bool InterpAnimation(const double _deltaTime);

	/**
	* @fn CheckNextFrameEnd
	* @brief 次のフレームに終了するか
	* @return bool 
	*/
	bool CheckNextFrameEnd();

	/**
	* @fn CheckAnimationFinish
	* @brief アニメーションが終了したかを確認する
	* @return bool 
	*/
	bool CheckAnimationFinish();

public:
	/**
	* @fn PlayAnimation
	* @brief アニメーションを再生するクラス
	* @param std::shared_ptr<SkeletalMesh_Re>           (_skeletalMesh)
	* @param std::shared_ptr<SkeletalMeshAnimationClip> (_animationClip)
	* @param const float                                (_playRate)
	* @param const float                                (_interpTime)
	* @param const float                                (_interpStartAnimationClipTime)
	* @return void
	*/
	void PlayAnimation(std::shared_ptr<SkeletalMesh> _skeletalMesh, std::shared_ptr<SkeletalMeshAnimationClip> _animationClip, const float _playRate, const float _interpTime = 0.0f, const float _interpStartAnimationClipTime = 0.0f);

	/**
	* @fn SkipAnimationFrame
	* @brief 指定したフレーム数アニメーションをスキップする
	* @param const double (_skipFrame) 飛ばしたいフレーム数
	* @return void 
	*/
	void SkipAnimationFrame(const double _skipFrame);

	/**
	 * @fn　GetPlayAnimation
	 * @brief 現在再生しているアニメーションのゲッター
	 * @return std::shared_ptr<SkeletalMeshAnimation> 現在再生しているアニメーション
	*/
	inline std::weak_ptr<SkeletalMeshAnimationClip> GetPlayAnimation();

	/**
	 * @fn　IsEndOnNextFrame
	 * @brief アニメーションが次のフレームで終了するか返す
	 * @return bool 
	*/
	inline bool IsEndOnNextFrame();

	/**
	* @fn IsPlay
	* @brief アニメーションを再生しているかを返す
	* @return void
	*/
	inline bool IsPlay() const noexcept;
};

//--------------------- INLINES --------------------------

inline std::weak_ptr<SkeletalMeshAnimationClip> AnimationPlayer::GetPlayAnimation()
{
	return mAnimPlayBackData.mAnimationClip;
}

inline bool AnimationPlayer::IsEndOnNextFrame()
{
	return mbEndOnNextFrame;
}

inline bool AnimationPlayer::IsPlay() const noexcept
{
	return mbIsPlay;
}

