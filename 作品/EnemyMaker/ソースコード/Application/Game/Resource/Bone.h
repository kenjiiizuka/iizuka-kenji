/**
* @file Bone.h
* @brief Boneクラスの定義
*/


#pragma once
//------------ INCLUDES -----------
#include <memory>
#include <SimpleMath.h>
#include "../Component/TransformComponent/Transform.h"
#include "../../System/AssetSystem/SkeletalMesh/BoneAsset.h"
#include "SkeletalMesh.h"



/**
* @class Bone
* @brief Skeletonを構成するボーンクラス
*/
class Bone
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	Bone();
	
	/**
	* デストラクタ
	*/
	virtual ~Bone();

protected:
	/** トランスフォーム */
	Transform mTransform;
	
	/** 親ボーン */
	std::weak_ptr<Bone> mParentBone;

	/** 子ボーン */
	std::vector<std::shared_ptr<Bone>> mChildren;

	/** ボーンのアセットデータ */
	std::weak_ptr<BoneAsset> mBoneAsset;

	/** ボーン行列 */
	DirectX::SimpleMath::Matrix mBoneMatrix;

	/** このボーンを持っているスケルタルメッシュ */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;

	/** ボーンの名前 */
	std::string mBoneName;

	/** ワールド行列 */
	DirectX::SimpleMath::Matrix mWorldMatrix;

	/** デバッグ表示する際のボーンの色 */
	DirectX::SimpleMath::Vector4 mBoneColor;

	/** デバッグ表示するボーンの大きさ */
	float mBoneRadius;

private:
	/** バインドポーズ行列 */
	DirectX::SimpleMath::Matrix mBindPoseMatrix;

	/** アニメーション行列 */
	DirectX::SimpleMath::Matrix mAnimationMatrix;

public:
	/**
	 * @fn Initialize
	 * @brief 初期化処理
	 * @detail BoneAssetからボーンの情報を受け取り必要な処理をする
	 * @param const std::weak_ptr<BoneAsset> (_boneAsset)
	 * @param std::weak_ptr<Bone>            (_parentBone)
	 * @param const size_t                   (_numChildren)
	 * @return void
	*/
	void Initialize(const std::weak_ptr<BoneAsset> _boneAsset, const std::weak_ptr<Bone> _parentBone, const size_t _numChildren);

	/**
	* @fn Draw
	* @brief ボーンの位置を描画する
	* @return void
	*/
	void Draw();

	/**
	 * @fn CalucBoneMatrix
	 * @brief ボーン行列を計算する関数
	 * @param DirectX::SimpleMath::Matrix (_parentBoneMatrix)
	 * @return void
	*/
	virtual void CalcuBindPoseBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity);

	/**
	* @fn CalucAnimatedBoneMatrix
	* @brief アニメーションを適応したボーン行列を計算する
	* @param DirectX::SimpleMath::Matrix (_parentBoneMatrix)
	* @return void
	*/
	virtual void CalcuAnimatedBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity);

	/**
	* @fn CalucWorldBoneMatrix
	* @brief ワールド空間のボーン行列を計算する
	* @param const DirectX::SimpleMath::Matrix& (_parentBoneMatrix)
	* @return void
	*/
	virtual void CalucWorldBoneMatrix(const DirectX::SimpleMath::Matrix& _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity);

public:
	/**
	* @fn AddChildBone
	* @brief 子ボーン追加
	* @param const std::shared_ptr<Bone> (_newChildBone)
	* @return void
	*/
	void AddChildBone(const std::shared_ptr<Bone> _newChildBone);

	/**
	 * @fn GetChildBones
	 * @brief 子ボーンの配列を返す
	 * @return std::vector<std::shared_ptr<Bone>>
	*/
	inline std::vector<std::shared_ptr<Bone>> GetChildBones() const;

	/**
	 * @fn SetParentBone
	 * @brief 親ボーンをセット
	 * @param std::weak_ptr<Bone>&  (_bone)
	 * @return void
	*/
	inline void SetParentBone(std::shared_ptr<Bone>& _bone);

	/**
	* @fn SetChildBones
	* @brief 子ボーンをセットする
	* @param std::vector<std::shared_ptr<Bone>> (_childBones)
	* @return void 
	*/
	inline void SetChildBones(std::vector<std::shared_ptr<Bone>>& _childBones);

	/**
	* @fn GetBoneName
	* @brief ボーンの名前を取得
	* @return std::string
	*/
	inline std::string GetBoneName() const noexcept;

	/**
	* @fn GetBoneMatrix
	* @brief ボーン行列を返す ボーン空間になっているのでSkeletalMeshのWorld行列とかけて座標変換する必要がある
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetBoneMatrix() const noexcept;
	
	/**
	* @fn SetBoneMatrix
	* @brief ボーンマトリックスのセッター
	* @param const DirectX::SimpleMath::Matrix& (_boneMatrix)
	* @return void
	*/
	inline void SetBoneMatrix(const DirectX::SimpleMath::Matrix& _boneMatrix) noexcept;

	/**
	* @fn GetBindPoseMatrix
	* @brief バインドポーズ行列を作成する
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetBindPoseMatrix() const noexcept;

	/**
	* @fn SetAnimationMatrix
	* @brief アニメーション行列をセットする
	* @param const DirectX::SimpleMath::Matrix& (_animationMatrix)
	* @return void
	*/
	inline void SetAnimationMatrix(const DirectX::SimpleMath::Matrix& _animationMatrix) noexcept;

	/**
	* @fn GetBoneWorldMatrix
	* @brief ボーンのワールド行列を返す
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetBoneWorldMatrix() const noexcept;

};

//----------- INLINES ---------
 
inline std::vector<std::shared_ptr<Bone>> Bone::GetChildBones() const
{
	return mChildren;
}

inline void Bone::SetParentBone(std::shared_ptr<Bone>& _bone) 
{
	mParentBone = _bone;
}

inline void Bone::SetChildBones(std::vector<std::shared_ptr<Bone>>& _childBones)
{
	mChildren = _childBones;
}

inline std::string Bone::GetBoneName() const noexcept
{
	return mBoneName;
}

inline DirectX::SimpleMath::Matrix Bone::GetBoneMatrix() const noexcept
{
	return mBoneMatrix;
}

inline void Bone::SetBoneMatrix(const DirectX::SimpleMath::Matrix& _boneMatrix) noexcept
{
	mBoneMatrix = _boneMatrix;
}

inline DirectX::SimpleMath::Matrix Bone::GetBindPoseMatrix() const noexcept
{
	return mBindPoseMatrix;
}

inline void Bone::SetAnimationMatrix(const DirectX::SimpleMath::Matrix& _animationMatrix) noexcept
{
	mAnimationMatrix = _animationMatrix;
}

inline DirectX::SimpleMath::Matrix Bone::GetBoneWorldMatrix() const noexcept
{
	return mWorldMatrix;
}
