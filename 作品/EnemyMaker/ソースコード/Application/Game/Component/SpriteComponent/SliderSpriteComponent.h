/**
* @file SliderSpriteComponent.h
* @brief SpriteComponent�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ----------
#include "SpriteComponent.h"

/**
* @class SliderSpriteComponent
* @brief �ő�T�C�Y�����Ă����A�䗦��n�����ƂŒ��_�ʒu���ő�T�C�Y����̈ʒu�ɂ��Ă���܂�
*        �Q�[�W�ȂǂɎg�p���₷���悤�ɂ���Sprite
*/
class SliderSpriteComponent : public SpriteComponent
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SliderSpriteComponent();

	/**
	* �f�X�g���N�^
	*/
	~SliderSpriteComponent();

private:
	/** �ő�T�C�Y */
	DirectX::SimpleMath::Vector2 mMaxSize;

	/** ���݂̃X���C�_�[�̃T�C�Y */
	DirectX::SimpleMath::Vector2 mCurrentSliderSize;

	/** �X���C�_�[���ő�T�C�Y�̎���UV */
	DirectX::SimpleMath::Vector2 mMaxUV;

	/** ���݂�UV�@�X���C�_�[�̃T�C�Y�ƍ��킹���l */
	DirectX::SimpleMath::Vector2 mCurrentUV;

public:
	void Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _maxSize, DirectX::SimpleMath::Vector4 _vertexColor = {1.0f,1.0f,1.0f,1.0f});

	void Update(const double _deltaTime) override;

	/**
	* @fn SetSliderSize
	* @brief �X���C�_�[�̃T�C�Y�̃Z�b�^�[
	* @detail �T�C�Y�� 0 �` 1�ɐ��K�������l��n�����ƂŃX���C�_�[�T�C�Y�����߂Ă���
	* @param const float (_sliderSize_t)
	* @return void
	*/
	void SetSliderSize(const float _sliderSize_t);

	/**
	* @fn SetMaxSize
	* @brief �ő�T�C�Y�̃Z�b�^�[
	* @param const DirectX::SimpleMath::Vector2 (_maxSize)
	* @return void
	*/
	inline void SetMaxSize(const DirectX::SimpleMath::Vector2 _maxSize);

};

//--------- INLINES ---------

inline void SliderSpriteComponent::SetMaxSize(const DirectX::SimpleMath::Vector2 _maxSize)
{
	mMaxSize = _maxSize;
}