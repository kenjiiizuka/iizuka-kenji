/**
* @file PlayerTestScene
* @brief PlayerTestScene.h
*/

#pragma once

//---------- INCLUDES -----------
#include "../Scene.h"
#include "../../GameObject/Player/PlayerEditor.h"

/**
* @class PlayerTestScene
* @brief �v���C���[���f�o�b�O�A�e�X�g���邽�߂̃V�[��
*/
class PlayerTestScene : public Scene
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
	*/
	void Update() override;

private:
	/** �v���C���[�G�f�B�^�[ */
	std::shared_ptr<PlayerEditor> mPlayerEditor;


	std::weak_ptr<class EffectComponent> effectComp;
};

