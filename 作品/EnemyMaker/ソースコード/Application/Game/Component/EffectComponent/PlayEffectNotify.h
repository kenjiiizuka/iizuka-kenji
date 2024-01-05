/**
* @file PlayEffectNotify.h
* @brief PlayEffectNotifyクラス
*/

#pragma once

//--------- INCLUDES -----------
#include "../SkeletalMeshComponent/AnimationNotify.h"
#include <string>
#include <Effekseer.h>
#include <SimpleMath.h>

//---------- 前方宣言 ---------
class AssetHandle;

/**
* @class PlayEffectNotify
* @brief エフェクトを再生する通知
* @detail アタッチされているアニメーションをしているSkeletalMeshのオーナーのゲームオブジェクトの位置にエフェクトを再生する
*         Offsetを設定してエフェクト発生位置を調整できる　Offsetの空間はSkeletalMeshのオーナーのゲームオブジェクトのローカル
*         ScaleはSkeletalMeshのオーナーのゲームオブジェクトの影響を受けない
*         回転はSkeletalMeshのオーナーのゲームオブジェクトの回転が設定される
*/
class PlayEffectNotify : public AnimationNotify
{
public:
	/**
	* コンストラクタ
	*
	* @param[in] std::weak_ptr<SkeletalMeshAnimation> (_attachAnimation) アタッチされるアニメーション
	*/
	PlayEffectNotify(SkeletalMeshAnimationClip* _attachAnimation, float _attachFrame);

	/**
	* デストラクタ
	*/
	~PlayEffectNotify();

private:
	/** エフェクトアセットへのハンドル */
	std::shared_ptr<AssetHandle> mAssetHandle;

	/** エフェクトハンドル */
	Effekseer::Handle mEffectHandle;

	/** オフセット位置 */
	DirectX::SimpleMath::Vector3 mOffsetPosition;

	/** スケール */
	DirectX::SimpleMath::Vector3 mScale;
public:
	/**
　　 * @fn　NotifyBegin
　　 * @brief 通知の開始処理
　　 * @return void
　　*/
	void NotifyBegin() override;

	/**
	* @fn LoadEffect
	* @brief エフェクト読み込み関数
	* @param std::string_view (_filePath)
	*/
	void LoadEffect(std::string_view _filePath);

	/**
	* @fn SetOffset
	* @brief オフセットのセッター
	* @param const DirectX::SimpleMath::Vector3 (_offset)
	* @return void
	*/
	inline void SetOffset(const DirectX::SimpleMath::Vector3 _offset) noexcept;

	/**
	* @fn GetOffset
	* @brief オフセットを取得
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetOffset() const noexcept;

	/**
	* @fn SetScale
	* @brief スケールのセッター
	* @param const float (_scale)
	* @return void
	*/
	inline void SetScale(const float _scale) noexcept;

	/**
	* @fn SetScale
	* @brief スケールのセッター
	* @param const DirectX::SimpleMath::Vector3 (_scale)
	* @return void
	*/
	inline void SetScale(const DirectX::SimpleMath::Vector3 _scale) noexcept;

	/**
	* @fn GetScale
	* @brief スケールの取得
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetScale() const noexcept;

};

//----------- INLINES ------------

inline void PlayEffectNotify::SetOffset(const DirectX::SimpleMath::Vector3 _offset) noexcept
{
	mOffsetPosition = _offset;
}

inline DirectX::SimpleMath::Vector3 PlayEffectNotify::GetOffset() const noexcept
{
	return mOffsetPosition;
}

inline void PlayEffectNotify::SetScale(const float _scale) noexcept
{
	mScale = {_scale, _scale, _scale};
}

inline void PlayEffectNotify::SetScale(const DirectX::SimpleMath::Vector3 _scale) noexcept
{
	mScale = _scale;
}

inline DirectX::SimpleMath::Vector3 PlayEffectNotify::GetScale() const noexcept
{
	return mScale;
}
