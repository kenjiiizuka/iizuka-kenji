/**
* @file WinLogo.h
* @brief WinLogo�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include "../GameObject.h"

class AnimationSpriteComponent;
class BlackPanel;

/**
* @class WinLogo
* @brief �������S�I�u�W�F�N�g
*/
class WinLogo : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	WinLogo();

	/**
	* �f�X�g���N�^
	*/
	~WinLogo();

private:
	/** ���S�X�v���C�g */
	std::weak_ptr<AnimationSpriteComponent> mSprite;

	/** �p�l�� */
	std::weak_ptr<BlackPanel> mPanel;

	/** �A�j���[�V�������I�������������� */
	bool mbIsFinishAnimation;

public:
	/**
	* @fn Init
	* @brief ����������
	* @detail �������S�\���p�̃R���|�[�l���g�ǉ�
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update(const double _deltaTime);

	/**
	* @fn IsInterpFinish
	* @brief ��Ԃ��I��������
	* @return bool
	*/
	inline bool IsAnimationFinish() const noexcept;

};

//---------- INLINES ----------

inline bool WinLogo::IsAnimationFinish() const noexcept
{
	return mbIsFinishAnimation;
}

