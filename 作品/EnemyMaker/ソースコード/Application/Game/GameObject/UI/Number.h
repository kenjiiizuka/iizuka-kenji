/**
* @file Number.h
* @brief Number�N���X�̒�`
*/

#pragma once

//-------- INCLUDES ----------
#include "../GameObject.h"

class BillboardObject;
class AssetHandle;

/**
* @class Number
* @brief �������r���{�[�h�`�悷��@�\������
*/
class Number : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	Number();

	/**
	* �f�X�g���N�^
	*/
	~Number();

private:
	/** �����p�̃e�N�X�`�� */
	std::vector<std::shared_ptr<AssetHandle>> mNumberTextures;

	/** �\�����鐔�� */
	uint16_t mNumber;

	/** ������`�悷��r���{�[�h�I�u�W�F�N�g  �r���{�[�h�A�\�����Ă��鐔�� */
	std::vector<std::weak_ptr<BillboardObject>> mNumberBillboard;

public:
	/**
	* @fn Init
	* @brief ����������
	* @return void
	*/
	void Init();

public:
	/**
	* @fn SetNumber
	* @brief �������Z�b�g����
	* @param const uint8_t (_number)
	* @return void
	*/
	void SetNumber(const uint8_t _number);

	/**
	* @fn SetDiffuse
	* @brief �f�B�t���[�Y��ݒ�
	* @param const DirectX::SimpleMath::Color (_color)
	* @return void
	*/
	void SetDiffuse(const DirectX::SimpleMath::Color _color);

	/**
	* @fn SetPosition
	* @brief ���W�̃Z�b�^�[
	* @param DirectX::SimpleMath::Vector3 (_position)
	* @return void
	*/
	void SetPosition(DirectX::SimpleMath::Vector3 _position) override;

};

//----------- INLINES -----------
