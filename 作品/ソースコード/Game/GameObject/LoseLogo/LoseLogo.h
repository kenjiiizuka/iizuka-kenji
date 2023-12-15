/**
* @file LoseLogo.h
* @brief LoseLogo�N���X
*/

#pragma once

//--------- INCLUDES ----------
#include "../GameObject.h"

//--------- �O���錾 ---------
class AnimationSpriteComponent;
class BlackPanel;

/**
* @class LoseLogo
* @brief �s�k�������̃��S�I�u�W�F�N�g
*/
class LoseLogo : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	LoseLogo();

	/**
	* �f�X�g���N�^
	*/
	~LoseLogo();

private:
	/** �X�v���C�g */
	std::weak_ptr<AnimationSpriteComponent> mSprite;

	/** �p�l�� */
	std::weak_ptr<BlackPanel> mPanel;

	/** �A�j���[�V�����̍Đ����I������ */
	bool mbIsFinishAnimation;

public:
	/**
	* @fn Init
	* @brief ����������
	* @detail �g�p����X�v���C�g�̐��������Ă��܂�
	* @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief �X�V����
	* @detail �X�V����
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn IsInterpFinish
	* @brief ��Ԃ��I����������Ԃ�
	* @return bool true ��Ԋ��� false ��ԏI��
	*/
	inline bool IsAnimationFinish() const noexcept;
};

//--------- INLINES ---------

inline bool LoseLogo::IsAnimationFinish() const noexcept
{
	return mbIsFinishAnimation;
}

