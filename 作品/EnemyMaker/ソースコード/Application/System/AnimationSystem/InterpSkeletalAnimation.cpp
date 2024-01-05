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
	// �����Ȃ�
}

InterpSkeletalAnimation::~InterpSkeletalAnimation()
{
	// �����Ȃ�
}

void InterpSkeletalAnimation::InterpBegin(const float _interpTime, const std::shared_ptr<Skeleton> _interpSkeleton, const float _baseInterpStartTime, const float _toInterpClipTime,  const std::shared_ptr<SkeletalMeshAnimationClip> _animationClipInterpBase, const std::shared_ptr<SkeletalMeshAnimationClip> _animationClipInterpTo)
{
	// �}�b�v�̃N���A
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

	// ��Ԃ̔䗦�����߂�
	float t = MathLibrary::Clamp01(_time / mInterpTime);

	for (Channel& toChannel : toChannels)
	{
		// �{�[�����擾����
		std::shared_ptr<Bone> bone = _skeleton->GetBoneByName(toChannel.mBoneName).lock();

		// ���݂��Ȃ��{�[���̓X�L�b�v
		if (!bone)
		{
			continue;
		}
		Channel baseChannel;

		// �����{�[���̃`�����l�������邩���m�F
		for (size_t channel_i = 0; Channel& channel : baseChannels)
		{
			// �{�[���̖��O�ŏƍ�
			if (channel.mBoneName == toChannel.mBoneName)
			{
				baseChannel = channel;
				break;
			}
		}

		DXSimpleMath::Matrix animationMatrix;
		// ��v����`�����l�����Ȃ�������
		if (baseChannel.mBoneName == "")
		{
			mInterpToClip.lock()->CalucAnimationMatrix(toChannel,mToInterpClipTime, animationMatrix);
		}
		else
		{
			CalcuInterpKey(baseChannel, toChannel, animationMatrix, t);
		}
		// �{�[���ɃA�j���[�V�����s����Z�b�g����
		bone->SetAnimationMatrix(animationMatrix);
	}
	return mbFinish;
}

void InterpSkeletalAnimation::CalcuInterpKey(Channel _baseChannel, Channel _toChannel, DirectX::SimpleMath::Matrix& _animationMatrix, const float _t)
{
	std::shared_ptr<SkeletalMeshAnimationClip> toClip = mInterpToClip.lock();
	std::shared_ptr<SkeletalMeshAnimationClip> baseClip = mInterpBaseClip.lock();

	// ��Ԑ�̃L�[�̏����v�Z
	DXSimpleMath::Vector3 toPosition;
	DXSimpleMath::Vector3 toScale;
	DXSimpleMath::Quaternion toQuaternion;
	toClip->CalucAnimationKey(_toChannel, mToInterpClipTime, toPosition, toScale, toQuaternion);
	
	// ��Ԍ��̃L�[�̏����v�Z
	DXSimpleMath::Vector3 basePosition;
	DXSimpleMath::Vector3 baseScale;
	DXSimpleMath::Quaternion baseQuaternion;
	baseClip->CalucAnimationKey(_baseChannel, mBaseInterpStartTime, basePosition, baseScale, baseQuaternion);
	
	// ��Ԃ��ƃA�j���[�V�����݂̂����W�������Ă���Ȃ獷���������ĕ�Ԑ�A�j���[�V�����̈ʒu�ɍ��킹��
	if (baseClip->IsSynchroPosition() && (!toClip->IsDisplaced() || !toClip->IsSynchroPosition() ))
	{
		DirectX::SimpleMath::Vector3 difference = basePosition - toPosition;
		basePosition -= difference;
	}

	// ��]���������Ă���A�j���[�V�����̏ꍇ��Y��]�����킹��
	if (baseClip->IsSynchroRotation())
	{
		baseQuaternion.y = toQuaternion.y;
	}

	// �⊮���ăA�j���[�V�����}�g���b�N�X���쐬����
	DXSimpleMath::Vector3 lerpPosition = DXSimpleMath::Vector3::Lerp(basePosition, toPosition, _t);
	DXSimpleMath::Vector3 lerpScale = DXSimpleMath::Vector3::Lerp(baseScale, toScale, _t);
	DXSimpleMath::Quaternion lerpQuaternion = DXSimpleMath::Quaternion::Lerp(baseQuaternion, toQuaternion, _t);
	MathLibrary::MakeWorldMatrix(lerpPosition, lerpScale, lerpQuaternion, _animationMatrix);
}
