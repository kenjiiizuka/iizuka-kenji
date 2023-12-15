/**
* @file RingCollisionComponent.h
* @brief RingCollisionComponentクラスの定義
*/

#pragma once

//------------ INCLUDES -------------
#include "PrimitiveComponent.h"

/**
* @class RingCollisionComponent
* @brief リング状のコリジョンクラス
*/
class RingCollisionComponent : public PrimitiveComponent
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	RingCollisionComponent();

	/**
	* デストラクタ
	*/
	~RingCollisionComponent();

private:
	/** リングの内側の半径 */
	float mRadius;	

public:
	
	void Update(const double _deltaTime) override;

	/**
	* @fn GetRadius
	* @brief リングの半径を返す
	* @return float 
	*/
	inline float GetRadius() const noexcept;

	/**
	* @fn SetRadius
	* @brief リングの半径のセッター
	* @param const float (_radius)
	* @return void
	*/
	inline void SetRadius(const float _radius) noexcept;
};

//-------------- INLINES -------------

inline float RingCollisionComponent::GetRadius() const noexcept
{
	return mRadius;
}

inline void RingCollisionComponent::SetRadius(const float _radius) noexcept
{
	mRadius = _radius;
}
