//------------ INCLUDES ------------
#include "AudioComponent.h"
#include "../../../System/AudioSystem/AudioSystemIncludes.h"

AudioComponent::AudioComponent()
{
	// ˆ—‚È‚µ
}

AudioComponent::~AudioComponent()
{
	// ˆ—‚È‚µ
}

void AudioComponent::Init(std::string_view _filePath, const bool _loop)
{
	mAudioClip = std::make_shared<AudioClip>();
	mAudioClip->Initialize(_filePath);
	mAudioClip->SetLoop(_loop);
}

void AudioComponent::PlaySound2D(const float _volume)
{
	mAudioClip->Play();
	mAudioClip->SetVolume(_volume);
}

void AudioComponent::PlaySound3D(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _rotation, const float _volume)
{
	AudioSystem::GetInstance().SpawnAudioEmitterAndPlay(mAudioClip, _rotation, _position);
	mAudioClip->SetVolume(_volume);
}
