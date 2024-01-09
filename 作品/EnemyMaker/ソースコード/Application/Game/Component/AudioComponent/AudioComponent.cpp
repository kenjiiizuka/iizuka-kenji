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
	// �����Ȃ�
}

AudioComponent::~AudioComponent()
{
	// �����Ȃ�
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
	// ���ʂ�⊮����	
	float t = static_cast<float>(MathLibrary::Clamp01(mFadeInElapsedTime / mFadeInTime));
	float volume = MathLibrary::LerpFloat(0.0f, mVolume, t);
	
	// ���ʂ̃Z�b�g
	mAudioClip->SetVolume(volume);

	// �t�F�[�h�C���I���`�F�b�N
	if (mFadeInElapsedTime >= mFadeInTime)
	{
		mbIsFadeIn = false;
		return;
	}

	// �o�ߎ��Ԃ����Z
	mFadeInElapsedTime += _deltaTime;
}

void AudioComponent::FadeOut(const double _deltaTime)
{
	// ���ʂ�⊮����	
	float t = static_cast<float>(MathLibrary::Clamp01(mFadeOutElapsedTime / mFadeOutTime));
	float volume = MathLibrary::LerpFloat(mVolume, 0.0f, t);

	// ���ʂ̃Z�b�g
	mAudioClip->SetVolume(volume);

	// �t�F�[�h�C���I���`�F�b�N
	if (mFadeOutElapsedTime >= mFadeOutTime)
	{
		mbIsFadeOut = false;

		// ��~
		mAudioClip->Stop();
		return;
	}

	// �o�ߎ��Ԃ����Z
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
	// �t�F�[�h�A�E�g����Ȃ�K�v�Ȓl�̏����� �Đ��̒�~�͂��Ȃ�
	if (_isFadeOut)
	{
		mbIsFadeOut = true;
		mFadeOutTime = _fadeOutTime;
		mFadeInElapsedTime = 0.0f;
		return;
	}

	// �Đ��̒�~
	mAudioClip->Stop();
}
