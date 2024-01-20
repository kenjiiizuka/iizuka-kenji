/**
* @file Logger.h
* @brief Logger�N���X�̒�`
*/

#pragma once

//------- INCLUDES ----------
#include "../Singleton.h"
#include <string>
#include <fstream>
#include <vector>

/**
* @class Logger
* @brief ���O���o�͂��A�t�@�C���ɏ������ދ@�\������
* @detail OpenLogFile�ŏ������ݐ�̃t�@�C�����J���ALog�Ńt�@�C���ɏ������ށA�I������CloseLogFile�ŕ���K�v������܂�
*/
class Logger : public Singleton<Logger>
{
	/**-------------------------------------------------------------
	* Singleton<Logger>�N���X�݂̂���R���X�g���N�^,�f�X�g���N�^��
	* �A�N�Z�X�ł���悤�ɂ��邽�߂Ƀt�����h�w��
	---------------------------------------------------------------*/
	friend class Singleton<Logger>;
	
private:
	/**
	* �R���X�g���N�^
	*/
	Logger();

	/**
	* �f�X�g���N�^
	*/
	~Logger();

	/**
	 * �R�s�[�R���X�g���N�^
	 * �R�s�[�֎~�̂��� = delete �w��
	 *
	 * @param const Logger& (_from)
	*/
	Logger(const Logger& _from) = delete;

	/**
	 * ������Z�q�̃I�[�o�[���[�h
	 * ����֎~�̂��� = delete �w��
	 *
	 * @param const Logger& (_from)
	*/
	void operator = (const Logger& _from) = delete;

private:
	/** ���O�������ݐ�̃t�@�C�� */
	std::vector<std::ofstream> mLogFiles;

public:
	/**
	* @fn OpenLogFile
	* @brief ���O�������ݐ�̃t�@�C�����J��
	* @param std::string_view (_filePath)
	* @detail �w�肵���t�@�C�����Ȃ��Ă������Ńt�@�C�����쐬����܂��B
	* @return void
	*/
	void OpenLogFile(std::string_view _filePath);

	/**
	* @fn WriteLog
	* @brief ���O��������
	* @param std::string_view (_log)
	* @param const size_t (_logfileID)
	* @return void
	*/
	void WriteLog(std::string_view _log, const size_t _logfileID = 0);

};

