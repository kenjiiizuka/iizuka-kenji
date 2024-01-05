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

private:
	/** �A�E�g���C���J���[ */
	DirectX::SimpleMath::Color mOutlineColor;

public:
	/**
	* @fn UpdateBuffer
	* @brief �o�b�t�@�[�̍X�V����
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

	/**
	* @fn SetOutlineColor
	* @brief �A�E�g���C���J���[�̃Z�b�^�[
	* @param const DirectX::SimpleMath::Color (_color)
	* @return void
	*/
	inline void SetOutlineColor(const DirectX::SimpleMath::Color _color);

};

//---------- INLINES ----------

inline void OutlinePixelShader::SetOutlineColor(const DirectX::SimpleMath::Color _color)
{
	mOutlineColor = _color;
}