/**
* @file SkeletalMesh.h
* @brief SkeletalMesh�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ------------
#include <memory>
#include <string>
#include "../Component/TransformComponent/Transform.h"
#include "../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../System/AssetSystem/AssetHandle.h"
#include "../../System/AssetSystem/SkeletalMesh/SkeletalMeshAsset.h"

//---------- �O���錾 ------------
class Skeleton;
class GameObject;

/**
* @class SkeletalMesh
* @brief �X�P���^�����b�V���N���X
*/
class SkeletalMesh
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SkeletalMesh();
	
	/**
	* �f�X�g���N�^
	*/
	~SkeletalMesh();

private:
	/** SkeletalMeshAsset�ւ̃n���h�� */
	std::shared_ptr<AssetHandle> mAssetHandle;
	
	/** �X�P���g�� */
	std::shared_ptr<Skeleton> mSkeleton;

	/** �`��p�I�u�W�F�N�g */
	std::shared_ptr<VisualEntity> mVisualEntity;

	/** �A�j���[�V�������Ă��邩 */
	bool mbAnimate;

	/** �g�����X�t�H�[�� */
	Transform mTransform;

	/** ���[���h��Ԃ̃g�����X�t�H�[�� */
	Transform mWorldTransform;

	/** ���[���h�s�� */
	DirectX::SimpleMath::Matrix mWorldMatrix;

	/** �I�[�i�[�̃Q�[���I�u�W�F�N�g */
	GameObject* mOwnerGameObject;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @param const std::string& (_filePath)
	* @return void
	*/
	void Initialize(const std::string& _filePath);

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update();

	/**
	* @fn Draw
	* @brief �`�揈��
	* @return void
	*/
	void Draw();
	
private:
	/**
	* @fn CreateVisualEntity
	* @brief �`��p�I�u�W�F�N�g�̐����֐�
	* @return void
	*/
	void CreateVisualEntity();

public:
	/**
	* @fn GetSkeletalMeshAsset
	* @brief �X�P���^�����b�V���A�Z�b�g��Ԃ�
	* @return SkeletalMeshAsset
	*/
	inline SkeletalMeshAsset GetSkeletalMeshAsset() const noexcept;

	/**
	* @fn GetSkeleton
	* @brief Skeleton�̎�Q�Ƃ�Ԃ�
	* @return std::weak_ptr<Skeleton>
	*/
	inline std::weak_ptr<Skeleton> GetSkeleton() const;

	/**
	* @fn SetAnimate
	* @brief �A�j���[�V�������Ă��邩���Z�b�g����
	* @param const bool (_animate)
	* @return void
	*/
	inline void SetAnimate(bool _animate) noexcept;
	
	/**
	* @fn SetTransform
	* @brief �g�����X�t�H�[���̃Z�b�g
	* @param Transform (_trans)
	* @return void
	*/
	inline void SetTransform(Transform _trans);

	/**
	* @fn CalucWorldMatrix
	* @brief ���[���h�s����v�Z����
	* @detail �����ɐe�q�t�����������,�����ɐe�q�t���������s���n�����ΐe�q�t�������
	* @param const DirectX::SimpleMath::Matrix& (_parentMatrix)
	* @return void
	*/
	void CalucWorldMatrix(const DirectX::SimpleMath::Matrix& _parentMatrix);

	/**
	* @fn SetWorldMatrix
	* @brief ���[���h�s��ɃZ�b�^�[
	* @param const DirectX::SimpleMath::Matrix& (_worldMatrix)
	* @return void
	*/
	inline void SetWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix);

	/**
	* @fn GetWorldMatrix
	* @brief ���[���h�s���Ԃ�
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetWorldMatrix() const noexcept;

	/**
	* @fn SetGameObject
	* @brief �I�[�i�[�̃Q�[���I�u�W�F�N�g�̃Z�b�^�[
	* @param GameObject* (_owner)
	* @return void
	*/
	inline void SetOwnerObject(GameObject* _owner) noexcept;

	/**
	* @fn GetOwnerOjbect
	* @brief �I�[�i�[�̃Q�[���I�u�W�F�N�g�̃Q�b�^�[
	* @return GameObject*
	*/
	inline GameObject* GetOwnerObject() const noexcept;

	/**
	* @fn GetTransform
	* @brief �g�����X�t�H�[���̃Q�b�^�[
	* @return Transform
	*/
	inline Transform GetWorldTransform() const noexcept;

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
	* @fn SetDrawType
	* @brief �`��^�C�v��ݒ�
	* @param const DrawType (_drawType) �`��̎��
	* @param const size_t   (_id)      �`��̎�ނ�ݒ肵�����V�F�[�_�[ID
	* @return void
	*/
	inline void SetDrawType(const CullType _drawType, const size_t _id);

	/**
	* @fn SetMaterialDiffuse
	* @brief �}�e���A���f�B�t���[�Y�̃Z�b�^�[
	* @detail �������b�V���̏ꍇ�ł����ׂẴ��b�V���Ƀf�B�t���[�Y��ݒ肷��
	* @param const DirectX::SimpleMath::Color (_diffuse)
	* @return void
	*/
	inline void SetMaterialDiffuse(const DirectX::SimpleMath::Color _diffuse);

};

//------------ INLINES ----------

inline void SkeletalMesh::SetWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix)
{
	mWorldMatrix = _worldMatrix;
}

inline DirectX::SimpleMath::Matrix SkeletalMesh::GetWorldMatrix() const noexcept
{
	return mWorldMatrix;
}

inline SkeletalMeshAsset SkeletalMesh::GetSkeletalMeshAsset() const noexcept
{
	return mAssetHandle->Get<SkeletalMeshAsset>();
}

inline std::weak_ptr<Skeleton> SkeletalMesh::GetSkeleton() const
{
	return mSkeleton;
}

inline void SkeletalMesh::SetAnimate(bool _animate) noexcept
{
	mbAnimate = _animate;
}

inline void SkeletalMesh::SetTransform(Transform _trans)
{
	mTransform = _trans;
}

inline void SkeletalMesh::SetOwnerObject(GameObject* _owner) noexcept
{
	mOwnerGameObject = _owner;
}

inline GameObject* SkeletalMesh::GetOwnerObject() const noexcept
{
	return mOwnerGameObject;
}

inline Transform SkeletalMesh::GetWorldTransform() const noexcept
{
	return mWorldTransform;
}

inline void SkeletalMesh::SwapShader()
{
	mVisualEntity->SwapShader();
}

inline void SkeletalMesh::SetDrawType(const CullType _drawType, const size_t _id)
{
	mVisualEntity->SetCullType(_drawType, _id);
}

inline void SkeletalMesh::SetMaterialDiffuse(const DirectX::SimpleMath::Color _diffuse)
{
	for (std::shared_ptr<VisualEntityData> entity : mVisualEntity->GetAllVisualEntityData())
	{
		entity->SetMaterialDiffuse(_diffuse);
	}
}

template<DerivedVertexShader VShader>
inline std::shared_ptr<VShader> SkeletalMesh::AddVertexShader()
{
	return mVisualEntity->MakeVertexShader<VShader>();
}

template<DerivedPixelShader PShader>
inline std::shared_ptr<PShader> SkeletalMesh::AddPixelShader()
{
	return mVisualEntity->MakePixelShader<PShader>();
}
