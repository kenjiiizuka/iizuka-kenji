/**
* @file PlayerAttackCapsuleCollisionComponent.h
* @brief PlayerAttackCapsuleCollisionComponentクラスの定義
*/

#pragma once

//------------ INCLUDES -----------
#include "CapsuleCollisionComponent.h"

/**
* @class PlayerAttackCapsuleCollisionComponent
* @brief プレイヤーの武器に付ける攻撃用のコリジョン
*/
class PlayerAttackCapsuleCollisionComponent : public CapsuleCollisionComponent
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	PlayerAttackCapsuleCollisionComponent();

	/**
	* デストラクタ
	*/
	~PlayerAttackCapsuleCollisionComponent();

private:
	/** 攻撃ダメージ */
	float mDamage;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @param const float (_height)
	* @param const float (_radius)
	* @param const float (_damage)
	* @return void
	*/
	void Init(const float _height, const float _radius, const float _damage);

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn ExecuteBeginHit
	* @brief オーナーのBeginHit関数を実行する関数
	* @detail 連続で当たることを防ぐために、最初に当たったコリジョンをBeginHit関数に渡すだけにしている
	* @return void
	*/
	void ExecuteBeginHit() override;

};

