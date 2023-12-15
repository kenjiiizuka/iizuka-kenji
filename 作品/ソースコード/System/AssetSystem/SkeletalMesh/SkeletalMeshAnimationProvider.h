/**
* @file SkeletalMeshAnimationProvider
* @brief SkeletalMeshAnimationProvider�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ---------------
#include "../IAssetProvider.h"


/**
* @class SkeletalMeshAnimationProvider
* @brief �X�P���^�����b�V���A�j���[�V�����̓ǂݍ��݂�����N���X
*/
class SkeletalMeshAnimationProvider final :  public IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SkeletalMeshAnimationProvider();

	/**
	* �f�X�g���N�^
	*/
	~SkeletalMeshAnimationProvider();

public:	
	/**
	 * @fn Load
	 * @brief �o�C�i���t�@�C����ǂݍ��ޏ���
	 * @param const std::string& (_filePath)
	 * @return std::shared_ptr<IAsset>
	*/
	std::shared_ptr<IAsset> Load(const std::string& _filePath) const override;

	/**
	 * @fn GetProviderType
	 * @brief �v���o�C�^�[��Type��Ԃ�
	 * @detail typeid���g�p���ăv���o�C�^�[�̌^��Ԃ��Ă���
	 * @return std::type_info �v���o�C�_�[�̌^
	*/
	inline virtual const std::type_info& GetProviderType() const override;

protected:
	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	void Setting();
	
};

//--------- INLINES ---------

inline const std::type_info& SkeletalMeshAnimationProvider::GetProviderType() const
{
	return typeid(SkeletalMeshAnimationProvider);
}


