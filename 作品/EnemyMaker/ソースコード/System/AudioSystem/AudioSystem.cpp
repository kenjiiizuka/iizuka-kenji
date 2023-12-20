//--------- LINK ---------
#pragma comment (lib, "XAudio2.lib")

//------------ INCLUDES -----------
#include "AudioSystem.h"
#include "../../ImGui/ImGuiUtility.h"
#include "../../Game/Scene/SceneManager.h"
#include "../../Game/GameObject/Camera/CameraManager.h"
#include "../../Game/GameObject/Camera/Camera.h"
#include "../../Game/GameObject/AudioLisner/AudioListener.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/Resource/AudioEmitter.h"
#include "AudioSource.h"
#include <iostream>

AudioSystem::AudioSystem()
	: mMasterVoice(nullptr)
	, mSubMixVoice(nullptr)
	, mFormatRIFF({0})
	, mMasterVolume(1.0f)
	, mX3DAudio()
{
	// RIFF�t�H�[�}�b�g�ݒ�ɂ���
	mFormatRIFF.dwChannelMask = 0;
	mFormatRIFF.Format.wFormatTag = 1;
	mFormatRIFF.Format.nChannels = 2;
	mFormatRIFF.Format.nSamplesPerSec = 44100;
	mFormatRIFF.Format.nAvgBytesPerSec = 176400;
	mFormatRIFF.Format.nBlockAlign = 4;
	mFormatRIFF.Format.wBitsPerSample = 16;
	mFormatRIFF.Format.cbSize = 0;
	mFormatRIFF.Samples = { 0 };
	mFormatRIFF.SubFormat = { 0 };
}

AudioSystem::~AudioSystem()
{
	// �����Ȃ�
}

void AudioSystem::Initialize()
{
	// XAudio2������
	HRESULT hr = XAudio2Create(mXAudio2.GetAddressOf(), 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr))
	{
		return;
	}

	// �}�X�^�[�{�C�X�̍쐬
	hr = mXAudio2->CreateMasteringVoice(&mMasterVoice);
	if (FAILED(hr))
	{
		return;
	}

 	hr = mXAudio2->CreateSubmixVoice(&mSubMixVoice, mFormatRIFF.Format.nChannels, mFormatRIFF.Format.nSamplesPerSec);

	// 3DXAudio�̏�����
	DWORD dwChannelMask;
	mMasterVoice->GetChannelMask(&dwChannelMask);
	hr =X3DAudioInitialize(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, mX3DAudio);
	if (FAILED(hr))
	{
		std::cout << "3DAudio�̏������Ɏ��s���܂���" << std::endl;
		return;
	}

	// �I�[�f�B�I�v�[���̐���
	mAudioSourcePool.resize(100);
	for (std::shared_ptr<AudioSource>& audioSource : mAudioSourcePool)
	{
		audioSource = std::make_shared<AudioSource>();
		audioSource->Initialize(mFormatRIFF);
	}

	mMasterVoice->SetVolume(mMasterVolume);
}

void AudioSystem::Uninitialize()
{
	// �}�X�^�[�{�C�X��XAudio2�̉��
	mMasterVoice->DestroyVoice();
	mSubMixVoice->DestroyVoice();
}

void AudioSystem::Update()
{
//	ImGui::Begin("AudioConfig");

	// ImGui::SliderFloat("MasterVolume", &mMasterVolume, 0.0f,1.0f);
	// mMasterVoice->SetVolume(mMasterVolume);
	// ImGui::End();


	for (auto it = mAudioEmitters.begin(); it != mAudioEmitters.end();)
	{
		if (it->get()->IsDestroy())
		{
			it = mAudioEmitters.erase(it);
		}
		else 
		{
			it++;
		}
	}

	for (std::shared_ptr<AudioEmitter>& emitter : mAudioEmitters)
	{
		emitter->Update();
		Calculate3DAudio(emitter);
	}
}

