/**
* @file HitStopComponent.h
* @brief HitStopComponent�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ----------
#include "../Component.h"

/**
* @class HitStopComponent
* @brief HitStop�֐����g�p���邱�ƂŃI�[�i�[�I�u�W�F�N�g�Ƀq�b�g�X�g�b�v��������
* @detail �I�[�i�[��TimeDilation��ω������ăq�b�g�X�g�b�v�������Ă���B
*         �q�b�g�X�g�b�v�Ɠ�����TimeDilation���g�p�����������������ꍇ�͂ǂ��炩�Е����������ł��Ȃ��\��������̂Œ���
*/
class HitStopComponent : public Component
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	HitStopComponent();

	/**
	* �f�X�g���N�^
	*/
	~HitStopComponent();

protected:
	/** �q�b�g�X�g�b�v�������鎞�� */
	double mHitStopSeconds;
	
	/** �q�b�g�X�g�b�v�������n�߂Ă���̌o�ߎ��� */
	double mElapsedStopTime;

	/** �I�[�i�[�̃q�b�g�X�g�b�v��������O�̃^�C���_�C���[�V���� */
	double mOwnerDefaultTimeDilation;

	/** �q�b�g�X�g�b�v���������Ă��邩�\���t���O */
	bool mbStop;
public:
	/**
	* @fn HitStop
	* @brief �q�b�g�X�g�b�v��������֐�
	* @detail �A���g�p����ƃq�b�g�X�g�b�v�������葱����̂Œ���
	* @param const double (_stopPower)  �q�b�g�X�g�b�v����  0�`1�͈̔͂Ŏw�肵�Ă������� 0���q�b�g�X�g�b�v�Ȃ� 1�����S��~����q�b�g�X�g�b�v
	* @param const double (_stopSeconds) �q�b�g�X�g�b�v����b�� �P�ȏ�̒l���w�肷�邱�ƂŃq�b�g�X�g�b�v��������܂�
	* @param const double (_defaultTimeDilation) �q�b�g�X�g�b�v���I������ɖ߂�^�C���_�C���[�V����
	* @return void
	*/
	void HitStop(const double _stopPower, const double _stopSeconds, const double _defaultTimeDilation);

	/**
	* @fn Update
	* @brief �X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;
};
