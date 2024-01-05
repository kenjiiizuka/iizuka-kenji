/**
* @file RingBlockObject
* @brief RingBlockObject.h
*/

#pragma once

//----------- INCLUDES ---------
#include "../GameObject.h"

/**
* @class RingBlockObject
* @brief �퓬�G���A�O�ɏo�Ȃ��悤�ɂ��邽�߂̃I�u�W�F�N�g
*/
class CircleBlockObject : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CircleBlockObject();

	/**
	* �f�X�g���N�^
	*/
	~CircleBlockObject();

public:
	/**
	* @fn Init
	* @brief ����������
	* @return void
	*/
	void Init() override;

private:
	/** �����O�̔��a */
	float mRingRadius;

};

