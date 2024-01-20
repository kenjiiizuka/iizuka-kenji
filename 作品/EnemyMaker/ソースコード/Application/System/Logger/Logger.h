/**
* @file Logger.h
* @brief Loggerクラスの定義
*/

#pragma once

//------- INCLUDES ----------
#include "../Singleton.h"
#include <string>
#include <fstream>
#include <vector>

/**
* @class Logger
* @brief ログを出力し、ファイルに書き込む機能を持つ
* @detail OpenLogFileで書き込み先のファイルを開き、Logでファイルに書き込む、終了時にCloseLogFileで閉じる必要があります
*/
class Logger : public Singleton<Logger>
{
	/**-------------------------------------------------------------
	* Singleton<Logger>クラスのみからコンストラクタ,デストラクタに
	* アクセスできるようにするためにフレンド指定
	---------------------------------------------------------------*/
	friend class Singleton<Logger>;
	
private:
	/**
	* コンストラクタ
	*/
	Logger();

	/**
	* デストラクタ
	*/
	~Logger();

	/**
	 * コピーコンストラクタ
	 * コピー禁止のため = delete 指定
	 *
	 * @param const Logger& (_from)
	*/
	Logger(const Logger& _from) = delete;

	/**
	 * 代入演算子のオーバーロード
	 * 代入禁止のため = delete 指定
	 *
	 * @param const Logger& (_from)
	*/
	void operator = (const Logger& _from) = delete;

private:
	/** ログ書き込み先のファイル */
	std::vector<std::ofstream> mLogFiles;

public:
	/**
	* @fn OpenLogFile
	* @brief ログ書き込み先のファイルを開く
	* @param std::string_view (_filePath)
	* @detail 指定したファイルがなくても自動でファイルが作成されます。
	* @return void
	*/
	void OpenLogFile(std::string_view _filePath);

	/**
	* @fn WriteLog
	* @brief ログ書き込み
	* @param std::string_view (_log)
	* @param const size_t (_logfileID)
	* @return void
	*/
	void WriteLog(std::string_view _log, const size_t _logfileID = 0);

};

