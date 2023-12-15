//------------ INCLUDES -----------
#include "SkeletalMeshAnimationClip.h"
#include "../../Utility/MathLibrary.h"
#include "../../System/AssetSystem/SkeletalMesh/SkeletalMeshAnimationProvider.h"
#include "../../System/AssetSystem/AssetManager.h"
#include "../../System/AssetSystem/AssetHandle.h"


//---------- NAMESPACEAILIAS ----------------
namespace DXSimpleMath = DirectX::SimpleMath;

SkeletalMeshAnimationClip::SkeletalMeshAnimationClip()
	: mDuration(0.0f)
	, mTickPerSeconds(0.0f)
	, mbLoop(false)
	, mbSynchroPosition(false)
	, mbSynchroRotation(false)
	, mbNotifyStateBeginExecuted(false)
	, mbNotifyStateEndExecuted(false)
	, mbDisplacedStartAnimation(false)
{
	// �����Ȃ�
}

SkeletalMeshAnimationClip::~SkeletalMeshAnimationClip()
{
	// �����Ȃ�
}

void SkeletalMeshAnimationClip::Initialize(const std::string& _filePath)
{
	// �A�j���[�V�����f�[�^�̓ǂݍ���
	mAnimationAssetHandle = AssetManager::GetInstance().Load<SkeletalMeshAnimationProvider>(_filePath);

	// �ǂݍ��݂ł��Ă��邩�m�F
	if (!mAnimationAssetHandle->IsValid())
	{
		return;
	}

	// �t�@�C���p�X�𖼑O�Ƃ��Ďg�p����
	mAnimationName = _filePath;

	// �A�Z�b�g����f�[�^���擾����
	SkeletalMeshAnimationData animationData = mAnimationAssetHandle->Get<SkeletalMeshAnimationData>();
	mChannels = animationData.GetChannels();
	mDuration = animationData.GetDuration();
	mTickPerSeconds = animationData.GetTickPerSecond();
}

void SkeletalMeshAnimationClip::Begin()
{
	// �ʒm�̏���������
	for (size_t notify_i = 0; std::pair<std::shared_ptr<AnimationNotify>, float>& animNotify : mAnimNotifies)
	{
		mbNotifyExecuted[notify_i] = false;
		animNotify.first->NotifyInitBase();
		notify_i++;
	}

	// �ʒm�X�e�[�g�̏���������
	for (size_t notifyState_i = 0; std::shared_ptr<AnimationNotifyState> notifyState : mAnimNotifyStates)
	{
		notifyState->NotifyInitBase();
		mbNotifyStateBeginExecuted[notifyState_i] = false;
		mbNotifyStateEndExecuted[notifyState_i] = false;
		notifyState_i++;
	}
}

void SkeletalMeshAnimationClip::Update(const float _currentPlayTime)
{
	uint16_t currentPlayTime = static_cast<uint16_t>(_currentPlayTime);

	// �A�j���[�V�����ʒm�̏���
	for (size_t notify_i = 0; std::pair<std::shared_ptr<AnimationNotify>, float>& animNotify : mAnimNotifies)
	{
		uint16_t attachFrame = static_cast<uint16_t>(animNotify.first->GetAttachFrame());
		if (currentPlayTime >= attachFrame && !mbNotifyExecuted[notify_i])
		{
			animNotify.first->NotifyBegin();
			animNotify.first->NotifyUpdate();
			animNotify.first->NotifyEnd();
			mbNotifyExecuted[notify_i] = true;
		}
		notify_i++;
	}

	// �A�j���[�V�����ʒm�X�e�[�g�̏���
	for (size_t notifyState_i = 0; std::shared_ptr<AnimationNotifyState> notifyState : mAnimNotifyStates)
	{
		uint16_t startFrame = notifyState->GetStartFrame();
		uint16_t endFrame = notifyState->GetEndFrame();
		
		if (currentPlayTime >= startFrame && !mbNotifyStateBeginExecuted[notifyState_i])
		{
			notifyState->NotifyBeginBase();
			mbNotifyStateBeginExecuted[notifyState_i] = true;
		}
		else if (startFrame < currentPlayTime && currentPlayTime < endFrame)
		{
			notifyState->NotifyUpdate();
		}
		else if (currentPlayTime >= endFrame && !mbNotifyStateEndExecuted[notifyState_i])
		{
			notifyState->NotifyEndBase();
			mbNotifyStateEndExecuted[notifyState_i] = true;
		}
		notifyState_i++;
	}
}

