/**
* @file OutlinePixelShader.h
* @brief OutlinePixelShader�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include "PixelShader.h"

/**
* @class OutlinePixelShader
* @brief �A�E�g���C���`��p�̃s�N�Z���V�F�[�_�[
*/
class OutlinePixelShader : public PixelShader
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param VisualEntity* (_entity) ���̃V�F�[�_�[���g���`��I�u�W�F�N�g
	*/
	OutlinePixelShader(VisualEntity* _entity);

	/**
	* �f�X�g���N�^
	*/
	~OutlinePixelShader();
};


