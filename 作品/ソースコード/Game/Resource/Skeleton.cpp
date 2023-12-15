//-------------- INCLUDES ------------
#include <iostream>
#include "Skeleton.h"
#include "Socket.h"

Skeleton::Skeleton()
{
	// �����Ȃ�
}

Skeleton::~Skeleton()
{
	// �����Ȃ�
}

void Skeleton::Initialize(const std::weak_ptr<BoneAsset> _boneAsset)
{
	// �{�[���A�Z�b�g�̎Q�Ƃ��L�������m�F
	if (!_boneAsset.lock())
	{
		std::cout << "�{�[���A�Z�b�g�̎Q�Ƃ��g���܂���" << std::endl;
		return;
	}

	// �{�[�����쐬����
	CreateBoneFromBoneAsset(mRootBone,nullptr, _boneAsset);

	// �{�[�����ϒ��z���Map�ɓo�^����
	RegisterBoneMapAndBoneVector(mRootBone);

	// �{�[�����o�C���h�{�[�Y�̏�Ԃɂ���
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
	// �A�j���[�V���������{�[���s������߂�
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

	// �q�{�[���̎擾
	size_t numChild = 0;
	std::vector<std::shared_ptr<BoneAsset>> childBoneAssets;
	if (_boneAsset.lock()->HasChildren())
	{
		childBoneAssets = _boneAsset.lock()->GetChildBones();
		numChild = childBoneAssets.size();
	}

	// �{�[���̍쐬
	_bone = std::make_shared<Bone>();
	
	// �{�[��������
	_bone->Initialize(_boneAsset, _parentBone, numChild);

	// �q�{�[���̎擾
	std::vector<std::shared_ptr<Bone>> childBones(numChild);
	for (size_t boneAsset_i = 0; std::shared_ptr<Bone>& childBone : childBones)
	{
		CreateBoneFromBoneAsset(childBone, _bone, childBoneAssets[boneAsset_i]);
		boneAsset_i++;
	}

	// �q�{�[���̓o�^
	_bone->SetChildBones(childBones);

}

void Skeleton::RegisterBoneMapAndBoneVector(std::shared_ptr<Bone>& _bone)
{
	// �}�b�v�ɓo�^
	bool success = mBoneMap.try_emplace(_bone->GetBoneName(), _bone).second;
	if (!success)
	{
		std::cout << _bone->GetBoneName() << "�̓}�b�v�ɓo�^�ł��܂���ł���" << std::endl;
	}
	// �ϒ��z��ɒǉ�
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
	// �w�肳�ꂽ�e�{�[�������݂��邩�m�F
	if (!mBoneMap.contains(_parentBoneName))
	{
		return std::shared_ptr<Socket>();
	}

	// �}�b�v�ɓo�^����Ă��鎞��
	std::shared_ptr<Bone> validBone = mBoneMap[_parentBoneName].lock();

	// �\�P�b�g�̐���
	std::shared_ptr<Socket> socket = std::make_shared<Socket>();
	socket->Initialize(_socketTrans, _socketName, validBone);

	// �\�P�b�g���}�b�v�ɒǉ�
	mBoneMap.try_emplace(_socketName, socket);

	// �A�N�Z�X�p�̔z��ɒǉ�
	mBonesVector.emplace_back(socket);

	// �{�[���̊K�w�\���ɑg�ݍ���
	validBone->AddChildBone(socket);

	return socket;
}


