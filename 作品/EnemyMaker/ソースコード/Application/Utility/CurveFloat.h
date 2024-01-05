/**
* @file CurveFloat.h
* @brief CurveFloat�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include <string>
#include <vector>
#include "../ImGui/ImGuiUtility.h"

/**
* @class CurveFloat
* @brief �J�[�u�N���X
* @detail ����:���� �c��:�l
*/
class CurveFloat
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CurveFloat();

	/**
	* �f�X�g���N�^
	*/
	~CurveFloat();

private:
	/** �f�[�^��ۑ�����t�@�C���p�X */
	std::string mFilePath;

	/** �J�[�u��̃L�[ */
	std::vector<ImVec2> mCurveKey;

	/** �J�[�u�E�B���h�E�̃T�C�Y */
	ImVec2 mSize;

public:
	/**
	* @fn Initialize
	* @brief �t�@�C�����J���f�[�^������Γǂݍ���
	* @param std::string_view (_filePath)
	* @return void
	*/
	void Initialize(std::string_view _filePath);

	/**
	* @fn Edit
	* @brief �J�[�u��ҏW����֐�
	* @param std::string_view (_label)
	* @return void
	*/
	void Edit(std::string_view _label);

	/**
	* @fn GetValue
	* @brief ���Ԃɉ������l��Ԃ�
	* @detail _time�� 0 �` 1�͈̔� �͈͊O�̒l�ł��֐�����01�ɃN�����v���Ă���
	* @param const float (_time)
	* @return float 
	*/
	float GetValueByTime(const float _time);

private:
	/**
	* @fn Save
	* @brief �L�[�̒l��ۑ�����
	* @return void
	*/
	void Save();

};

