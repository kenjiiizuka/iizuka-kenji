//----------- INCLUDES ------------
#include "AudioSource.h"
#include "AudioSystem.h"
#include <iostream>

AudioSource::AudioSource()
	: mSourceVoice(nullptr)
	, mSourceState(SourceVoiceCallback::SourceState_None)
	, mCallBack(mSourceState)
{
	// ˆ—‚È‚µ
}

AudioSource::~AudioSource()
{
	if (mSourceVoice)
	{
		mSourceVoice->DestroyVoice();
	}	
}

void AudioSource::Initialize(WAVEFORMATEXTENSIBLE& _format)
{
	HRESULT hr = AudioSystem::GetInstance().GetXAudio2().CreateSourceVoice(&mSourceVoice, (WAVEFORMATEX*)&_format, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &mCallBack);
	if (FAILED(hr))
	{
		std::cout << "SourceVoice‚Ìì¬‚ÉŽ¸”s" << std::endl;
	}
}

void AudioSource::Play(XAUDIO2_BUFFER& _audioBuffer, const float _volume)
{
	// ƒLƒ…[‚ÌƒNƒŠƒA
	mSourceVoice->FlushSourceBuffers();

	HRESULT hr = mSourceVoice->SubmitSourceBuffer(&_audioBuffer);
	if (FAILED(hr))
	{
		std::cout << "SubmitSourceBuffer‚ÉŽ¸”s" << std::endl;
		return;
	}

	mSourceVoice->SetVolume(_volume);
	mSourceVoice->Start();
}

void AudioSource::Stop()
{
	mSourceVoice->Stop();
	mSourceVoice->SetVolume(0.0f);
	mSourceState = SourceVoiceCallback::SourceState_None;
}

