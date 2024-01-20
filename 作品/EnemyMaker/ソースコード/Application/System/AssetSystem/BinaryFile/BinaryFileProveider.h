/**
* @file BinaryFileProvider.h
* @brief BinaryFileProvider�N���X�̒�`
*/


#pragma once

//------------ INCLUDES -----------
#include "../IAssetProvider.h"

/**
* @class BinaryFileProvider
* @brief �o�C�i���t�@�C���̓ǂݍ��݂�����@�\������
*/
class BinaryFileProvider : public IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BinaryFileProvider();

	/**
	* �f�t�H���g�f�X�g���N�^
	*/
	~BinaryFileProvider();
	
private:
	/** �t�@�C�����J���Ȃ������ꍇ�Ƀt�@�C�����쐬���邩�ǂ�����\�� */
	bool mbCreateFile;

public:
	/**
	 * @fn GetProviderType
	 * @brief �v���o�C�^�[��Type��Ԃ�
	 * @detail typeid���g�p���ăv���o�C�^�[�̌^��Ԃ��Ă���
	 * @return const std::type_info& �v���o�C�_�[�̌^
	*/
	inline const std::type_info& GetProviderType() const final override;

	/**
	 * @fn Load
	 * @brief �o�C�i���t�@�C����ǂݍ��ޏ���
	 * @param const std::string& (_filePath)
	 * @return std::shared_ptr<IAsset>
	*/
	std::shared_ptr<IAsset> Load(const std::string& _filePath) const override;
	
private:
	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	void Setting() override;
};

//--------- INLINES ---------

inline const std::type_info& BinaryFileProvider::GetProviderType() const
{
	return typeid(BinaryFileProvider);
}
