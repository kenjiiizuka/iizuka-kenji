/**
* @file BillboardObject.h
* @brief BillboardObject�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include "../GameObject.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"

//---------- �O���錾 ---------
class Camera;
class PlaneComponent;

/**
* @class BillboardObject
* @brief �r���{�[�h�I�u�W�F�N�g ��ɃJ�����̕����������@�\�������Ă���
*/
class BillboardObject : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BillboardObject();

	/**
	* �f�X�g���N�^
	*/
	~BillboardObject();

private:
	/** ���C���J���� */
	std::weak_ptr<Camera> mMainCamera;

	/** �v���[���R���|�[�l���g */
	std::weak_ptr<PlaneComponent> mPlane;

public:
	/**
	* @fn Init
	* @brief ����������
	* @param const DirectX::SimpleMath::Vector2 (_size)
	* @return void
	*/
	void Init(const DirectX::SimpleMath::Vector2 _size = {1.0f,1.0f});

	/**
	* @fn Draw
	* @brief �`�揈��
	* @return void
	*/
	void Draw() override;

private:
	/**
	* @fn LookAtCamera
	* @brief �J�����̕���������
	* @return void
	*/
	virtual void LookAtCamera();

public:
	/**
	* @fn SetPosition
	* @brief ���W�̃Z�b�^�[
	* @param DirectX::SimpleMath::Vector3 (_position)
	* @return void
	*/
	void SetPosition(DirectX::SimpleMath::Vector3 _position) override;

	/**
	* @fn SetTexture
	* @brief �e�N�X�`���̃Z�b�^�[
	* @param const Texture (_texture)
	* @return void
	*/
	void SetTexture(const Texture _texture);

	/**
	* @fn SetMaterialDiffuse
	* @brief �}�e���A���f�B�t���[�Y���Z�b�g����
	* @param const DirectX::SimpleMath::Color (_diffuse)
	* @return void
	*/
	void SetMaterialDiffuse(const DirectX::SimpleMath::Color _diffuse);

	/**
	* @fn CalcuWorldMatrix
	* @brief ���[���h�s��̈ʒu���v�Z����
	* @param const DirectX::SimpleMath::Matrix& (_matrix)
	* @return void
	*/
	void CalcuWorldMatrix(const DirectX::SimpleMath::Matrix& _matrix);


};

