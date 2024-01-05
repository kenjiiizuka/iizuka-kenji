/**
* @file BillboardObject.h
* @brief BillboardObjectクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "../GameObject.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"

//---------- 前方宣言 ---------
class Camera;
class PlaneComponent;

/**
* @class BillboardObject
* @brief ビルボードオブジェクト 常にカメラの方向を向く機能を持っている
*/
class BillboardObject : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BillboardObject();

	/**
	* デストラクタ
	*/
	~BillboardObject();

private:
	/** メインカメラ */
	std::weak_ptr<Camera> mMainCamera;

	/** プレーンコンポーネント */
	std::weak_ptr<PlaneComponent> mPlane;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @param const DirectX::SimpleMath::Vector2 (_size)
	* @return void
	*/
	void Init(const DirectX::SimpleMath::Vector2 _size = {1.0f,1.0f});

	/**
	* @fn Draw
	* @brief 描画処理
	* @return void
	*/
	void Draw() override;

private:
	/**
	* @fn LookAtCamera
	* @brief カメラの方向を向く
	* @return void
	*/
	virtual void LookAtCamera();

public:
	/**
	* @fn SetPosition
	* @brief 座標のセッター
	* @param DirectX::SimpleMath::Vector3 (_position)
	* @return void
	*/
	void SetPosition(DirectX::SimpleMath::Vector3 _position) override;

	/**
	* @fn SetTexture
	* @brief テクスチャのセッター
	* @param const Texture (_texture)
	* @return void
	*/
	void SetTexture(const Texture _texture);

	/**
	* @fn SetMaterialDiffuse
	* @brief マテリアルディフューズをセットする
	* @param const DirectX::SimpleMath::Color (_diffuse)
	* @return void
	*/
	void SetMaterialDiffuse(const DirectX::SimpleMath::Color _diffuse);

	/**
	* @fn CalcuWorldMatrix
	* @brief ワールド行列の位置を計算する
	* @param const DirectX::SimpleMath::Matrix& (_matrix)
	* @return void
	*/
	void CalcuWorldMatrix(const DirectX::SimpleMath::Matrix& _matrix);


};

