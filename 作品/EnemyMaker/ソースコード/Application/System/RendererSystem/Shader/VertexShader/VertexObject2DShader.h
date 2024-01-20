/**
* @file VertexObject2DShader.h
* @brief VertexObject2DShader�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ----------
#include "VertexShader.h"

/**
* @class VertexObject2DShader
* @brief 2D�I�u�W�F�N�g�`��p���_�V�F�[�_�[
*/
class VertexObject2DShader : public VertexShader
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param VisualEntity* (_entity) �̃V�F�[�_�[�̎g�p����`��I�u�W�F�N�g
	*/
	VertexObject2DShader(VisualEntity* _entity);

public:
	/**
	* @fn UpdateBuffer
	* @brief �X�V����
	* @param uint8_t (_dataID)
	* @return void
	*/
	virtual void UpdateBuffer(uint8_t _dataID);
};

