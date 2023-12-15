/**
* @file Bone.h
* @brief Boneクラスの定義
*/

#pragma once

//------------ INCLUDES -----------
#include <memory>
#include <vector>
#include <string>
#include <SimpleMath.h>

/**
* @class Bone
* @brief Boneのデータを持つ
* @detail 親ボーン子ボーンへのポインタを持つ
*/
class BoneAsset
{
	/**---------------------------------------------------------------------------------
	* SkeletalMeshProviderのみデータをセットできるようにするためにフレンド指定をしている
	*/
	friend class SkeletalMeshProvider;

public:
	/**
	* デフォルトコンストラクタ
	*/
	BoneAsset();

	/**
	* デストラクタ
	*/
	~BoneAsset();

private:
	/** ボーンの名前 */
	std::string mBoneName;

	/** ボーンインデックス */
	size_t mIndex;

	/** 親ボーンのポインタ */
	std::weak_ptr<BoneAsset> mParentBone;

	/** 子ボーンのポインタ */
	std::vector<std::shared_ptr<BoneAsset>> mChildBones;

	/** トランスフォーム行列 */
	DirectX::SimpleMath::Matrix mTransformationMatrix;

	/** 影響を与える頂点へのオフセット行列 */
	DirectX::SimpleMath::Matrix mBindPoseMatrix;

public:
	/**
	* @fn GetBoneName
	* @brief ボーンの名前を返す関数
	* @return std::string
	*/
	inline std::string GetBoneName()const noexcept;

	/**
	* @fn GetBoneIndex
	* @brief ボーンのインデックスを返す
	* @return size_t
	*/
	inline size_t GetBoneIndex() const noexcept;

	/**
	* @fn GetParentBoneAsset
	* @brief 親のボーンアセットを返す
	* @return std::weak_ptr<BoneAsset>
	*/
	inline std::weak_ptr<BoneAsset> GetParentBoneAsset() const;

	/**
	* @fn GetChildBones
	* @brief 子ボーンを返す
	* @return std::vector<std::weak_ptr<BoneAsset>>
	*/
	inline std::vector<std::shared_ptr<BoneAsset>> GetChildBones() const;

	/**
	* @fn HasChildren
	* @brief 子ボーンを持っているか
	* @return bool true 持っている : false 持っていない
	*/
	inline bool HasChildren() const noexcept;

	/**
	 * @fn GetTransformationMatrix
	 * @brief ボーンのトランスフォームマトリックスを返す
	 * @return DirectX::SimpleMath::Matrix 
	*/
	inline DirectX::SimpleMath::Matrix GetTransformationMatrix() const noexcept;

	/**
	* @fn GetBindPoseMatrix
	* @brief バインドポーズ行列を返す
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetBindPoseMatrix() const noexcept;
};

//------------ INLINES -----------

inline std::string BoneAsset::GetBoneName() const noexcept
{
	return mBoneName;
}

inline size_t BoneAsset::GetBoneIndex() const noexcept
{
	return mIndex;
}

inline std::weak_ptr<BoneAsset> BoneAsset::GetParentBoneAsset() const
{
	return mParentBone;
}

inline std::vector<std::shared_ptr<BoneAsset>> BoneAsset::GetChildBones() const
{
	return mChildBones;
}

inline bool BoneAsset::HasChildren() const noexcept
{
	return !mChildBones.empty();
}

inline DirectX::SimpleMath::Matrix BoneAsset::GetTransformationMatrix() const noexcept
{
	return mTransformationMatrix;
}

inline DirectX::SimpleMath::Matrix BoneAsset::GetBindPoseMatrix() const noexcept
{
	return mBindPoseMatrix;
}


