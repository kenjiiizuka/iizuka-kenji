/**
* @file Skeleton.h
* @brief Skeleton�N���X�̒�`
*/

#pragma once

//----------- INCLUDES -----------
#include <memory>
#include <unordered_map>
#include "../../System/AssetSystem/SkeletalMesh/BoneAsset.h"
#include "../Component/TransformComponent/Transform.h"

//------------ �O���錾 -----------
class Bone;
class Socket;

/**
* @class Skeleton
* @brief SkeletalMesh�̃A�j���[�V������ό`�𐧌䂷�邽�߂̍��g��
*/
class Skeleton
{
public:
	/**
	 * �f�t�H���g�R���X�g���N�^
	*/
	Skeleton();

	/**
	 * �f�X�g���N�^
	*/
	~Skeleton();
	
private:
	/** ���[�g�{�[�� */
	std::shared_ptr<Bone> mRootBone;
	
	/** ���ׂẴ{�[���ɑ΂��ăA�N�Z�X�������ꍇ�p��vector�Ƀ{�[���f�[�^��ێ����� */
	std::vector<std::weak_ptr<Bone>> mBonesVector;

	/** �{�[���}�b�v �{�[�����ŃA�N�Z�X���₷�����邽�� */
	std::unordered_map<std::string ,std::weak_ptr<Bone>> mBoneMap;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @param const std::weak_ptr<BoneAsset> (_boneAsset)
	*/
	void Initialize(const std::weak_ptr<BoneAsset> _boneAsset);

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update();

	/**
	* @fn Draw
	* @brief Skeleton��`�悷��֐�
	* @return void
	*/
	void Draw();

	/**
	* @fn Animate
	* @brief Skeleton���A�j���[�V����������
	* @return void
	*/
	void Animate();

	/**
	* @fn CalucWorldBoneMatrix
	* @brief ����Skeleton���\�����Ă���Bone��World�s����v�Z����
	* @param const DirectX::SimpleMath::Matrix& (_skeletalMeshWorldMatrix)
	* @return void
	*/
	void CalucWorldBoneMatrix(const DirectX::SimpleMath::Matrix& _skeletalMeshWorldMatrix);

private:
	/**
	 * @fn CreateBoneFromBoneAsset
	 * @brief �{�[���A�Z�b�g����{�[�����\������
	 * @param std::shared_ptr<Bone>&          (_bone)
	 * @param std::shared_ptr<Bone>           (_parentBone)
	 * @param const std::weak_ptr<BoneAsset>  (_boneAsset)
	 * @return void
	*/
	void CreateBoneFromBoneAsset(std::shared_ptr<Bone>& _bone, std::shared_ptr<Bone> _parentBone, const std::weak_ptr<BoneAsset> _boneAsset);

	/**
	* @fn RegisterBoneMapAndBoneVector
	* @brief �{�[�����}�b�v�Ɖϒ��z��ɑ������ċN�֐�
	* @param std::shared_ptr<Bone>& (_bone)
	* @return void
	*/
	void RegisterBoneMapAndBoneVector(std::shared_ptr<Bone>& _bone);

	/**
	* @fn OutPutBoneName
	* @brief �n���ꂽ�{�[���ȉ��̊K�w���{�[���̖��O��\������
	* @param std::shared_ptr<Bone> (_bone)
	* @return void
	*/
	void OutPutBoneName(std::shared_ptr<Bone> _bone);

public:
	/**
	* @fn CreateSocket
	* @brief �\�P�b�g���쐬����֐�
	* @param const std::string&   (_parentBoneName)
	* @param const Transform&     (_socketTrans)
	* @param const std::string&   (_socketName)
	* @return void
	*/
	std::shared_ptr<Socket> CreateSocket(const std::string& _parentBoneName, const Transform& _socketTrans, const std::string& _socketName);

	/**
	* @fn GetBoneVector
	* @brief ���ׂẴ{�[�����i�[���Ă���z���Ԃ�
	* @return std::vector<std::weak_ptr<Bone>>
	*/
	inline std::vector<std::weak_ptr<Bone>> GetBonesVector() const;

	/**
	* @fn GetBoneByName
	* @brief �{�[���𖼑O�ɂ���Ď擾����
	* @param const std::string& (_boneName)
	* @return std::weak_ptr<Bone>
	*/
	inline std::weak_ptr<Bone> GetBoneByName(const std::string& _boneName) const;

	/**
	* @fn GetRootBone
	* @brief ���[�g�{�[���̃Q�b�^�[
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
	// �L�[������ΕԂ�
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
