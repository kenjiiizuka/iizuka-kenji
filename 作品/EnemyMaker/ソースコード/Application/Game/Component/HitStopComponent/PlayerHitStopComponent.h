/**
* @file PlayerHitStopComponent.h
* @brief PlayerHitStopComponentクラスの定義
*/
#pragma once

//----------- INCLUDES -------------
#include "HitStopComponent.h"

/**
* @class PlayerHitStopComponent
* @brief プレイヤー専用のヒットストップコンポーネント
* @detail 与えたダメージによってヒットストップの強さ、時間を設定する
*         使用する際は、SetAttackDamage関数で与えたダメージを設定してからHitStop関数を使用すること
*         ダメージが設定されていない場合はヒットストップがかからない
*/
class PlayerHitStopComponent : public HitStopComponent
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	PlayerHitStopComponent();

	/**
	* デストラクタ
	*/
	~PlayerHitStopComponent();

private:
	/** 敵に与えるダメージ */
	float mDamage;

	/** ヒットストップの重み　ダメージ * 重みでヒットストップの時間を決める */
	float mHitStopSecondWeight;

public:
	/**
	* @HitStop
	* @brief ヒットストップをかける関数
	* @detail 連続使用するとヒットストップがかかり続けるので注意
	*         設定されているダメージからヒットストップの強さ、長さを設定する
	* @return void
	*/
	void HitStop();

	/**
	* @fn SetAttackDamage
	* @brief ヒットストップの強さ、時間を設定するために敵に与えるダメージ数を設定する関数
	* @param const float (_damage)
	* @return void
	*/
	inline void SetAttackDamage(const float _damage);
};

//-------- INLINES ---------

inline void PlayerHitStopComponent::SetAttackDamage(const float _damage)
{
	mDamage = _damage;
}