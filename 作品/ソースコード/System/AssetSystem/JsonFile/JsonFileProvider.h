/**
* @file JsonFileProvider.h
* @brief JsonFileProvider�N���X�̒�`
*/
#pragma once

//------------ INCLUDES -------------
#include "../IAssetProvider.h"

/**
* @class JsonFileProvider
* @brief json�`���̃t�@�C���̓ǂݍ��݂�����
*/
class JsonFileProvider : public IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	JsonFileProvider();

	/**
	* �f�X�g���N�^
	*/
	~JsonFileProvider();

private:
	/** �t�@�C�����Ȃ������ꍇ�ɐV�����쐬���邩 */
	bool mbCreateFile;

private:
	/**
	* @fn LoadBase
	* @brief �A�Z�b�g�ǂݍ��݂����ۂɎ��s���鏈��
	* @detail �ǂݍ��݂���������ƃL���b�V���}�b�v�ɓo�^����
	* @param const std::string& _filePath
	*/
	std::shared_ptr<IAsset> Load(const std::string& _filePath) const;

	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	void Setting();

public:

	/**
	* @fn GetProviderType
	* @brief �v���o�C�^�[��Type��Ԃ�
	* @detail typeid���g�p���ăv���o�C�^�[�̌^��Ԃ��Ă���
	* @return std::type_info �v���o�C�_�[�̌^
	*/
	inline const std::type_info& GetProviderType() const;

};

//------------ INLINES ----------

inline const std::type_info& JsonFileProvider::GetProviderType() const
{
	return typeid(JsonFileProvider);
}
