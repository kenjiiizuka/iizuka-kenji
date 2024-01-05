/**
* @file Number.h
* @brief Numberクラスの定義
*/

#pragma once

//-------- INCLUDES ----------
#include "../GameObject.h"

class BillboardObject;
class AssetHandle;

/**
* @class Number
* @brief 数字をビルボード描画する機能を持つ
*/
class Number : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	Number();

	/**
	* デストラクタ
	*/
	~Number();

private:
	/** 数字用のテクスチャ */
	std::vector<std::shared_ptr<AssetHandle>> mNumberTextures;

	/** 表示する数字 */
	uint16_t mNumber;

	/** 数字を描画するビルボードオブジェクト  ビルボード、表示している数字 */
	std::vector<std::weak_ptr<BillboardObject>> mNumberBillboard;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	void Init();

public:
	/**
	* @fn SetNumber
	* @brief 数字をセットする
	* @param const uint8_t (_number)
	* @return void
	*/
	void SetNumber(const uint8_t _number);

	/**
	* @fn SetDiffuse
	* @brief ディフューズを設定
	* @param const DirectX::SimpleMath::Color (_color)
	* @return void
	*/
	void SetDiffuse(const DirectX::SimpleMath::Color _color);

	/**
	* @fn SetPosition
	* @brief 座標のセッター
	* @param DirectX::SimpleMath::Vector3 (_position)
	* @return void
	*/
	void SetPosition(DirectX::SimpleMath::Vector3 _position) override;

};

//----------- INLINES -----------
