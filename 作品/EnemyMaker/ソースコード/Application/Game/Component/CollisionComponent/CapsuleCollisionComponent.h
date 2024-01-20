/**
* @file  CapsuleCollisionComponent.h
* @brief CapsuleCollisionComponentクラスの定義
*/

#pragma once

//---------- INCLUDES --------
#include "PrimitiveComponent.h"

//--------- 前方宣言 ----------
class CapsuleMesh;

/**
* @class CapsuleCollisionComponent
* @brief カプセルのコリジョンの情報をもつクラス
*/
class CapsuleCollisionComponent : public PrimitiveComponent
{
public:
	/**
	* コンストラクタ
	*/
	CapsuleCollisionComponent();

private:
	/** カプセルの高さ */
	float mHeight;

	/** カプセルの半径 */
	float mRadius;
	
	/** デバッグ表示するか */
	bool mbDebugDraw;

	/** オーナーのワールドマトリックス */
	DirectX::SimpleMath::Matrix mOwnerWorldMatrix;
	
	/** オフセットマトリックス */
	DirectX::SimpleMath::Matrix mOffsetMatrix;

	/** 前フレームのボーンの行列 */
	DirectX::SimpleMath::Matrix prevBoneMat;

	/** 当たり判定表示用のカプセル */
	std::shared_ptr<CapsuleMesh> mCapsule;

public:	
	/**
	 * @fn　Init
	 * @brief 初期化処理　当たり判定描画用モデルの読み込み
	 * @param float (_height) カプセルの高さ
	 * @param float (_radius) カプセルの半径
	 * @return void
	*/
	void Init(float _height, float _radius);

	/**
	* @fn Draw
	* @brief 描画処理
	* @return void
	*/
	void Draw() override;

private:
	/**
　　 * @fn　CalucCollisionTransform
　　 * @brief コリジョンの位置を求める
　　 * @return void
　　*/
	void CalucCollisionTransform() override;

public:
	/**
	 * @fn　SetHeight
	 * @brief 高さのセッター
	 * @param float (_height) カプセルの高さ
	 * @return void
	*/
	void SetHeight(float _height) noexcept;

	/**
	 * @fn　GetHeight
	 * @brief 高さのゲッター
	 * @return float カプセルの高さ
	*/
	inline float GetHeight() const noexcept;

	/**
	 * @fn　SetRadius
	 * @brief 半径のセッター
	 * @param float (_radius) カプセルの半径
	 * @return void
	*/
	void SetRadius(float _radius) noexcept;

	/**
	 * @fn　GetRadius
	 * @brief 半径のゲッター
	 * @return float 半径
	*/
	inline float GetRadius() const noexcept; 

	/**
	* @fn SetDebugDraw
	* @brief デバッグ表示をするかのセッター
	* @param const bool (_draw)
	* @return void
	*/
	inline void SetDebugDraw(const bool _draw) noexcept;
};


//------------------------ INLINES ---------------------------

inline float CapsuleCollisionComponent::GetHeight() const noexcept
{
	return mHeight;
}

inline float CapsuleCollisionComponent::GetRadius() const noexcept
{
	return mRadius;
}

inline void CapsuleCollisionComponent::SetDebugDraw(const bool _draw) noexcept
{
	mbDebugDraw = _draw;
}

