//-------------- INCLUDES --------------
#include <iostream>
#include "SkeletalMeshVertexShader.h"
#include "../../VisualEntity/VisualEntity.h"
#include "../../../../Utility/MathLibrary.h"
#include "../../../../Game/Resource/Skeleton.h"
#include "../../../../Game/Resource/Bone.h"
#include "../../../../Utility/Debug.h"
#include "../../../../Game/GameObject/Enemy/Bear/BearEnemy.h"
#include "../ShaderStruct.h"
#include "../../../../Game/Scene/Scene.h"
#include "../../../../Game/GameObject/Light/LightBase.h"
#include "../../../../Game/Scene/SceneManager.h"
#include <vector>
#include <array>

using namespace::DirectX::SimpleMath;

SkeletalMeshVertexShader::SkeletalMeshVertexShader(VisualEntity* _entity)
	: VertexShader(_entity)
{
	LoadWithShaderReflection("VS_SkeletalMesh.cso");
	mbIsDropShadow = true;
}

void SkeletalMeshVertexShader::UpdateBuffer(uint8_t _dataID)
{
	Matrix world = mVisualEntity->GetWorldMatrix();
	world = world.Transpose();
	WriteWorldMatrix(&world);
	// �X�P���g�������邩���m�F����
	if (!mSkeleton.lock())
	{
		std::cout << "�X�P���g��������܂���" << std::endl;
		return;
	}

	std::shared_ptr<Skeleton> validSkeleton = mSkeleton.lock();
	// �X�P���g�����\�����Ă���{�[�����擾
	std::vector<std::weak_ptr<Bone>> bones = validSkeleton->GetBonesVector();

	Matrix rootBoneMat = validSkeleton->GetRootBone().lock()->GetBoneMatrix();

	// �{�[���s��A�o�C���h�|�[�Y�s����擾����
	std::array<std::vector<Matrix>, 2> boneMatrixes{};
	for (std::weak_ptr<Bone> bone : bones)
	{
		// �{�[�������邩���m�F����
		if (!bone.lock())
		{
			continue;
		}
		boneMatrixes[0].emplace_back(bone.lock()->GetBoneMatrix().Transpose());
		boneMatrixes[1].emplace_back(bone.lock()->GetBindPoseMatrix().Transpose());
	}
	// �萔�o�b�t�@�X�V
	boneMatrixes[0].resize(200, Matrix::Identity);
	boneMatrixes[1].resize(200, Matrix::Identity);
	WriteBuffer(2, boneMatrixes[0].data());
	WriteBuffer(3, boneMatrixes[1].data());

	// �}�e���A���̃Z�b�g
	VisualEntityData::Material mat = mVisualEntity->GetVisualEntityData(_dataID)->GetMaterial();
	MATERIAL material;
	material.Ambient = mat.mAmbient;
	material.Diffuse = mat.mDiffuse;
	material.Emission = mat.Emission;
	material.Shininess = mat.mShininess;
	material.Specular = mat.mSpecular;
	WriteBuffer(4, &material);

	// ���C�g�̃Z�b�g
	std::shared_ptr<LightBase> light = SceneManager::GetInstance().GetCurrentScene().lock()->GetGameObject<LightBase>();
	Vector4 lightBuffer[3] = {
		{0.0f,-1.0f,0.0f,0.0f},
		{1.0f,1.0f,1.0f,1.0f},
		{0.3f,0.3f,0.3f,0.3f}
	};
	if (light)
	{
		GameObject* owner = mVisualEntity->GetOwnerObject();
		Vector3 direction = owner ? -owner->GetComponent<TransformComponent>()->GetPosition() - light->GetPosition() : light->GetDirection();
		lightBuffer[0] = { direction.x, direction.y, direction.z, 0.0f };
		lightBuffer[1] = light->GetDiffuse();
		lightBuffer[2] = light->GetAmbient();
	}
	WriteBuffer(5, &lightBuffer);

}
