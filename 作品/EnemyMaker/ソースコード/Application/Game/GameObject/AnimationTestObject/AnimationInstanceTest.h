/**
* @file AnimationInstanceTest.h
* @brief AnimationInstanceTestクラスの定義
*/

#pragma once

//------------ INCLUDES -----------
#include "../../Component/SkeletalMeshComponent/AnimationInstance.h"

/**
* @class AnimationInstanceTest
* @brief アニメーションテスト用のアニメーションインスタンス
*/
class AnimationInstanceTest : public AnimationInstance
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AnimationInstanceTest();

	/**
	* デストラクタ
	*/
	~AnimationInstanceTest();

public:
	/**
	 * @fn　AnimationInit
	 * @brief 初期化処理
	 * @return void
	*/
	virtual void AnimationInit() override;

	/**
	 * @fn　AnimationUpdate
	 * @brief Animationの更新処理
	 * @return void
	*/
	virtual void AnimationUpdate();

};

