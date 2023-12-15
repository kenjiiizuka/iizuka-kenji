/**
* @file  AnimationNotify.h
* @brief アニメ－ションの特定のフレームでの処理をするクラス
*/


#pragma once

//----------- INCLUDES --------
#include <memory>


//-------- INCLUDES ---------
class SkeletalMeshAnimationClip;
class SkeletalMesh;


/**
* @class AnimationNotify
* @brief アニメーション通知クラス
* @detail アニメーションクリップの特定のフレームにアタッチし、特定のフレームで処理を実行する
*/
class AnimationNotify
{
public:
	/**
	* 値の初期化
	* 
	* @param[in] std::weak_ptr<SkeletalMeshAnimation> (_attachAnimation) アタッチされるアニメーション
	*/
	AnimationNotify(SkeletalMeshAnimationClip* _attachAnimation, float _attachFrame);

	/**
	* デストラクタ
	*/
	virtual ~AnimationNotify() {};

protected:
	/** この通知が付けられているアニメーション */
	SkeletalMeshAnimationClip* mAttachedAnimation;

	/** アニメーションに対応したスケルタルメッシュ */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;

	/** アタッチされているフレーム */
	float mAttachedFrame;

public:
	/**
　　 * @fn　NotifyInitBase
　　 * @brief 通知の初期処理
　　 * @return void
　　*/
	virtual void NotifyInitBase();

	/**
　　 * @fn　NotifyBeginBase
　　 * @brief 通知開始のベース処理 
　　 * @return void
　　*/
	virtual void NotifyBeginBase();

	/**
　　 * @fn　NotifyBeginBase
　　 * @brief 通知終了のベース処理
　　 * @return void
　　*/
	virtual void NotifyEndBase();
	
	/**
　　 * @fn　NotifyInit
　　 * @brief 通知の初期処理
　　 * @return void
　　*/
	virtual void NotifyInit() {};

	/**
　　 * @fn　NotifyBegin
　　 * @brief 通知の開始処理
　　 * @return void
　　*/
	virtual void NotifyBegin() {};

	/**
　　 * @fn　NotifyUpdate
　　 * @brief 通知の更新処理
　　 * @return void
　　*/
	virtual void NotifyUpdate() {};

	/**
　　 * @fn　NotifyEnd
　　 * @brief 通知の終了処理
　　 * @return void
　　*/
	virtual void NotifyEnd() {};

public:
	/**
	* @fn GetAttachFrame
	* @brief アタッチされているフレームを返す
	* @return float 
	*/
	inline float GetAttachFrame() const noexcept;

	/**
	* @fn SetAttachFrame
	* @brief アタッチするフレームのセッター
	* @param const float (_attachFrame)
	* @return void
	*/
	inline void SetAttachFrame(const float _attachFrame) noexcept;

};

//----------- INLINES ----------

inline float AnimationNotify::GetAttachFrame() const noexcept
{
	return mAttachedFrame;
}

inline void AnimationNotify::SetAttachFrame(const float _attachFrame) noexcept
{
	mAttachedFrame = _attachFrame;
}

