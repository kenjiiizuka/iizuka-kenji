//---------- INCLUDES ----------
#include "AudioClip.h"
#include "../../System/AudioSystem/AudioSystem.h"
#include "../../System/AssetSystem/Audio/AudioAssetIncludes.h"
#include "../../System/AudioSystem/AudioSource.h"
#include <source_location>

AudioClip::AudioClip()
	: mbLoop(false)
	, mVolume(1.0f)
{
	// �����Ȃ�
}

AudioClip::~AudioClip()
{
	// �����Ȃ�
}

void AudioClip::Initialize(std::string_view _filePath)
{
	// �A�Z�b�g�ǂݍ���
	mAudioAssetHandle = AssetManager::GetInstance().Load<AudioProvider>(_filePath.data());

	// �ǂ݂��݂ł��Ă��邩���m�F����
	if (!mAudioAssetHandle->IsValid())
	{
		constexpr std::source_location location = std::source_location::current();
		std::cout << _filePath << "�̓ǂݍ��݂Ɏ��s���܂���";
		std::cout << "�t�@�C���� : " << location.file_name() << "�s : " << location.line() << std::endl;
		return;
	}
}

void AudioClip::Play() 
{	
	// �I�[�f�B�I�o�b�t�@�[���擾
	AudioAsset& audioAsset = mAudioAssetHandle->Get<AudioAsset>();
	XAUDIO2_BUFFER audio2Buffer = audioAsset.GetXAudio2Buffer();

	// ���[�v���邩���Ȃ�����ݒ�
	if (mbLoop)
	{
		audio2Buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else // ���[�v���Ȃ�
	{
		audio2Buffer.LoopCount = XAUDIO2_NO_LOOP_REGION;
	}
	audio2Buffer.PlayBegin = 0;
	audio2Buffer.PlayLength = 0;

	mAudioSource = AudioSystem::GetInstance().AudioPlay(audio2Buffer);
}

void AudioClip::Stop() const
{
	mAudioSource.lock()->Stop();
}

void AudioClip::SetVolume(const float _volume) noexcept
{
	mVolume = _volume;
	if (mAudioSource.lock())
	{
		mAudioSource.lock()->SetVolume(mVolume);
	}
}

