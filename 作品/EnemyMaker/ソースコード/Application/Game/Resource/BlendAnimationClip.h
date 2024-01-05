/**
* @file BlendAnimationClip
* @brief BlendAnimationClip.h
*/

#pragma once

//-------- INCLUDES -----------
#include <vector>
#include "SkeletalMeshAnimationClip.h"

/**
* @class BlendAnimationClip
* @brief �u�����h���ꂽ�A�j���[�V�����N���b�v��񋟂���
*/
class BlendAnimationClip : public SkeletalMeshAnimationClip
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param std::shared_ptr<SkeletalMeshAnimationClip> (_clip1)
	* @param std::shared_ptr<SkeletalMeshAnimationClip> (_clip2)
	* @param const float                                (_min)
	* @param const float                                (_max)
	* @param const float                                (_blendWeight)
	*/
	BlendAnimationClip(std::shared_ptr<SkeletalMeshAnimationClip> _clip1, std::shared_ptr<SkeletalMeshAnimationClip> _clip2, const float _max, const float _min, const float _blendWeight);

private:
	/** �u�����h�E�F�C�g */
	float mBlendWeight;

	/** �u�����h�̍ő�l */
	float mMaxBlendValue;

	/** �u�����h�̍ŏ��l */
	float mMinBlendValue;

	/** �u�����h����A�j���[�V���� */
	std::vector<std::weak_ptr<SkeletalMeshAnimationClip>> mBlendAnimation;

	/** �N���b�v2�̃`�����l�� */
	std::vector<Channel> mChannelClip2;

	/** ���Ȃ����̃`�����l���̐� */
	size_t mMinChannelNum;

public:
	/**
�@�@ * @fn�@Begin
�@�@ * @brief �A�j���[�V�����J�n����
�@�@ * @return void
�@�@*/
	void Begin() override;

	/**
	* @fn CalucAnimationMatrix
	* @brief �`�����l���̎w�肳�ꂽ���Ԃ̃A�j���[�V�����}�g���b�N�X��Ԃ��֐�
	* @param Channel& (_channel)
	* @param const double (_time)
	* @param DirectX::SimpleMath::Matrix& (_animationMatrix)
	* @return void
	*/
	void CalucAnimationMatrix(Channel& _channel, const double _time, DirectX::SimpleMath::Matrix& _animationMatrix) override;

private:
	/**
�@�@ * @fn�@AnimationDataNormalize
�@�@ * @brief �A�j���[�V�����f�[�^�̐��K��������֐�
	 * @param std::vector<Channel>& (_channel) �A�j���[�V�����f�[�^
	 * @param const float& (_scaleFactor) ���K������ۂ̃X�P�[�����O�̒l
�@�@ * @return void
�@�@*/
	void AnimationDataNormalize(std::vector<Channel>& _channel, const float _scaleFactor);

public: 
	/**
�@�@ * @fn�@InputBlendValue
�@�@ * @brief �u�����h�̒l����͂���֐�
	 * @param const float (_value) ���͒l
�@�@ * @return void
�@�@*/
	void InputBlendValue(const float& _value);

	/** 
	* @dn SetBlendMaxValue
	* @brief �u�����h�l���v�Z����͈̔͂̍ő�l���Z�b�g����
	* @param const float _max
	* @return void
	*/
	inline void SetBlendMaxValue(const float _max) noexcept;

};

//----------- INLINES ----------

inline void BlendAnimationClip::SetBlendMaxValue(const float _max) noexcept
{
	mMaxBlendValue = _max;
}