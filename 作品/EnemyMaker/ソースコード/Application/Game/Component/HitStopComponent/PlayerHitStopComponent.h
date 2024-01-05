/**
* @file PlayerHitStopComponent.h
* @brief PlayerHitStopComponent�N���X�̒�`
*/
#pragma once

//----------- INCLUDES -------------
#include "HitStopComponent.h"

/**
* @class PlayerHitStopComponent
* @brief �v���C���[��p�̃q�b�g�X�g�b�v�R���|�[�l���g
* @detail �^�����_���[�W�ɂ���ăq�b�g�X�g�b�v�̋����A���Ԃ�ݒ肷��
*         �g�p����ۂ́ASetAttackDamage�֐��ŗ^�����_���[�W��ݒ肵�Ă���HitStop�֐����g�p���邱��
*         �_���[�W���ݒ肳��Ă��Ȃ��ꍇ�̓q�b�g�X�g�b�v��������Ȃ�
*/
class PlayerHitStopComponent : public HitStopComponent
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	PlayerHitStopComponent();

	/**
	* �f�X�g���N�^
	*/
	~PlayerHitStopComponent();

private:
	/** �G�ɗ^����_���[�W */
	float mDamage;

	/** �q�b�g�X�g�b�v�̏d�݁@�_���[�W * �d�݂Ńq�b�g�X�g�b�v�̎��Ԃ����߂� */
	float mHitStopSecondWeight;

public:
	/**
	* @HitStop
	* @brief �q�b�g�X�g�b�v��������֐�
	* @detail �A���g�p����ƃq�b�g�X�g�b�v�������葱����̂Œ���
	*         �ݒ肳��Ă���_���[�W����q�b�g�X�g�b�v�̋����A������ݒ肷��
	* @return void
	*/
	void HitStop();

	/**
	* @fn SetAttackDamage
	* @brief �q�b�g�X�g�b�v�̋����A���Ԃ�ݒ肷�邽�߂ɓG�ɗ^����_���[�W����ݒ肷��֐�
	* @param const float (_damage)
	* @return void
	*/
	inline void SetAttackDamage(const float _damage);
};

//-------- INLINES ---------

inline void PlayerHitStopComponent::SetAttackDamage(const float _damage)
{
	mDamage = _damage;
}