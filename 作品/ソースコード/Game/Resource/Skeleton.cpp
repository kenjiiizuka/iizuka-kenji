//-------------- INCLUDES ------------
#include <iostream>
#include "Skeleton.h"
#include "Socket.h"

Skeleton::Skeleton()
{
	// 処理なし
}

Skeleton::~Skeleton()
{
	// 処理なし
}

void Skeleton::Initialize(const std::weak_ptr<BoneAsset> _boneAsset)
{
	// ボーンアセットの参照が有効化を確認
	if (!_boneAsset.lock())
	{
		std::cout << "ボーンアセットの参照が使えません" << std::endl;
		return;
	}

	// ボーンを作成する
	CreateBoneFromBoneAsset(mRootBone,nullptr, _boneAsset);

	// ボーンを可変長配列とMapに登録する
	RegisterBoneMapAndBoneVector(mRootBone);

	// ボーンをバインドボーズの状態にする
	mRootBone->CalucBindPoseBoneMatrix(DirectX::SimpleMath::Matrix::Identity);
}

void Skeleton::Update()
{
	if (mBoneMap.contains("SwordSocket"))
	{
		std::static_pointer_cast<Socket>(mBoneMap["SwordSocket"].lock())->Update();
	}
}

void Skeleton::Draw()
{
	for (std::weak_ptr<Bone>& bone : mBonesVector)
	{
		bone.lock()->Draw();
	}
}

void Skeleton::Animate()
{
	// アニメーションしたボーン行列を求める
 	mRootBone->CalucAnimatedBoneMatrix();
}

void Skeleton::CalucWorldBoneMatrix(const DirectX::SimpleMath::Matrix& _skeletalMeshWorldMatrix)
{
	for (std::weak_ptr<Bone>& bone : mBonesVector)
	{
		if (bone.lock())
		{
			bone.lock()->CalucWorldBoneMatrix(_skeletalMeshWorldMatrix);
		}
	}	
}

void Skeleton::CreateBoneFromBoneAsset(std::shared_ptr<Bone>& _bone, std::shared_ptr<Bone> _parentBone, const std::weak_ptr<BoneAsset> _boneAsset)
{
	if (!_boneAsset.lock())
	{
		return;
	}

	// 子ボーンの取得
	size_t numChild = 0;
	std::vector<std::shared_ptr<BoneAsset>> childBoneAssets;
	if (_boneAsset.lock()->HasChildren())
	{
		childBoneAssets = _boneAsset.lock()->GetChildBones();
		numChild = childBoneAssets.size();
	}

	// ボーンの作成
	_bone = std::make_shared<Bone>();
	
	// ボーン初期化
	_bone->Initialize(_boneAsset, _parentBone, numChild);

	// 子ボーンの取得
	std::vector<std::shared_ptr<Bone>> childBones(numChild);
	for (size_t boneAsset_i = 0; std::shared_ptr<Bone>& childBone : childBones)
	{
		CreateBoneFromBoneAsset(childBone, _bone, childBoneAssets[boneAsset_i]);
		boneAsset_i++;
	}

	// 子ボーンの登録
	_bone->SetChildBones(childBones);

}

void Skeleton::RegisterBoneMapAndBoneVector(std::shared_ptr<Bone>& _bone)
{
	// マップに登録
	bool success = mBoneMap.try_emplace(_bone->GetBoneName(), _bone).second;
	if (!success)
	{
		std::cout << _bone->GetBoneName() << "はマップに登録できませんでした" << std::endl;
	}
	// 可変長配列に追加
	mBonesVector.emplace_back(_bone);

	for (std::shared_ptr<Bone> childBone : _bone->GetChildBones())
	{
		RegisterBoneMapAndBoneVector(childBone);
	}
}

void Skeleton::OutPutBoneName(std::shared_ptr<Bone> _bone)
{
	std::cout << _bone->GetBoneName() << std::endl;
	std::vector<std::shared_ptr<Bone>> children = _bone->GetChildBones();
	for (std::shared_ptr<Bone> bone : children)
	{
		OutPutBoneName(bone);
	}
}

std::shared_ptr<Socket> Skeleton::CreateSocket(const std::string& _parentBoneName, const Transform& _socketTrans, const std::string& _socketName)
{
	// 指定された親ボーンが存在するか確認
	if (!mBoneMap.contains(_parentBoneName))
	{
		return std::shared_ptr<Socket>();
	}

	// マップに登録されている時は
	std::shared_ptr<Bone> validBone = mBoneMap[_parentBoneName].lock();

	// ソケットの生成
	std::shared_ptr<Socket> socket = std::make_shared<Socket>();
	socket->Initialize(_socketTrans, _socketName, validBone);

	// ソケットをマップに追加
	mBoneMap.try_emplace(_socketName, socket);

	// アクセス用の配列に追加
	mBonesVector.emplace_back(socket);

	// ボーンの階層構造に組み込む
	validBone->AddChildBone(socket);

	return socket;
}


