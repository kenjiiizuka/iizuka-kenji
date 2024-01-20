/**
* @file AudioSource.h
* @brief AudioSourceクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "SourceVoiceCallBack.h"

/**
* @class AudioSource
* @brief IXAudio2SourceVoiceをラップし、管理しやすくしたクラス
* @detailコールバッククラスから現在のAudioの状態を管理している
*/
class AudioSource
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AudioSource();

	/**
	* デストラクタ
	*/
	~AudioSource();

private:
	/** ソースボイス */
	IXAudio2SourceVoice* mSourceVoice;

	/** コールバック */
	SourceVoiceCallback mCallBack;
	
	/** サウンドソースのステート */
	SourceVoiceCallback::SourceState mSourceState;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail 引数で渡されたフォーマットでソースボイスを作成する
	* @return void
	*/
	void Initialize(WAVEFORMATEXTENSIBLE& _format);

	/**
	* @fn Play
	* @brief 渡されたバッファーを再生する
	* @param XAUDIO2_BUFFER& (_audioBuffer)
	* @param const float     (_volume)
	* @return void
	*/
	void Play(XAUDIO2_BUFFER& _audioBuffer, const float _volume);

	/**
	* @fn Stop
	* @brief 再生の停止
	* @return void
	*/
	void Stop();

	/**
	* @fn IsPlayAble
	* @brief 再生可能かを返す
	* @return bool true 再生可能 false 再生不可
	*/
	inline bool IsPlayAble() const noexcept;

	/**
	* @fn IsFinish
	* @brief 再生が終了したことを返す
	* @return bool true 再生終了 false 再生中
	*/
	inline bool IsFinish() const noexcept;

	/**
	* @fn GetSourceVoice
	* @brief 使用しているソースボイスを返す
	* @return IXAudio2SourceVoice*
	*/
	inline IXAudio2SourceVoice& GetSourceVoice() noexcept;

	/**
	* @fn SetVolume
	* @brief ソースボイスのvolumeをセットする
	* @param const float (_volume)
	* @return void
	*/
	inline void SetVolume(const float _volume) noexcept;
};

//----------- INLINES ----------

inline bool AudioSource::IsPlayAble() const noexcept
{
	return mSourceState == SourceVoiceCallback::SourceState_None;
}

inline bool AudioSource::IsFinish() const noexcept
{
	return mSourceState == SourceVoiceCallback::SourceState_Finish;
}

inline IXAudio2SourceVoice& AudioSource::GetSourceVoice() noexcept
{
	return *mSourceVoice;
}

inline void AudioSource::SetVolume(const float _volume) noexcept
{
	mSourceVoice->SetVolume(_volume);
}
