/**
* @file CommandSelector.h
* @brief CommandSelector�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ----------
#include "../GameObject.h"
#include "../../../System/InputSystem/InputData.h"

//---------- �O���錾 ----------
class CommandObject;
class SpriteComponent;
class AudioComponent;

/**
* @class CommandSelector
* @brief �o�^���ꂽ�R�}���h��I������N���X
* @detail CommandObject��o�^
*         ����{�^���������ꂽ�Ƃ��ɑI������Ă���R�}���h��ID��Ԃ�
* �@�@�@�@����{�^���̃f�t�H���g��[Pad��A]
*         ID�͓o�^���ꂽ����1���犄��U����
*         �I������p�̃J�[�\�����\������܂�
*/
class CommandSelector : public GameObject
{
public:
	/**
	* @enum �I������Ă���ID�������񋓌^
	* @detail �}�W�b�N�i���o�[�̎g�p�h�~�ׂ̈ɒ�`���Ă���
	*          GetSelectCommandID�ŋA���Ă���l���Ȃɂ��𔻒f����ۂɎg���悤��
	*/
	enum ID : uint8_t
	{
		NoSelect = 0,
		ID_1,
		ID_2,
		Max
	};

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CommandSelector();

	/**
	* �f�X�g���N�^
	*/
	~CommandSelector();

private:
	/** �R�}���h */
	std::vector<std::weak_ptr<CommandObject>> mCommands;

	/** ���ݑI�����Ă���R�}���hID */
	ID mCurrentChoiceID;

	/** �I�����Ă���R�}���h�������X�v���C�g */
	std::weak_ptr<SpriteComponent> mCursorSprite;

	/** �R�}���h���莞�̉� */
	std::weak_ptr<AudioComponent> mSelectSE;

	/** �J�[�\���ړ����̃R�}���h */
	std::weak_ptr<AudioComponent> mCursorMoveSE;

	/** ����{�^�� */
	Pad mSelectButton;

public:
	/**
	* @fn Init
	* @brief ������
	* @return void
	*/
	void Init();

	/**
	* @fn Update
	* @brief �X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime);

private:
	/**
	* @fn MoveCursor
	* @brief �w�肳�ꂽID�̃J�[�\���Ɉړ�����
	* @param const ID (_id)
	* @return void
	*/
	void MoveCursor(const ID _id);

public:
	/**
	* @fn AddCommand
	* @brief �R�}���h�ǉ��֐�
	* @param const std::shared_ptr<CommandObject>
	* @return void
	*/
	void AddCommand(const std::shared_ptr<CommandObject> _command);

	/**
	* @fn ResetCursorPosition
	* @brief �J�[�\���̈ʒu�����Z�b�g����֐�
	* @detail �J�[�\���̈ʒu��ID0�̃R�}���h�Ƀ��Z�b�g����
	* @return void
	*/
	void ResetCursorPosition();

	/**
	* @fn GetSelectCommand
	* @brief ����{�^���������ꂽ���ɑI�����ꂽ�R�}���hID��Ԃ�
	* @detail ����{�^����������Ă��Ȃ�����0��Ԃ�
	* @return ID 
	*/
	ID GetSelectCommandID() const noexcept;

};

