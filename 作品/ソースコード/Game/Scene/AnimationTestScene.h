/**
* @file AnimationTestScene.h
* @brief AnimationTestScene�N���X�̍쐬
*/

#pragma once

//------------ INCLUDES ------------
#include "Scene.h"

/**
* @fn AnimationTestScene
* @brief �A�j���[�V�����e�X�g�p�̃V�[��
*/
class AnimationTestScene : public Scene
{
public:
	/**
	* @fn Initialize
	* @brief ����������
	* @return void
	*/
	void Initialize() override;

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update() override;

};

