/**
* @file BattleStartLogo.h
* @brief BattleStartLogoクラスの定義
*/

#pragma once


//---------- INCLUDES --------
#include "../GameObject.h"

//---------- 前方宣言 --------
class AnimationSpriteComponent;

/**
* @class BattleStartLogo
* @brief 戦闘開始のロゴ
*/
class BattleStartLogo : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BattleStartLogo();

	/**
	* デストラクタ
	*/
	~BattleStartLogo();

private:
	/** アニメーションが終了したか */
	bool mbIsAnimationFinish;

	/** ロゴ表示スプライト */
	std::weak_ptr<AnimationSpriteComponent> mSprite;

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
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn IsInterpFinish
	* @brief 補間が終了したかを返す
	* @return bool true 補間終了 false 終了していない
	*/
	inline bool IsAnimationFinish() const noexcept;

};

//-------- INLINES ---------

inline bool BattleStartLogo::IsAnimationFinish() const noexcept
{
	return mbIsAnimationFinish;
}