void SkeletalMeshAnimationClip::PositionKeyLerp(const double& _time, DirectX::SimpleMath::Vector3& _outPutPosition, Channel& _channel)
{
	// ���݂̃L�[���擾
	VectorKey positionKey;
	_channel.GetCurrentPositionKey(_time, positionKey);
	// ���̃L�[���擾�A����Ε⊮�����l�����߂�
	VectorKey nextPositionKey;
	if (_channel.GetNextPositionKey(positionKey, nextPositionKey))
	{
		double t = _time - positionKey.mTime / nextPositionKey.mTime - positionKey.mTime;
		_outPutPosition = DXSimpleMath::Vector3::Lerp(positionKey.mValue, nextPositionKey.mValue, static_cast<float>(t));
	}
	else
	{
		_outPutPosition = positionKey.mValue;
	}
}

void SkeletalMeshAnimationClip::RotationKeyLerp(const double& _time, DirectX::SimpleMath::Quaternion& _outPutQuaternion, Channel& _channel)
{
	// ���݂̃L�[���擾
	QuaternionKey rotationKey;
	_channel.GetCurrentRotationKey(_time, rotationKey);
	// ���̃L�[���擾�A����Ε⊮�����l�����߂�
	QuaternionKey nextRotationKey;
	if (_channel.GetNextRotationKey(rotationKey, nextRotationKey))
	{
		double t = _time - rotationKey.mTime / nextRotationKey.mTime - rotationKey.mTime;
		_outPutQuaternion = DXSimpleMath::Quaternion::Lerp(rotationKey.mValue, nextRotationKey.mValue, static_cast<float>(t));
	}
	else
	{
		_outPutQuaternion = rotationKey.mValue;
	}
}

void SkeletalMeshAnimationClip::ScaleKeyLerp(const double& _time, DirectX::SimpleMath::Vector3& _outPutScale, Channel& _channel)
{
	// ���݂̃L�[���擾
	VectorKey scaleKey;
	_channel.GetCurrentScaleKey(_time, scaleKey);
	// ���̃L�[���擾�A����Ε⊮�����l�����߂�
	VectorKey nextScaleKey;
	if (_channel.GetNextScaleKey(scaleKey, nextScaleKey))
	{
		double t = _time - scaleKey.mTime / nextScaleKey.mTime - scaleKey.mTime;
		_outPutScale = DXSimpleMath::Vector3::Lerp(scaleKey.mValue, nextScaleKey.mValue, static_cast<float>(t));
	}
	else
	{
		_outPutScale = scaleKey.mValue;
	}
}

void SkeletalMeshAnimationClip::CalucAnimationMatrix(Channel& _channel, const double _time, DirectX::SimpleMath::Matrix& _animationMatrix)
{
	DXSimpleMath::Vector3 position;
	DXSimpleMath::Vector3 scale;
	DXSimpleMath::Quaternion quaternion;
	PositionKeyLerp(_time, position, _channel);
	ScaleKeyLerp(_time, scale, _channel);
	RotationKeyLerp(_time, quaternion, _channel);
	MathLibrary::MakeWorldMatrix(position, scale, quaternion, _animationMatrix);
}

void SkeletalMeshAnimationClip::CalucAnimationKey(Channel& _channel, const double _time, DirectX::SimpleMath::Vector3& _position, DirectX::SimpleMath::Vector3& _scale, DirectX::SimpleMath::Quaternion& _quaternion)
{
	PositionKeyLerp(_time, _position, _channel);
	ScaleKeyLerp(_time, _scale, _channel);
	RotationKeyLerp(_time, _quaternion, _channel);
}