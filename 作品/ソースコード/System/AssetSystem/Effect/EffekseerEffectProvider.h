/**
* @file EffekseerEffectProvider.h
* @brief EffekseerEffectProvider�N���X�̒�`
*/

#pragma once

//----------- INCLUDES -----------
#include "../IAssetProvider.h"

/**
* @class EffekseerEffectProvider
* @brief �G�t�F�N�V�A�̃G�t�F�N�g��ǂݍ��ރN���X
*/
class EffekseerEffectProvider : public IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	EffekseerEffectProvider();

	/**
	* �f�X�g���N�^
	*/
	~EffekseerEffectProvider();

private:
	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	virtual void Setting();

	/**
	* @fn LoadBase
	* @brief �A�Z�b�g�ǂݍ��݂����ۂɎ��s���鏈��
	* @detail �ǂݍ��݂���������ƃL���b�V���}�b�v�ɓo�^����
	* @param const std::string& _filePath
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const;

public:
	/**
	* @fn GetProviderType
	* @brief �v���o�C�^�[��Type��Ԃ�
	* @detail typeid���g�p���ăv���o�C�^�[�̌^��Ԃ��Ă���
	* @return std::type_info �v���o�C�_�[�̌^
	*/
	inline virtual const std::type_info& GetProviderType() const;

};

//---------- INLINES ---------

inline const std::type_info& EffekseerEffectProvider::GetProviderType() const
{
	return typeid(EffekseerEffectProvider);
}
