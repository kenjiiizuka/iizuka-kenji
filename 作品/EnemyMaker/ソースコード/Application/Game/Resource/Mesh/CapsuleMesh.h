/**
* @file CapsuleMesh.h
* @brief CapsuleMesh�N���X��`
*/

#pragma once

//------------ INCLUDES -----------
#include "../../Component/StaticMeshComponent/StaticMesh.h"

/**
* @class CapsuleMesh
* @brief �J�v�Z���^�̃��b�V����\���쐬����
*/
class CapsuleMesh : public StaticMesh
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CapsuleMesh();

	/**
	* �f�X�g���N�^
	*/
	~CapsuleMesh();

private:
	/** �J�v�Z���̔��a */
	float mRadius;

	/** ���� */
	float mHeight;

	/** ���������̕����� */
	uint16_t mDivisionHorizontal;

	/** ���������̕����� */
	uint16_t mDivisionVertical;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @param const float    (_radius)
	* @param const float    (_height)
	* @param const uint16_t (_divisionHorizontal)
	* @param const uint16_t (_divisionVertical)
	* @return void
	*/
	void Initialize(const float _radius, const float _height, const uint16_t _divisionHorizontal, const uint16_t _divisionVertical);

	/**
	* @fn Draw
	* @brief �`�揈��
	* @detail �Z�b�g���ꂽ�g�����X�t�H�[������X�P�[�����������s����v�Z���Ă��܂�
	* @return void
	*/
	void Draw() override;

private:
	/**
	* @fn CreateVisualEntity
	* @brief �J�v�Z�����b�V���̃f�[�^���쐬
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

	/**
	* @fn MakeCylinder
	* @brief �V�����_�[���b�V�����쐬����
	* @param std::vector<Vertex>& (_vertices)
	* @return void
	*/
	void MakeCylinder(std::vector<Vertex>& _vertices);

	/**
	* @fn CalucCapsuleVertexPosition
	* @brief �J�v�Z���̒��_�ʒu���v�Z����
	* @return std::vector<Vertex>
	*/
	std::vector<Vertex> CalucCapsuleVertexPosition();

public:
	/**
	* @fn SetRadius
	* @brief ���a���Z�b�g����֐�
	* @param const float (_radius)
	* @return void
	*/
	void SetRadius(const float _radius);

	/**
	* @fn SetHeight
	* @brief �����̃Z�b�^�[
	* @param const float (_height)
	* @return void
	*/
	void SetHeight(const float _height);

	/**
	* @fn SetTransform
	* @brief �g�����X�t�H�[���̃Z�b�^�[
	* @param const Transform& (_transform)
	* @return void
	*/
	inline void SetTransform(const Transform& _transform) noexcept;	
};

//--------- INLINES ----------

inline void CapsuleMesh::SetTransform(const Transform& _transform) noexcept
{
	mTransform = _transform;
}