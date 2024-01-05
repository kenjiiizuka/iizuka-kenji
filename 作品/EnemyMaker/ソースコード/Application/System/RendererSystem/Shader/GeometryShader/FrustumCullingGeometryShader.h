/**
* @file FrustumCullingGeometryShader.h
* @brief FrustumCullingGeometryShader�N���X�̒�`
*/
#pragma once

//---------- INCLUDES ----------
#include "GeometryShader.h"

/**
* @class FrustumCullingGeometryShader
* @brief �t���X�g�����J�����O�p�W�I���g���V�F�[�_�[
*/
class FrustumCullingGeometryShader : public GeometryShader
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param VisualEntity* (_entity) ���̃V�F�[�_�[���g�p����`��I�u�W�F�N�g
	*/
	FrustumCullingGeometryShader(VisualEntity* _entity);

	/**
	* �f�X�g���N�^
	*/
	~FrustumCullingGeometryShader();

	/**
	* @fn UpdateBuffer
	* @brief �o�b�t�@�[�̍X�V����
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID) override;

};

