#pragma once
#include "../../Camera/Camera.h"

/**
* @file  Player.h
* @brief プレイヤーカメラ
*/

class Player;
class TransformComponent;

class PlayerCamera : public Camera
{
public:
	PlayerCamera();
	
private:
	/** プレイヤーの参照 */
	std::weak_ptr<Player> mPlayer; // プレイヤー
	
	/** プレイヤーのトランスフォームコンポーネントの参照 */
	std::weak_ptr<TransformComponent> mPlayerTransform;
 
	/** プレイヤーとの距離 */
	float mDistanceToPlayer;

	/** カメラの移動速度 横 */
	float mMoveHorizontalRadius;

	/** カメラの移動速度 縦 */
	float mMoveVerticaRadius;

	/**  カメラの移動補間速度 */
	float mMoveInterpSpeed;

	/** 注視点の高さを調整値 */
	float mFixFoucusHeight;

	/** プレイヤーへの初期位置からのベクトル */
	DirectX::SimpleMath::Vector3 mInitToPlayerVector; 

	/** カメラのプレイヤーを中心として回転を表す */
	DirectX::SimpleMath::Quaternion mRotation;

	/** 操作上下反転 */
	bool bVerticalInverce;

	/** 操作左右反転 */
	bool bHorizontalInverce;

public:
	/* 初期化処理  */
	void FixInit(std::weak_ptr<Player> _plyer);

	/* 更新処理 */
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn CalcuFocusPosition
	* @brief 注視点を計算する
	* @return void
	*/
	void CalcuFocusPosition() override;

public:

	/* プレイヤーの参照のセッター */
	void SetPlayer(std::weak_ptr<Player> _player);

		
};

