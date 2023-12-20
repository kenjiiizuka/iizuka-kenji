/**
* @file Bone.h
* @brief Bone�N���X�̒�`
*/

#pragma once

//------------ INCLUDES -----------
#include <memory>
#include <vector>
#include <string>
#include <SimpleMath.h>

/**
* @class Bone
* @brief Bone�̃f�[�^������
* @detail �e�{�[���q�{�[���ւ̃|�C���^������
*/
class BoneAsset
{
	/**---------------------------------------------------------------------------------
	* SkeletalMeshProvider�̂݃f�[�^���Z�b�g�ł���悤�ɂ��邽�߂Ƀt�����h�w������Ă���
	*/
	friend class SkeletalMeshProvider;

public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BoneAsset();

	/**
	* �f�X�g���N�^
	*/
	~BoneAsset();

private:
	/** �{�[���̖��O */
	std::string mBoneName;

	/** �{�[���C���f�b�N�X */
	size_t mIndex;

	/** �e�{�[���̃|�C���^ */
	std::weak_ptr<BoneAsset> mParentBone;

	/** �q�{�[���̃|�C���^ */
	std::vector<std::shared_ptr<BoneAsset>> mChildBones;

	/** �g�����X�t�H�[���s�� */
	DirectX::SimpleMath::Matrix mTransformationMatrix;

	/** �e����^���钸�_�ւ̃I�t�Z�b�g�s�� */
	DirectX::SimpleMath::Matrix mBindPoseMatrix;

public:
	/**
	* @fn GetBoneName
	* @brief �{�[���̖��O��Ԃ��֐�
	* @return std::string
	*/
	inline std::string GetBoneName()const noexcept;

	/**
	* @fn GetBoneIndex
	* @brief �{�[���̃C���f�b�N�X��Ԃ�
	* @return size_t
	*/
	inline size_t GetBoneIndex() const noexcept;

	/**
	* @fn GetParentBoneAsset
	* @brief �e�̃{�[���A�Z�b�g��Ԃ�
	* @return std::weak_ptr<BoneAsset>
	*/
	inline std::weak_ptr<BoneAsset> GetParentBoneAsset() const;

	/**
	* @fn GetChildBones
	* @brief �q�{�[����Ԃ�
	* @return std::vector<std::weak_ptr<BoneAsset>>
	*/
	inline std::vector<std::shared_ptr<BoneAsset>> GetChildBones() const;

	/**
	* @fn HasChildren
	* @brief �q�{�[���������Ă��邩
	* @return bool true �����Ă��� : false �����Ă��Ȃ�
	*/
	inline bool HasChildren() const noexcept;

	/**
	 * @fn GetTransformationMatrix
	 * @brief �{�[���̃g�����X�t�H�[���}�g���b�N�X��Ԃ�
	 * @return DirectX::SimpleMath::Matrix 
	*/
	inline DirectX::SimpleMath::Matrix GetTransformationMatrix() const noexcept;

	/**
	* @fn GetBindPoseMatrix
	* @brief �o�C���h�|�[�Y�s���Ԃ�
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetBindPoseMatrix() const noexcept;
};

//------------ INLINES -----------

inline std::string BoneAsset::GetBoneName() const noexcept
{
	return mBoneName;
}

inline size_t BoneAsset::GetBoneIndex() const noexcept
{
	return mIndex;
}

inline std::weak_ptr<BoneAsset> BoneAsset::GetParentBoneAsset() const
{
	return mParentBone;
}

inline std::vector<std::shared_ptr<BoneAsset>> BoneAsset::GetChildBones() const
{
	return mChildBones;
}

inline bool BoneAsset::HasChildren() const noexcept
{
	return !mChildBones.empty();
}

inline DirectX::SimpleMath::Matrix BoneAsset::GetTransformationMatrix() const noexcept
{
	return mTransformationMatrix;
}

inline DirectX::SimpleMath::Matrix BoneAsset::GetBindPoseMatrix() const noexcept
{
	return mBindPoseMatrix;
}


