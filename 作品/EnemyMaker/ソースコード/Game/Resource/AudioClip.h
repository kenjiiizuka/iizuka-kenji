/**
* @file AudioClip.h
* @brief AudioClipクラスの定義
*/

#pragma once

//------------- INCLUDES -------------
#include <xaudio2.h>
#include <string>
#include <memory>

//--------- 前方宣言 ----------
class AssetHandle;
class AudioSource;

/**
* @class AudioClip
* @brief オーディオアセットからXAudioで再生可能な形式にして持つ
*/
class AudioClip
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AudioClip();

	/**
	* デストラクタ
	*/
	~AudioClip();

private:
	/** オーディオセットのハンドル */
	std::shared_ptr<AssetHandle> mAudioAssetHandle;

	/** サウンドの音量 */
	float mVolume;
		
	/** ループ再生するか */
	bool mbLoop;

	/** オーディオソース */
	std::weak_ptr<AudioSource> mAudioSource;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param std::string_view (_filePath)
	* @return void
	*/
	void Initialize(std::string_view _filePath);

	/**
	* @fn Play
	* @brief サウンドソースを再生する関数
	* @detail 最初から始める
	* @return void
	*/
	void Play();

	/**
	* @fn Stop
	* @brief 再生を止める
	* @return void
	*/
	void Stop() const;

	/**
	* @fn SetVolume
	* @brief volumeセットする
	* @param const float (_volume)
	* @return void
	*/
	void SetVolume(const float _volume) noexcept;

	/**
	* @fn GetAudioSource
	* @brief 使用しているオーディオソースを返す
	* @detail 再生中ならオーディオソースを返し、再生していなければnullptrを返す
	* @return std::shared_ptr<AudioSource>
	*/
	inline std::shared_ptr<AudioSource> GetAudioSource() const noexcept;

	/**
	* @fn SetLoop
	* @brief ループ再生するかをセットする
	* @param const bool (_loop)
	* @return void
	*/
	inline void SetLoop(const bool _loop) noexcept;

};

//------------ INLINES ------------

inline void AudioClip::SetLoop(const bool _loop) noexcept
{
	mbLoop = _loop;
}

inline std::shared_ptr<AudioSource> AudioClip::GetAudioSource() const noexcept
{
	return mAudioSource.lock() ? mAudioSource.lock() : nullptr;
}