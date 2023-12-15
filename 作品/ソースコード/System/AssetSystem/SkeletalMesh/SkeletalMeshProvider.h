/**
* @file SkeletalMeshProvider.h
* @brief SkeletalMeshProvider�N���X�̒�`
*/

#pragma once

//----------- INCLUDES -----------
#include <assimp/scene.h>
#include <memory>
#include <SimpleMath.h>
#include "../IAssetProvider.h"
#include "SkeletalMeshAsset.h"


//---------- �O���錾 -----------
class BoneAsset;

/**
* @class SkeletalMeshProvider
* @brief SkeletalMesh�̓ǂݍ�������N���X
*/
class SkeletalMeshProvider : public IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SkeletalMeshProvider();

	/**
	* �f�X�g���N�^
	*/
	~SkeletalMeshProvider();

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


private:
	/**
	* @fn LoadVertexData
	* @brief ���_�f�[�^�̓ǂݍ���
	* @param  std::shared_ptr<SkeletalMeshAsset>&      (_skeletalMesh)
	* @param const aiMesh&                             (_aiMesh)
	* @return void
	*/
	void LoadVertexData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiMesh& _aiMesh) const;

	/**
	* @fn SetWeightAndBoneIndex
	* @brief �X�L���E�F�C�g�ƃ{�[���C���f�b�N�X�𒸓_�f�[�^�ɃZ�b�g����
	* @param SkeletalMeshAsset::Vertex& (_vertex)
	* @param const float                (_weight)
	* @param const int16_t              (_boneIndex)
	* @return void
	*/
	void SetWeightAndBoneIndex(SkeletalMeshAsset::Vertex& _vertex, const float _weight, const int16_t _boneIndex) const;

	/**
	* @fn LoadMaterialData
	* @brief �}�e���A���f�[�^�̓ǂݍ���
	* @param  std::shared_ptr<SkeletalMeshAsset>&      (_skeletalMesh)
	* @param const aiMaterial&                         (_aiMaterial)
	* @param const std::string&                        (_filePath)
	* @return void
	*/
	void LoadMaterialData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiMaterial& _aiMaterial, const std::string& _filePath) const;

	/**
	* @fn LoadBoneData
	* @brief �{�[���f�[�^�̓ǂݍ���
	* @param std::shared_ptr<SkeletalMeshAsset>&       (_skeletalMesh)
	* @param aiBone**                                  (_aiBones)
	* @param const size_t                              (_boneNum)
	* @return void
	*/
	void LoadBoneData(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, aiBone** _aiBones, const size_t _boneNum) const;

	/**
	* @fn LoadNode
	* @brief �m�[�h�ǂݍ���
	* @param std::shared_ptr<SkeletalMeshAsset>& (_skeletalMesh)
	* @param const aiNode*                       (_rootNode)
	* @return void
	*/
	void LoadNode(std::shared_ptr<SkeletalMeshAsset>& _skeletalMesh, const aiNode* _rootNode) const;

	/**
	* @fn ReadNode
	* @brief �m�[�h��ǂݎ��֐�
	* @param std::shared_ptr<BoneAsset>& (_boneAsset)
	* @param const aiNode&               (_aiNode)
	* @return void
	*/
	void ReadNode(std::shared_ptr<BoneAsset>& _boneAsset, const aiNode& _aiNode) const;

	/**
	* @fn RegisterBoneMapAndSetBoneIndex
	* @brief �}�b�v�Ƀ{�[����o�^���A�{�[���ɃC���f�b�N�X���Z�b�g����֐�
	* @detail �{�[�������[�g���炷�ׂĎQ�Ƃ��邽�߂ɂ͍ċN�̏������K�v�ł��邽�߁A�������x�I�ɏd����
	*         �ċN�֐����g�p����񐔂����炷���߂ɁAMap�ɓo�^�ƃC���f�b�N�X�̃Z�b�g�𓯂��֐��Ȃ��ōs��
	* @param std::shared_ptr<SkeletalMeshAsset>& (_skeletalMeshAsset)
	* @param const std::shared_ptr<BoneAsset>&   (_boneAsset)
	* @return void
	*/
	void RegisterBoneMapAndSetBoneIndex(std::shared_ptr<SkeletalMeshAsset>& _skeletalMeshAsset, const std::shared_ptr<BoneAsset>& _boneAsset) const;

	/**
	* @fn ConvAiMatrix
	* @brief Assimp�̍s���DirectX::SimpleMath::Matrix�ɕϊ�����
	* @param const aiMatrix4x4& _aiMatrix
	* @return DirectX::SimpleMath::Matrix
	*/
	DirectX::SimpleMath::Matrix ConvAiMatrix(const aiMatrix4x4& _aiMatrix) const noexcept;

protected:
	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	void Setting() override;
};

//---------- INLINES -----------

inline const std::type_info& SkeletalMeshProvider::GetProviderType() const
{
	return typeid(SkeletalMeshProvider);
}

