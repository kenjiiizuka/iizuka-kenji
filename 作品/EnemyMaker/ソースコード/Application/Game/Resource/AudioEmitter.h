/**
* @file AudioEmitter.h
* @brief AudioEmitterクラスの定義
*/

#pragma once

//----------- INCLUDES ------------
#include <Windows.h>
#include <x3daudio.h>
#include <xaudio2.h>
#include <SimpleMath.h>
#include "AudioClip.h"

//----------- 前方宣言 -----------
class AudioSource;

/**
* @class AudioEmitter
* @brief オーディオエミッター
* @detail 3dSoundを流すためのエミッター
*         再生が終ると自動的に破棄される
*/
class AudioEmitter
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AudioEmitter();

	/**
	* デストラクタ
	*/
	~AudioEmitter();

private:
	/** エミッター */
	X3DAUDIO_EMITTER mEmitter;

	/** AudioClip */
	std::weak_ptr<AudioClip> mAudioClip;

	/** このエミッターのオーディオクリップを再生しているオーディオソース */
	std::weak_ptr<AudioSource> mAudioSource;

	/** 破棄フラグ */
	bool mbDestroy;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail エミッターの設定を行う
	* @param const std::shared_ptr<AudioClip>   (_audioClip)
	* @param const UINT32                       (_channelCount)
	* @param const DirectX::SimpleMath::Vector3 (_rotation)
	* @param const DirectX::SimpleMath::Vector3 (_position)
	* @param const float                        (_innerRadius)
	* @return void
	*/
	void Initialize(const std::shared_ptr<AudioClip> _audioClip, const UINT32 _channelCount, const DirectX::SimpleMath::Vector3 _rotation, const DirectX::SimpleMath::Vector3 _position, const float _innerRadius);

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update();

private:	
	/**
	* @fn CheckFinish
	* @brief サウンドが終了したかを判断する
	* @detail サウンドが終了していれば関数内でmbDestroyフラグをtrueにする
	* @return void
	*/
	void CheckFinish();

public:
	/**
	* @fn GetEmitter
	* @brief エミッターを返す
	* @return X3DAUDIO_EMITTER&
	*/
	inline X3DAUDIO_EMITTER& GetEmitter() noexcept;

	/**
	* @fn GetAudioSource
	* @brief オーディオソースを返す
	* @return std::weak_ptr<AudioSource>
	*/
	inline std::weak_ptr<AudioSource> GetAudioSource() const noexcept;

	/**
	* @fn IsDestroy
	* @brief 破棄する必要があるか
	* @return bool true 
	*/
	inline bool IsDestroy() const noexcept;

};

//----------- INLINES ----------

inline X3DAUDIO_EMITTER& AudioEmitter::GetEmitter() noexcept
{
	return mEmitter;
}

inline std::weak_ptr<AudioSource> AudioEmitter::GetAudioSource() const noexcept
{
	return mAudioSource;
}

inline bool AudioEmitter::IsDestroy() const noexcept
{
	return mbDestroy;
}
