//------------ INCLUDES ------------
#include "AudioComponent.h"
#include "../../../System/AudioSystem/AudioSystemIncludes.h"
#include "../../../Utility/MathLibrary.h"

AudioComponent::AudioComponent()
	: mbIsFadeIn(false)
	, mVolume(1.0f)
	, mFadeInElapsedTime(0.0f)
	, mFadeInTime(10.0f)
	, mFadeOutElapsedTime(0.0f)
	, mFadeOutTime(10.0f)
	, mbIsFadeOut(false)
{
	// 処理なし
}

AudioComponent::~AudioComponent()
{
	// 処理なし
}

void AudioComponent::Init(std::string_view _filePath, const bool _loop)
{
	mAudioClip = std::make_shared<AudioClip>();
	mAudioClip->Initialize(_filePath);
	mAudioClip->SetLoop(_loop);
}

void AudioComponent::Update(const double _deltaTime)
{
	if (mbIsFadeIn)
	{
		FadeIn(_deltaTime);
	}
	else if (mbIsFadeOut)
	{
		FadeOut(_deltaTime);
	}
}

void AudioComponent::FadeIn(const double _deltaTime)
{
	// 音量を補完する	
	float t = static_cast<float>(MathLibrary::Clamp01(mFadeInElapsedTime / mFadeInTime));
	float volume = MathLibrary::LerpFloat(0.0f, mVolume, t);
	
	// 音量のセット
	mAudioClip->SetVolume(volume);

	// フェードイン終了チェック
	if (mFadeInElapsedTime >= mFadeInTime)
	{
		mbIsFadeIn = false;
		return;
	}

	// 経過時間を加算
	mFadeInElapsedTime += _deltaTime;
}

void AudioComponent::FadeOut(const double _deltaTime)
{
	// 音量を補完する	
	float t = static_cast<float>(MathLibrary::Clamp01(mFadeOutElapsedTime / mFadeOutTime));
	float volume = MathLibrary::LerpFloat(mVolume, 0.0f, t);

	// 音量のセット
	mAudioClip->SetVolume(volume);

	// フェードイン終了チェック
	if (mFadeOutElapsedTime >= mFadeOutTime)
	{
		mbIsFadeOut = false;

		// 停止
		mAudioClip->Stop();
		return;
	}

	// 経過時間を加算
	mFadeOutElapsedTime += _deltaTime;
}

void AudioComponent::PlaySound2D(const float _volume, const bool _isFade, const double _fadeInTime)
{
	mAudioClip->Play();
	mAudioClip->SetVolume(_volume);

	mVolume = _volume;
	mbIsFadeIn = _isFade;
	mFadeInTime = _fadeInTime;
	mFadeInElapsedTime = 0.0f;
}

void AudioComponent::PlaySound3D(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _rotation, const float _volume)
{
	AudioSystem::GetInstance().SpawnAudioEmitterAndPlay(mAudioClip, _rotation, _position);
	mAudioClip->SetVolume(_volume);
}

void AudioComponent::Stop(const bool _isFadeOut, const double _fadeOutTime)
{
	// フェードアウトするなら必要な値の初期化 再生の停止はしない
	if (_isFadeOut)
	{
		mbIsFadeOut = true;
		mFadeOutTime = _fadeOutTime;
		mFadeInElapsedTime = 0.0f;
		return;
	}

	// 再生の停止
	mAudioClip->Stop();
}
