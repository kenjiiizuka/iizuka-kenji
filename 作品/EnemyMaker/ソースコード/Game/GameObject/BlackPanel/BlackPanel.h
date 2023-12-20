/**
* @file BlackPanel.h
* @brief BlackPanelクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "../GameObject.h"

//---------- 前方宣言 ----------
class SpriteComponent;

/**
* @class BlackPanel
* @brief 半透明の画面全体を覆う黒色のパネル
*/
class BlackPanel : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BlackPanel();

	/**
	* デストラクタ
	*/
	~BlackPanel();

private:
	/** 黒色のパネルを表示するスプライト */
	std::weak_ptr<SpriteComponent> mSprite;

	/** パネルのα値 */
	float mAlpha;

	/** α値補間にかける時間 */
	float mAlphaInterpTime;

	/** α値の現在の補間時間 */
	float mCurrentAlphaInterpTime;

	/** 補間するフラグ */
	bool mbInterp;

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
	* @param const double _deltaTime
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn InterpStart
	* @brief 補間開始処理
	* @param const float (_interpTime) 補間にかける時間
	* @return void
	*/
	void InterpStart(const float _interpTime = 1.0f) noexcept;

	/**
	* @fn IsInterpFinish
	* @brief 補間が終了したかを返す
	* @return bool true 補間終了 false 補完中 
	*/
	inline bool IsInterpFinish() const noexcept;

};

//-------- INLIENS ---------

inline bool BlackPanel::IsInterpFinish() const noexcept
{
	return mAlpha >= 1.0f;
}