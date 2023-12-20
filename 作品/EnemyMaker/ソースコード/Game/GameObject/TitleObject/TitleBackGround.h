/**
* @file TitleBackGround.h
* @brief TitleBackGround�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ----------
#include "../GameObject.h"

//----------- INCLUDES ------------
class SpriteComponent;

/**
* @class TitleBackGround
* @brief �^�C�g���̃o�b�O�O���E���h�I�u�W�F�N�g
*/
class TitleBackGround : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	TitleBackGround();

	/**
	* �f�X�g���N�^
	*/
	~TitleBackGround();

private:
	/** ���C���[�P�X�v���C�g */
	std::weak_ptr<SpriteComponent> mLayer1Sprite;

	/** ���C���[2�X�v���C�g*/
	std::weak_ptr<SpriteComponent> mLayer2Sprite;

	/** �^�C�g�����S */
	std::weak_ptr<SpriteComponent> mTitleLogo;

	/** ���C���[2�̃G�~�b�V���� */
	DirectX::SimpleMath::Color mLayer2Emission;

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
	* @return void
	*/
	void Update(const double _deltaTime) override;



};

