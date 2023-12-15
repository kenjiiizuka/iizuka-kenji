/**
* @file AnimationSynchro.h
* @brief AnimationSynchro�N���X�̒�`
*/

#pragma once

//------------- INCLUDES ------------
#include <memory>
#include <SimpleMath.h>
#include "../../Game/Component/TransformComponent/Transform.h"

//---------- �O���錾 -----------
class SkeletalMesh;
class Bone;
class SkeletalMeshAnimationClip;
class GameObject;

/**
* @class AnimationSynchro
* @brief �A�j���[�V�����œ������b�V����GameObject�̍��W�𓯊�����N���X
*/
class AnimationSynchronizer
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AnimationSynchronizer();

	/**
	* �f�X�g���N�^
	*/
	~AnimationSynchronizer();

private:
	/** ��������X�P���^�����b�V�� */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;

	/** �A�j���[�V�����N���b�v */
	std::weak_ptr<SkeletalMeshAnimationClip> mAnimationClip;

	/** �����Ώۂ�SkeletalMesh��Root�{�[�� */
	std::weak_ptr<Bone> mBone;

	/** SkeletalMesh�̃I�[�i�[�I�u�W�F�N�g */
	GameObject* mMeshOwnerObject;

	/** �A�j���[�V�����J�n����SkeletalMesh�̃��[���h�s�� */
	DirectX::SimpleMath::Matrix mSkeletalMeshWorldMatrix;

	/** �X�P���^�����b�V���̃g�����X�t�H�[�� */
	Transform mSkeletalMeshTrans;

	/** ���[�g�{�[���̃g�����X�t�H�[�� */
	Transform mRootBoneTrans;

	/** ���W���� */
	bool mbSynchroPosition;

	/** ��]���� */
	bool mbSynchroRotation;

	/** �A�����ē������������Ă��邱�Ƃ����� */
	bool mbRepeated;

	/** ���[�g������Ă���ʒu����J�n����A�j���[�V�����Ȃ̂� */
	bool mbDisplacedStartAnimation;

	/** �����J�n���čŏ��̃t���[�������� */
	bool mbFirstFrame;

public:
	/**
	* @fn SynchroBegin
	* @brief ���������J�n����
	* @param std::shared_ptr<SkeletalMesh> (_skeletalMesh)
	* @param const bool                    (_synchroPosition)
	* @param const bool                    (_synchroRotation)
	* @param const bool                    (_repeated)
	* @param const bool                    (_displaced)
	* @return void
	*/
	void SynchroBegin(std::shared_ptr<SkeletalMesh> _skeletalMesh, const bool _synchroPosition, const bool _synchroRotation, const bool _repeated, const bool _displaced);

	/**
	* @fn Synchro
	* @brief �����X�V����
	* @detail ���[�g�������A�j���[�V�����ɍ��킹��GameObject�𓮂����Ă���
	* @return void
	*/
	void Synchro();

	/**
	* @fn SynchroEnd
	* @brief �����I������
	* @return void
	*/
	void SynchroEnd();

private:
	/**
	* @fn SynchroCollision
	* @brief �R���W�����Ɠ��������鏈��
	* @param Transform& (_rootBoneTrans)
	* @return void
	*/
	void SynchroCollision(Transform& _rootBoneTrans);

	/**
	* @fn RepeatSynchroSetup
	* @brief �A�����ē������������邽�߂̏���
	* @return void
	*/
	void RepeatSynchroSetup();

public:
	/**
	* @fn RepeatedEnd
	* @brief �A�������I����AnimationPlayer����`����֐�
	* @return void
	*/
	inline void RepeatedEnd() noexcept;

};
