/**
* @file AudioClip.h
* @brief AudioClip�N���X�̒�`
*/

#pragma once

//------------- INCLUDES -------------
#include <xaudio2.h>
#include <string>
#include <memory>

//--------- �O���錾 ----------
class AssetHandle;
class AudioSource;

/**
* @class AudioClip
* @brief �I�[�f�B�I�A�Z�b�g����XAudio�ōĐ��\�Ȍ`���ɂ��Ď���
*/
class AudioClip
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AudioClip();

	/**
	* �f�X�g���N�^
	*/
	~AudioClip();

private:
	/** �I�[�f�B�I�Z�b�g�̃n���h�� */
	std::shared_ptr<AssetHandle> mAudioAssetHandle;

	/** �T�E���h�̉��� */
	float mVolume;
		
	/** ���[�v�Đ����邩 */
	bool mbLoop;

	/** �I�[�f�B�I�\�[�X */
	std::weak_ptr<AudioSource> mAudioSource;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @param std::string_view (_filePath)
	* @return void
	*/
	void Initialize(std::string_view _filePath);

	/**
	* @fn Play
	* @brief �T�E���h�\�[�X���Đ�����֐�
	* @detail �ŏ�����n�߂�
	* @return void
	*/
	void Play();

	/**
	* @fn Stop
	* @brief �Đ����~�߂�
	* @return void
	*/
	void Stop() const;

	/**
	* @fn SetVolume
	* @brief volume�Z�b�g����
	* @param const float (_volume)
	* @return void
	*/
	void SetVolume(const float _volume) noexcept;

	/**
	* @fn GetAudioSource
	* @brief �g�p���Ă���I�[�f�B�I�\�[�X��Ԃ�
	* @detail �Đ����Ȃ�I�[�f�B�I�\�[�X��Ԃ��A�Đ����Ă��Ȃ����nullptr��Ԃ�
	* @return std::shared_ptr<AudioSource>
	*/
	inline std::shared_ptr<AudioSource> GetAudioSource() const noexcept;

	/**
	* @fn SetLoop
	* @brief ���[�v�Đ����邩���Z�b�g����
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