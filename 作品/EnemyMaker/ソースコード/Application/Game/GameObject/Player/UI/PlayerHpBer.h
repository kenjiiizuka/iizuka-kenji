/**
* @file PlayerHpBer.h
* @brief PlayerHpBer�N���X�̒�`
*/

#pragma once

//-------- INCLUDES --------
#include "../../HpBer/HpBer.h"

/**
* @class PlayerHpBer
* @ brief �v���C���[��HP�o�[
*/
class PlayerHpBer : public HpBer
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	PlayerHpBer();

	/**
	* �f�X�g���N�^
	*/
	~PlayerHpBer();

private:

	/**
	* @fn InitSprite
	* @brief �g�p����X�v���C�g�̏�����
	* @return void
	*/
	void InitSprite() override;
};

