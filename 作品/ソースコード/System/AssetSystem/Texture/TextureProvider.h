/**
* @file TextureProvider.h
* @brief TextureProvider�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ------------
#include "../IAssetProvider.h"


//---------- �O���錾 -----------
class Texture;

/**
* @class TextureProvider
* @brief �e�N�X�`����ǂݍ��ރN���X
*/
class TextureProvider : public IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	TextureProvider();

	/**
	* �f�X�g���N�^
	*/
	~TextureProvider();

private:
	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	virtual void Setting() {};

	/**
	* @fn LoadBase
	* @brief �A�Z�b�g�ǂݍ��݂����ۂɎ��s���鏈��
	* @detail �ǂݍ��݂���������ƃL���b�V���}�b�v�ɓo�^����
	* @param const std::string& (_filePath)
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const;

	/**
	* @fn LoadByWICTexture
	* @brief WIC�ɂ���ăe�N�X�`����ǂݍ��ފ֐�
	* @param std::string_view          (_filePath)
	* @param std::shared_ptr<Texture>& (_texture)
	* @return void
	*/
	bool LoadByWICTexture(std::string_view _filePath, std::shared_ptr<Texture>& _texture) const;

	/**
	* @fn CreateTextureFromTGA
	* @brief TGA�e�N�X�`�����쐬����
	* @param std::string_view          (_filePath)
	* @param std::shared_ptr<Texture>& (_texture)
	* @return void
	*/
	bool CreateTextureFromTGA(std::string_view _filePath, std::shared_ptr<Texture>& _texture) const;

public:
	/**
	* @fn GetProviderType
	* @brief �v���o�C�^�[��Type��Ԃ�
	* @detail typeid���g�p���ăv���o�C�^�[�̌^��Ԃ��Ă���
	* @return std::type_info �v���o�C�_�[�̌^
	*/
	inline virtual const std::type_info& GetProviderType() const;

};

//----------- INLINES ----------

inline const std::type_info& TextureProvider::GetProviderType() const
{
	return typeid(TextureProvider);
}


