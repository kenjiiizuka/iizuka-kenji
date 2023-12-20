/**
* @file AudioAsset.h
* @brief AudioAsset�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ---------
#include "../IAsset.h"
#include <memory>
#include <xaudio2.h>

/**
* @class AudioClip
* @brief XAudio�ōĐ��\��Audio�A�Z�b�g
*/
class AudioAsset : public IAsset
{
	/**-----------------------------------------------------------------------
	* �f�[�^�̃Z�b�g��AudioProvider�N���X����݂̂Ɍ��肷�邽�߂Ƀt�����h�w��
	-------------------------------------------------------------------------*/
	friend class AudioProvider;

public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AudioAsset();

	/**
	* �f�X�g���N�^
	*/
	~AudioAsset();

private:
	/** �I�[�f�B�I�f�[�^�o�b�t�@�[ */
	XAUDIO2_BUFFER mXAudio2Buffer;

	/** �f�[�^�o�b�t�@�[ mXAudio2Buffer�̌� */
	std::shared_ptr<BYTE> mDataBuffer;

public:
	/**
	* @fn GetAssetType
	* @brief �A�Z�b�g�̃^�C�v��Ԃ�
	* @detail typeid���g�p���Č^���ʂ����Ă���
	* @return const std::type_info&
	*/
	inline virtual const std::type_info& GetAssetType() const noexcept;

	/**
	* @fn GetXAudio2Buffer
	* @brief XAUDIO2_BUFFER��Ԃ�
	* @return XAUDIO2_BUFFER
	*/
	inline XAUDIO2_BUFFER GetXAudio2Buffer() const noexcept;

	/**
	* @fn GetAudioDataBuffer
	* @brief �I�[�f�B�I�f�[�^�o�b�t�@�[��Ԃ�
	* @return std::weak_ptr<BYTE>
	*/
	inline std::weak_ptr<BYTE> GetAudioDataBuffer() const noexcept;

};

//---------- INLINES -----------

inline const std::type_info& AudioAsset::GetAssetType() const noexcept
{
	return typeid(AudioAsset);
}

inline XAUDIO2_BUFFER AudioAsset::GetXAudio2Buffer() const noexcept
{
	return mXAudio2Buffer;
}

inline std::weak_ptr<BYTE> AudioAsset::GetAudioDataBuffer() const noexcept
{
	return mDataBuffer;
}
