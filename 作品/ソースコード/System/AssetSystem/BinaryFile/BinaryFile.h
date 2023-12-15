#pragma once
/**
* @file BinaryFile.h
* @brief BinaryFileクラスの定義
*/

//----------- INCLUDES -----------
#include <fstream>
#include <vector>
#include "../IAsset.h"

//---------- 前方宣言 ---------
class BinaryFileProvider;

/** 
* @enum WriteMode
* @brief ファイルの書き込みモードの定義
*/
enum class WriteMode
{
	Add = std::ios_base::app,         /**< ファイルの末尾に追記する */
	Override = std::ios_base::binary, /**< ファイルに上書きする　既存のデータは消える */
};

/**
* @class BinaryFile
* @brief バイナリーファイルのデータを保持する
*/
class BinaryFile : public IAsset
{
	/**---------------------------------------------------------------------------------------------
	 * ファイルストリームへのセットをBinaryFileProviderからのみアクセス可能にするためにフレンド指定
	*/
	friend class BinaryFileProvider;

public:
	/**
	 * デフォルトコンストラクタ
	*/
	BinaryFile();
	
	/**
	 * デフォルトデストラクタ
	*/
	~BinaryFile();
	
private:
	/** ストリームサイズ */
	std::streamsize mStreamSize;

	/** ファイルパス */
	std::string mFilePath;

private:
	/**
	 * @fn CheckFileSize
	 * @brief 渡されたストリームのサイズを返す
	 * @param std::istream& (_stream)
	*/
	std::streamsize CheckFileSize(std::istream& _stream);

	/**
	 * @fn Read
	 * @brief ファイルから指定されたバイト数読みとる
	 * @param std::ifstream& (_stream)
	 * @param std::vector<char>& (_outputData)
	 * @param const std::streamsize& _readSize
	*/
	void Read(std::ifstream& _stream, std::vector<char>& _outputData, const std::streamsize& _readSize);

public:
	/**
	 * @fn GetAssetType
	 * @brief アセットのタイプを返す
	 * @detail typeidを使用して型判別をしている
	 * @return const std::type_info&
	*/
	inline const std::type_info& GetAssetType() const noexcept;

	/**
	 * @fn ReadAllData
	 * @brief すべてのデータの読み込みをする
	 * @param std::vector<char>& (_outputData)
	 * @return void
	*/
	void ReadAllData(std::vector<char>& _outputData);

	/**
	* @fn WriteData
	* @brief データをファイルに書き込む関数
	* @param const char*     (_writeData)
	* @param const size_t    (_writeDataSize) 
	* @param const WriteMode (_writeMode) デフォルトは追記
	* @return void
	*/
	void WriteData(const char* _writeData, const size_t _writeDataSize, const WriteMode _writeMode = WriteMode::Add);
};

//---------- INLINES ----------

inline const std::type_info& BinaryFile::GetAssetType() const noexcept
{
	return typeid(BinaryFile);
}

