/**
* @file HitStopComponent.h
* @brief HitStopComponentクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include "../Component.h"

/**
* @class HitStopComponent
* @brief HitStop関数を使用することでオーナーオブジェクトにヒットストップをかける
* @detail オーナーのTimeDilationを変化させてヒットストップをかけている。
*         ヒットストップと同時にTimeDilationを使用した処理をしたい場合はどちらか片方しか処理できない可能性があるので注意
*/
class HitStopComponent : public Component
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	HitStopComponent();

	/**
	* デストラクタ
	*/
	~HitStopComponent();

protected:
	/** ヒットストップをかける時間 */
	double mHitStopSeconds;
	
	/** ヒットストップをかけ始めてからの経過時間 */
	double mElapsedStopTime;

	/** オーナーのヒットストップをかける前のタイムダイレーション */
	double mOwnerDefaultTimeDilation;

	/** ヒットストップがかかっているか表すフラグ */
	bool mbStop;
public:
	/**
	* @fn HitStop
	* @brief ヒットストップをかける関数
	* @detail 連続使用するとヒットストップがかかり続けるので注意
	* @param const double (_stopPower)  ヒットストップ強さ  0～1の範囲で指定してください 0がヒットストップなし 1が完全停止するヒットストップ
	* @param const double (_stopSeconds) ヒットストップする秒数 １以上の値を指定することでヒットストップがかかります
	* @param const double (_defaultTimeDilation) ヒットストップが終った後に戻るタイムダイレーション
	* @return void
	*/
	void HitStop(const double _stopPower, const double _stopSeconds, const double _defaultTimeDilation);

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;
};
