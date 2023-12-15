/**
* @file StaticMeshProvider.h
* @brief StaticMeshProvider�N���X�̒�`
*/

#pragma once

//--------------- INCLUDES ------------
#include <assimp/scene.h>
#include "../IAssetProvider.h"

//------------ INCLUDES -------------
class StaticMeshAsset;

/**
* @class StaticMeshProvider
* @brief �X�^�e�B�b�N���b�V���̓ǂݍ��݂�����N���X
*/
class StaticMeshProvider final : public IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	StaticMeshProvider();

	/**
	* �f�X�g���N�^
	*/
	~StaticMeshProvider();

public:
	/**
	 * @fn GetProviderType
	 * @brief �v���o�C�^�[��Type��Ԃ�
	 * @detail typeid���g�p���ăv���o�C�^�[�̌^��Ԃ��Ă���
	 * @return std::type_info �v���o�C�_�[�̌^
	*/
	inline virtual const std::type_info& GetProviderType() const override;

	/**
	 * @fn Load
	 * @brief �A�Z�b�g�ǂݍ��݂����ۂɎ��s���鏈��
	 * @detail �ǂݍ��݂���������ƃL���b�V���}�b�v�ɓo�^����
	 * @param const std::string& _filePath
	 * @return std::shared_ptr<IAsset>
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const override;

protected:
	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	void Setting() override;

private:
	/**
	* @fn LoadVertexData
	* @brief ���_�f�[�^�̓ǂݍ���
	* @param std::shared_ptr<StaticMeshAsset>& (_staticMeshAsset)
	* @param const aiMesh&                     (_aiMesh)
	* @return void
	*/
	void LoadVertexData(std::shared_ptr<StaticMeshAsset>& _staticMeshAsset, const aiMesh& _aiMesh) const;

	/**
	* @fn LoadMaterialData
	* @brief �}�e���A���f�[�^�̓ǂݍ���
	* @param  std::shared_ptr<StaticMeshAsset>&        (_staticMesh)
	* @param const aiMaterial&                         (_aiMaterial)
	* @param const std::string&                        (_filePath)
	* @return void
	*/
	void LoadMaterialData(std::shared_ptr<StaticMeshAsset>& _staticMesh, const aiMaterial& _aiMaterial, const std::string& _filePath) const;

};

//--------- INLINES ---------

inline const std::type_info& StaticMeshProvider::GetProviderType() const
{
	return typeid(StaticMeshProvider);
}
