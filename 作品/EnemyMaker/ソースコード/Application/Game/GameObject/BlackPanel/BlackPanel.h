/**
* @file BlackPanel.h
* @brief BlackPanel�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include "../GameObject.h"

//---------- �O���錾 ----------
class SpriteComponent;

/**
* @class BlackPanel
* @brief �������̉�ʑS�̂𕢂����F�̃p�l��
*/
class BlackPanel : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BlackPanel();

	/**
	* �f�X�g���N�^
	*/
	~BlackPanel();

private:
	/** ���F�̃p�l����\������X�v���C�g */
	std::weak_ptr<SpriteComponent> mSprite;

	/** �p�l���̃��l */
	float mAlpha;

	/** ���l��Ԃɂ����鎞�� */
	float mAlphaInterpTime;

	/** ���l�̌��݂̕�Ԏ��� */
	float mCurrentAlphaInterpTime;

	/** ��Ԃ���t���O */
	bool mbInterp;

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
	* @param const double _deltaTime
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn InterpStart
	* @brief ��ԊJ�n����
	* @param const float (_interpTime) ��Ԃɂ����鎞��
	* @return void
	*/
	void InterpStart(const float _interpTime = 1.0f) noexcept;

	/**
	* @fn IsInterpFinish
	* @brief ��Ԃ��I����������Ԃ�
	* @return bool true ��ԏI�� false �⊮�� 
	*/
	inline bool IsInterpFinish() const noexcept;

};

//-------- INLIENS ---------

inline bool BlackPanel::IsInterpFinish() const noexcept
{
	return mAlpha >= 1.0f;
}