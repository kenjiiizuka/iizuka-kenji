/**
* @file AudioSystem.h
* @brief AudioSystemクラスの作成
*/
#pragma once

//------------ INCLUDES -------------
#include "../Singleton.h"
#include <xaudio2.h>
#include <Windows.h>
#include <x3daudio.h>
#include <SimpleMath.h>
#include <wrl/client.h>

//------- 前方宣言 ---------
class AudioEmitter;
class AudioClip;
class AudioSource;
class AudioListener;

/**
* @class AudioSystem
* @brief オーディオシステムクラス
* @detail Audioに関数インターフェースをユーザーシステムに提供する
*/
class AudioSystem : public Singleton<AudioSystem>
{
    /**----------------------------------------------------------------------------------------------
    * 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
    * クラス外から生成、破棄できないようにするためにフレンド指定する
    ------------------------------------------------------------------------------------------------*/
    friend class Singleton<AudioSystem>;

private:
    /**
    * コンストラクタ
    */
    AudioSystem();

    /**
    * デストラクタ
    */
    ~AudioSystem();

    /**
    * コピーコンストラクタ
    * コピー禁止のために delete指定
    */
    AudioSystem(const AudioSystem&) = delete;

    /**
    * 代入演算子のオーバーロード
    * 代入禁止のため delete指定
    */
    void operator=(const AudioSystem&) = delete;

private:
    /** XAudio2 */
    Microsoft::WRL::ComPtr<IXAudio2> mXAudio2;

    /** マスターボイス */
    IXAudio2MasteringVoice* mMasterVoice;

    /** サブミックスボイス */
    IXAudio2SubmixVoice* mSubMixVoice;

    /** RIFF方式のフォーマット */
    WAVEFORMATEXTENSIBLE mFormatRIFF;

    /** マスター音量 */
    float mMasterVolume;

    /** 3Dオーディオ */
    X3DAUDIO_HANDLE mX3DAudio;
 
    /** リスナー */
    std::weak_ptr<AudioListener> mAudioListener;

    /** 3Dオーディオ用のエミッター */
    std::vector<std::shared_ptr<AudioEmitter>> mAudioEmitters;

    /** オーディオソースプール */
    std::vector<std::shared_ptr<AudioSource>> mAudioSourcePool;
 
public:
    /**
    * @fn Initialize
    * @brief 初期化処理
    */
    void Initialize();

    /**
    * @fn Uninitialize
    * brief 終了処理
    */
    void Uninitialize();

    /**
    * @fn Update
    * @brief 更新処理
    * @return void
    */
    void Update();

    /** 
    * @fn ClearAudio
    * @brief 今使われているAudioSource,Emitterをすべて初期化する
    * @detail シーンの切り替わりなど一括ですべてのAudioを停止、初期化するために使用する
    */
    void ClearAudio();

    /**
    * @fn AudioPlay
    * @brief 音を再生する
    * @param XAUDIO2_BUFFER& (_audioBuffer) 再生したいオーディオバッファー
    * @return std::weak_ptr<AudioSource> 再生しているAudioSource
    */
    std::weak_ptr<AudioSource> AudioPlay(XAUDIO2_BUFFER& _audioBuffer);

    /**
    * @fn CreateSoundSource
    * @brief ソースボイスを作成する関数
    * @param IXAudio2SourceVoice** (_source) ソースボイスの作成先
    * @return HRESULT
    */
    HRESULT CreateSoundSource(IXAudio2SourceVoice** _source);

    /**
    * @fn Calculate3DAudio
    * @brief 3DAudioの計算をする
    * @param std::shared_ptr<AudioEmitter> (_emitter) 
    * @return void
    */
    void Calculate3DAudio(std::shared_ptr<AudioEmitter> _emitter);

    /**
    * @fn SetMasterVolume
    * @brief マスター音量をセットする
    * @param const float (_volume)
    * @return void
    */
    void SetMasterVolume(const float _volume);

    /**
    * @fn SpawnAudioEmitter
    * @brief オーディオエミッターをスポーンさせる
    * @param const std::shared_ptr<AudioClip> (_clip)
    * @param const DirectX::SimpleMath::Vector3 (_rotation)
    * @param const DirectX::SimpleMath::Vector3 (_position)
    * @param const float                        (_innerRadius)
    * @return void
    */
    void SpawnAudioEmitterAndPlay(const std::shared_ptr<AudioClip> _clip, const DirectX::SimpleMath::Vector3 _rotation, const DirectX::SimpleMath::Vector3 _position, const float _innerRadius = 1.0f);

    /**
    * @fn GetAudioListenerObject
    * @brief リスナーオブジェクトを返す
    * @return std::weak_ptr<AudioListener>
    */
    inline std::weak_ptr<AudioListener> GetAudioListenerObject() const noexcept;

    /**
    * @fn GetXAudio2
    * @brief XAudio2インスタンスへの参照を返す
    * @return IXAudio2&
    */
    inline IXAudio2& GetXAudio2() noexcept;

    /**
    * @fn SetListener
    * @brief std::shared_ptr<AudioListener> (_listener)
    * @return void
    */
    inline void SetListener(std::shared_ptr<AudioListener> _listener);
};

//-------- INLINES ---------

inline IXAudio2& AudioSystem::GetXAudio2() noexcept
{
    return *mXAudio2.Get();
}

inline void AudioSystem::SetListener(std::shared_ptr<AudioListener> _listener)
{
    mAudioListener = _listener;
}

inline std::weak_ptr<AudioListener> AudioSystem::GetAudioListenerObject() const noexcept
{
    return mAudioListener;
}
