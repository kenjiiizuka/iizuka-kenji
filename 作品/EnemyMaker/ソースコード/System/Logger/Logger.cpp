//---------- INCLUDES ----------
#include "Logger.h"
#include <chrono>
#include <iostream>

Logger::Logger()
{
	// 処理なし
}

Logger::~Logger()
{
	// 処理なし
}

void Logger::OpenLogFile(std::string_view _filePath)
{
	// ofstreamがコピー不可なのでファイルオープンごとにリサイズして生成する
	mLogFiles.resize(mLogFiles.size() + 1);
	
	// ファイルオープン ファイルに追加する形で書き込む
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
	// IDに対応したファイルがあるかチェック
	if (!(_logfileID < mLogFiles.size()))
	{
		// std::cout << "IDに対応したログファイルがありません Logger.cpp" << std::endl;
		return;
	}

	// システム時間をゲット
	auto nowSystemClock = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(nowSystemClock);

	// ローカルタイムに変換
	std::tm localClock;	
	localtime_s(&localClock, &time);

	// local_timeは、システム時間のエポックからの経過時間によって構築できる
	std::chrono::local_time<std::chrono::system_clock::duration> now {std::chrono::system_clock::now().time_since_epoch()};

	// 秒単位の時間点 (日付と時間が出力される)
	std::chrono::local_seconds sec_tp = std::chrono::floor<std::chrono::seconds>(now);
	
	// 日単位の時間点 (日付と、値ゼロの時間が出力される。sys_timeとは挙動が違うので注意)
	std::chrono::local_days day_tp = std::chrono::floor<std::chrono::days>(now);
	
	// 年 月 日 時 分 秒を出力	
	mLogFiles[_logfileID] << localClock.tm_year + 1900 << "y ";
	mLogFiles[_logfileID] << localClock.tm_mon + 1 << "m ";
	mLogFiles[_logfileID] << localClock.tm_mday << "d  ";
	mLogFiles[_logfileID] << localClock.tm_hour << ":";
	mLogFiles[_logfileID] << localClock.tm_min << ":";
	mLogFiles[_logfileID] << localClock.tm_sec << "  ";

	// ログ書き込み
	mLogFiles[_logfileID] << "{ " << _log << " }" << std::endl;
}




