/**
* @file RingBlockObject
* @brief RingBlockObject.h
*/

#pragma once

//----------- INCLUDES ---------
#include "../GameObject.h"

/**
* @class RingBlockObject
* @brief 戦闘エリア外に出ないようにするためのオブジェクト
*/
class CircleBlockObject : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	CircleBlockObject();

	/**
	* デストラクタ
	*/
	~CircleBlockObject();

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	void Init() override;

private:
	/** リングの半径 */
	float mRingRadius;

};

