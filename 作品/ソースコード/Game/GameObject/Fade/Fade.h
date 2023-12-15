/**
* @file Fade.h
* @brief Fadeクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include <functional>
#include "../GameObject.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"


/**
* @class Fade
* @brief フェードイン、フェードアウト用のオブジェクト
*/
class Fade : public GameObject
{
public:
	/**
	* @enum FadeState
	* @brief Fadeの状態を示す
	*/
	enum FadeState : uint8_t
	{
		Fade_None = 0,   /**< なにもしていない状態 */
		Fade_In,         /**< フェードイン */
		Fade_Out,        /**< フェードアウト */
	};

public:
	/**
	* デフォルトコンストラクタ
	*/
	Fade();

	/**
	* デストラクタ
	*/
	~Fade();

private:
	/** フェードの状態 */
	FadeState mFadeState;

	/** フェード用のスプライト */
	std::weak_ptr<SpriteComponent> mFadeSprite;

	/** フェード用のスプライトのα値 */
	float mAlpha;

	/** フェードの速度 */
	float mFadeSpeed;

	/** フェードの今の状態の更新処理 */
	std::function<void(const double)> mFadeUpdate;

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

private:
	/**
	* @fn FadeInUpdate
	* @brief フェードインの更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void FadeInUpdate(const double _deltaTime);

	/**
	* @fn FadeOutUpdate
	* @brief フェードアウトの更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void FadeOutUpdate(const double _deltaTime);

public:
	/**
	* @fn FadeIn
	* @brief フェードイン開始関数
	* @param const float (_fadeSpeed) フェードの速度
	* @return void
	*/
	inline void FadeIn(const float _fedeSpeed = 2.0f) noexcept;

	/**
	* @fn FadeOut
	* @brief フェードアウト開始関数
	* @param const float (_fadeSpeed) フェードの速度
	* @return void
	*/
	inline void FadeOut(const float _fadeSpeed = 2.0f) noexcept;

	/**
	* @fn IsFading
	* @brief フェード中かを返す
	* @return bool true フェード中 false フェードしていない
	*/
	inline bool IsFading() const noexcept;

};

//--------- INLINES -----------

inline void Fade::FadeIn(const float _fadeSpeed) noexcept
{
	mFadeState = Fade_In;
	mAlpha = 1.0f;
	mFadeSpeed = _fadeSpeed;
	mFadeSprite.lock()->SetVisible(true);
	mFadeUpdate = std::bind(&Fade::FadeInUpdate, this, std::placeholders::_1);
}

inline void Fade::FadeOut(const float _fadeSpeed) noexcept
{
	mFadeState = Fade_Out;
	mAlpha = 0.0f;
	mFadeSpeed = _fadeSpeed;
	mFadeSprite.lock()->SetVisible(true);
	mFadeUpdate = std::bind(&Fade::FadeOutUpdate, this, std::placeholders::_1);
}

inline bool Fade::IsFading() const noexcept
{
	return mFadeState != Fade_None;
}
