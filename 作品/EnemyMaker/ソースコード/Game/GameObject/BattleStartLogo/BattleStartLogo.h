/**
* @file BattleStartLogo.h
* @brief BattleStartLogo�N���X�̒�`
*/

#pragma once


//---------- INCLUDES --------
#include "../GameObject.h"

//---------- �O���錾 --------
class AnimationSpriteComponent;

/**
* @class BattleStartLogo
* @brief �퓬�J�n�̃��S
*/
class BattleStartLogo : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BattleStartLogo();

	/**
	* �f�X�g���N�^
	*/
	~BattleStartLogo();

private:
	/** �A�j���[�V�������I�������� */
	bool mbIsAnimationFinish;

	/** ���S�\���X�v���C�g */
	std::weak_ptr<AnimationSpriteComponent> mSprite;

public:
	/**
	* @fn Init
	* @brief ����������
	* @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief �X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn IsInterpFinish
	* @brief ��Ԃ��I����������Ԃ�
	* @return bool true ��ԏI�� false �I�����Ă��Ȃ�
	*/
	inline bool IsAnimationFinish() const noexcept;

};

//-------- INLINES ---------

inline bool BattleStartLogo::IsAnimationFinish() const noexcept
{
	return mbIsAnimationFinish;
}



