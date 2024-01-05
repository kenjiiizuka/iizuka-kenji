/**
* @file TitleBackGround.h
* @brief TitleBackGroundクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include "../GameObject.h"

//----------- INCLUDES ------------
class SpriteComponent;

/**
* @class TitleBackGround
* @brief タイトルのバッググラウンドオブジェクト
*/
class TitleBackGround : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	TitleBackGround();

	/**
	* デストラクタ
	*/
	~TitleBackGround();

private:
	/** レイヤー１スプライト */
	std::weak_ptr<SpriteComponent> mLayer1Sprite;

	/** レイヤー2スプライト*/
	std::weak_ptr<SpriteComponent> mLayer2Sprite;

	/** タイトルロゴ */
	std::weak_ptr<SpriteComponent> mTitleLogo;

	/** レイヤー2のエミッション */
	DirectX::SimpleMath::Color mLayer2Emission;

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
	* @return void
	*/
	void Update(const double _deltaTime) override;



};

