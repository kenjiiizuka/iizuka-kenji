//----------- INCLUDES ------------
#include "AudioSource.h"
#include "AudioSystem.h"
#include <iostream>

AudioSource::AudioSource()
	: mSourceVoice(nullptr)
	, mSourceState(SourceVoiceCallback::SourceState_None)
	, mCallBack(mSourceState)
{
	// 処理なし
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
		std::cout << "SourceVoiceの作成に失敗" << std::endl;
	}
}

void AudioSource::Play(XAUDIO2_BUFFER& _audioBuffer, const float _volume)
{
	// キューのクリア
	mSourceVoice->FlushSourceBuffers();

	HRESULT hr = mSourceVoice->SubmitSourceBuffer(&_audioBuffer);
	if (FAILED(hr))
	{
		std::cout << "SubmitSourceBufferに失敗" << std::endl;
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

