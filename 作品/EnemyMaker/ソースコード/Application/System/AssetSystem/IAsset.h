#pragma once
/**
* @file IAsset.h
* @brief IAsset�N���X�̒�`
*/

//--------- INCLUDES --------
#include <typeinfo>

/**
* @class IAsset
* @brief �A�Z�b�g�̃C���^�[�t�F�[�X�N���X
*/
class IAsset
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	IAsset()
	{
		// �����Ȃ�
	}

	/**
	* �f�t�H���g�f�X�g���N�^
	*/
	virtual ~IAsset()
	{
		// �����Ȃ�
	}

public:
	/**
	* @fn GetAssetType
	* @brief �A�Z�b�g�̃^�C�v��Ԃ�
	* @detail typeid���g�p���Č^���ʂ����Ă���
	* @return const std::type_info& 
	*/
	inline virtual const std::type_info& GetAssetType() const noexcept = 0;

};

