#pragma once
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
	void InitSprite() override;
	

};

