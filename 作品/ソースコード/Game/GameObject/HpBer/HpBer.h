/**
* @file HpBer.h
* @brief HpBerクラスの定義
*/
#pragma once

//---------- INCLUDES -----------
#include "../GameObject.h"

//---------- 前方宣言 ----------
class SpriteComponent;

/** Hpberオブジェクト */
class HpBer : public GameObject
{
public:
	HpBer();
	
private:
	/** 現在のHP */
	float mCurrentHp;

	/** 前フレームのHP */
	float mPrevHp;

	/** 最大Hp */
	float mMaxHp;

	/** 減ったHp */
	float mDecreaseDamage;

	/** ゲージの消失開始までのDelay */
	float mDelayTimeToGageLost;

	/** ゲージロストまでのDelayがどのくらい経過したか */
	float mElapsedDelayTimeToGageLost;

	/** ロストゲージを消していくことをしめすフラグ */
	bool mbLostGageDecreasing;

	/** 消失し初めてからの経過時間 */
	float mLostElapsedTime;

	/** ダメージを受けた瞬間のロストゲージの長さ */
	float mLostGageInitialLength;

	/** 消失ゲージが完璧に消えるまでの時間 */
	float mGageLostSpeedPerSec;

protected:
	/** ゲージ消失時にでるゲージ */
	std::weak_ptr<SpriteComponent> mGageLostSprite;

	/** ゲージを描画しているスプライト */
	std::weak_ptr<SpriteComponent> mGageSprite;

	/** ゲージの枠のスプライト */
	std::weak_ptr<SpriteComponent> mFrameSprite;

	/** ゲージのサイズ */
	DirectX::SimpleMath::Vector2 mGageSize;

	/** ゲージの座標 */
	DirectX::SimpleMath::Vector2 mGagePosition;

	/** 枠の座標 */
	DirectX::SimpleMath::Vector2 mFramePosition;

	/** 枠の大きさ */
	DirectX::SimpleMath::Vector2 mFrameSize;

public:
	/**
　　 * @fn Init
	 * @brief 初期化処理
	 * @param float (_maxHp)
	 * @param float (_currentHp) 
	 * @param DirectX::SimpleMath::Vector2 (_position) フレームの座標
	 * @param DirectX::SimpleMath::Vector2 (_size) フレームのサイズ
	 * @param float (_gageOffset) ゲージのフレームに対するオフセット
　　 * @return void
　　*/
	void Init(float _maxHp, float _currentHp, DirectX::SimpleMath::Vector2 _position, DirectX::SimpleMath::Vector2 _size, float _offset = 3);

	/**
　　 * @fn Update
	 * @brief 更新処理
　　 * @return void
　　*/
	void Update(const double _deltaTime) override;

private:
	/**
　　 * @fn InitSprite
	 * @brief スプライトの初期化処理
　　 * @return void
　　*/
	virtual void InitSprite();

	/**
	* @fn DecreaseGage
	* @brief ゲージを減らす処理
	* @return void
	*/
	void DecreaseGage();

	/**
　　 * @fn GageLost
	 * @brief ゲージ消失処理
　　 * @return void
　　*/
	void GageLost();

public:
	/**
　　 * @fn SetCurrentHp
	 * @brief Hpのセッター
　　 * @return void
　　*/
	inline void SetCurrentHp(float _hp);
};

//---------------- INLINES -----------------

inline void HpBer::SetCurrentHp(float _hp)
{
	// 減ったダメージを計算する
	mDecreaseDamage = _hp - mCurrentHp;
	mCurrentHp = _hp;
}