/**
* @file Fade.h
* @brief Fade�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ---------
#include <functional>
#include "../GameObject.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"


/**
* @class Fade
* @brief �t�F�[�h�C���A�t�F�[�h�A�E�g�p�̃I�u�W�F�N�g
*/
class Fade : public GameObject
{
public:
	/**
	* @enum FadeState
	* @brief Fade�̏�Ԃ�����
	*/
	enum FadeState : uint8_t
	{
		Fade_None = 0,   /**< �Ȃɂ����Ă��Ȃ���� */
		Fade_In,         /**< �t�F�[�h�C�� */
		Fade_Out,        /**< �t�F�[�h�A�E�g */
	};

public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	Fade();

	/**
	* �f�X�g���N�^
	*/
	~Fade();

private:
	/** �t�F�[�h�̏�� */
	FadeState mFadeState;

	/** �t�F�[�h�p�̃X�v���C�g */
	std::weak_ptr<SpriteComponent> mFadeSprite;

	/** �t�F�[�h�p�̃X�v���C�g�̃��l */
	float mAlpha;

	/** �t�F�[�h�̑��x */
	float mFadeSpeed;

	/** �t�F�[�h�̍��̏�Ԃ̍X�V���� */
	std::function<void(const double)> mFadeUpdate;

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

private:
	/**
	* @fn FadeInUpdate
	* @brief �t�F�[�h�C���̍X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void FadeInUpdate(const double _deltaTime);

	/**
	* @fn FadeOutUpdate
	* @brief �t�F�[�h�A�E�g�̍X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void FadeOutUpdate(const double _deltaTime);

public:
	/**
	* @fn FadeIn
	* @brief �t�F�[�h�C���J�n�֐�
	* @param const float (_fadeSpeed) �t�F�[�h�̑��x
	* @return void
	*/
	inline void FadeIn(const float _fedeSpeed = 2.0f) noexcept;

	/**
	* @fn FadeOut
	* @brief �t�F�[�h�A�E�g�J�n�֐�
	* @param const float (_fadeSpeed) �t�F�[�h�̑��x
	* @return void
	*/
	inline void FadeOut(const float _fadeSpeed = 2.0f) noexcept;

	/**
	* @fn IsFading
	* @brief �t�F�[�h������Ԃ�
	* @return bool true �t�F�[�h�� false �t�F�[�h���Ă��Ȃ�
	*/
	inline bool IsFading() const noexcept;

};

//--------- INLINES -----------

inline void Fade::FadeIn(const float _fadeSpeed) noexcept
{
	mFadeState = Fade_In;
	mAlpha = 1.0f;
	mFadeSpeed = _fadeSpeed;
	mFadeSprite.lock()->SetVisible(true);
	mFadeUpdate = std::bind(&Fade::FadeInUpdate, this, std::placeholders::_1);
}

inline void Fade::FadeOut(const float _fadeSpeed) noexcept
{
	mFadeState = Fade_Out;
	mAlpha = 0.0f;
	mFadeSpeed = _fadeSpeed;
	mFadeSprite.lock()->SetVisible(true);
	mFadeUpdate = std::bind(&Fade::FadeOutUpdate, this, std::placeholders::_1);
}

inline bool Fade::IsFading() const noexcept
{
	return mFadeState != Fade_None;
}
