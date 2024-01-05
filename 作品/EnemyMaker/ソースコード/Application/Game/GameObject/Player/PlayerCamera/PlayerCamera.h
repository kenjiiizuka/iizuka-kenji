/**
* @file  Player.h
* @brief PlayerCamera
*/

#pragma once

//--------- INCLUDES ----------
#include "../../Camera/Camera.h"

//--------- 前方宣言 -----------
class Player;
class TransformComponent;

/**
* @class PlayerCamera
* @brief プレイヤーのカメラ
*/
class PlayerCamera : public Camera
{
	/**
	* @enum State
	* @brief カメラの状態を示す
	*/
	enum CameraState : uint8_t
	{
		State_Free = 0, /**< フリーカメラ状態 */
		State_RockOn,   /**< ロックオン状態 */
	};

public:
	/**
	* デフォルトコンストラクタ
	*/
	PlayerCamera();
	
private:
	/** プレイヤーの参照 */
	std::weak_ptr<Player> mPlayer; // プレイヤー
	
	/** プレイヤーのトランスフォームコンポーネントの参照 */
	std::weak_ptr<TransformComponent> mPlayerTransform;
 
	/** カメラの状態 */
	CameraState mState;

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
	bool bVerticalInverse;

	/** 操作左右反転 */
	bool bHorizontalInverse;

	/** 初期位置リセット */
	bool mbResetPosition;

	/** リセットにかける時間 */
	double mResetTime;

	/** リセット開始してからの経過時間 */
	double mResetElapsedTime;

public:
	/**
	* @fn FixInit
	* @brief 初期化処理
	* @param std::weak_ptr<Player> (_plyer)
	* @return void
	*/
	void Init(std::weak_ptr<Player> _plyer);

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn CalcuFocusPosition
	* @brief 注視点を計算する
	* @return void
	*/
	void CalcuFocusPosition() override;

	/**
	* @fn PositionReset
	* @brief 位置のリセット
	* @detail カメラの位置を初期位置に戻す処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void PositionReset(const double _deltaTime);

	/**
	* @fn ControlRotation
	* @brief カメラの回転を制御する関数
	* @detail コントローラーの操作によってカメラの回転を制御する関数
	* @param const double (_deltaTime)
	* @return void
	*/
	void ControlRotation(const double _deltaTime);

	/**
	* @fn CheckRotationLimit
	* @brief 回転が最大値を超えていないかを確認し、超えていれば修正する
	* @return void
	*/
	void CheckRotationLimit();

	/**
	* @fn CalcuPosition
	* @brief カメラ位置を求める
	* @return void
	*/
	void CalcuPosition();

public:
	/**
	* @fn SetPlayer
	* @brief プレイヤーのセッター
	* @param std::weak_ptr<Player> (_player)
	* @return void
	*/
	void SetPlayer(std::weak_ptr<Player> _player);
	
};

