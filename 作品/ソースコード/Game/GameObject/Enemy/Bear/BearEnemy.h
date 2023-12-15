/**
* @file  BearEnemy.h
* @brief BearEnemyクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "../EnemyBase.h"


//--------- 前方宣言 ---------
class EnemyWeapon;
class CapsuleCollisionComponent;

/**
* @class BearEnemy
* @brief 熊の敵
*/
class BearEnemy : public EnemyBase
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BearEnemy();

private:
	/** 武器 */
	std::weak_ptr<EnemyWeapon> mWeapon;

	/** カプセルコリジョン */
	std::vector<std::weak_ptr<CapsuleCollisionComponent>> mCapsuleCollision;

public:
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn 
	*/
	void CollisionFix();

	/**
	* @fn SetupCollision
	* @brief ボーンにコリジョンを設定する
	* @detail コリジョンを付けるためにInitで必ず使用すること
	* @return void
	*/
	void SetupCollision();

	/**
	* @fn AttachCapsuleCollision
	* @brief カプセルコリジョンを名前の一致するボーンにアタッチする
	* @detail ボーンにアタッチし、コリジョンのレイヤーも設定している
	* @param const std::string& (_boneName)
	* @param const float        (_radius)
	* @param const float        (_height)
	* @param const Transform&    (_offsetTrans)
	* @return void
	*/
	void AttachCapsuleCollision(const std::string& _boneName, const float _radius, const float _height, const Transform& _offsetTrans);

public:
	/**
	 * @fn GetWeapon
	 * @brief 持っている武器を返す
	 * @return std::weak_ptr<EnemyWeapon> 
	*/
	inline std::weak_ptr<EnemyWeapon> GetWeapon() const;
	
};

//--------- INLINES ----------

inline std::weak_ptr<EnemyWeapon> BearEnemy::GetWeapon() const
{
	return mWeapon;
}