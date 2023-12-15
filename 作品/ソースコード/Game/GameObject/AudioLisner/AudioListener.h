#pragma once

#include <Windows.h>
#include <x3daudio.h>
#include "../GameObject.h"



/**
* @class AudioListener
* @brief �I�[�f�B�I���X�i�[
* @detail 3D��ԏ�ŉ��𕷂��I�u�W�F�N�g
*/
class AudioListener : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AudioListener();

	/**
	* �f�X�g���N�^
	*/
	~AudioListener();

private:
	/** ���X�i�[�ɂ���I�u�W�F�N�g */
	std::weak_ptr<GameObject> mListenerObject;

	/** ���X�i�[�I�u�W�F�N�g�̃g�����X�t�H�[�� */
	std::weak_ptr<TransformComponent> mListenerTransformComponent;

	/** ���X�i- */
	X3DAUDIO_LISTENER mListener;

public:
	/**
	* @fn Init
	* @brief ����������
	* @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief �X�V����
	* @param const double _deltaTime
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn GetListener
	* @brief ���X�i�[��Ԃ�
	* @return X3DAUDIO_LISTENER
	*/
	inline X3DAUDIO_LISTENER GetListener() const noexcept;

	/**
	* @fn SetListenerObject
	* @brief ���X�i�[�I�u�W�F�N�g���Z�b�g����
	* @param std::shared_ptr<GameObject> (_listenerObject)
	* @return void
	*/
	void SwitchListenerObject(std::shared_ptr<GameObject> _listenerObject) noexcept;

};

//---------- INLINES ---------

inline X3DAUDIO_LISTENER AudioListener::GetListener() const noexcept
{
	return mListener;
}
