/**
* @file OutlineSkeletalMeshVertexShader.h
* @brief OutlineSkeletalMeshVertexShader�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ----------
#include "VertexShader.h"

//-------- �O���錾 ----------
class Skeleton;

/**
* @class OutlineSkeletalMeshVertexShader
* @brief SkeletalMesh�̃A�E�g���C����`�悷��V�F�[�_�[
*/
class OutlineSkeletalMeshVertexShader : public VertexShader
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param VisualEntity* (_entity)
	*/
	OutlineSkeletalMeshVertexShader(VisualEntity* _entity);

	/**
	* �f�X�g���N�^
	*/
	~OutlineSkeletalMeshVertexShader();

	/**
	* @fn UpdateBuffer
	* @brief �萔�o�b�t�@�\�̍X�V����
	* @param uint8_t _dataID 
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

private:
	/** �\������SkeletalMesh�̃X�P���g�� */
	std::weak_ptr<Skeleton> mSkeleton;

	/** �A�E�g���C���̑��� */
	float mOutlineThickness;

public:
	/**
	* @fn SetSkeleton
	* @brief �X�P���g���̃Z�b�g
	* @return void
	*/
	inline void SetSkeleton(std::shared_ptr<Skeleton> _skeleton);

};

//--------- INLINES ---------

inline void OutlineSkeletalMeshVertexShader::SetSkeleton(std::shared_ptr<Skeleton> _skeleton)
{
	mSkeleton = _skeleton;
}
