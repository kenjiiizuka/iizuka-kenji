//--------- INCLUDES -----------
#include "AnimationPlayer.h"
#include "../../Game/Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../Utility/MathLibrary.h"
#include "../../Utility/Debug.h"
#include "../../System/AnimationSystem/AnimationSynchronizer.h"
#include "../../Game/Resource/SkeletalMesh.h"
#include "../../Game/Resource/Skeleton.h"
#include "../../Game/Resource/SkeletalMeshAnimationClip.h"
#include "../../Game/Resource/Bone.h"
#include "../../System/AnimationSystem/InterpSkeletalAnimation.h"
#include "../../System/Logger/Logger.h"

//----------- NAMESPACEAILIAS ---------------
using namespace DirectX::SimpleMath;

AnimationPlayer::AnimationPlayer()
	: mbEndOnNextFrame(false)
	, mbIsPlay(false)
	, mbEndSync(false)
{
	mSynchronizer = std::make_shared<AnimationSynchronizer>();
	mAnimationInterp = std::make_shared<InterpSkeletalAnimation>();
}

void AnimationPlayer::AnimationUpdate(const double _deltaTime)
{	
	// アニメーションが再生されていない場合の処理
	if (!mbIsPlay)
	{
		AnimationStopping();
		return;
	}

	mAnimPlayBackData.mAnimationClip.lock()->Update(static_cast<float>(mAnimPlayBackData.mCurrentPlayTime));

	// 次のフレームにアニメーションが終了するかを確認する
	mbEndOnNextFrame = CheckNextFrameEnd();

	// アニメーション再生処理
	// スケルタルメッシュとアニメーションデータへの参照が有効化を確認 無効ならつぎの要素にいく
	if (!(mAnimPlayBackData.mAnimationClip.lock() && mAnimPlayBackData.mSkeletalMesh.lock()))
	{
		return;
	}

	// 補間の処理をする
	if (mAnimPlayBackData.mbInterp)
	{
		mAnimPlayBackData.mbInterp = !InterpAnimation(_deltaTime);		
	}
	// 補完しなければ通常再生
	else
	{
		StepAnimation(_deltaTime);	
	}

	mAnimPlayBackData.mSkeletalMesh.lock()->GetSkeleton().lock()->Animate();

	// アニメーション同期処理
	if (mAnimPlayBackData.mbSynchro)
	{
		mSynchronizer->Synchro();
	}

	// アニメーションが終了しているか確認する
	if (!CheckAnimationFinish())
	{
		mbIsPlay = false;
		mbEndSync = mAnimPlayBackData.mbSynchro;
	}
	
	if (!mbIsPlay)
	{
		// ループ再生ならtrueになりもう一度再生される
		mbIsPlay = mAnimPlayBackData.mbLoop;
		mAnimPlayBackData.mCurrentPlayTime = 0.0f;
	}	
}

void AnimationPlayer::AnimationStopping()
{
	if (!mbEndSync)
	{
		return;
	}
	// アニメーション同期の終了処理
	mSynchronizer->AnimationEndSync();
}

void AnimationPlayer::StepAnimation(const double _deltaTime)
{
	std::shared_ptr<SkeletalMesh> skeletalMesh = mAnimPlayBackData.mSkeletalMesh.lock();
	std::shared_ptr<SkeletalMeshAnimationClip> animationData = mAnimPlayBackData.mAnimationClip.lock();
	std::shared_ptr<Skeleton> skeleton = skeletalMesh->GetSkeleton().lock();

	skeletalMesh->SetAnimate(true);

	// アニメーションデータを取得
	std::vector<Channel> channels = animationData->GetChannels();

	// アニメーションデータをSkeletonに適応する
	for (Channel& channel : channels)
	{
		// アニメショーン行列を計算する
		Matrix animationMatrix;
		animationData->CalucAnimationMatrix(channel, mAnimPlayBackData.mCurrentPlayTime, animationMatrix);

		// 対応しているボーンにアニメーション行列をセットする
		std::weak_ptr<Bone> bone = skeleton->GetBoneByName(channel.mBoneName);
		if (!bone.lock())
		{
			continue;
		}
		bone.lock()->SetAnimationMatrix(animationMatrix);
	}	

	// 再生時間を進める
	mAnimPlayBackData.mCurrentPlayTime += mAnimPlayBackData.mTickPerSeconds * mAnimPlayBackData.mPlayRate * _deltaTime;
}

void AnimationPlayer::InterpBegin(const std::shared_ptr<SkeletalMeshAnimationClip>& _baseAnimationClip, const float _interpStartAnimationClipTime, const std::shared_ptr<SkeletalMeshAnimationClip> _toAnimationClip, const float _interpTime)
{
	// 補間もとのアニメーションのフレーム数を設定
	float interpBaseTime = static_cast<float>(mAnimPlayBackData.mCurrentPlayTime);

	// 前のアニメーションが終了していれば最後のフレームから補完する
	interpBaseTime = interpBaseTime == 0.0f ? _baseAnimationClip->GetEndFrame() : interpBaseTime;

	// 補間の開始処理
	mAnimationInterp->InterpBegin(
		_interpTime,
		mAnimPlayBackData.mSkeletalMesh.lock()->GetSkeleton().lock(),
		interpBaseTime,
		_interpStartAnimationClipTime,
		_baseAnimationClip,
		_toAnimationClip
	);

	// 補間に使用するパラメーターの設定
	mAnimPlayBackData.mbInterp = true;
	mAnimPlayBackData.mInterpTime = _interpTime;
	mAnimPlayBackData.mElapsedInterpTime = 0.0f;
}

