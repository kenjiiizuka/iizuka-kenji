//----------- INCLUDES ----------
#include "InterpSkeletalAnimation.h"
#include "../FPSController/FPSController.h"
#include "../../Game/Resource/Bone.h"
#include "../../Game/Resource/Skeleton.h"
#include "../../Game/Resource/SkeletalMeshAnimationClip.h"
#include "../../Utility/MathLibrary.h"

//-------- NAMESPACEAILAS ---------
namespace DXSimpleMath = DirectX::SimpleMath;

InterpSkeletalAnimation::InterpSkeletalAnimation()
	: mInterpTime(0.0f)
	, mBaseInterpStartTime(0.0f)
	, mToInterpClipTime(0.0f)
	, mbFinish(false)
{
	// 処理なし
}

InterpSkeletalAnimation::~InterpSkeletalAnimation()
{
	// 処理なし
}

void InterpSkeletalAnimation::InterpBegin(const float _interpTime, const std::shared_ptr<Skeleton> _interpSkeleton, const float _baseInterpStartTime, const float _toInterpClipTime,  const std::shared_ptr<SkeletalMeshAnimationClip> _animationClipInterpBase, const std::shared_ptr<SkeletalMeshAnimationClip> _animationClipInterpTo)
{
	// マップのクリア
	mInterpToClip = _animationClipInterpTo;
	mInterpBaseClip = _animationClipInterpBase;
	mInterpTime = _interpTime;	
	mBaseInterpStartTime = _baseInterpStartTime;
	mToInterpClipTime = _toInterpClipTime;	
	mbFinish = false;
}

bool InterpSkeletalAnimation::Interp(const float _time, std::shared_ptr<Skeleton> _skeleton)
{	
	std::shared_ptr<SkeletalMeshAnimationClip> toClip = mInterpToClip.lock();
	std::shared_ptr<SkeletalMeshAnimationClip> baseClip = mInterpBaseClip.lock();
	if (!(toClip && baseClip))
	{
		return mbFinish;
	}

	std::vector<Channel> toChannels = toClip->GetChannels();
	std::vector<Channel> baseChannels = baseClip->GetChannels();

	// 補間の比率を求める
	float t = MathLibrary::Clamp01(_time / mInterpTime);

	for (Channel& toChannel : toChannels)
	{
		// ボーンを取得する
		std::shared_ptr<Bone> bone = _skeleton->GetBoneByName(toChannel.mBoneName).lock();

		// 存在しないボーンはスキップ
		if (!bone)
		{
			continue;
		}
		Channel baseChannel;

		// 同じボーンのチャンネルがあるかを確認
		for (size_t channel_i = 0; Channel& channel : baseChannels)
		{
			// ボーンの名前で照合
			if (channel.mBoneName == toChannel.mBoneName)
			{
				baseChannel = channel;
				break;
			}
		}

		DXSimpleMath::Matrix animationMatrix;
		// 一致するチャンネルがなかったら
		if (baseChannel.mBoneName == "")
		{
			mInterpToClip.lock()->CalucAnimationMatrix(toChannel,mToInterpClipTime, animationMatrix);
		}
		else
		{
			CalcuInterpKey(baseChannel, toChannel, animationMatrix, t);
		}
		// ボーンにアニメーション行列をセットする
		bone->SetAnimationMatrix(animationMatrix);
	}
	return mbFinish;
}

void InterpSkeletalAnimation::CalcuInterpKey(Channel _baseChannel, Channel _toChannel, DirectX::SimpleMath::Matrix& _animationMatrix, const float _t)
{
	std::shared_ptr<SkeletalMeshAnimationClip> toClip = mInterpToClip.lock();
	std::shared_ptr<SkeletalMeshAnimationClip> baseClip = mInterpBaseClip.lock();

	// 補間先のキーの情報を計算
	DXSimpleMath::Vector3 toPosition;
	DXSimpleMath::Vector3 toScale;
	DXSimpleMath::Quaternion toQuaternion;
	toClip->CalucAnimationKey(_toChannel, mToInterpClipTime, toPosition, toScale, toQuaternion);
	
	// 補間元のキーの情報を計算
	DXSimpleMath::Vector3 basePosition;
	DXSimpleMath::Vector3 baseScale;
	DXSimpleMath::Quaternion baseQuaternion;
	baseClip->CalucAnimationKey(_baseChannel, mBaseInterpStartTime, basePosition, baseScale, baseQuaternion);
	
	// 補間もとアニメーションのみが座標同期しているなら差分を引いて補間先アニメーションの位置に合わせる
	if (baseClip->IsSynchroPosition() && (!toClip->IsDisplaced() || !toClip->IsSynchroPosition() ))
	{
		DirectX::SimpleMath::Vector3 difference = basePosition - toPosition;
		basePosition -= difference;
	}

	// 回転同期をしているアニメーションの場合はY回転を合わせる
	if (baseClip->IsSynchroRotation())
	{
		baseQuaternion.y = toQuaternion.y;
	}

	// 補完してアニメーションマトリックスを作成する
	DXSimpleMath::Vector3 lerpPosition = DXSimpleMath::Vector3::Lerp(basePosition, toPosition, _t);
	DXSimpleMath::Vector3 lerpScale = DXSimpleMath::Vector3::Lerp(baseScale, toScale, _t);
	DXSimpleMath::Quaternion lerpQuaternion = DXSimpleMath::Quaternion::Lerp(baseQuaternion, toQuaternion, _t);
	MathLibrary::MakeWorldMatrix(lerpPosition, lerpScale, lerpQuaternion, _animationMatrix);
}
