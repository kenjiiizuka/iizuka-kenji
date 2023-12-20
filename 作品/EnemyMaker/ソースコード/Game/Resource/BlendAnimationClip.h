/**
* @file BlendAnimationClip
* @brief BlendAnimationClip.h
*/

#pragma once

//-------- INCLUDES -----------
#include <vector>
#include "SkeletalMeshAnimationClip.h"

/**
* @class BlendAnimationClip
* @brief ブレンドされたアニメーションクリップを提供する
*/
class BlendAnimationClip : public SkeletalMeshAnimationClip
{
public:
	/**
	* コンストラクタ
	* 
	* @param std::shared_ptr<SkeletalMeshAnimationClip> (_clip1)
	* @param std::shared_ptr<SkeletalMeshAnimationClip> (_clip2)
	* @param const float                                (_min)
	* @param const float                                (_max)
	* @param const float                                (_blendWeight)
	*/
	BlendAnimationClip(std::shared_ptr<SkeletalMeshAnimationClip> _clip1, std::shared_ptr<SkeletalMeshAnimationClip> _clip2, const float _max, const float _min, const float _blendWeight);

private:
	/** ブレンドウェイト */
	float mBlendWeight;

	/** ブレンドの最大値 */
	float mMaxBlendValue;

	/** ブレンドの最小値 */
	float mMinBlendValue;

	/** ブレンドするアニメーション */
	std::vector<std::weak_ptr<SkeletalMeshAnimationClip>> mBlendAnimation;

	/** クリップ2のチャンネル */
	std::vector<Channel> mChannelClip2;

	/** 少ない方のチャンネルの数 */
	size_t mMinChannelNum;

public:
	/**
　　 * @fn　Begin
　　 * @brief アニメーション開始処理
　　 * @return void
　　*/
	void Begin() override;

	/**
	* @fn CalucAnimationMatrix
	* @brief チャンネルの指定された時間のアニメーションマトリックスを返す関数
	* @param Channel& (_channel)
	* @param const double (_time)
	* @param DirectX::SimpleMath::Matrix& (_animationMatrix)
	* @return void
	*/
	void CalucAnimationMatrix(Channel& _channel, const double _time, DirectX::SimpleMath::Matrix& _animationMatrix) override;

private:
	/**
　　 * @fn　AnimationDataNormalize
　　 * @brief アニメーションデータの正規化をする関数
	 * @param std::vector<Channel>& (_channel) アニメーションデータ
	 * @param const float& (_scaleFactor) 正規化する際のスケーリングの値
　　 * @return void
　　*/
	void AnimationDataNormalize(std::vector<Channel>& _channel, const float _scaleFactor);

public: 
	/**
　　 * @fn　InputBlendValue
　　 * @brief ブレンドの値を入力する関数
	 * @param const float (_value) 入力値
　　 * @return void
　　*/
	void InputBlendValue(const float& _value);

	/** 
	* @dn SetBlendMaxValue
	* @brief ブレンド値を計算するの範囲の最大値をセットする
	* @param const float _max
	* @return void
	*/
	inline void SetBlendMaxValue(const float _max) noexcept;

};

//----------- INLINES ----------

inline void BlendAnimationClip::SetBlendMaxValue(const float _max) noexcept
{
	mMaxBlendValue = _max;
}