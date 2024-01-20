/**
* @file Socket.h
* @brief Socket�N���X�̒�`
*/

#pragma once

//------------ INCLUDES ------------
#include <string>
#include "Bone.h"


/**
* @class Socket
* @brief �A�^�b�`�|�C���g�Ƃ��Ďg�p����Skeleton�ɒǉ����镨
*/
class Socket : public Bone
{
public:
	/**
	 * �f�t�H���g�R���X�g���N�^
	*/
	Socket();

	/**
	 * �f�X�g���N�^
	*/
	~Socket();

private:
	/** �g�����X�t�H�[���[�V�����s�� �e�{�[������̈ʒu������ */
	DirectX::SimpleMath::Matrix mTransformation;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @param const Transform&      (_transform)
	* @param const std::string&    (_socketName)
	* @param const std::shared_ptr (_parentBone)
	* @return void
	*/
	void Initialize(const Transform& _transform, const std::string& _socketName, const std::shared_ptr<Bone> _parentBone);
	
	/**
	 * @fn CalucBoneMatrix
	 * @brief �{�[���s����v�Z����֐�
	 * @param DirectX::SimpleMath::Matrix (_parentBoneMatrix)
	 * @return void
	*/
	void CalcuBindPoseBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity) override;

	/**
	* @fn CalucAnimatedBoneMatrix
	* @brief �A�j���[�V������K�������{�[���s����v�Z����
	* @param DirectX::SimpleMath::Matrix (_parentBoneMatrix)
	* @return void
	*/
	void CalcuAnimatedBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity) override;

public:
	/** 
	* @fn SetTransform
	* @brief �g�����X�t�H�[���̃Z�b�^�[
	* @param const Transform& (_transform)
	* @return void
	*/
	inline void SetTransform(const Transform& _transform) noexcept;

	/**
	* @fn GetTransform
	* @brief �g�����X�t�H�[���̃Q�b�^�[
	* @return Transform 
	*/
	inline Transform GetTransform() const noexcept;
};

//-------------- INLINES --------------

inline void Socket::SetTransform(const Transform& _transform) noexcept
{
	mTransform = _transform;
}

inline Transform Socket::GetTransform() const noexcept
{
	return mTransform;
}


