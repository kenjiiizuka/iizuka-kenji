#pragma once

/**
* @file IDamageAble.h
* @brief IDamageAbleクラスの定義 
*/

/** ダメージのやり取りをするためのインターフェースクラス */
class IDamageAble
{
public:
	virtual void TakenDamage(float _damage) = 0;

};

