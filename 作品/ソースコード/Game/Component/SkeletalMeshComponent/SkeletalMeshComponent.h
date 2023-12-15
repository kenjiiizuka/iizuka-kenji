/**
* @file SkeletalMeshComponent.h
* @brief SkeletalMeshComponentクラスの定義
*/

#pragma once

//--------- INCLUDES -----------
#include "../Component.h"
#include <string>
#include<memory>
#include "../../Resource/SkeletalMesh.h"
#include "AnimationInstance.h"

//--------- 前方宣言 -----------
class AnimationPlayer;


template<class AnimInstance>
concept DerivedAnimationInstance = std::derived_from<AnimInstance, AnimationInstance>;

/**
* @class SkeletalMeshComponent
* @brief スケルタルメッシュに関する機能を持つクラス
*/
class SkeletalMeshComponent : public Component
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SkeletalMeshComponent();

	/**
	* デストラクタ
	*/
	~SkeletalMeshComponent();

private:	
	/** スケルタルメッシュ */
	std::shared_ptr<SkeletalMesh> mSkeletalMesh;

	/** アニメーションインスタンス */
	std::shared_ptr <AnimationInstance> mAnimInstance;

	/** アニメーション再生するクラス */
	std::shared_ptr<AnimationPlayer> mAnimPlayer;

	/**  アニメーションが再生されているか */
	bool bPlayAnimation;

	/** トランスフォーム */
	Transform mTransform;

public:
	void Load(const std::string _filePath, bool _flipUV = true);


	void Init() override;


	void Update(const double _deltaTime) override;


	void Draw() override;

public:
	/* アニメーションインスタンスのゲッター */
	std::shared_ptr<AnimationInstance> GetAnimationInstance();
	
	/**
	* @fn PlayAnimation
	* @brief アニメーション再生関数をラップした関数
	* @param const std::string& (_animationName)
	* @param const float        (_playRate)
	* @param const float        (_blendTime)
	* @return void
	*/
	void PlayAnimation(const std::string& _animationName, const float _playRate = 1.0f, const float _blendTime = 0.0f);
	
	/**
	* @fn CreateAnimInstance
	* @brief アニメーションインスタンスの作成
	* @return std::shared_ptr<AnimInstance>
	*/
	template<DerivedAnimationInstance AnimInstance>
	inline std::shared_ptr<AnimInstance> CreateAnimInstance();
	
	/**
	* @fn CalucSkeletalMeshWorldMatrix
	* @brief SkeletalMeshのワールド行列を計算してセットする
	* @return void
	*/
	void CalucSkeletalMeshWorldMatrix();

	/**
	* @fn SetPosition
	* @brief 座標のセッター
	* @param const DirectX::SimpleMath::Vector3& (_position)
	* @return void
	*/
	inline void SetPosition(const DirectX::SimpleMath::Vector3& _position);

	/**
	* @fn SetPosition
	* @brief スケールのセッター
	* @param const DirectX::SimpleMath::Vector3& (_position)
	* @return void
	*/
	inline void SetScale(const DirectX::SimpleMath::Vector3& _scale);

	/**
	* @fn SetPosition
	* @brief スケールのセッター
	* @param const float (_scale)
	* @return void
	*/
	inline void SetScale(const float _scale);

	/**
	* @fn SetPosition
	* @brief 回転のセッター
	* @param const DirectX::SimpleMath::Vector3& (_rotation)
	* @return void
	*/
	inline void SetRotation(const DirectX::SimpleMath::Vector3& _rotation);

	/**
	* @fn GetSkeletalMesh
	* @brief スケルタルメッシュを返す
	* @return std::weak_ptr<SkeletalMesh>
	*/
	inline std::weak_ptr<SkeletalMesh> GetSkeletalMesh() const;

	/**
	* @fn GetTransform
	* @brief トランスフォームのゲッター
	* @return Transform
	*/
	inline Transform GetTransform() const;

	/**
	* @fn GetAnimationPlayer
	* @brief アニメーションプレイヤーを返す
	* @return std::weak_ptr<AnimationPlayer>
	*/
	inline std::weak_ptr<AnimationPlayer> GetAnimationPlayer() const noexcept;
};

//-------------- INLINES --------------

inline void SkeletalMeshComponent::SetPosition(const DirectX::SimpleMath::Vector3& _position)
{
	mTransform.mPosition = _position;
}

inline void SkeletalMeshComponent::SetScale(const DirectX::SimpleMath::Vector3& _scale)
{
	mTransform.mScale = _scale;
	CalucSkeletalMeshWorldMatrix();
}

inline void SkeletalMeshComponent::SetScale(const float _scale)
{
	mTransform.mScale = { _scale, _scale, _scale };
	CalucSkeletalMeshWorldMatrix();
}

inline void SkeletalMeshComponent::SetRotation(const DirectX::SimpleMath::Vector3& _rotation)
{
	mTransform.mRotation = _rotation;
	CalucSkeletalMeshWorldMatrix();
}

inline std::weak_ptr<SkeletalMesh> SkeletalMeshComponent::GetSkeletalMesh() const
{
	return mSkeletalMesh;
}

inline Transform SkeletalMeshComponent::GetTransform() const
{
	return mTransform;
}

inline std::weak_ptr<AnimationPlayer> SkeletalMeshComponent::GetAnimationPlayer() const noexcept
{
	return mAnimPlayer;
}

template<DerivedAnimationInstance AnimInstance>
inline std::shared_ptr<AnimInstance> SkeletalMeshComponent::CreateAnimInstance()
{
	mAnimInstance = std::make_shared<AnimInstance>();
	mAnimInstance->SetOwnerSkeletalMesh(mSkeletalMesh);
	mAnimInstance->SetAnimationPlayer(mAnimPlayer);
	mAnimInstance->SetOwner(mOwner);
	mAnimInstance->AnimationInit();
	return std::static_pointer_cast<AnimInstance>(mAnimInstance);
}