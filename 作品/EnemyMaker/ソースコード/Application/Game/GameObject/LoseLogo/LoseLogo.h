/**
* @file LoseLogo.h
* @brief LoseLogoクラス
*/

#pragma once

//--------- INCLUDES ----------
#include "../GameObject.h"

//--------- 前方宣言 ---------
class AnimationSpriteComponent;
class BlackPanel;

/**
* @class LoseLogo
* @brief 敗北した時のロゴオブジェクト
*/
class LoseLogo : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	LoseLogo();

	/**
	* デストラクタ
	*/
	~LoseLogo();

private:
	/** スプライト */
	std::weak_ptr<AnimationSpriteComponent> mSprite;

	/** パネル */
	std::weak_ptr<BlackPanel> mPanel;

	/** アニメーションの再生が終ったか */
	bool mbIsFinishAnimation;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @detail 使用するスプライトの生成をしています
	* @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @detail 更新処理
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn IsInterpFinish
	* @brief 補間が終了したかを返す
	* @return bool true 補間完了 false 補間終了
	*/
	inline bool IsAnimationFinish() const noexcept;
};

//--------- INLINES ---------

inline bool LoseLogo::IsAnimationFinish() const noexcept
{
	return mbIsFinishAnimation;
}