bool AnimationPlayer::InterpAnimation(const double _deltaTime)
{
	// 補間
	bool finish = mAnimationInterp->Interp(mAnimPlayBackData.mElapsedInterpTime, mAnimPlayBackData.mSkeletalMesh.lock()->GetSkeleton().lock());
	
	// 時間を進める
	mAnimPlayBackData.mElapsedInterpTime += static_cast<float>(_deltaTime);

	// 補間が終了したかを確認	
	return finish || (mAnimPlayBackData.mElapsedInterpTime >= mAnimPlayBackData.mInterpTime);
}

bool AnimationPlayer::CheckNextFrameEnd()
{
	// 誤差をなくすためにuint16_t型にキャストする
	uint16_t duration = static_cast<uint16_t>(mAnimPlayBackData.mAnimationClip.lock()->GetEndFrame());
	return static_cast<uint16_t>(mAnimPlayBackData.mCurrentPlayTime) == duration - 1;
}

bool AnimationPlayer::CheckAnimationFinish()
{
	// 誤差をなくすためにuint16t型にキャストする
	uint16_t duration = static_cast<uint16_t>(mAnimPlayBackData.mAnimationClip.lock()->GetEndFrame());
	return !(static_cast<uint16_t>(mAnimPlayBackData.mCurrentPlayTime) >= duration);
}

void AnimationPlayer::PlayAnimation(std::shared_ptr<SkeletalMesh> _skeletalMesh, std::shared_ptr<SkeletalMeshAnimationClip> _animationClip, const float _playRate, const float _interpTime, const float _interpStartAnimationClipTime)
{
	std::shared_ptr<SkeletalMeshAnimationClip> prevPlayAnimation = mAnimPlayBackData.mAnimationClip.lock();

	// 補間するか確認 	 
	mAnimPlayBackData.mSkeletalMesh = _skeletalMesh;

	// 前回再生したアニメーションがあり補完するなら開始処理をする
	 if (_interpTime != 0.0f && prevPlayAnimation)
	 {
	 	InterpBegin(prevPlayAnimation, _interpStartAnimationClipTime, _animationClip, _interpTime);
	 }
	
	// 同期処理をするなら同期開始処理をする
	 mAnimPlayBackData.mbSynchro = _animationClip->IsSynchroPosition() || _animationClip->IsSynchroRotation();
	if (mAnimPlayBackData.mbSynchro)
	{
		bool repeated = prevPlayAnimation ? prevPlayAnimation->IsSynchroPosition() : false;
		bool displaced = _animationClip->IsDisplaced();
		mSynchronizer->SynchroBegin(mAnimPlayBackData.mSkeletalMesh.lock(), _animationClip->IsSynchroPosition(), _animationClip->IsSynchroRotation(), repeated, displaced);
		mAnimPlayBackData.mbSynchroNeedInit = false;
	}

	// アニメーション再生に必要なデータをセット
	mbIsPlay = true;
	mbEndOnNextFrame = false;
	mAnimPlayBackData.mbLoop = _animationClip->IsLoop();
	mAnimPlayBackData.mCurrentPlayTime = _interpStartAnimationClipTime; // 補間先アニメーショーンの開始位置に設定
	mAnimPlayBackData.mAnimationClip = _animationClip;
	mAnimPlayBackData.mSkeletalMesh = _skeletalMesh;
	mAnimPlayBackData.mPlayRate = _playRate;
	mAnimPlayBackData.mTickPerSeconds = _animationClip->GetTickPerSecond();

	// アニメーションクリップの開始処理
	mAnimPlayBackData.mAnimationClip.lock()->Begin();
}

void AnimationPlayer::SkipAnimationFrame(const double _skipFrame)
{
	// スキップ後のフレームがアニメーションの長さを超えていないか確認
	// 超えていればアニメーションの長さ - 1 フレームに設定する
	double duration = mAnimPlayBackData.mAnimationClip.lock()->GetEndFrame();
	double skipedFrame = mAnimPlayBackData.mCurrentPlayTime + _skipFrame;
	if (skipedFrame >= duration)
	{
		skipedFrame = duration - 1;
	}
	else if(skipedFrame < 0)
	{
		skipedFrame = 0;
	}
	mAnimPlayBackData.mCurrentPlayTime = skipedFrame;
}

AnimationPlayBackData::AnimationPlayBackData()
	: mbLoop(false)
	, mbInterp(false)
	, mbSynchroNeedInit(false)
	, mCurrentPlayTime(0)
	, mPlayRate(1.0f)
	, mTickPerSeconds(0.0f)
	, mInterpTime(0.0f)
	, mElapsedInterpTime(0.0f)
	, mbSynchro(false)
{
	// 処理なし
}
