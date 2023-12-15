/**
* @file TitleEnemyAnimationInstance.h
* @brief TitleEnemyAnimationInstanceクラスの定義
*/

#pragma once

//------------ INCLUDES ------------
#include "../../Component/SkeletalMeshComponent/AnimationInstance.h"

/**
* @class TitleEnemyAnimationInstance
* @brief タイトル用のエネミーのアニメーションインスタンス
*/
class TitleEnemyAnimationInstance : public AnimationInstance
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	TitleEnemyAnimationInstance();

	/**
	* デストラクタ
	*/
	~TitleEnemyAnimationInstance();

private:
	/** 息を大きくすうアニメーションを再生する確率 */
	float mBreathProbability;

public:
	/**
	 * @fn　AnimationInit
	 * @brief 初期化処理
	 * @return void
	*/
	virtual void AnimationInit();

	/**
	 * @fn　AnimationUpdate
	 * @brief Animationの更新処理
	 * @return void
	*/
	virtual void AnimationUpdate();


};

