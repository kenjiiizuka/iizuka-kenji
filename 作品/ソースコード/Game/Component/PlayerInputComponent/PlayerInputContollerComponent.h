/**
* @file PlayerInputController.h
* @brief PlayerInputControllerクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "../../Component/Component.h"
#include "../../../System/InputSystem/XInput.h"
#include <array>


/**
* @class PlayerInputController
* @brief プレイヤーのコントローラ―の入力を管理するクラス
*/
class PlayerInputControllerComponent : public Component
{
public:
	/**
	* @enum Operation
	* @brief プレイヤーのボタン操作を定義したもの
	*/
	enum Operation : uint8_t
	{
		Operation_AttackY = 0, /**< Y攻撃操作 */
		Operation_AttackB,     /**< B攻撃操作 */
		Operation_Step,        /**< ステップ操作 */
		Operation_Max,         /**< 最大数 */
	};

	/**
	* デフォルトコンストラクタ
	*/
	PlayerInputControllerComponent();

	/**
	* デストラクタ
	*/
	~PlayerInputControllerComponent();

private:
	/** 入力されてからの経過時間 */
	float mInputElapsedFrame;

	/** 入力許容時間 */
	float mAllowInputTime;

	/** プレイヤーのする操作とボタンを紐づけた配列 */
	std::array<Pad, Operation_Max> mOperationButtons;

	/** 各操作に入力がされているかを格納する */
	std::array<bool, Operation_Max> mOperationInput;

public:
	/**
	* @fn Update
	* @brief 更新処理
	* @detail コントローラーからの入力を監視
	*         入力があれば、mAllowInputTimeの間は入力していることにする
	*         途中で別のボタンが押されたらそちらに切り替わる
	* @param const double (_deltaTime) デルタタイム
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn GetTrigger
	* @brief プレイヤーの操作に使うボタンが押されているかを返す
	* @param const Operation _operation
	* @return bool true 入力あり : false 入力なし 
	*/
	inline bool GetTrigger(const Operation _operation) const noexcept;

};

//--------- INLINES ----------

inline bool PlayerInputControllerComponent::GetTrigger(const Operation _operation) const noexcept
{
	return mOperationInput[_operation];
}
