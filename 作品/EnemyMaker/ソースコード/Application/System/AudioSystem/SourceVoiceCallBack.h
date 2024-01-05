/**
* @file SourceVoiceCallBack.h
* @brief SourceVoiceCallBackクラスの定義
*/

#pragma once

//------- INCLUDES -----------
#include <xaudio2.h>
#include <stdint.h>

/**
* @class SourceVoiceCallBack
* @brief ボイスのコールバック関数を実装したクラス
*/
class SourceVoiceCallback: public IXAudio2VoiceCallback
{
public: 
    /**
    * @enum SourceState
    * @brief サウンドソースの状態を示す
    */
    enum SourceState : uint8_t
    {
        SourceState_None = 0, /**< 何もしていない状態  */
        SourceState_Play,     /**< 再生中 */
        SourceState_Finish,   /**< 再生が終了したフレーム */
    };

    /**
    * デフォルトコンストラクタ
    */
    SourceVoiceCallback(SourceState& _state);

    /**
    * デストラクタ
    */
    ~SourceVoiceCallback();

    /** サウンドソースの状態 */
    SourceState& mState;

    /**
    * @fn OnStreamEnd
    * @brief 再生が終了したタイミングで実行されるコールバック関数
    * @return void
    */
    STDMETHOD_(void, OnStreamEnd)() override;
    
    /**
    * @fn OnBufferEnd
    * @brief バッファーの再生が終了したタイミングで実行されるコールバック関数
    * @return void
    */
    STDMETHOD_(void, OnBufferEnd) (void* pBufferContext) override;

    /**
    * @fn OnBufferStart
    * @brief バッファーの再生タイミングで実行されるコールバック関数
    * @return void
    */
    STDMETHOD_(void, OnBufferStart) (void* pBufferContext) override;

    // 使用しないコールバック関数
    STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) override {}
    STDMETHOD_(void, OnVoiceProcessingPassStart) (UINT32 SamplesRequired) override {} 
    STDMETHOD_(void, OnLoopEnd) (void* pBufferContext) override {}
    STDMETHOD_(void, OnVoiceError) (void* pBufferContext, HRESULT Error) override {}
};
