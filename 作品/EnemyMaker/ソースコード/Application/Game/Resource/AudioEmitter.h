/**
* @file AudioEmitter.h
* @brief AudioEmitter�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ------------
#include <Windows.h>
#include <x3daudio.h>
#include <xaudio2.h>
#include <SimpleMath.h>
#include "AudioClip.h"

//----------- �O���錾 -----------
class AudioSource;

/**
* @class AudioEmitter
* @brief �I�[�f�B�I�G�~�b�^�[
* @detail 3dSound�𗬂����߂̃G�~�b�^�[
*         �Đ����I��Ǝ����I�ɔj�������
*/
class AudioEmitter
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AudioEmitter();

	/**
	* �f�X�g���N�^
	*/
	~AudioEmitter();

private:
	/** �G�~�b�^�[ */
	X3DAUDIO_EMITTER mEmitter;

	/** AudioClip */
	std::weak_ptr<AudioClip> mAudioClip;

	/** ���̃G�~�b�^�[�̃I�[�f�B�I�N���b�v���Đ����Ă���I�[�f�B�I�\�[�X */
	std::weak_ptr<AudioSource> mAudioSource;

	/** �j���t���O */
	bool mbDestroy;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail �G�~�b�^�[�̐ݒ���s��
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
	* @brief �X�V����
	* @return void
	*/
	void Update();

private:	
	/**
	* @fn CheckFinish
	* @brief �T�E���h���I���������𔻒f����
	* @detail �T�E���h���I�����Ă���Ί֐�����mbDestroy�t���O��true�ɂ���
	* @return void
	*/
	void CheckFinish();

public:
	/**
	* @fn GetEmitter
	* @brief �G�~�b�^�[��Ԃ�
	* @return X3DAUDIO_EMITTER&
	*/
	inline X3DAUDIO_EMITTER& GetEmitter() noexcept;

	/**
	* @fn GetAudioSource
	* @brief �I�[�f�B�I�\�[�X��Ԃ�
	* @return std::weak_ptr<AudioSource>
	*/
	inline std::weak_ptr<AudioSource> GetAudioSource() const noexcept;

	/**
	* @fn IsDestroy
	* @brief �j������K�v�����邩
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
