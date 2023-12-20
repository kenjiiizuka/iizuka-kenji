/**
* @file SourceVoiceCallBack.h
* @brief SourceVoiceCallBack�N���X�̒�`
*/

#pragma once

//------- INCLUDES -----------
#include <xaudio2.h>
#include <stdint.h>

/**
* @class SourceVoiceCallBack
* @brief �{�C�X�̃R�[���o�b�N�֐������������N���X
*/
class SourceVoiceCallback: public IXAudio2VoiceCallback
{
public: 
    /**
    * @enum SourceState
    * @brief �T�E���h�\�[�X�̏�Ԃ�����
    */
    enum SourceState : uint8_t
    {
        SourceState_None = 0, /**< �������Ă��Ȃ����  */
        SourceState_Play,     /**< �Đ��� */
        SourceState_Finish,   /**< �Đ����I�������t���[�� */
    };

    /**
    * �f�t�H���g�R���X�g���N�^
    */
    SourceVoiceCallback(SourceState& _state);

    /**
    * �f�X�g���N�^
    */
    ~SourceVoiceCallback();

    /** �T�E���h�\�[�X�̏�� */
    SourceState& mState;

    /**
    * @fn OnStreamEnd
    * @brief �Đ����I�������^�C�~���O�Ŏ��s�����R�[���o�b�N�֐�
    * @return void
    */
    STDMETHOD_(void, OnStreamEnd)() override;
    
    /**
    * @fn OnBufferEnd
    * @brief �o�b�t�@�[�̍Đ����I�������^�C�~���O�Ŏ��s�����R�[���o�b�N�֐�
    * @return void
    */
    STDMETHOD_(void, OnBufferEnd) (void* pBufferContext) override;

    /**
    * @fn OnBufferStart
    * @brief �o�b�t�@�[�̍Đ��^�C�~���O�Ŏ��s�����R�[���o�b�N�֐�
    * @return void
    */
    STDMETHOD_(void, OnBufferStart) (void* pBufferContext) override;

    // �g�p���Ȃ��R�[���o�b�N�֐�
    STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) override {}
    STDMETHOD_(void, OnVoiceProcessingPassStart) (UINT32 SamplesRequired) override {} 
    STDMETHOD_(void, OnLoopEnd) (void* pBufferContext) override {}
    STDMETHOD_(void, OnVoiceError) (void* pBufferContext, HRESULT Error) override {}
};
