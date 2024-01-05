/**
* @file Bone.h
* @brief Bone�N���X�̒�`
*/


#pragma once
//------------ INCLUDES -----------
#include <memory>
#include <SimpleMath.h>
#include "../Component/TransformComponent/Transform.h"
#include "../../System/AssetSystem/SkeletalMesh/BoneAsset.h"
#include "SkeletalMesh.h"



/**
* @class Bone
* @brief Skeleton���\������{�[���N���X
*/
class Bone
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	Bone();
	
	/**
	* �f�X�g���N�^
	*/
	virtual ~Bone();

protected:
	/** �g�����X�t�H�[�� */
	Transform mTransform;
	
	/** �e�{�[�� */
	std::weak_ptr<Bone> mParentBone;

	/** �q�{�[�� */
	std::vector<std::shared_ptr<Bone>> mChildren;

	/** �{�[���̃A�Z�b�g�f�[�^ */
	std::weak_ptr<BoneAsset> mBoneAsset;

	/** �{�[���s�� */
	DirectX::SimpleMath::Matrix mBoneMatrix;

	/** ���̃{�[���������Ă���X�P���^�����b�V�� */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;

	/** �{�[���̖��O */
	std::string mBoneName;

	/** ���[���h�s�� */
	DirectX::SimpleMath::Matrix mWorldMatrix;

	/** �f�o�b�O�\������ۂ̃{�[���̐F */
	DirectX::SimpleMath::Vector4 mBoneColor;

	/** �f�o�b�O�\������{�[���̑傫�� */
	float mBoneRadius;

private:
	/** �o�C���h�|�[�Y�s�� */
	DirectX::SimpleMath::Matrix mBindPoseMatrix;

	/** �A�j���[�V�����s�� */
	DirectX::SimpleMath::Matrix mAnimationMatrix;

public:
	/**
	 * @fn Initialize
	 * @brief ����������
	 * @detail BoneAsset����{�[���̏����󂯎��K�v�ȏ���������
	 * @param const std::weak_ptr<BoneAsset> (_boneAsset)
	 * @param std::weak_ptr<Bone>            (_parentBone)
	 * @param const size_t                   (_numChildren)
	 * @return void
	*/
	void Initialize(const std::weak_ptr<BoneAsset> _boneAsset, const std::weak_ptr<Bone> _parentBone, const size_t _numChildren);

	/**
	* @fn Draw
	* @brief �{�[���̈ʒu��`�悷��
	* @return void
	*/
	void Draw();

	/**
	 * @fn CalucBoneMatrix
	 * @brief �{�[���s����v�Z����֐�
	 * @param DirectX::SimpleMath::Matrix (_parentBoneMatrix)
	 * @return void
	*/
	virtual void CalcuBindPoseBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity);

	/**
	* @fn CalucAnimatedBoneMatrix
	* @brief �A�j���[�V������K�������{�[���s����v�Z����
	* @param DirectX::SimpleMath::Matrix (_parentBoneMatrix)
	* @return void
	*/
	virtual void CalcuAnimatedBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity);

	/**
	* @fn CalucWorldBoneMatrix
	* @brief ���[���h��Ԃ̃{�[���s����v�Z����
	* @param const DirectX::SimpleMath::Matrix& (_parentBoneMatrix)
	* @return void
	*/
	virtual void CalucWorldBoneMatrix(const DirectX::SimpleMath::Matrix& _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity);

public:
	/**
	* @fn AddChildBone
	* @brief �q�{�[���ǉ�
	* @param const std::shared_ptr<Bone> (_newChildBone)
	* @return void
	*/
	void AddChildBone(const std::shared_ptr<Bone> _newChildBone);

	/**
	 * @fn GetChildBones
	 * @brief �q�{�[���̔z���Ԃ�
	 * @return std::vector<std::shared_ptr<Bone>>
	*/
	inline std::vector<std::shared_ptr<Bone>> GetChildBones() const;

	/**
	 * @fn SetParentBone
	 * @brief �e�{�[�����Z�b�g
	 * @param std::weak_ptr<Bone>&  (_bone)
	 * @return void
	*/
	inline void SetParentBone(std::shared_ptr<Bone>& _bone);

	/**
	* @fn SetChildBones
	* @brief �q�{�[�����Z�b�g����
	* @param std::vector<std::shared_ptr<Bone>> (_childBones)
	* @return void 
	*/
	inline void SetChildBones(std::vector<std::shared_ptr<Bone>>& _childBones);

	/**
	* @fn GetBoneName
	* @brief �{�[���̖��O���擾
	* @return std::string
	*/
	inline std::string GetBoneName() const noexcept;

	/**
	* @fn GetBoneMatrix
	* @brief �{�[���s���Ԃ� �{�[����ԂɂȂ��Ă���̂�SkeletalMesh��World�s��Ƃ����č��W�ϊ�����K�v������
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetBoneMatrix() const noexcept;
	
	/**
	* @fn SetBoneMatrix
	* @brief �{�[���}�g���b�N�X�̃Z�b�^�[
	* @param const DirectX::SimpleMath::Matrix& (_boneMatrix)
	* @return void
	*/
	inline void SetBoneMatrix(const DirectX::SimpleMath::Matrix& _boneMatrix) noexcept;

	/**
	* @fn GetBindPoseMatrix
	* @brief �o�C���h�|�[�Y�s����쐬����
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetBindPoseMatrix() const noexcept;

	/**
	* @fn SetAnimationMatrix
	* @brief �A�j���[�V�����s����Z�b�g����
	* @param const DirectX::SimpleMath::Matrix& (_animationMatrix)
	* @return void
	*/
	inline void SetAnimationMatrix(const DirectX::SimpleMath::Matrix& _animationMatrix) noexcept;

	/**
	* @fn GetBoneWorldMatrix
	* @brief �{�[���̃��[���h�s���Ԃ�
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetBoneWorldMatrix() const noexcept;

};

//----------- INLINES ---------
 
inline std::vector<std::shared_ptr<Bone>> Bone::GetChildBones() const
{
	return mChildren;
}

inline void Bone::SetParentBone(std::shared_ptr<Bone>& _bone) 
{
	mParentBone = _bone;
}

inline void Bone::SetChildBones(std::vector<std::shared_ptr<Bone>>& _childBones)
{
	mChildren = _childBones;
}

inline std::string Bone::GetBoneName() const noexcept
{
	return mBoneName;
}

inline DirectX::SimpleMath::Matrix Bone::GetBoneMatrix() const noexcept
{
	return mBoneMatrix;
}

inline void Bone::SetBoneMatrix(const DirectX::SimpleMath::Matrix& _boneMatrix) noexcept
{
	mBoneMatrix = _boneMatrix;
}

inline DirectX::SimpleMath::Matrix Bone::GetBindPoseMatrix() const noexcept
{
	return mBindPoseMatrix;
}

inline void Bone::SetAnimationMatrix(const DirectX::SimpleMath::Matrix& _animationMatrix) noexcept
{
	mAnimationMatrix = _animationMatrix;
}

inline DirectX::SimpleMath::Matrix Bone::GetBoneWorldMatrix() const noexcept
{
	return mWorldMatrix;
}
