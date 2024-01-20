/**
* @file AudioSource.h
* @brief AudioSource�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include "SourceVoiceCallBack.h"

/**
* @class AudioSource
* @brief IXAudio2SourceVoice�����b�v���A�Ǘ����₷�������N���X
* @detail�R�[���o�b�N�N���X���猻�݂�Audio�̏�Ԃ��Ǘ����Ă���
*/
class AudioSource
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AudioSource();

	/**
	* �f�X�g���N�^
	*/
	~AudioSource();

private:
	/** �\�[�X�{�C�X */
	IXAudio2SourceVoice* mSourceVoice;

	/** �R�[���o�b�N */
	SourceVoiceCallback mCallBack;
	
	/** �T�E���h�\�[�X�̃X�e�[�g */
	SourceVoiceCallback::SourceState mSourceState;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail �����œn���ꂽ�t�H�[�}�b�g�Ń\�[�X�{�C�X���쐬����
	* @return void
	*/
	void Initialize(WAVEFORMATEXTENSIBLE& _format);

	/**
	* @fn Play
	* @brief �n���ꂽ�o�b�t�@�[���Đ�����
	* @param XAUDIO2_BUFFER& (_audioBuffer)
	* @param const float     (_volume)
	* @return void
	*/
	void Play(XAUDIO2_BUFFER& _audioBuffer, const float _volume);

	/**
	* @fn Stop
	* @brief �Đ��̒�~
	* @return void
	*/
	void Stop();

	/**
	* @fn IsPlayAble
	* @brief �Đ��\����Ԃ�
	* @return bool true �Đ��\ false �Đ��s��
	*/
	inline bool IsPlayAble() const noexcept;

	/**
	* @fn IsFinish
	* @brief �Đ����I���������Ƃ�Ԃ�
	* @return bool true �Đ��I�� false �Đ���
	*/
	inline bool IsFinish() const noexcept;

	/**
	* @fn GetSourceVoice
	* @brief �g�p���Ă���\�[�X�{�C�X��Ԃ�
	* @return IXAudio2SourceVoice*
	*/
	inline IXAudio2SourceVoice& GetSourceVoice() noexcept;

	/**
	* @fn SetVolume
	* @brief �\�[�X�{�C�X��volume���Z�b�g����
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
