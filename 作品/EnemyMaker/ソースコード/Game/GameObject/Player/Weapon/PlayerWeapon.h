/**
* @file  PlayerWeapon.h
* @brief プレイヤーが持つ武器
*/

#pragma once

//-------- INCLUDES --------
#include "../../Weapon/Weapon.h"


//--------- 前方宣言 ---------
class Player;
class PlayerAttackCapsuleCollisionComponent;
class AudioComponent;
class EffectComponent;

/**
* @class PlayerWeapon
* @brief プレイヤーの武器クラス
* @detail プレイヤーが持つ専用のクラス 武器のメッシュと当たり判定を持つ
		  当たり判定はPlayerWeaponCollisionActiveNotifyStateでアニメーションに合わせて
		  コリジョンのオンオフを切り替えている
*/
class PlayerWeapon : public Weapon
{
public:
	/**
	* 値の初期化
	*/
	PlayerWeapon();

private:
	/** この武器を持つプレイヤー */
	Player* mPlayer;
   
	/** カプセルの半径 */
	float mCapsuleRadius;

	/** カプセルのt高さ */
	float mCapsuleHeight;

	/** コリジョン */
	std::weak_ptr<PlayerAttackCapsuleCollisionComponent> mCapsuleCollision;

	/** ヒットSE再生用のオーディオコンポーネント */
	std::weak_ptr<AudioComponent> mHitSE;

	/** ヒットエフェクト */
	std::weak_ptr<EffectComponent> mHitEffect;

public:
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @param const std::string&            (_filePath)          読み込む武器メッシュのファイルパス
	 * @param std::shared_ptr<Bone>         (_attachBone)        アタッチするボーン
	 * @param std::shared_ptr<SkeletalMesh> (_skeletalMesh)      アタッチするボーンを持っているスケルタルメッシュ
	 * @return void
	*/
	void Init(const std::string& _filePath, std::shared_ptr<Bone> _attachBone, std::shared_ptr<SkeletalMesh> _skeletalMesh) override;

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	virtual void Update(const double _deltaTime) override;

	/**
	 * @fn BeginHit
	 * @brief 何かにあったときの処理
	 * @param GameObject* (_hitObject) 当たったオブジェクト
	 * @return void
	*/
	void BeginHit(GameObject* _hitObject, PrimitiveComponent* _hitComp) override;

	/**
	* @fn GetCollision
	* @brief 武器のコリジョンを取得する
	* @return std::weak_ptr<PlayerAttackCapsuleCollisionComponent>
	*/
	inline std::weak_ptr<PlayerAttackCapsuleCollisionComponent> GetCollision() const noexcept;
};

//--------- INLINES ----------

inline std::weak_ptr<PlayerAttackCapsuleCollisionComponent> PlayerWeapon::GetCollision() const noexcept
{
	return mCapsuleCollision;
}
