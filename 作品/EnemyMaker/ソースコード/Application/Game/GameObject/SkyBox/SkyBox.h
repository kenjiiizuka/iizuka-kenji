/**
* @file SkyBox
* @brief SkyBox�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ----------
#include "../GameObject.h"

/**
* @class SkyBox
* @brief SkyBox�I�u�W�F�N�g
*/
class SkyBox : public GameObject
{
public:
	/**
	* �R���X�g���N�^
	*/
	SkyBox();

	/**
	* @fn Init
	* @brief ����������
	* @return void
	*/
	void Init() override;
};

