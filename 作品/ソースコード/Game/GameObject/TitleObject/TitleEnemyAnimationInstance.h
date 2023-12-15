/**
* @file TitleEnemyAnimationInstance.h
* @brief TitleEnemyAnimationInstance�N���X�̒�`
*/

#pragma once

//------------ INCLUDES ------------
#include "../../Component/SkeletalMeshComponent/AnimationInstance.h"

/**
* @class TitleEnemyAnimationInstance
* @brief �^�C�g���p�̃G�l�~�[�̃A�j���[�V�����C���X�^���X
*/
class TitleEnemyAnimationInstance : public AnimationInstance
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	TitleEnemyAnimationInstance();

	/**
	* �f�X�g���N�^
	*/
	~TitleEnemyAnimationInstance();

private:
	/** ����傫�������A�j���[�V�������Đ�����m�� */
	float mBreathProbability;

public:
	/**
	 * @fn�@AnimationInit
	 * @brief ����������
	 * @return void
	*/
	virtual void AnimationInit();

	/**
	 * @fn�@AnimationUpdate
	 * @brief Animation�̍X�V����
	 * @return void
	*/
	virtual void AnimationUpdate();


};

