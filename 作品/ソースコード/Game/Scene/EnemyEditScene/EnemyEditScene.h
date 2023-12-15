/**
* @file EnemyEditScene.h
* @brief EnemyEditScene�N���X�̒�`
*/

#pragma once

//----------- INCLUDES --------------
#include "../Scene.h"
#include "../../GameObject/Enemy/BearEnemyEditor.h"

/**
* @class EnemyEditScene
* @brief �G�l�~�[��ҏW����V�[��
*/
class EnemyEditScene : public Scene
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	EnemyEditScene();

	/**
	* �f�X�g���N�^
	*/
	~EnemyEditScene();

private:
	/** �F�̓G�̃G�f�B�^�[ */
	std::shared_ptr<BearEnemyEditor> mEditor;

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

	/**
	* @fn Uninitialize
	* @brief �I������
	* @return void
	*/
	void Uninitialize() override;

};

