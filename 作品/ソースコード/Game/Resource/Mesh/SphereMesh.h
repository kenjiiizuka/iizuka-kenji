/**
* @file SphereMesh.h
* @brief SphereMesh�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ------------
#include "../../Component/StaticMeshComponent/StaticMesh.h"

/**
* @class SphereMesh
* @brief �����b�V���N���X
* @detail �����b�V�����쐬���A�`�悵�Ă���
*/
class SphereMesh : public StaticMesh
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SphereMesh();

	/**
	* �f�X�g���N�^
	*/
	~SphereMesh();

private:
	/** ���������̕����� */
	uint16_t mDivisionHorizontal;

	/** ���������̕����� */
	uint16_t mDivisionVertical;

	/** ���a */
	float mRadius;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail SphereMesh�̍쐬������
	* @param const float     (_radius)
	* @param const uint16_t  (_divisionHorizontal)
	* @param const uint16_t  (_divisionVertical)
	* @param 
	*/
	void Initialize(const float _radius, const uint16_t _divisionHorizontal = 100, const uint16_t _divisionVertical = 100);

private:
	/**
	* @fn CreateVisualEntity
	* @brief �����b�V���̃f�[�^���쐬
	*/
	void CreateVisualEntity() override;

	/**
	* @fn MakeVertexData
	* @brief ���_�f�[�^�̍쐬
	* @param VisualEntityData::Description& (_desc) �쐬�������_�f�[�^���i�[�����
	* @return void
	*/
	void MakeVertexData(VisualEntityData::Description& _desc);

	/**
	* @fn MakeIndexData
	* @brief �C���f�b�N�X�f�[�^���쐬
	* @param VisualEntityData::Description& (_desc) �쐬�����C���f�b�N�X�f�[�^���i�[�����
	*/
	void MakeIndexData(VisualEntityData::Description& _desc);

};

