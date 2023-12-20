/**
* @file SliderSpriteComponent.h
* @brief SpriteComponentクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include "SpriteComponent.h"

/**
* @class SliderSpriteComponent
* @brief 最大サイズをしていし、比率を渡すことで頂点位置を最大サイズからの位置にしてくれます
*        ゲージなどに使用しやすいようにしたSprite
*/
class SliderSpriteComponent : public SpriteComponent
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SliderSpriteComponent();

	/**
	* デストラクタ
	*/
	~SliderSpriteComponent();

private:
	/** 最大サイズ */
	DirectX::SimpleMath::Vector2 mMaxSize;

	/** 現在のスライダーのサイズ */
	DirectX::SimpleMath::Vector2 mCurrentSliderSize;

	/** スライダーが最大サイズの時のUV */
	DirectX::SimpleMath::Vector2 mMaxUV;

	/** 現在のUV　スライダーのサイズと合わせた値 */
	DirectX::SimpleMath::Vector2 mCurrentUV;

public:
	void Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _maxSize, DirectX::SimpleMath::Vector4 _vertexColor = {1.0f,1.0f,1.0f,1.0f});

	void Update(const double _deltaTime) override;

	/**
	* @fn SetSliderSize
	* @brief スライダーのサイズのセッター
	* @detail サイズを 0 ～ 1に正規化した値を渡すことでスライダーサイズを決めている
	* @param const float (_sliderSize_t)
	* @return void
	*/
	void SetSliderSize(const float _sliderSize_t);

	/**
	* @fn SetMaxSize
	* @brief 最大サイズのセッター
	* @param const DirectX::SimpleMath::Vector2 (_maxSize)
	* @return void
	*/
	inline void SetMaxSize(const DirectX::SimpleMath::Vector2 _maxSize);

};

//--------- INLINES ---------

inline void SliderSpriteComponent::SetMaxSize(const DirectX::SimpleMath::Vector2 _maxSize)
{
	mMaxSize = _maxSize;
}