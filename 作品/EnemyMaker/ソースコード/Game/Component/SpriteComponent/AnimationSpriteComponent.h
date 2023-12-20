/**
* @file AnimationSpriteComponent.h
* @brief AnimationSpriteComponentクラスの定義
*/

#pragma once

//-------- INCLUDES --------
#include "SpriteComponent.h"

/**
* @class AnimationSpriteComponent
* @brief テクスチャアニメーションができるスプライトコンポーネント
*/
class AnimationSpriteComponent : public SpriteComponent
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AnimationSpriteComponent();

	/**
	* デストラクタ
	*/
	~AnimationSpriteComponent();

private:
	/** アニメーションテーブル */
	std::vector<uint8_t> mAnimationTable;

	/** テクスチャの1分割のサイズ */
	DirectX::SimpleMath::Vector2 mUVSize;

	/** 縦横の分割数 */
	DirectX::SimpleMath::Vector2 mSplit;

	/** アニメーションをすすめるフレーム */
	float mAnimationFrame;

	/** アニメーション再生しているか */
	bool mbIsPlay;

	/** ループ再生するか */
	bool mbIsLoop;

	/** アニメーション開始してからの経過時間 最後のテクスチャまでいったらリセットされる */
	float mElapsedTime;

	/** 表示するテクスチャのXの位置 */
	uint8_t mCurrentX;

	/** 表示するテクスチャのYの位置 */
	uint8_t mCurrentY;

	/** 前フレームのテクスチャのX位置 */
	uint8_t mPrevX;

public:
	/**
　　 * @fn Init
	 * @brief 初期化処理
	 * @param DirectX::SimpleMath::Vector2 (_pos)
	 * @param DirectX::SimpleMath::Vector2 (_size)
	 * @param DirectX::SimpleMath::Vector4 (_diffuse)
　　 * @return void
　　*/
	void Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _size, DirectX::SimpleMath::Vector4 _vertexColor = { 1.0f,1.0f,1.0f,1.0f }) override;

	/**
	* @@fn Update
	* @brief 更新処理
	* @detail アニメーションデーブルを進める
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

public:
	/**
	* @fn SetupAnimationTable
	* @brief アニメーションテーブルを設定する関数
	* @detail アニメーションさせたいテクスチャの縦横の分割数から求める
	* @param const float (_xSplit)
	* @param const float (_ySplit)
	* @return void
	*/
	void SetupAnimationTable(const float _xSplit, const float _ySplit);

	/**
	* @fn SetLoop
	* @brief ループ再生するかのセッター
	* @param const bool (_loop)
	* @return void 
	*/
	inline void SetLoop(const bool _loop) noexcept;

	/**
	* @fn PlayAnimation
	* @brief アニメーションを再生する関数
	* @return void
	*/
	inline void PlayAnimation() noexcept;

	/**
	* @fn StopAnimation
	* @brief アニメーションを停止する関数
	* @return void
	*/
	inline void StopAnimation() noexcept;

	/**
	* @fn IsPlay
	* @brief アニメーション再生しているか
	* @return bool true 再生しているか false 再生していない
	*/
	inline bool IsPlay() const noexcept;
};

//---------- INLINES -----------

inline void AnimationSpriteComponent::SetLoop(const bool _loop) noexcept
{
	mbIsLoop = _loop;
}

inline void AnimationSpriteComponent::PlayAnimation() noexcept
{
	mbIsPlay = true;
	mCurrentX = 0;
	mCurrentY = 0;
	mElapsedTime = 0.0f;
}

inline void AnimationSpriteComponent::StopAnimation() noexcept
{
	mbIsPlay = false;
}

inline bool AnimationSpriteComponent::IsPlay() const noexcept
{
	return mbIsPlay;
}
