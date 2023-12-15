/**
* @file StaticMeshAsset.h
* @brief StaticMeshAsset�N���X�̒�`
*/


#pragma once


//----------- INCLUDES ----------
#include <SimpleMath.h>
#include <vector>
#include "../IAsset.h"
#include "../../RendererSystem/VisualEntity/VisualEntityData.h"

/**
* @class StaticMeshAsset
* @brief �X�^�e�B�b�N���b�V���A�Z�b�g�N���X
*/
class StaticMeshAsset : public IAsset
{
	/**----------------------------------------------------------------------------------------------
    * ���_�f�[�^�Ȃǂɓǂݍ��݂�����StaticMeshProvider�ȊO����G��Ȃ��悤�ɂ��邽�߂Ƀt�����h�w��
    ------------------------------------------------------------------------------------------------ */
	friend class StaticMeshProvider;

public:
	/**
	* @struct Vertex
	* @brief StaticMesh�̒��_�f�[�^�\����
	*/
	struct Vertex
	{
		DirectX::SimpleMath::Vector3 mPosition; /**< ���_���W */
		DirectX::SimpleMath::Vector3 mNormal;   /**< �@�� */
		DirectX::SimpleMath::Vector2 mUV;       /**< UV */
		DirectX::SimpleMath::Vector4 mColor;    /**< ���_�J���[ */

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Vertex();

		/**
		* �R���X�g���N�^
		* 
		* @param const DirectX::SimpleMath::Vector3& (_position)
		* @param const DirectX::SimpleMath::Vector3& (_normal)
		* @param const DirectX::SimpleMath::Vector2& (_uv)
		* @param const DirectX::SimpleMath::Vector4& (_color)
		*/
		Vertex(const DirectX::SimpleMath::Vector3& _position, const DirectX::SimpleMath::Vector3& _normal, const DirectX::SimpleMath::Vector2& _uv, const DirectX::SimpleMath::Vector4& _color);
	};

public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	StaticMeshAsset();

	/**
	* �f�X�g���N�^
	*/
	~StaticMeshAsset();


private:
	/** ���_�f�[�^ �������b�V�����i�[�ł���悤��std::vector<std::vector<Vertex>> */
	std::vector<std::vector<Vertex>> mVertices;

	/** �C���f�b�N�X�o�b�t�@�쐬�̂��߂̃f�[�^ �������b�V���̉\��������̂�std::vector<std::vector<Vertex>>�^ */
	std::vector<std::vector<uint32_t>> mIndices;

	/** �}�e���A���f�[�^�@���b�V�����ƂɈ��*/
	std::vector<VisualEntityData::Material> mMaterials;

public:
	/**
	* @fn GetAssetType
	* @brief �A�Z�b�g�̃^�C�v��Ԃ�
	* @detail typeid���g�p���Č^���ʂ����Ă���
	* @return const std::type_info&
	*/
	inline const std::type_info& GetAssetType() const noexcept override;

	/**
	* @fn GetVertices
	* @brief ���_�f�[�^��Ԃ�
	* @return std::vector<std::vector<Vertex>>
	*/
	inline std::vector<std::vector<Vertex>> GetVertices() const;

	/**
	* @fn GetIndices
	* @brief �C���f�b�N�X�f�[�^��Ԃ�
	* @return std::vector<std::vector<uint32_t>>
	*/
	inline std::vector<std::vector<uint32_t>> GetIndices() const;

	/**
	* @fn GetMaterials
	* @brief �}�e���A����Ԃ�
	* @return std::vector<VisualEntityData::Material>
	*/
	inline std::vector<VisualEntityData::Material> GetMaterials() const;

};

//---------- INLINES ----------

inline const std::type_info& StaticMeshAsset::GetAssetType() const noexcept
{
	return typeid(StaticMeshAsset);
}

inline std::vector<std::vector<StaticMeshAsset::Vertex>> StaticMeshAsset::GetVertices() const
{
	return mVertices;
}

inline std::vector<std::vector<uint32_t>> StaticMeshAsset::GetIndices() const
{
	return mIndices;
}

inline std::vector<VisualEntityData::Material> StaticMeshAsset::GetMaterials() const
{
	return mMaterials;
}

