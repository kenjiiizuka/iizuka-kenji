/**
* @file AnimationSpriteComponent.h
* @brief AnimationSpriteComponent�N���X�̒�`
*/

#pragma once

//-------- INCLUDES --------
#include "SpriteComponent.h"

/**
* @class AnimationSpriteComponent
* @brief �e�N�X�`���A�j���[�V�������ł���X�v���C�g�R���|�[�l���g
*/
class AnimationSpriteComponent : public SpriteComponent
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AnimationSpriteComponent();

	/**
	* �f�X�g���N�^
	*/
	~AnimationSpriteComponent();

private:
	/** �A�j���[�V�����e�[�u�� */
	std::vector<uint8_t> mAnimationTable;

	/** �e�N�X�`����1�����̃T�C�Y */
	DirectX::SimpleMath::Vector2 mUVSize;

	/** �c���̕����� */
	DirectX::SimpleMath::Vector2 mSplit;

	/** �A�j���[�V�����������߂�t���[�� */
	float mAnimationFrame;

	/** �A�j���[�V�����Đ����Ă��邩 */
	bool mbIsPlay;

	/** ���[�v�Đ����邩 */
	bool mbIsLoop;

	/** �A�j���[�V�����J�n���Ă���̌o�ߎ��� �Ō�̃e�N�X�`���܂ł������烊�Z�b�g����� */
	float mElapsedTime;

	/** �\������e�N�X�`����X�̈ʒu */
	uint8_t mCurrentX;

	/** �\������e�N�X�`����Y�̈ʒu */
	uint8_t mCurrentY;

	/** �O�t���[���̃e�N�X�`����X�ʒu */
	uint8_t mPrevX;

public:
	/**
�@�@ * @fn Init
	 * @brief ����������
	 * @param DirectX::SimpleMath::Vector2 (_pos)
	 * @param DirectX::SimpleMath::Vector2 (_size)
	 * @param DirectX::SimpleMath::Vector4 (_diffuse)
�@�@ * @return void
�@�@*/
	void Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _size, DirectX::SimpleMath::Vector4 _vertexColor = { 1.0f,1.0f,1.0f,1.0f }) override;

	/**
	* @@fn Update
	* @brief �X�V����
	* @detail �A�j���[�V�����f�[�u����i�߂�
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

public:
	/**
	* @fn SetupAnimationTable
	* @brief �A�j���[�V�����e�[�u����ݒ肷��֐�
	* @detail �A�j���[�V�������������e�N�X�`���̏c���̕��������狁�߂�
	* @param const float (_xSplit)
	* @param const float (_ySplit)
	* @return void
	*/
	void SetupAnimationTable(const float _xSplit, const float _ySplit);

	/**
	* @fn SetLoop
	* @brief ���[�v�Đ����邩�̃Z�b�^�[
	* @param const bool (_loop)
	* @return void 
	*/
	inline void SetLoop(const bool _loop) noexcept;

	/**
	* @fn PlayAnimation
	* @brief �A�j���[�V�������Đ�����֐�
	* @return void
	*/
	inline void PlayAnimation() noexcept;

	/**
	* @fn StopAnimation
	* @brief �A�j���[�V�������~����֐�
	* @return void
	*/
	inline void StopAnimation() noexcept;

	/**
	* @fn IsPlay
	* @brief �A�j���[�V�����Đ����Ă��邩
	* @return bool true �Đ����Ă��邩 false �Đ����Ă��Ȃ�
	*/
	inline bool IsPlay() const noexcept;
};

//---------- INLINES -----------

inline void AnimationSpriteComponent::SetLoop(const bool _loop) noexcept
{
	mbIsLoop = _loop;
}

inline void AnimationSpriteComponent::PlayAnimation() noexcept
{
	mbIsPlay = true;
	mCurrentX = 0;
	mCurrentY = 0;
	mElapsedTime = 0.0f;
}

inline void AnimationSpriteComponent::StopAnimation() noexcept
{
	mbIsPlay = false;
}

inline bool AnimationSpriteComponent::IsPlay() const noexcept
{
	return mbIsPlay;
}
