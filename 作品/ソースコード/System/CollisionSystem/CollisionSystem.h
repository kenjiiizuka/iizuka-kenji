#pragma once
#include <vector>
#include <memory>
#include <SimpleMath.h>
#include "Collision.h"
#include "../Singleton.h"

/**
* @file  CollisionManager.h
* @brief 当たり判定の処理をするクラス
*/

//------------- 前方宣言 -------------
class PrimitiveComponent;
class ICollisionDetector;

/**
* @class CollisionSystem
* @brief コリジョンシステムの機能を持つクラス
* @details コリジョンの登録、登録されたコリジョンの重なり検出を行う
*/
class CollisionSystem final : public Singleton<CollisionSystem>
{
private:
	/**----------------------------------------------------------------------------------------------
    * 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
    * クラス外から生成、破棄できないようにするためにフレンド指定する
    ------------------------------------------------------------------------------------------------*/
	friend Singleton<CollisionSystem>;

	/**
	 * デフォルトコンストラクタ
	*/
	CollisionSystem();

	/**
	 * デストラクタ
	*/
	~CollisionSystem();

	/**
	 * コピーコンストラクタ
	 * コピー禁止のため = delete 指定
	 * 
	 * @param const CollisionSystem& (_from)
	*/
	CollisionSystem(const CollisionSystem& _from) = delete;

	/**
	 * 代入演算子のオーバーロード
	 * 代入禁止のため = delete 指定
	 * 
	 * @paramn const CollisionSystem& (_from)
	*/
	void operator = (const CollisionSystem& _from) = delete;

private:
	/** 登録されたコリジョン */
	std::vector<PrimitiveComponent*> mRegisterdCollisions;

	/** 当たり判定が有効なのか */
	bool mbSytemActive;

	/** コリジョン検出クラス */
	std::unique_ptr<ICollisionDetector> mCollisionDetector;

public:
	/**
	 * @fn Init
	 * @brief 初期処理
	 * @return void
	*/
	void Init();

	/**
	 * @fn SwitchActive
	 * @brief コリジョンシステムの有効無効切り替え関数
	 * @param bool (_active) true : 有効  false : 無効
	 * @return void
	*/
	inline void SwitchActive(bool _active);
	
	/**
	 * @fn Update
	 * @brief 更新処理(登録されたコリジョンの当たり判定を取る)
	 * @return void
	*/
	 void Update();
	
public:
	/**
	 * @fn SetCollision
	 * @brief コリジョンの登録
	 * @param std::shared_ptr<PrimitiveComponent> (_collision) 登録するコリジョン
	 * @return void
	*/
	inline void RegistrationCollision(PrimitiveComponent* _collision);

	/**
	 * @fn RegistrationCollision
	 * @brief コリジョンの登録解除
	 * @param std::shared_ptr<PrimitiveComponent> (_collision) 登録解除するコリジョン
	 * @return void
	*/
	inline void UnRegistrationCollision(PrimitiveComponent* _collision);

};

//---------------------- INLINES -----------------------

void CollisionSystem::RegistrationCollision(PrimitiveComponent* _collision)
{
	mRegisterdCollisions.push_back(_collision);
}

inline void CollisionSystem::UnRegistrationCollision(PrimitiveComponent* _collision)
{
	// 配列から登録を解除するコリジョンを探し出し配列から除外する
	auto it = std::find(mRegisterdCollisions.begin(), mRegisterdCollisions.end(), _collision);
	if (it != mRegisterdCollisions.end())
	{
		mRegisterdCollisions.erase(it);
	}
}

inline void CollisionSystem::SwitchActive(bool _active)
{
	mbSytemActive = _active;
	// オフになるならコリジョンを登録しているリストをクリア
	if (!mbSytemActive)
	{
		mRegisterdCollisions.clear();
	}
}
