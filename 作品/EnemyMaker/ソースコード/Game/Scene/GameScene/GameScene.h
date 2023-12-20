/**
* @file GameScene.h
* @brief GameScene�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ---------
#include "../Scene.h"
#include "BattleManager.h"

//-------- �O���錾 --------
class Fade;

/**
* @class GameScene
* @brief �Q�[���V�[��
*/
class GameScene final : public Scene
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	GameScene();

	/**
	* �f�X�g���N�^
	*/
	~GameScene();

private:
	/** �o�g���}�l�[�W���[ */
	std::shared_ptr<BattleManager> mBattleManager;

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

private:
	/** �t�F�[�h�p�̃I�u�W�F�N�g */
	std::weak_ptr<Fade> mFade;

	/** �V�[���J�ڂ̓��͂��������� */
	bool mbTransitionScene;
};

