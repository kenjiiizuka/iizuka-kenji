//---------- INCLUDES ----------
#include "Logger.h"
#include <chrono>
#include <iostream>

Logger::Logger()
{
	// �����Ȃ�
}

Logger::~Logger()
{
	// �����Ȃ�
}

void Logger::OpenLogFile(std::string_view _filePath)
{
	// ofstream���R�s�[�s�Ȃ̂Ńt�@�C���I�[�v�����ƂɃ��T�C�Y���Đ�������
	mLogFiles.resize(mLogFiles.size() + 1);
	
	// �t�@�C���I�[�v�� �t�@�C���ɒǉ�����`�ŏ�������
	size_t index = mLogFiles.size() - 1;
	mLogFiles[index].open(_filePath.data(), std::ios::app);

	if (!mLogFiles[index].is_open())
	{
		std::cout << "Failed LogFileOpen" << _filePath << std::endl;
		return;
	}
}

void Logger::WriteLog(std::string_view _log, const size_t _logfileID)
{
	// ID�ɑΉ������t�@�C�������邩�`�F�b�N
	if (!(_logfileID < mLogFiles.size()))
	{
		// std::cout << "ID�ɑΉ��������O�t�@�C��������܂��� Logger.cpp" << std::endl;
		return;
	}

	// �V�X�e�����Ԃ��Q�b�g
	auto nowSystemClock = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(nowSystemClock);

	// ���[�J���^�C���ɕϊ�
	std::tm localClock;	
	localtime_s(&localClock, &time);

	// local_time�́A�V�X�e�����Ԃ̃G�|�b�N����̌o�ߎ��Ԃɂ���č\�z�ł���
	std::chrono::local_time<std::chrono::system_clock::duration> now {std::chrono::system_clock::now().time_since_epoch()};

	// �b�P�ʂ̎��ԓ_ (���t�Ǝ��Ԃ��o�͂����)
	std::chrono::local_seconds sec_tp = std::chrono::floor<std::chrono::seconds>(now);
	
	// ���P�ʂ̎��ԓ_ (���t�ƁA�l�[���̎��Ԃ��o�͂����Bsys_time�Ƃ͋������Ⴄ�̂Œ���)
	std::chrono::local_days day_tp = std::chrono::floor<std::chrono::days>(now);
	
	// �N �� �� �� �� �b���o��	
	mLogFiles[_logfileID] << localClock.tm_year + 1900 << "y ";
	mLogFiles[_logfileID] << localClock.tm_mon + 1 << "m ";
	mLogFiles[_logfileID] << localClock.tm_mday << "d  ";
	mLogFiles[_logfileID] << localClock.tm_hour << ":";
	mLogFiles[_logfileID] << localClock.tm_min << ":";
	mLogFiles[_logfileID] << localClock.tm_sec << "  ";

	// ���O��������
	mLogFiles[_logfileID] << "{ " << _log << " }" << std::endl;
}




