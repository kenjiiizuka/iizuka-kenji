/**
* @file AnimationTestObject.h
* @brief AnimationTestObject�N���X�̒�`
*/

#pragma once

//-------- INCLUDES ----------
#include "../GameObject.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"

/**
* @class AnimationTestObject
* @brief �A�j���[�V�����e�X�g�p�I�u�W�F�N�g
* @detail �f�o�b�O�A�e�X�g
*/
class AnimationTestObject : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AnimationTestObject();

	/**
	* �f�X�g���N�^
	*/
	~AnimationTestObject();

private:
	/** �X�P���^�����b�V���R���|�[�l���g */
	std::weak_ptr<SkeletalMeshComponent> mSkeletalMesh;


public:
	/**
	* @fn Init
	* @brief ����������
	* @return void
	*/
	void Init() override;

};

