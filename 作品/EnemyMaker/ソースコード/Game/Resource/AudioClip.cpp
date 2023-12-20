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
	// 処理なし
}

AudioClip::~AudioClip()
{
	// 処理なし
}

void AudioClip::Initialize(std::string_view _filePath)
{
	// アセット読み込み
	mAudioAssetHandle = AssetManager::GetInstance().Load<AudioProvider>(_filePath.data());

	// 読みこみできているかを確認する
	if (!mAudioAssetHandle->IsValid())
	{
		constexpr std::source_location location = std::source_location::current();
		std::cout << _filePath << "の読み込みに失敗しました";
		std::cout << "ファイル名 : " << location.file_name() << "行 : " << location.line() << std::endl;
		return;
	}
}

void AudioClip::Play() 
{	
	// オーディオバッファーを取得
	AudioAsset& audioAsset = mAudioAssetHandle->Get<AudioAsset>();
	XAUDIO2_BUFFER audio2Buffer = audioAsset.GetXAudio2Buffer();

	// ループするかしないかを設定
	if (mbLoop)
	{
		audio2Buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else // ループしない
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

