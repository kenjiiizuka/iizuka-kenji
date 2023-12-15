/**
* @file PlayerAttackCapsuleCollisionComponent.h
* @brief PlayerAttackCapsuleCollisionComponent�N���X�̒�`
*/

#pragma once

//------------ INCLUDES -----------
#include "CapsuleCollisionComponent.h"

/**
* @class PlayerAttackCapsuleCollisionComponent
* @brief �v���C���[�̕���ɕt����U���p�̃R���W����
*/
class PlayerAttackCapsuleCollisionComponent : public CapsuleCollisionComponent
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	PlayerAttackCapsuleCollisionComponent();

	/**
	* �f�X�g���N�^
	*/
	~PlayerAttackCapsuleCollisionComponent();

private:
	/** �U���_���[�W */
	float mDamage;

public:
	/**
	* @fn Init
	* @brief ����������
	* @param const float (_height)
	* @param const float (_radius)
	* @param const float (_damage)
	* @return void
	*/
	void Init(const float _height, const float _radius, const float _damage);

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn ExecuteBeginHit
	* @brief �I�[�i�[��BeginHit�֐������s����֐�
	* @detail �A���œ����邱�Ƃ�h�����߂ɁA�ŏ��ɓ��������R���W������BeginHit�֐��ɓn�������ɂ��Ă���
	* @return void
	*/
	void ExecuteBeginHit() override;

};

