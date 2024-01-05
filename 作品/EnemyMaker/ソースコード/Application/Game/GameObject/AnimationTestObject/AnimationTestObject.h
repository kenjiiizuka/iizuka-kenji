/**
* @file AnimationTestObject.h
* @brief AnimationTestObjectクラスの定義
*/

#pragma once

//-------- INCLUDES ----------
#include "../GameObject.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"

/**
* @class AnimationTestObject
* @brief アニメーションテスト用オブジェクト
* @detail デバッグ、テスト
*/
class AnimationTestObject : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AnimationTestObject();

	/**
	* デストラクタ
	*/
	~AnimationTestObject();

private:
	/** スケルタルメッシュコンポーネント */
	std::weak_ptr<SkeletalMeshComponent> mSkeletalMesh;


public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	void Init() override;

};

