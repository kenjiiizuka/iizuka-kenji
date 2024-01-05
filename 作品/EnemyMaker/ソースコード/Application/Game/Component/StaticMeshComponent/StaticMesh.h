#pragma once
//------------- INCLUDES ------------
#include <SimpleMath.h>
#include <memory>
#include <string>
#include "../../../System/RendererSystem/Renderer.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntityData.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../../System/RendererSystem/Shader/VertexShader/Object3DVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/LightPixelShader.h"
#include "../../../System/AssetSystem/AssetHandle.h"
#include "../TransformComponent/Transform.h"


class GameObject;

/**
* @class StaticMesh
* @brief �X�^�e�B�b�N���b�V���N���X
* @detail �X�^�e�B�b�N���b�V���̃A�Z�b�g�f�[�^����`��p�I�u�W�F�N�g���쐬���ATransform�������Ă���
*/
class StaticMesh
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	StaticMesh();

	/**
	* �f�X�g���N�^
	*/
	~StaticMesh();

private:
	/** StaticMeshAsset�ւ̃n���h�� */
	std::shared_ptr<AssetHandle> mAssetHandle;
	
	/** �I�[�i�[ */
	GameObject* mOwnerGameObject;

protected:
	/** �g�����X�t�H�[�� */
	Transform mTransform;

	/** ���[���h��Ԃ̃g�����X�t�H�[�� */
	Transform mWorldTransform;

	/** ���[���h�s�� */
	DirectX::SimpleMath::Matrix mWorldMatrix;

	/** �`��̎��� */
	std::shared_ptr<VisualEntity> mVisualEntity;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @param const std::string& (_filePath)
	* @return void
	*/
	void Initialize(const std::string& _filePath);

	/**
	 * @fn�@Draw
	 * @brief �`�揈��
	 * @return void
	*/
	virtual void Draw();

private:
	/**
	* @fn CreateVisualEntity
	* @brief �`��I�u�W�F�N�g�̍쐬
	* @return void
	*/
	virtual void CreateVisualEntity();

public:
	/**
	* @fn SetMaterialDiffuse
	* @brief �}�e���A���J���[���Z�b�g����
	* @param const DirectX::SimpleMath::Vector4 (_diffuse)
	* @return void
	*/
	void SetMaterialDiffuse(const DirectX::SimpleMath::Vector4 _diffuse);

	/**
	* @fn CalucWorldMatrix
	* @brief ���[���h�s����v�Z����
	* @detail �����ɐe�q�t�����������,�����ɐe�q�t���������s���n�����ΐe�q�t�������
	* @param const DirectX::SimpleMath::Matrix& _worldMatrix
	* @return void
	*/
	void CalucWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix);

	/**
	 * @fn�@GetVisualEntity
	 * @brief VisualEntity�̎擾
	 * @return std::shared_ptr<VisualEntity>
	*/
	inline std::shared_ptr<VisualEntity> GetVisualEntity();

	/**
	 * @fn�@SetOwnerObject
	 * @brief �I�[�i�[�̃I�u�W�F�N�g�Z�b�^�[
	 * @param GameObject* (_owner)
	 * @return void
	*/
	inline void SetOwnerObject(GameObject* _owner);

	/**
	* @fn SetWorldMatrix
	* @brief ���[���h�s��̃Z�b�^�[
	* @param DirectX::SimpleMath::Matrix _worldMatrix
	* @return void
	*/
	inline void SetWorldMatrix(DirectX::SimpleMath::Matrix _worldMatrix);

	/**
	* @fn SwapShader
	* @brief �V�F�[�_�[�̎g�p���Ԃ����ւ���
	* @return void
	*/
	inline void SwapShader();

	/**
	* @fn AddVertexShader
	* @brief ���_�V�F�[�_�[�̒ǉ��֐�
	* @detail �`��p�I�u�W�F�N�g�ɒ��_�V�F�[�_�[���쐬���ǉ�����
	* @return std::shared_ptr<VShader>
	*/
	template<DerivedVertexShader VShader>
	inline std::shared_ptr<VShader> AddVertexShader();

	/**
	* @fn AddPixelShader
	* @brief �s�N�Z���V�F�[�_�[�̒ǉ��֐�
	* @detail �`��p�I�u�W�F�N�g�Ƀs�N�Z���V�F�[�_�[���쐬���ǉ�����
	* @return std::shared_ptr<PShader>
	*/
	template<DerivedPixelShader PShader>
	inline std::shared_ptr<PShader> AddPixelShader();

	/**
	* @fn AddGeometryShader
	* @brief �W�I���g���V�F�[�_�[�ǉ��֐�
	* @detail �`��p�I�u�W�F�N�g�ɃW�I���g���V�F�[�_�[���쐬���ǉ�����
	* @return std::shared_ptr<GShader>
	*/
	template<DerivedGeometryShader GShader>
	inline std::shared_ptr<GShader> AddGeometryShader();

	/**
	* @fn SetDrawType
	* @brief �`��^�C�v��ݒ�
	* @param const DrawType (_drawType) �`��̎��
	* @param const size_t   (_id)      �`��̎�ނ�ݒ肵�����V�F�[�_�[ID
	* @return void
	*/
	inline void SetDrawType(const CullType _drawType, const size_t _id);

	/**
	* @fn SetVisible
	* @brief �`�悷�邩���Ȃ�����؂�ւ���֐�
	* @param const bool (_visible) true �`�悷�� false �`�悵�Ȃ�
	* @return void
	*/
	inline void SetVisible(const bool _visible);

};

//---------------- INLINES ------------------------------

inline std::shared_ptr<VisualEntity> StaticMesh::GetVisualEntity()
{
	return mVisualEntity;
}

inline void StaticMesh::SetWorldMatrix(DirectX::SimpleMath::Matrix _worldMatrix)
{
	mWorldMatrix = _worldMatrix;
}

inline void StaticMesh::SetOwnerObject(GameObject* _owner)
{
	mOwnerGameObject = _owner;
}

inline void StaticMesh::SwapShader()
{
	mVisualEntity->SwapShader();
}

inline void StaticMesh::SetDrawType(const CullType _drawType, const size_t _id)
{
	mVisualEntity->SetCullType(_drawType, _id);
}

inline void StaticMesh::SetVisible(const bool _visible)
{
	mVisualEntity->SetVisible(_visible);
}

template<DerivedVertexShader VShader>
inline std::shared_ptr<VShader> StaticMesh::AddVertexShader()
{
	return mVisualEntity->MakeVertexShader<VShader>();
}

template<DerivedPixelShader PShader>
inline std::shared_ptr<PShader> StaticMesh::AddPixelShader()
{
	return mVisualEntity->MakePixelShader<PShader>();
}

template<DerivedGeometryShader GShader>
inline std::shared_ptr<GShader> StaticMesh::AddGeometryShader()
{
	return mVisualEntity->MakeGeometryShader<GShader>();
}
