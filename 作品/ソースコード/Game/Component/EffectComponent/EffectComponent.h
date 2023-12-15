/**
* @file EffectComponent.h
* @brief EffectComponent�N���X�̒�`
*/

#pragma once

//--------- INCLUDES -----------
#include "../Component.h"
#include <string>
#include <SimpleMath.h>
#include <Effekseer.h>

//--------- �O���錾 -----------
class AssetHandle;

/**
* @class EffectComponent
* @brief �G�t�F�N�g�R���|�[�l���g
* @detail �G�t�F�N�g�̍Đ����ł���
*         Init�֐��Ŏw�肳�ꂽ�t�@�C���̃G�t�F�N�g����
*/
class EffectComponent : public Component
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	EffectComponent();

	/**
	* �f�X�g���N�^
	*/
	~EffectComponent();

private:
	/** �G�t�F�N�g�̃A�Z�b�g�ւ̃n���h�� */
	std::shared_ptr<AssetHandle> mAssetHandle;

	/** �G�t�F�N�g�n���h�� */
	Effekseer::Handle mEffectHandle;

public:
	/**
	* @fn Init
	* @brief ����������
	* @detail �w�肳�ꂽ�t�@�C���̃G�t�F�N�g��ǂݍ���
	* @return void
	*/
	void Init(std::string_view _filePath);

	/**
	* @fn PlayEffect
	* @brief �G�t�F�N�g�Đ��֐�
	* @param const DirectX::SimpleMath::Vector3 (_playPosition) �Đ��ʒu
	* @return void
	*/
	void PlayEffect(const DirectX::SimpleMath::Vector3 _playPosition);
};

