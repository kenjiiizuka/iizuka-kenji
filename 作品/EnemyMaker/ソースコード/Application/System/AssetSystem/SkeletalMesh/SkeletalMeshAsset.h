/**
* @file SkeletalMeshAsset.h
* @brief SkeletalMeshAsset�N���X�̒�`
*/


#pragma once


//---------- INCLUDES ---------
#include <SimpleMath.h>
#include <memory>
#include <unordered_map>
#include <string>
#include "../IAsset.h"
#include "../../RendererSystem/VisualEntity/VisualEntityData.h"

//--------- �O���錾 --------
class BoneAsset;

/**
* @class SkeletalMeshAsset
* @brief �X�P���^�����b�V���A�Z�b�g�N���X
*/
class SkeletalMeshAsset : public IAsset
{
	/**
	*  SkeletalMeshAsset�̒��_�f�[�^��A�{�[���f�[�^�ɑ΂���SkeletalMeshProvider�݂̂�
	*�@�A�N�Z�X�ł���悤�ɂ��邽�߃t�����h�w��
	*/
	friend class SkeletalMeshProvider;
	
public:
	/**
	* @struct Vertex
	* @brief SkeletalMesh�̒��_�f�[�^�\����
	*/
	struct Vertex
	{
		DirectX::SimpleMath::Vector3 mPosition; /**< ���_�ʒu */
		DirectX::SimpleMath::Vector3 mNormal;   /**< �@�� */
		DirectX::SimpleMath::Vector2 mUV;       /**< UV */
		DirectX::SimpleMath::Vector4 mColor;    /**< ���_�J���[ */
		float mWeights[4];                      /**< �Ή����Ă���{�[���ւ̏d�� */
		uint32_t mBoneIndices[4];                 /**< �Ή����Ă���{�[���C���f�b�N�X */

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Vertex();

		/**
		* �R���X�g���N�^
		* 
		* @param const DirectX::SimpleMath::Vector3 (_position)
		* @param const DirectX::SimpleMath::Vector3 (_normal)
		* @param const DirectX::SimpleMath::Vector2 (_uv)
		* @param const DirectX::SimpleMath::Vector4 (_color)
		*/
		Vertex(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _normal, const DirectX::SimpleMath::Vector2 _uv, const DirectX::SimpleMath::Vector4 _color);
	};

public:
	/**
	 * �f�t�H���g�R���X�g���N�^
	*/
	SkeletalMeshAsset();

	/**
	 * �f�X�g���N�^
	*/
	~SkeletalMeshAsset();

private:
	/** ���_�f�[�^ �������b�V���̉\��������̂�std::vector<std::vector<Vertex>>�^ */
	std::vector<std::vector<Vertex>> mVertices;

	/** �C���f�b�N�X�o�b�t�@�쐬�̂��߂̃f�[�^ �������b�V���̉\��������̂�std::vector<std::vector<Vertex>>�^ */
	std::vector<std::vector<uint32_t>> mIndices;

	/** �}�e���A���f�[�^�@���b�V�����ƂɈ��*/
	std::vector<VisualEntityData::Material> mMaterials;

	/** �{�[���f�[�^ �K�w�\���ɂȂ��Ă���̂Őe�{�[���̃|�C���^���炷�ׂẴ{�[���ɃA�N�Z�X�ł��� */
	std::shared_ptr<BoneAsset> mRootBone;

	/** �{�[����o�^����Map ���O�Ń{�[�����擾�����肷��ꍇ�Ɏ擾���₷���悤�ɂ��邽�߂̕ϐ� */
	std::unordered_map<std::string, std::weak_ptr<BoneAsset>> mBoneMap;

public:
	/**
	* @fn GetAssetType
	* @brief �A�Z�b�g�̃^�C�v��Ԃ�
	* @detail typeid���g�p���Č^���ʂ����Ă���
	* @return const std::type_info&
	*/
	inline const std::type_info& GetAssetType() const noexcept override;

	/**
	* @fn GetRootBone
	* @brief GetRootBoneAsset
	* @return std::weak_ptr<BoneAsset> ���[�g�{�[���A�Z�b�g�̎�Q��
	*/
	inline std::weak_ptr<BoneAsset> GetRootBoneAsset() const;

	/**
	* @fn GetVertices
	* @brief ���_�f�[�^��Ԃ�
	* @return std::vector<std::vector<Vertex>>
	*/
	inline std::vector<std::vector<Vertex>> GetVertices() const;

	/**
	* @fn GetIndices
	* @brief �C���f�b�N�X�f�[�^��Ԃ�
	* @return std::vector<std::vector<uint32_t>>
	*/
	inline std::vector<std::vector<uint32_t>> GetIndices() const;

	/**
	* @fn GetMaterials
	* @brief �}�e���A����Ԃ�
	* @return std::vector<VisualEntityData::Material>
	*/
	inline std::vector<VisualEntityData::Material> GetMaterials() const;
};

//-------------- INLINES -------------

inline const std::type_info& SkeletalMeshAsset::GetAssetType() const noexcept
{
	return typeid(SkeletalMeshAsset);
}

inline std::weak_ptr<BoneAsset> SkeletalMeshAsset::GetRootBoneAsset() const
{
	return mRootBone;
}

inline std::vector<std::vector<SkeletalMeshAsset::Vertex>> SkeletalMeshAsset::GetVertices() const
{
	return mVertices;
}

inline std::vector<std::vector<uint32_t>> SkeletalMeshAsset::GetIndices() const
{
	return mIndices;
}

inline std::vector<VisualEntityData::Material> SkeletalMeshAsset::GetMaterials() const
{
	return mMaterials;
}

