/**
* @file AnimationInstanceTest.h
* @brief AnimationInstanceTest�N���X�̒�`
*/

#pragma once

//------------ INCLUDES -----------
#include "../../Component/SkeletalMeshComponent/AnimationInstance.h"

/**
* @class AnimationInstanceTest
* @brief �A�j���[�V�����e�X�g�p�̃A�j���[�V�����C���X�^���X
*/
class AnimationInstanceTest : public AnimationInstance
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AnimationInstanceTest();

	/**
	* �f�X�g���N�^
	*/
	~AnimationInstanceTest();

public:
	/**
	 * @fn�@AnimationInit
	 * @brief ����������
	 * @return void
	*/
	virtual void AnimationInit() override;

	/**
	 * @fn�@AnimationUpdate
	 * @brief Animation�̍X�V����
	 * @return void
	*/
	virtual void AnimationUpdate();

};

