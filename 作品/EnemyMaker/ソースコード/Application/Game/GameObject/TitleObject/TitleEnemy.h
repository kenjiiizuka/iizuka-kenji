/**
* @file TitleEnemy.h
* @brief TitleEnemy�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ---------
#include "../GameObject.h"

/**
* @class TitleEnemy
* @brief �^�C�g���p�̃G�l�~�[
*/
class TitleEnemy : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	TitleEnemy();

	/**
	* �f�X�g���N�^
	*/
	~TitleEnemy();

public:
	/**
	* @fn Init
	* @brief ����������
	* @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief �X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;
};

