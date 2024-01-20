/**
* @file TexturePixelShader.h
* @brief TexturePixelShader�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ---------
#include "PixelShader.h"

/**
* @class TexturePixelShader
* @brief �e�N�X�`���݂̂�\������s�N�Z���V�F�[�_�[
*/
class TexturePixelShader : public PixelShader
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param VisualEntity* (_entity) 
	*/
	TexturePixelShader(VisualEntity* _entity);

	/**
	* @fn UpdateBuffer
	* @brief �萔�o�b�t�@�X�V����
	* @return uint8_t (_dataID)
	*/
	void UpdateBuffer(uint8_t _dataID) override;
};

