/**
* @file InterpSkeleton.h
* @brief InterpSkeletonクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include <memory>
#include <unordered_map>
#include <string>
#include <SimpleMath.h>
#include "../../System/AssetSystem/SkeletalMesh/SkeletalMeshAnimationData.h"

//---------- 前方宣言 ----------
class Bone;
class Skeleton;
class SkeletalMeshAnimationClip;

/**
* @class InterpSkeleton
* @brief 渡されたSkeletonの各ボーンの位置を指定されたSkeletonのボーンの位置に補間する
*/
class InterpSkeletalAnimation
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	InterpSkeletalAnimation();

	/**
	* デストラクタ
	*/
	~InterpSkeletalAnimation();

private:
	/** 補間にかける時間 */
	float mInterpTime;

	/** ベースのアニメーションクリップの補間開始位置 */
	float mBaseInterpStartTime;

	/** 補間先のアニメーションクリップの位置 */
	float mToInterpClipTime;

	/** 補間終了フラグ */
	bool mbFinish;

	/** 補間先のアニメーションクリップ */
	std::weak_ptr<SkeletalMeshAnimationClip> mInterpToClip;

	/** 補間のベースのアニメーションクリップ */
	std::weak_ptr<SkeletalMeshAnimationClip> mInterpBaseClip;

public:
	/**
	* @fn InterpBegin
	* @brief 補間の開始処理
	* @param const float                                      (_interpTime)              補間にかける時間
	* @param const std::shared_ptr<Skeleton>                  (_interpSkeleton)          補間対象のSkeleton
	* @param const float                                      (_baseInterpStartTime)     補間のベースアニメーションの補間を開始する位置
	* @param const float                                      (_toInterpClipTime)        補間先のアニメーションクリップの補間位置
	* @param const std::shared_ptr<SkeletalMeshAnimationClip> (_animationClipInterpBase) 補間のベースアニメーションクリップ
	* @param const std::shared_ptr<SkeletalMeshAnimationClip> (_animationClipInterpTo)   補間先アニメーションクリップ
	* @return void
	*/
	void InterpBegin(const float _interpTime, const std::shared_ptr<Skeleton> _interpSkeleton, const float _baseInterpStartTime, const float _toInterpClipTime, const std::shared_ptr<SkeletalMeshAnimationClip> _animationClipInterpBase, const std::shared_ptr<SkeletalMeshAnimationClip> _animationClipInterpTo);
	
	/**
	* @fn SkeletonInterp
	* @brief 補間処理
	* @param const float (_time)
	* @return bool true 補間終了 false 補間中
	*/
	bool Interp(const float _time, std::shared_ptr<Skeleton> _skeleton);

private:
	/**
	* @fn CalucInterpKey
	* @brief チャンネル間で補間する
	* @param Channel              (_baseChannel)
	* @param Channel              (_toChannel)
	* @param DirectX::SimpleMath& (_animationMatrix)
	* @param const float          (_t)
	* @return void
	*/
	void CalcuInterpKey(Channel _baseChannel, Channel _toChannel, DirectX::SimpleMath::Matrix& _animationMatrix, const float _t);
};

