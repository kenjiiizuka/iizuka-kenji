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
	* @enum OperationKind
	* @brief プレイヤーのボタン操作を定義したもの
	*/
	enum OperationKind : uint8_t
	{
		Operation_AttackY = 0, /**< Y攻撃操作 */
		Operation_AttackB,     /**< B攻撃操作 */
		Operation_Step,        /**< ステップ操作 */
		Operation_Guard,       /**< ガード操作 */
		Operation_Counter,     /**< カウンター */
		Operation_Max,         /**< 最大数 */
	};

	/**
	* @enum OperationType
	* @brief 操作の入力の種類を示す
	*/
	enum OperationType : uint8_t
	{
		OperationType_Trigger = 0, /**< トリガー入力 */
		OperationType_Press,       /**< 長押し入力 */
	};


	using Operation = std::pair<Pad, OperationType>;

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
	std::array<Operation, Operation_Max> mOperationButtons;

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
	* @param const OperationKind _operation
	* @return bool true 入力あり : false 入力なし 
	*/
	inline bool IsInput(const OperationKind _operation) const noexcept;
};

//--------- INLINES ----------

inline bool PlayerInputControllerComponent::IsInput(const OperationKind _operation) const noexcept
{
	return mOperationInput[_operation];
}
