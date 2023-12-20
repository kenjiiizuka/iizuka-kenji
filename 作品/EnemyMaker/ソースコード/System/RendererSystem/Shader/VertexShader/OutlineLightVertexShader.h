/**
* @file OutlineLightVertexShader.h
* @brief OutlineLightVertexShader�N���X
*/

#pragma once

//--------- INCLUDES ---------
#include "VertexShader.h"

/**
* @class OutlineLightVertexShader
* @brief �X�^�e�B�b�N���b�V���̃A�E�g���C���`��p�̃V�F�[�_�[
*/
class OutlineLightVertexShader : public VertexShader
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param VisualEntity* (_entity)
	*/
	OutlineLightVertexShader(VisualEntity* _entity);

	/**
	* �f�X�g���N�^
	*/
	~OutlineLightVertexShader();

private:
	/** �A�E�g���C���̑��� */
	float mOutlineThickness;

private:
	/**
	* @fn UpdateBuffer
	* @brief �萔�o�b�t�@�\�̍X�V����
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

public:
	/**
	* @fn SetOutlineThickness
	* @brief �A�E�g���C���̑������Z�b�g����
	* @param const float (_thickness)
	* @return void
	*/
	inline void SetOutlineThickness(const float _thickness) noexcept;

};

//------------ INLINES -------------

inline void OutlineLightVertexShader::SetOutlineThickness(const float _thickness) noexcept
{
	mOutlineThickness = _thickness;
}