#pragma once
/**
* @file BinaryFile.h
* @brief BinaryFile�N���X�̒�`
*/

//----------- INCLUDES -----------
#include <fstream>
#include <vector>
#include "../IAsset.h"

//---------- �O���錾 ---------
class BinaryFileProvider;

/** 
* @enum WriteMode
* @brief �t�@�C���̏������݃��[�h�̒�`
*/
enum class WriteMode
{
	Add = std::ios_base::app,         /**< �t�@�C���̖����ɒǋL���� */
	Override = std::ios_base::binary, /**< �t�@�C���ɏ㏑������@�����̃f�[�^�͏����� */
};

/**
* @class BinaryFile
* @brief �o�C�i���[�t�@�C���̃f�[�^��ێ�����
*/
class BinaryFile : public IAsset
{
	/**---------------------------------------------------------------------------------------------
	 * �t�@�C���X�g���[���ւ̃Z�b�g��BinaryFileProvider����̂݃A�N�Z�X�\�ɂ��邽�߂Ƀt�����h�w��
	*/
	friend class BinaryFileProvider;

public:
	/**
	 * �f�t�H���g�R���X�g���N�^
	*/
	BinaryFile();
	
	/**
	 * �f�t�H���g�f�X�g���N�^
	*/
	~BinaryFile();
	
private:
	/** �X�g���[���T�C�Y */
	std::streamsize mStreamSize;

	/** �t�@�C���p�X */
	std::string mFilePath;

private:
	/**
	 * @fn CheckFileSize
	 * @brief �n���ꂽ�X�g���[���̃T�C�Y��Ԃ�
	 * @param std::istream& (_stream)
	*/
	std::streamsize CheckFileSize(std::istream& _stream);

	/**
	 * @fn Read
	 * @brief �t�@�C������w�肳�ꂽ�o�C�g���ǂ݂Ƃ�
	 * @param std::ifstream& (_stream)
	 * @param std::vector<char>& (_outputData)
	 * @param const std::streamsize& _readSize
	*/
	void Read(std::ifstream& _stream, std::vector<char>& _outputData, const std::streamsize& _readSize);

public:
	/**
	 * @fn GetAssetType
	 * @brief �A�Z�b�g�̃^�C�v��Ԃ�
	 * @detail typeid���g�p���Č^���ʂ����Ă���
	 * @return const std::type_info&
	*/
	inline const std::type_info& GetAssetType() const noexcept;

	/**
	 * @fn ReadAllData
	 * @brief ���ׂẴf�[�^�̓ǂݍ��݂�����
	 * @param std::vector<char>& (_outputData)
	 * @return void
	*/
	void ReadAllData(std::vector<char>& _outputData);

	/**
	* @fn WriteData
	* @brief �f�[�^���t�@�C���ɏ������ފ֐�
	* @param const char*     (_writeData)
	* @param const size_t    (_writeDataSize) 
	* @param const WriteMode (_writeMode) �f�t�H���g�͒ǋL
	* @return void
	*/
	void WriteData(const char* _writeData, const size_t _writeDataSize, const WriteMode _writeMode = WriteMode::Add);
};

//---------- INLINES ----------

inline const std::type_info& BinaryFile::GetAssetType() const noexcept
{
	return typeid(BinaryFile);
}

