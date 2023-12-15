/**
* @file EffekseerTestScene.h
* @brief EffekseerTestScene�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include "Scene.h"

/**
* class EffekseerTestScene
* @brief �G�t�F�N�V�A�����e�X�g�V�[��
*/
class EffekseerTestScene : public Scene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

	std::weak_ptr<class EffectComponent> effectComp;

};

