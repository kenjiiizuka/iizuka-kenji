/**
* @file DamageUI.h
* @brief DamageUIクラスの定義
*/

#pragma once

//------------ INCLUDES ----------
#include "../GameObject.h"

//----------- 前方宣言 ----------
class Number;
class CurveFloat;

/**
* @class DamageUI
* @brief プレイヤーが敵に与えたダメージを表示するオブジェクト
*/
class DamageUI : public GameObject
{
	/**
	* @struct DamageBillboard
	* @brief ダメージ表示ビルボード
	*/
	struct DamageBillboard
	{
		std::weak_ptr<Number> mBillboard;           /**< ビルボード */
		double mElapsedTime;                         /**< 生成されてからの経過時間 */
		DirectX::SimpleMath::Vector3 mDirection;    /**< 移動方向 */

		/**
		* デフォルトコンストラクタ
		*/
		DamageBillboard();
	};

public:
	/**
	* デフォルトコンストラクタ
	*/
	DamageUI();

	/**
	* デストラクタ
	*/
	~DamageUI();

private:
	/** ダメージ表示ビルボード <ビルボード, 生成してからの経過時間> */
	std::vector<DamageBillboard> mDamageBillboard;

	/** ビルボードの生存時間 */
	double mBillboardLifeTime;

	/** 表示されているビルボードを動かすためのカーブ */
	std::shared_ptr<CurveFloat> mCurve;

	/** ビルボードを移動させるカーブを編集するフラグ */
	bool mbEditCurve;

public:	
	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	void Init();

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private: 
	/**
	* @fn MoveBillboard
	* @brief 表示されているダメージビルボードを移動させる
	* @param DamageBillboard& (_billboard)
	* @return void
	*/
	void MoveBillboard(DamageBillboard& _billboard);

	/**
	* @fn InterpAlpha
	* @brief α値を０まで補完する
	* @param DamageBillboard& (_billboard)
	* @return void
	*/
	void InterpAlpha(DamageBillboard& _billboard);

public:
	/**
	* @fn DisplayDamage
	* @brief ダメージを表示を開始する関数
	* @param const float (_damage)
	* @param const DirectX::SimpleMath::Vector3 (_position)
	* @return void
	*/
	void DisplayDamage(const float _damage, const DirectX::SimpleMath::Vector3 _position);

	/**
	* @fn SetEditCurve
	* @brief カーブを編集するかのセッター
	* @param const bool (_edit)
	* @return void
	*/
	inline void SetEditCurve(const bool _edit) noexcept;

};

//-------- INLINES -----------

inline void DamageUI::SetEditCurve(const bool _edit) noexcept
{
	mbEditCurve = _edit;
}