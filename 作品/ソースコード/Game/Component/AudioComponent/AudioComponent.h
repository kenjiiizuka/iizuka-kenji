/**
* @file AudioComponent.h
* @brief AudioComponent�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ----------
#include "../Component.h"
#include <string>
#include <SimpleMath.h>

//--------- �O���錾 --------
class AudioClip;


/**
* @class AudioComponent
* @brief AudioClip�������AAudio��2D�Đ��A3D�Đ������₷���悤�ɂ����N���X
*/
class AudioComponent : public Component
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AudioComponent();

	/**
	* �f�X�g���N�^
	*/
	~AudioComponent();

private:
	/** �I�[�f�B�I�N���b�v */
	std::shared_ptr<AudioClip> mAudioClip;

public:
	/**
	* @fn Init
	* @brief ����������
	* @param std::string_view (_filePath)
	* @param const bool       (_loop)
	* @detail AudioClip�̐���������
	* @return void
	*/
	void Init(std::string_view _filePath, const bool _loop = false);

	/**
	* @fn PlaySound2D
	* @brief AudioClip��2D�Đ�������
	* @param const float (_volume)
	* @return void
	*/
	void PlaySound2D(const float _volume = 1.0f);

	/**
	* @fn PlaySound3D
	* @brief AudioClip��3D�T�E���h���Đ�����
	* @param const DirectX::SimpleMath::Vector3 (_position)
	* @param const DirectX::SimpleMath::Vector3 (_rotation)
	* @param const const float                  (_volume)
	* @return void
	*/
	void PlaySound3D(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _rotation, const float _volume = 1.0f);
};

