/**
* @file PlayerHitReactionBigNotifyState.h
* @brief PlayerHitReactionBigNotifyStateクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "../../../../Component/SkeletalMeshComponent/AnimationNotifyState.h"
#include <SimpleMath.h>


//---------- 前方宣言 ---------
class CurveFloat;
class TransformComponent;

/**
* @class PlayerHitReactionBigNotifyState
* @brief プレイヤーのヒットリアクション大アニメーションにあわせてプレイヤーを動かす処理をしている
*/
class PlayerHitReactionBigNotifyState : public AnimationNotifyState
{
public:
	/**
	 * コンストラクタ
	 *
	 * @param SkeletalMeshAnimation* (_attachAnimation) アタッチされるアニメーション
	 * @param float (_attachStartFrame) アタッチするフレームの開始
	 * @param float (_attachEndFrame) アタッチするフレームの終了
	*/
	PlayerHitReactionBigNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame);
	
	/**
	* デストラクタ
	*/
	~PlayerHitReactionBigNotifyState();

private:
	/** プレイヤーをアニメーションに合わせて吹っ飛ばすためのカーブ */
	std::shared_ptr<CurveFloat> mBlowCurve;

	/** プレイヤーのトランスフォーム */
	std::weak_ptr<TransformComponent> mPlayerTransform;

	/** アニメーション長さ */
	float mAttachAnimationDuration;

	/** 吹っ飛び方向 */
	DirectX::SimpleMath::Vector3 mBlowVector;

public:
	/**
　　 * @fn　NotifyInit
　　 * @brief 通知の初期処理
　　 * @return void
　　*/
	void NotifyInit() override;

	/**
	* @fn NotifyBegin
	* @brief 通知処理開始処理
	* @return void
	*/
	void NotifyBegin() override;

	/**
　　 * @fn　NotifyUpdate
　　 * @brief 通知の更新処理
　　 * @return void
　　*/
	void NotifyUpdate() override;

	/**
	* @fn GetBlowCurve
	* @brief 吹っ飛びようカーブを返す
	* @return std::weak_ptr<CurveFloat>
	*/
	inline std::weak_ptr<CurveFloat> GetBlowCurve() const noexcept;

	/**
	* @fn SetBlowVector
	* @brief 吹っ飛びベクトルのセッター
	* @param const DirectX::SimpleMath::Vector3 (_blowVector)
	* @return void
	*/
	inline void SetBlowVector(const DirectX::SimpleMath::Vector3 _blowVector) noexcept;

};

//---------- INLINES ----------

inline std::weak_ptr<CurveFloat> PlayerHitReactionBigNotifyState::GetBlowCurve() const noexcept
{
	return mBlowCurve;
}

inline void PlayerHitReactionBigNotifyState::SetBlowVector(const DirectX::SimpleMath::Vector3 _blowVector) noexcept
{
	mBlowVector = _blowVector;
	mBlowVector.y = 0.0f;
	mBlowVector.Normalize();
}
