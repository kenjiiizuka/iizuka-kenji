/**
* @file AudioProvider.h
* @brief AudioProvider�N���X�̍쐬
*/

#pragma once

//---------- INCLUDES -----------
#include "../IAssetProvider.h"
#include <xaudio2.h>

/**
* @class AudioProvider
* @brief wav�t�@�C���̓ǂݍ��݂�����
* @detail XAudio2�Ŏg�p�����RIFF�t�@�C���ł���wav�t�@�C���̓ǂݍ��݂�����
*/
class AudioProvider : public IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AudioProvider();

	/**
	* �f�X�g���N�^
	*/
	~AudioProvider();

private:
	/**
	* @fn LoadBase
	* @brief �A�Z�b�g�ǂݍ��݂����ۂɎ��s���鏈��
	* @detail �ǂݍ��݂���������ƃL���b�V���}�b�v�ɓo�^����
	* @param const std::string& _filePath
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const;

	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	virtual void Setting();

	/**
	* @fn FindChunk
	* @brief wav�t�@�C������`�����N�f�[�^��������
	* @detail �}�C�N���\�t�g�������t�@�����X���Q�Ƃ����@wav�t�@�C������`�����N��������֐�
	*         https://learn.microsoft.com/ja-jp/windows/win32/xaudio2/how-to--load-audio-data-files-in-xaudio2
	* @param HANDLE (_hFile) �ǂݎ�肽��wav�t�@�C��
	* @param DWORD  (_fourcc)
	* @param DWORD& (_dwChunkSize) �`�����N�T�C�Y
	* @param DWORD& (_dwChunkDataPosition)
	* @return HRESULT �`�����N�������ꂽ����Ԃ�
	*/
	HRESULT FindChunk(HANDLE _hFile, DWORD _fourcc, DWORD& _dwChunkSize, DWORD& _dwChunkDataPosition) const;

	/**
	* @fn ReadChunkData
	* @brief �`�����N��ǂݎ��֐�
	* @detail �}�C�N���\�t�g�������t�@�����X���Q�Ƃ����@wav�t�@�C������`�����N��ǂݎ��֐�
	*         https://learn.microsoft.com/ja-jp/windows/win32/xaudio2/how-to--load-audio-data-files-in-xaudio2
	* @param HANDLE (_hFile)
	* @param void* (_buffer)
	* @param DWORD (_buffersize)
	* @param DWORD (_bufferoffset)
	*/
	HRESULT ReadChunkData(HANDLE _hFile, void* _buffer, DWORD _buffersize, DWORD _bufferoffset) const;

public:
	/**
	* @fn GetProviderType
	* @brief �v���o�C�^�[��Type��Ԃ�
	* @detail typeid���g�p���ăv���o�C�^�[�̌^��Ԃ��Ă���
	* @return std::type_info �v���o�C�_�[�̌^
	*/
	inline virtual const std::type_info& GetProviderType() const;

};

//--------- INLINES ----------

inline const std::type_info& AudioProvider::GetProviderType() const
{
	return typeid(AudioProvider);
}
