/**
* @file PlayEffectNotify.h
* @brief PlayEffectNotify�N���X
*/

#pragma once

//--------- INCLUDES -----------
#include "../SkeletalMeshComponent/AnimationNotify.h"
#include <string>
#include <Effekseer.h>
#include <SimpleMath.h>

//---------- �O���錾 ---------
class AssetHandle;

/**
* @class PlayEffectNotify
* @brief �G�t�F�N�g���Đ�����ʒm
* @detail �A�^�b�`����Ă���A�j���[�V���������Ă���SkeletalMesh�̃I�[�i�[�̃Q�[���I�u�W�F�N�g�̈ʒu�ɃG�t�F�N�g���Đ�����
*         Offset��ݒ肵�ăG�t�F�N�g�����ʒu�𒲐��ł���@Offset�̋�Ԃ�SkeletalMesh�̃I�[�i�[�̃Q�[���I�u�W�F�N�g�̃��[�J��
*         Scale��SkeletalMesh�̃I�[�i�[�̃Q�[���I�u�W�F�N�g�̉e�����󂯂Ȃ�
*         ��]��SkeletalMesh�̃I�[�i�[�̃Q�[���I�u�W�F�N�g�̉�]���ݒ肳���
*/
class PlayEffectNotify : public AnimationNotify
{
public:
	/**
	* �R���X�g���N�^
	*
	* @param[in] std::weak_ptr<SkeletalMeshAnimation> (_attachAnimation) �A�^�b�`�����A�j���[�V����
	*/
	PlayEffectNotify(SkeletalMeshAnimationClip* _attachAnimation, float _attachFrame);

	/**
	* �f�X�g���N�^
	*/
	~PlayEffectNotify();

private:
	/** �G�t�F�N�g�A�Z�b�g�ւ̃n���h�� */
	std::shared_ptr<AssetHandle> mAssetHandle;

	/** �G�t�F�N�g�n���h�� */
	Effekseer::Handle mEffectHandle;

	/** �I�t�Z�b�g�ʒu */
	DirectX::SimpleMath::Vector3 mOffsetPosition;

	/** �X�P�[�� */
	DirectX::SimpleMath::Vector3 mScale;
public:
	/**
�@�@ * @fn�@NotifyBegin
�@�@ * @brief �ʒm�̊J�n����
�@�@ * @return void
�@�@*/
	void NotifyBegin() override;

	/**
	* @fn LoadEffect
	* @brief �G�t�F�N�g�ǂݍ��݊֐�
	* @param std::string_view (_filePath)
	*/
	void LoadEffect(std::string_view _filePath);

	/**
	* @fn SetOffset
	* @brief �I�t�Z�b�g�̃Z�b�^�[
	* @param const DirectX::SimpleMath::Vector3 (_offset)
	* @return void
	*/
	inline void SetOffset(const DirectX::SimpleMath::Vector3 _offset) noexcept;

	/**
	* @fn GetOffset
	* @brief �I�t�Z�b�g���擾
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetOffset() const noexcept;

	/**
	* @fn SetScale
	* @brief �X�P�[���̃Z�b�^�[
	* @param const float (_scale)
	* @return void
	*/
	inline void SetScale(const float _scale) noexcept;

	/**
	* @fn SetScale
	* @brief �X�P�[���̃Z�b�^�[
	* @param const DirectX::SimpleMath::Vector3 (_scale)
	* @return void
	*/
	inline void SetScale(const DirectX::SimpleMath::Vector3 _scale) noexcept;

	/**
	* @fn GetScale
	* @brief �X�P�[���̎擾
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetScale() const noexcept;

};

//----------- INLINES ------------

inline void PlayEffectNotify::SetOffset(const DirectX::SimpleMath::Vector3 _offset) noexcept
{
	mOffsetPosition = _offset;
}

inline DirectX::SimpleMath::Vector3 PlayEffectNotify::GetOffset() const noexcept
{
	return mOffsetPosition;
}

inline void PlayEffectNotify::SetScale(const float _scale) noexcept
{
	mScale = {_scale, _scale, _scale};
}

inline void PlayEffectNotify::SetScale(const DirectX::SimpleMath::Vector3 _scale) noexcept
{
	mScale = _scale;
}

inline DirectX::SimpleMath::Vector3 PlayEffectNotify::GetScale() const noexcept
{
	return mScale;
}
