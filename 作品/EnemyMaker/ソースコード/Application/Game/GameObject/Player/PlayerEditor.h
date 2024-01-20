/**
* @file PlayerEditor.h
* @brief PlayerEditorクラスの定義
*/

#pragma once

//---------- INCLUDES ---------
#include "Player.h"

//-------- 前方宣言 --------
class CinematicCamera;

/**
* @class PlayerDebugger
* @brief プレイヤーのパラメーターの調整を行う
* @detail 調整したいプレイヤーを渡すことで調整できる
*/
class PlayerEditor
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	PlayerEditor();

	/**
	* デストラクタ
	*/
	~PlayerEditor();

private:
	/** プレイヤー */
	std::weak_ptr<Player> mPlayer;

	/** CharacterMoveComponentへの参照 */
	std::weak_ptr<PlayerMovementComponent> mMoveComp;
	
	/** 進行方向に向かせる補間速度 */
	float mFaceDirectionInterpSpeed;

	/** 最高速度 */
	float mMaxWalkSpeed;

	/** スケルタルメッシュ */
	std::weak_ptr<SkeletalMeshComponent> mSkeletalMeshComp;

	/** 攻撃のデータ */
	std::weak_ptr<PlayerAttackData> mAttackData;

	/** 死亡した時のカメラ */
	std::weak_ptr<CinematicCamera> mDeathCamera;

	/** Inputテキスト用の変数 */
	std::vector<std::string> mTempClipNameLeft;

	/** Inputテキスト用の変数 */
	std::vector<std::string> mTempClipNameRight;
public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param プレイヤーの編集したいコンポーネントやパラメーターなどへの参照、ポインタを取得している
	* @param const std::shared_ptr<Player> (_player)
	*/
	void Initialize(const std::shared_ptr<Player> _player);

	/**
	* @fn Uninitialize
	* @brief 終了処理
	* @return void
	*/
	void Uninitialize();

	/**
	* @fn Update
	* @brief 更新処理
	* @detail ImGuiを使用してGUIで編集する処理をしている
	* @return void
	*/
	void Update();

private:
	/**
	* @fn AttackHeader
	* @brief 攻撃を編集できるヘッダー
	* @return void
	*/
	void AttackHeader();

	/**
	* @fn StepHeader
	* @brief ステップを編集できるヘッダー
	* @return void
	*/
	void StepHeader();

	/**
	* @fn HitReactionHeader
	* @brief ヒットリアクションを編集できるヘッダー
	* @return void
	*/
	void HitReactionHeader();

	/**
	* @fn AttackNode
	* @brief 攻撃編集用のTreeNode
	* @param const PlayerEntities::AttackID (_attackID)
	* @param std::string_view               (_nodeName)
	* @param const uint8_t                  (_tempString_i)
	* @return void
	*/
	void AttackNode(const PlayerData::AttackID _attackID, std::string_view _nodeName, const uint8_t _tempString_i);

	/**
	* @fn EffectNotifyNode
	* @brief エフェクト再生通知を編集する
	* @param const PlayerData::AttackID (_attackID)
	* @return void
	*/
	void EffectNotifyNode(const PlayerData::AttackID _attackID);

public:
	/**
	* @fn SetDeathCamera
	* @brief 死亡用カメラのセッター
	* @param std::shared_ptr<CinematicCamera> (_camera)
	* @return void
	*/
	void SetDeathCamera(std::shared_ptr<CinematicCamera> _camera) noexcept;

};