void AudioSystem::ClearAudio()
{
	for (std::shared_ptr<AudioSource>& audioSource : mAudioSourcePool)
	{
		audioSource.reset();
		audioSource = std::make_shared<AudioSource>();
		audioSource->Initialize(mFormatRIFF);
	}
	mAudioEmitters.clear();
}

std::weak_ptr<AudioSource> AudioSystem::AudioPlay(XAUDIO2_BUFFER& _audioBuffer)
{
	for (size_t useCount = 0;std::shared_ptr<AudioSource> audioSource : mAudioSourcePool)
	{
		if (!audioSource->IsPlayAble())
		{
			useCount++;
			continue;
		}
		audioSource->Play(_audioBuffer, 1.0f);
		return audioSource;
	}
	return std::weak_ptr<AudioSource>();
}

HRESULT AudioSystem::CreateSoundSource(IXAudio2SourceVoice** _source)
{
	return mXAudio2->CreateSourceVoice(_source, (WAVEFORMATEX*)&mFormatRIFF);
}

void AudioSystem::Calculate3DAudio(std::shared_ptr<AudioEmitter> _emitter)
{
	XAUDIO2_VOICE_DETAILS deviceDetails;
	mMasterVoice->GetVoiceDetails(&deviceDetails);

	// �G�~�b�^�[���擾
	X3DAUDIO_EMITTER& emitter = _emitter->GetEmitter();

	// dsp�̐ݒ�
	X3DAUDIO_DSP_SETTINGS dpsSettings;
	dpsSettings.SrcChannelCount = emitter.ChannelCount;
	dpsSettings.DstChannelCount = emitter.ChannelCount;
	std::vector<FLOAT32> matrix(dpsSettings.SrcChannelCount * dpsSettings.DstChannelCount);
	dpsSettings.pMatrixCoefficients = matrix.data();

	// ���X�i�[���擾
	X3DAUDIO_LISTENER listener{};
	if (mAudioListener.lock()) 
	{
		listener = mAudioListener.lock()->GetListener();
	}

	// 3DAudio�v�Z
	X3DAudioCalculate(
		mX3DAudio,
		&listener,
		&emitter,
		X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_REVERB,
		&dpsSettings
	);

	
	if (!_emitter->GetAudioSource().lock())
	{
		return;
	}
	// �\�[�X�{�C�X�Ɍv�Z���ʂ�K��
	IXAudio2SourceVoice& sourceVoice = _emitter->GetAudioSource().lock()->GetSourceVoice();
	sourceVoice.SetOutputMatrix(mMasterVoice, dpsSettings.SrcChannelCount, deviceDetails.InputChannels,dpsSettings.pMatrixCoefficients);
	sourceVoice.SetFrequencyRatio(dpsSettings.DopplerFactor);
	sourceVoice.SetOutputMatrix(mSubMixVoice, dpsSettings.SrcChannelCount, dpsSettings.DstChannelCount, &dpsSettings.ReverbLevel);

	// �t�B���^�[�̐ݒ�
	XAUDIO2_FILTER_PARAMETERS filterParameters = { LowPassFilter, 2.0f * std::sinf(X3DAUDIO_PI / 6.0f * dpsSettings.LPFDirectCoefficient), 1.0f };
	sourceVoice.SetFilterParameters(&filterParameters);
}

void AudioSystem::SetMasterVolume(const float _volume)
{
	mMasterVolume = _volume;
	mMasterVoice->SetVolume(_volume);
}

void AudioSystem::SpawnAudioEmitterAndPlay(const std::shared_ptr<AudioClip> _clip, const DirectX::SimpleMath::Vector3 _rotation, const DirectX::SimpleMath::Vector3 _position, const float _innerRadius)
{
	std::shared_ptr<AudioEmitter> emitter = std::make_shared<AudioEmitter>();
	emitter->Initialize(_clip, mFormatRIFF.Format.nChannels,_rotation,_position, _innerRadius);
	mAudioEmitters.emplace_back(emitter);
}
