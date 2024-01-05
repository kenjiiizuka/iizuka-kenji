/**
* @file AudioSystem.h
* @brief AudioSystem�N���X�̍쐬
*/
#pragma once

//------------ INCLUDES -------------
#include "../Singleton.h"
#include <xaudio2.h>
#include <Windows.h>
#include <x3daudio.h>
#include <SimpleMath.h>
#include <wrl/client.h>

//------- �O���錾 ---------
class AudioEmitter;
class AudioClip;
class AudioSource;
class AudioListener;

/**
* @class AudioSystem
* @brief �I�[�f�B�I�V�X�e���N���X
* @detail Audio�Ɋ֐��C���^�[�t�F�[�X�����[�U�[�V�X�e���ɒ񋟂���
*/
class AudioSystem : public Singleton<AudioSystem>
{
    /**----------------------------------------------------------------------------------------------
    * ���N���X��Singleton�N���X����R���X�g���N�^�ƁA�f�X�g���N�^�ɃA�N�Z�X���邽�߂ɕK�v�ł���
    * �N���X�O���琶���A�j���ł��Ȃ��悤�ɂ��邽�߂Ƀt�����h�w�肷��
    ------------------------------------------------------------------------------------------------*/
    friend class Singleton<AudioSystem>;

private:
    /**
    * �R���X�g���N�^
    */
    AudioSystem();

    /**
    * �f�X�g���N�^
    */
    ~AudioSystem();

    /**
    * �R�s�[�R���X�g���N�^
    * �R�s�[�֎~�̂��߂� delete�w��
    */
    AudioSystem(const AudioSystem&) = delete;

    /**
    * ������Z�q�̃I�[�o�[���[�h
    * ����֎~�̂��� delete�w��
    */
    void operator=(const AudioSystem&) = delete;

private:
    /** XAudio2 */
    Microsoft::WRL::ComPtr<IXAudio2> mXAudio2;

    /** �}�X�^�[�{�C�X */
    IXAudio2MasteringVoice* mMasterVoice;

    /** �T�u�~�b�N�X�{�C�X */
    IXAudio2SubmixVoice* mSubMixVoice;

    /** RIFF�����̃t�H�[�}�b�g */
    WAVEFORMATEXTENSIBLE mFormatRIFF;

    /** �}�X�^�[���� */
    float mMasterVolume;

    /** 3D�I�[�f�B�I */
    X3DAUDIO_HANDLE mX3DAudio;
 
    /** ���X�i�[ */
    std::weak_ptr<AudioListener> mAudioListener;

    /** 3D�I�[�f�B�I�p�̃G�~�b�^�[ */
    std::vector<std::shared_ptr<AudioEmitter>> mAudioEmitters;

    /** �I�[�f�B�I�\�[�X�v�[�� */
    std::vector<std::shared_ptr<AudioSource>> mAudioSourcePool;
 
public:
    /**
    * @fn Initialize
    * @brief ����������
    */
    void Initialize();

    /**
    * @fn Uninitialize
    * brief �I������
    */
    void Uninitialize();

    /**
    * @fn Update
    * @brief �X�V����
    * @return void
    */
    void Update();

    /** 
    * @fn ClearAudio
    * @brief ���g���Ă���AudioSource,Emitter�����ׂď���������
    * @detail �V�[���̐؂�ւ��Ȃǈꊇ�ł��ׂĂ�Audio���~�A���������邽�߂Ɏg�p����
    */
    void ClearAudio();

    /**
    * @fn AudioPlay
    * @brief �����Đ�����
    * @param XAUDIO2_BUFFER& (_audioBuffer) �Đ��������I�[�f�B�I�o�b�t�@�[
    * @return std::weak_ptr<AudioSource> �Đ����Ă���AudioSource
    */
    std::weak_ptr<AudioSource> AudioPlay(XAUDIO2_BUFFER& _audioBuffer);

    /**
    * @fn CreateSoundSource
    * @brief �\�[�X�{�C�X���쐬����֐�
    * @param IXAudio2SourceVoice** (_source) �\�[�X�{�C�X�̍쐬��
    * @return HRESULT
    */
    HRESULT CreateSoundSource(IXAudio2SourceVoice** _source);

    /**
    * @fn Calculate3DAudio
    * @brief 3DAudio�̌v�Z������
    * @param std::shared_ptr<AudioEmitter> (_emitter) 
    * @return void
    */
    void Calculate3DAudio(std::shared_ptr<AudioEmitter> _emitter);

    /**
    * @fn SetMasterVolume
    * @brief �}�X�^�[���ʂ��Z�b�g����
    * @param const float (_volume)
    * @return void
    */
    void SetMasterVolume(const float _volume);

    /**
    * @fn SpawnAudioEmitter
    * @brief �I�[�f�B�I�G�~�b�^�[���X�|�[��������
    * @param const std::shared_ptr<AudioClip> (_clip)
    * @param const DirectX::SimpleMath::Vector3 (_rotation)
    * @param const DirectX::SimpleMath::Vector3 (_position)
    * @param const float                        (_innerRadius)
    * @return void
    */
    void SpawnAudioEmitterAndPlay(const std::shared_ptr<AudioClip> _clip, const DirectX::SimpleMath::Vector3 _rotation, const DirectX::SimpleMath::Vector3 _position, const float _innerRadius = 1.0f);

    /**
    * @fn GetAudioListenerObject
    * @brief ���X�i�[�I�u�W�F�N�g��Ԃ�
    * @return std::weak_ptr<AudioListener>
    */
    inline std::weak_ptr<AudioListener> GetAudioListenerObject() const noexcept;

    /**
    * @fn GetXAudio2
    * @brief XAudio2�C���X�^���X�ւ̎Q�Ƃ�Ԃ�
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
