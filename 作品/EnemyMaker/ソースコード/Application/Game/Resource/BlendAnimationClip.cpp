//----------- INCLUDES ----------
#include "BlendAnimationClip.h"
#include "../../Utility/MathLibrary.h"

//--------- NAMESPACEAILIAS -----------
namespace DXSimpleMath = DirectX::SimpleMath;

BlendAnimationClip::BlendAnimationClip(std::shared_ptr<SkeletalMeshAnimationClip> _clip1, std::shared_ptr<SkeletalMeshAnimationClip> _clip2, const float _max, const float _min, const float _blendWeight)
	: SkeletalMeshAnimationClip()
	, mBlendWeight(_blendWeight)
	, mMinBlendValue(_min)
	, mMaxBlendValue(_max)
{	
	mChannels = _clip1->GetChannels();
	mChannelClip2 = _clip2->GetChannels();
	
	// 短い方を基準にアニメーションデータを正規化する
	mDuration = _clip1->GetDuration();
	if (mDuration < _clip2->GetDuration())
	{
		float scaleFactor = mDuration / _clip2->GetDuration();
		AnimationDataNormalize(mChannelClip2, scaleFactor);
		mTickPerSeconds = _clip1->GetTickPerSecond();
	}
	else
	{
		mDuration = _clip2->GetDuration();
		float scaleFactor = mDuration / _clip1->GetDuration();
		AnimationDataNormalize(mChannels, scaleFactor);
		mTickPerSeconds = _clip2->GetTickPerSecond();
	}

	mEndFrame = mDuration;

	// 少ない方のチャンネルの数を取得する
	mMinChannelNum = mChannelClip2.size() < mChannels.size() ? mChannelClip2.size() : mChannels.size();

	mBlendAnimation.resize(2);
	mBlendAnimation[0] = _clip1;
	mBlendAnimation[1] = _clip2;

	// セクションの初期値設定
	mSections.emplace_back(std::pair<uint16_t, std::string>(0, "Default"));
	mCurrentSection = mSections[0].second;
}

void BlendAnimationClip::Begin()
{
	SkeletalMeshAnimationClip::Begin();
	mBlendWeight = 0.0f;
}

void BlendAnimationClip::CalucAnimationMatrix(Channel& _channel, const double _time, DirectX::SimpleMath::Matrix& _animationMatrix)
{
	for (uint32_t i = 0; i < mChannelClip2.size(); i++)
	{
		// 一致するボーンデータがあればブレンドする
		if (mChannelClip2[i].mBoneName == _channel.mBoneName)
		{
			DXSimpleMath::Matrix clip1Matrix;
			DXSimpleMath::Matrix clip2Matrix;
			mBlendAnimation[1].lock()->CalucAnimationMatrix(mChannelClip2[i], _time, clip2Matrix);	
			mBlendAnimation[0].lock()->CalucAnimationMatrix(_channel, _time, clip1Matrix);

			DirectX::SimpleMath::Vector3 clip1Pos;
			DirectX::SimpleMath::Vector3 clip1Scale;
			DirectX::SimpleMath::Quaternion clip1Quat;
			MathLibrary::DecomposeMatrix(clip1Pos, clip1Scale, clip1Quat, clip1Matrix);

			DirectX::SimpleMath::Vector3 clip2Pos;
			DirectX::SimpleMath::Vector3 clip2Scale;
			DirectX::SimpleMath::Quaternion clip2Quat;
			MathLibrary::DecomposeMatrix(clip2Pos, clip2Scale, clip2Quat, clip2Matrix);

			DXSimpleMath::Vector3 pos = DXSimpleMath::Vector3::Lerp(clip1Pos, clip2Pos, mBlendWeight);
			DXSimpleMath::Vector3 scale = DXSimpleMath::Vector3::Lerp(clip1Scale, clip2Scale, mBlendWeight);
			DXSimpleMath::Quaternion quat = DXSimpleMath::Quaternion::Lerp(clip1Quat, clip2Quat, mBlendWeight);

			MathLibrary::MakeWorldMatrix(pos, scale, quat, _animationMatrix);

			return;
		}
	}
	mBlendAnimation[0].lock()->CalucAnimationMatrix(_channel, _time, _animationMatrix);
}

void BlendAnimationClip::AnimationDataNormalize(std::vector<Channel>& _channel, const float _scaleFactor)
{
	for (Channel& channel : _channel)
	{
		for (VectorKey& key : channel.mPositionKeys)
		{
			key.mTime *= _scaleFactor;
		}
		for (VectorKey& key : channel.mScaleKeys)
		{
			key.mTime *= _scaleFactor;
		}
		for (QuaternionKey& key : channel.mRotationKeys)
		{
			key.mTime *= _scaleFactor;
		}
	}
}

void BlendAnimationClip::InputBlendValue(const float& _value)
{
	mBlendWeight = _value / (mMaxBlendValue - mMinBlendValue);
	MathLibrary::Clamp01(mBlendWeight);
}


