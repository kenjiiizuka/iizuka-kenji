#pragma once

/**
* @file EnemyWeapon.h
* @brief EnemyWeaponクラスの定義
*/

//------------ INCLUDES ------------
#include "../Weapon/Weapon.h"

//------------ 前方宣言 ------------
class EnemyAttackCapsuleCollisionComponent;

/**
* @class EnemyWeapon
* @brief エネミーがもつ武器クラス
*/
class EnemyWeapon : public Weapon
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	EnemyWeapon() 
	{
		// 処理なし
	}

	/**
	* デフォルトデストラクタ
	*/
	~EnemyWeapon()
	{
		// 処理なし
	}

private:
	/** 武器に付ける敵の攻撃コリジョン */
	std::weak_ptr<EnemyAttackCapsuleCollisionComponent> mAttackCollision;

public: 
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @param const std::string&            (_filePath)          読み込む武器メッシュのファイルパス
	 * @param std::shared_ptr<Bone>         (_attachBone)        アタッチするボーン
	 * @param std::shared_ptr<SkeletalMesh> (_skeletalMesh)      アタッチするボーンを持っているスケルタルメッシ
	 * @return void
	*/
	void Init(const std::string& _filePath, std::shared_ptr<Bone> _attachBone, std::shared_ptr<SkeletalMesh> _skeletalMesh) override;

public:
	/**
	 * @fn SetCollisonActive
	 * @brief 武器のコリジョンの有効、無効を切り替えるラッパー関数
	 * @param bool (_active) 読み込む武器メッシュのファイルパス
	 * @return void
	*/
	void SetCollisonActive(bool _active);

	/**
	 * @fn SetDamage
	 * @brief ダメージをセットする
	 * @param float (_damage)
	 * @return void
	*/
	void SetDamage(float _damage);


	/**
	 * @fn GetAttackCollision
	 * @brief ついているコリジョンを返す
	 * @return std::weak_ptr<EnemyAttackCapsuleCollisionComponent>
	*/
	inline std::weak_ptr<EnemyAttackCapsuleCollisionComponent> GetAttackCollision() const;
};

//---------- INLINES ----------

inline std::weak_ptr<EnemyAttackCapsuleCollisionComponent> EnemyWeapon::GetAttackCollision() const
{
	return mAttackCollision;
}
