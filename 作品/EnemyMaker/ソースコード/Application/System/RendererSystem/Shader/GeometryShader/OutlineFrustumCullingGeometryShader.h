/**
* @file OutlineFrustumCullingGeometryShader.h
* @brief OutlineFrustumCullingGeometryShader�N���X�̒�`
*/
#pragma once

//---------- INCLUDES ------------
#include "GeometryShader.h"

/**
* @class OutlineFrustumCullingGeometryShader
* @brief �A�E�g���C���p�̃t���X�g�����J�����O�V�F�[�_�[
*/
class OutlineFrustumCullingGeometryShader : public GeometryShader
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param VisualEntity* (_entity) ���̃V�F�[�_�[���g�p����`��I�u�W�F�N�g
	*/
	OutlineFrustumCullingGeometryShader(VisualEntity* _entity);

	/**
	* �f�X�g���N�^
	*/
	~OutlineFrustumCullingGeometryShader();

	/**
	* @fn UpdateBuffer
	* @brief �o�b�t�@�[�̍X�V����
	* @param uint8_t (_dataID)
	* @return void
	*/
	void UpdateBuffer(uint8_t _dataID);

};

