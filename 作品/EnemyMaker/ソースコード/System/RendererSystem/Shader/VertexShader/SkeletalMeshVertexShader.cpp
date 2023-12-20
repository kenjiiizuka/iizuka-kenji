//-------------- INCLUDES --------------
#include <iostream>
#include "SkeletalMeshVertexShader.h"
#include "../../VisualEntity/VisualEntity.h"
#include "../../../../Utility/MathLibrary.h"
#include "../../../../Game/Resource/Skeleton.h"
#include "../../../../Game/Resource/Bone.h"
#include "../../../../Utility/Debug.h"
#include "../../../../Game/GameObject/Enemy/Bear/BearEnemy.h"
#include <vector>
#include <array>

using namespace::DirectX::SimpleMath;

SkeletalMeshVertexShader::SkeletalMeshVertexShader(VisualEntity* _entity)
	: VertexShader(_entity)
{
	LoadWithShaderReflection("VS_SkeletalMesh.cso");
}

void SkeletalMeshVertexShader::UpdateBuffer(uint8_t _dataID)
{
	Matrix world = mVisualEntity->GetWorldMatrix();
	world = world.Transpose();
	WriteWorldMatrix(&world);
	// スケルトンがあるかを確認する
	if (!mSkeleton.lock())
	{
		std::cout << "スケルトンがありません" << std::endl;
		return;
	}

	std::shared_ptr<Skeleton> validSkeleton = mSkeleton.lock();
	// スケルトンを構成しているボーンを取得
	std::vector<std::weak_ptr<Bone>> bones = validSkeleton->GetBonesVector();

	Matrix rootBoneMat = validSkeleton->GetRootBone().lock()->GetBoneMatrix();

	// ボーン行列、バインドポーズ行列を取得する
	std::array<std::vector<Matrix>, 2> boneMatrixes{};
	for (std::weak_ptr<Bone> bone : bones)
	{
		// ボーンがあるかを確認する
		if (!bone.lock())
		{
			continue;
		}
		boneMatrixes[0].emplace_back(bone.lock()->GetBoneMatrix().Transpose());
		boneMatrixes[1].emplace_back(bone.lock()->GetBindPoseMatrix().Transpose());
	}
	// 定数バッファ更新
	boneMatrixes[0].resize(200, Matrix::Identity);
	boneMatrixes[1].resize(200, Matrix::Identity);
	WriteBuffer(2, boneMatrixes[0].data());
	WriteBuffer(3, boneMatrixes[1].data());
}
