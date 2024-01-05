/**
* @file Skeleton.h
* @brief Skeletonクラスの定義
*/

#pragma once

//----------- INCLUDES -----------
#include <memory>
#include <unordered_map>
#include "../../System/AssetSystem/SkeletalMesh/BoneAsset.h"
#include "../Component/TransformComponent/Transform.h"

//------------ 前方宣言 -----------
class Bone;
class Socket;

/**
* @class Skeleton
* @brief SkeletalMeshのアニメーションや変形を制御するための骨組み
*/
class Skeleton
{
public:
	/**
	 * デフォルトコンストラクタ
	*/
	Skeleton();

	/**
	 * デストラクタ
	*/
	~Skeleton();
	
private:
	/** ルートボーン */
	std::shared_ptr<Bone> mRootBone;
	
	/** すべてのボーンに対してアクセスしたい場合用にvectorにボーンデータを保持する */
	std::vector<std::weak_ptr<Bone>> mBonesVector;

	/** ボーンマップ ボーン名でアクセスしやすくするため */
	std::unordered_map<std::string ,std::weak_ptr<Bone>> mBoneMap;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param const std::weak_ptr<BoneAsset> (_boneAsset)
	*/
	void Initialize(const std::weak_ptr<BoneAsset> _boneAsset);

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update();

	/**
	* @fn Draw
	* @brief Skeletonを描画する関数
	* @return void
	*/
	void Draw();

	/**
	* @fn Animate
	* @brief Skeletonをアニメーションさせる
	* @return void
	*/
	void Animate();

	/**
	* @fn CalucWorldBoneMatrix
	* @brief このSkeletonを構成しているBoneのWorld行列を計算する
	* @param const DirectX::SimpleMath::Matrix& (_skeletalMeshWorldMatrix)
	* @return void
	*/
	void CalucWorldBoneMatrix(const DirectX::SimpleMath::Matrix& _skeletalMeshWorldMatrix);

private:
	/**
	 * @fn CreateBoneFromBoneAsset
	 * @brief ボーンアセットからボーンを構成する
	 * @param std::shared_ptr<Bone>&          (_bone)
	 * @param std::shared_ptr<Bone>           (_parentBone)
	 * @param const std::weak_ptr<BoneAsset>  (_boneAsset)
	 * @return void
	*/
	void CreateBoneFromBoneAsset(std::shared_ptr<Bone>& _bone, std::shared_ptr<Bone> _parentBone, const std::weak_ptr<BoneAsset> _boneAsset);

	/**
	* @fn RegisterBoneMapAndBoneVector
	* @brief ボーンをマップと可変長配列に代入する再起関数
	* @param std::shared_ptr<Bone>& (_bone)
	* @return void
	*/
	void RegisterBoneMapAndBoneVector(std::shared_ptr<Bone>& _bone);

	/**
	* @fn OutPutBoneName
	* @brief 渡されたボーン以下の階層をボーンの名前を表示する
	* @param std::shared_ptr<Bone> (_bone)
	* @return void
	*/
	void OutPutBoneName(std::shared_ptr<Bone> _bone);

public:
	/**
	* @fn CreateSocket
	* @brief ソケットを作成する関数
	* @param const std::string&   (_parentBoneName)
	* @param const Transform&     (_socketTrans)
	* @param const std::string&   (_socketName)
	* @return void
	*/
	std::shared_ptr<Socket> CreateSocket(const std::string& _parentBoneName, const Transform& _socketTrans, const std::string& _socketName);

	/**
	* @fn GetBoneVector
	* @brief すべてのボーンを格納している配列を返す
	* @return std::vector<std::weak_ptr<Bone>>
	*/
	inline std::vector<std::weak_ptr<Bone>> GetBonesVector() const;

	/**
	* @fn GetBoneByName
	* @brief ボーンを名前によって取得する
	* @param const std::string& (_boneName)
	* @return std::weak_ptr<Bone>
	*/
	inline std::weak_ptr<Bone> GetBoneByName(const std::string& _boneName) const;

	/**
	* @fn GetRootBone
	* @brief ルートボーンのゲッター
	* @return std::weak_ptr<Bone>
	*/
	inline std::weak_ptr<Bone> GetRootBone() const noexcept;
};

//----------- INLINES ----------

inline std::vector<std::weak_ptr<Bone>> Skeleton::GetBonesVector() const
{
	return mBonesVector;
}

inline std::weak_ptr<Bone> Skeleton::GetBoneByName(const std::string& _boneName) const
{
	// キーがあれば返す
	if (mBoneMap.contains(_boneName))
	{
		return mBoneMap.at(_boneName);
	}
	return std::weak_ptr<Bone>();
}

inline std::weak_ptr<Bone> Skeleton::GetRootBone() const noexcept
{
	return mRootBone;
}
