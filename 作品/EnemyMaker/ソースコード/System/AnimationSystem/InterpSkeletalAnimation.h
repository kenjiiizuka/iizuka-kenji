/**
* @file InterpSkeleton.h
* @brief InterpSkeleton�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include <memory>
#include <unordered_map>
#include <string>
#include <SimpleMath.h>
#include "../../System/AssetSystem/SkeletalMesh/SkeletalMeshAnimationData.h"

//---------- �O���錾 ----------
class Bone;
class Skeleton;
class SkeletalMeshAnimationClip;

/**
* @class InterpSkeleton
* @brief �n���ꂽSkeleton�̊e�{�[���̈ʒu���w�肳�ꂽSkeleton�̃{�[���̈ʒu�ɕ�Ԃ���
*/
class InterpSkeletalAnimation
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	InterpSkeletalAnimation();

	/**
	* �f�X�g���N�^
	*/
	~InterpSkeletalAnimation();

private:
	/** ��Ԃɂ����鎞�� */
	float mInterpTime;

	/** �x�[�X�̃A�j���[�V�����N���b�v�̕�ԊJ�n�ʒu */
	float mBaseInterpStartTime;

	/** ��Ԑ�̃A�j���[�V�����N���b�v�̈ʒu */
	float mToInterpClipTime;

	/** ��ԏI���t���O */
	bool mbFinish;

	/** ��Ԑ�̃A�j���[�V�����N���b�v */
	std::weak_ptr<SkeletalMeshAnimationClip> mInterpToClip;

	/** ��Ԃ̃x�[�X�̃A�j���[�V�����N���b�v */
	std::weak_ptr<SkeletalMeshAnimationClip> mInterpBaseClip;

public:
	/**
	* @fn InterpBegin
	* @brief ��Ԃ̊J�n����
	* @param const float                                      (_interpTime)              ��Ԃɂ����鎞��
	* @param const std::shared_ptr<Skeleton>                  (_interpSkeleton)          ��ԑΏۂ�Skeleton
	* @param const float                                      (_baseInterpStartTime)     ��Ԃ̃x�[�X�A�j���[�V�����̕�Ԃ��J�n����ʒu
	* @param const float                                      (_toInterpClipTime)        ��Ԑ�̃A�j���[�V�����N���b�v�̕�Ԉʒu
	* @param const std::shared_ptr<SkeletalMeshAnimationClip> (_animationClipInterpBase) ��Ԃ̃x�[�X�A�j���[�V�����N���b�v
	* @param const std::shared_ptr<SkeletalMeshAnimationClip> (_animationClipInterpTo)   ��Ԑ�A�j���[�V�����N���b�v
	* @return void
	*/
	void InterpBegin(const float _interpTime, const std::shared_ptr<Skeleton> _interpSkeleton, const float _baseInterpStartTime, const float _toInterpClipTime, const std::shared_ptr<SkeletalMeshAnimationClip> _animationClipInterpBase, const std::shared_ptr<SkeletalMeshAnimationClip> _animationClipInterpTo);
	
	/**
	* @fn SkeletonInterp
	* @brief ��ԏ���
	* @param const float (_time)
	* @return bool true ��ԏI�� false ��Ԓ�
	*/
	bool Interp(const float _time, std::shared_ptr<Skeleton> _skeleton);

private:
	/**
	* @fn CalucInterpKey
	* @brief �`�����l���Ԃŕ�Ԃ���
	* @param Channel              (_baseChannel)
	* @param Channel              (_toChannel)
	* @param DirectX::SimpleMath& (_animationMatrix)
	* @param const float          (_t)
	* @return void
	*/
	void CalcuInterpKey(Channel _baseChannel, Channel _toChannel, DirectX::SimpleMath::Matrix& _animationMatrix, const float _t);
};

