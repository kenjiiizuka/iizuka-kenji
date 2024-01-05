/**
* @file TitleScene.h
* @brief TitleScene�N���X�̒�`
*/

#pragma once

//-------- INCLUDES -----------
#include "../Scene.h"
#include <vector>

//-------- �O���錾 --------
class Fade;
class CommandSelector;
class StaticMeshObject;
class AudioComponent;

/**
* @class TitleScene
* @brief �^�C�g���V�[��
*/
class TitleScene : public Scene
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	TitleScene();

	/**
	* �f�X�g���N�^
	*/
	~TitleScene();

	/**
	* @fn Initialize
	* @brief ����������
	* @detail �^�C�g���ɕK�v�ȃI�u�W�F�N�g�𐶐����Ă��܂�
	* @return void
	*/
	void Initialize() override;

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update() override;

private:
	/** �t�F�[�h�p�̃I�u�W�F�N�g */
	std::weak_ptr<Fade> mFade;

	/** �R�}���h�Z���N�^�[ */
	std::weak_ptr<CommandSelector> mCommandSelector;

	/** �V�[���J�ڂ̓��͂��������� */
	bool mbTransitionScene;

	/** �I���R�}���h���I�����ꂽ�� */
	bool mbEnd;

	/** �t�F�[�h�̑��x */
	float mFadeSpeed;

	/** �����I�u�W�F�N�g */
	std::vector<std::weak_ptr<StaticMeshObject>> mProps;

	/** BGM�Đ��p�R���|�[�l���g */
	std::weak_ptr<AudioComponent> mBGM;

};

