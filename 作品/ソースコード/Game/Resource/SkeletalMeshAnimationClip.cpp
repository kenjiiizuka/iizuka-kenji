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
	// 処理なし
}

SkeletalMeshAnimationClip::~SkeletalMeshAnimationClip()
{
	// 処理なし
}

void SkeletalMeshAnimationClip::Initialize(const std::string& _filePath)
{
	// アニメーションデータの読み込み
	mAnimationAssetHandle = AssetManager::GetInstance().Load<SkeletalMeshAnimationProvider>(_filePath);

	// 読み込みできているか確認
	if (!mAnimationAssetHandle->IsValid())
	{
		return;
	}

	// ファイルパスを名前として使用する
	mAnimationName = _filePath;

	// アセットからデータを取得する
	SkeletalMeshAnimationData animationData = mAnimationAssetHandle->Get<SkeletalMeshAnimationData>();
	mChannels = animationData.GetChannels();
	mDuration = animationData.GetDuration();
	mTickPerSeconds = animationData.GetTickPerSecond();
}

void SkeletalMeshAnimationClip::Begin()
{
	// 通知の初期化処理
	for (size_t notify_i = 0; std::pair<std::shared_ptr<AnimationNotify>, float>& animNotify : mAnimNotifies)
	{
		mbNotifyExecuted[notify_i] = false;
		animNotify.first->NotifyInitBase();
		notify_i++;
	}

	// 通知ステートの初期化処理
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

	// アニメーション通知の処理
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

	// アニメーション通知ステートの処理
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
	// 現在のキーを取得
	VectorKey positionKey;
	_channel.GetCurrentPositionKey(_time, positionKey);
	// 次のキーを取得、あれば補完した値を求める
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
	// 現在のキーを取得
	QuaternionKey rotationKey;
	_channel.GetCurrentRotationKey(_time, rotationKey);
	// 次のキーを取得、あれば補完した値を求める
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
	// 現在のキーを取得
	VectorKey scaleKey;
	_channel.GetCurrentScaleKey(_time, scaleKey);
	// 次のキーを取得、あれば補完した値を求める
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