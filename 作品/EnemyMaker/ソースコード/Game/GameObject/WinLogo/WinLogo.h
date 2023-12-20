/**
* @file WinLogo.h
* @brief WinLogoクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "../GameObject.h"

class AnimationSpriteComponent;
class BlackPanel;

/**
* @class WinLogo
* @brief 勝利ロゴオブジェクト
*/
class WinLogo : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	WinLogo();

	/**
	* デストラクタ
	*/
	~WinLogo();

private:
	/** ロゴスプライト */
	std::weak_ptr<AnimationSpriteComponent> mSprite;

	/** パネル */
	std::weak_ptr<BlackPanel> mPanel;

	/** アニメーションが終了したかを示す */
	bool mbIsFinishAnimation;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @detail 勝利ロゴ表示用のコンポーネント追加
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update(const double _deltaTime);

	/**
	* @fn IsInterpFinish
	* @brief 補間が終了したか
	* @return bool
	*/
	inline bool IsAnimationFinish() const noexcept;

};

//---------- INLINES ----------

inline bool WinLogo::IsAnimationFinish() const noexcept
{
	return mbIsFinishAnimation;
}

