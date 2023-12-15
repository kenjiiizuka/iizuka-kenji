#include <iostream>
#include "BinaryFile.h"

BinaryFile::BinaryFile()
	: mStreamSize(0)
{
	// 処理なし
}

BinaryFile::~BinaryFile()
{
	// 処理なし
}

std::streamsize BinaryFile::CheckFileSize(std::istream& _stream)
{
	// ファイルのサイズを取得 シークを末尾に移動→サイズを取得→シークを先頭に移動
	std::streamsize size;
	_stream.seekg(0, std::ios::end);
	size = _stream.tellg();
	_stream.seekg(0, std::ios::beg);
	return size;
}

void BinaryFile::Read(std::ifstream& _stream, std::vector<char>& _outputData, const std::streamsize& _readSize)
{
	_outputData.resize(_readSize);
	_stream.read(_outputData.data(), _readSize);
}

void BinaryFile::ReadAllData(std::vector<char>& _outputData)
{
	// バイナリモードで開く
	std::ifstream stream;
	stream.open(mFilePath, std::ios::binary);

	// 開けているかチェック
	if (!stream.is_open())
	{
		std::cout << "ファイルオープン失敗 ：" << mFilePath << std::endl;
		return;
	}

	// ファイルサイズをチェック
	mStreamSize = CheckFileSize(stream);

	// ファイルからすべてのデータを読み取る
	Read(stream, _outputData, mStreamSize);

	// ファイルクローズ
	stream.close();
}

void BinaryFile::WriteData(const char* _writeData, const size_t _writeDataSize, const WriteMode _writeMode)
{
	std::ofstream stream;

	// バイナリモードで開く
	stream.open(mFilePath, static_cast<std::ios_base::openmode>(_writeMode));
	// 開けているかチェック
	if (!stream.is_open())
	{
		std::cout << "ファイルオープン失敗 ：" << mFilePath << std::endl;		
		return;
	}
	
	// 書き込み
	stream.write(_writeData, static_cast<std::streamsize>(_writeDataSize));
	stream.close();
}

