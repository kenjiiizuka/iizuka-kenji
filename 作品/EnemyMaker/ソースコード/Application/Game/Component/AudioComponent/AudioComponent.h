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

	/** �t�F�[�h�Đ����邩 */
	bool mbIsFadeIn;

	/** ���� */
	float mVolume;

	/** �t�F�[�h�C���J�n���Ă���̌o�ߎ��� */
	double mFadeInElapsedTime;

	/** �t�F�[�h�C���ɂ����鎞�� */
	double mFadeInTime;

	/** �t�F�[�h�A�E�g�����邩 */
	bool mbIsFadeOut;

	/** �t�F�[�h�A�E�g�ɂ����鎞�� */
	double mFadeOutTime;

	/** �t�F�[�h�A�E�g�J�n���Ă���̌o�ߎ��� */
	double mFadeOutElapsedTime;

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
	* @fn Update
	* @brief �X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn  FadeIn
	* @brief �t�F�[�h�C������
	* @param const double (_deltaTime)
	* @return void 
	*/
	void FadeIn(const double _deltaTime);

	/**
	* @fn  FadeOut
	* @brief �t�F�[�h�A�E�g����
	* @param const double (_deltaTime)
	* @return void
	*/
	void FadeOut(const double _deltaTime);

public:
	/**
	* @fn PlaySound2D
	* @brief AudioClip��2D�Đ�������
	* @param const float  (_volume)     ����
	* @param const bool   (_isFade)     �t�F�[�h�Đ����邩
	* @param const double (_fadeInTime) �t�F�[�h�C���ɂ����鎞��
	* @return void
	*/
	void PlaySound2D(const float _volume = 1.0f, const bool _isFade = false, const double _fadeInTime = 10.0f);

	/**
	* @fn PlaySound3D
	* @brief AudioClip��3D�T�E���h���Đ�����
	* @param const DirectX::SimpleMath::Vector3 (_position)
	* @param const DirectX::SimpleMath::Vector3 (_rotation)
	* @param const const float                  (_volume)
	* @return void
	*/
	void PlaySound3D(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _rotation, const float _volume = 1.0f);

	/**
	* @fn Stop
	* @brief �Đ����~���鏈��
	* @param const bool (_isFadeOut)
	* @param cont double (_fadeOutTime)
	* @return void
	*/
	void Stop(const bool _isFadeOut = false, const double _fadeOutTime = 2.0f);
};

