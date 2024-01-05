#pragma once
#include "../../HpBer/HpBer.h"

/**
* @class PlayerHpBer
* @ brief プレイヤーのHPバー
*/
class PlayerHpBer : public HpBer
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	PlayerHpBer();

	/**
	* デストラクタ
	*/
	~PlayerHpBer();

private:
	void InitSprite() override;
	

};

