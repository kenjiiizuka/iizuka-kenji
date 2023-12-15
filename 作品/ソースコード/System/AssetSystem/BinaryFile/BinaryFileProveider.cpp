//--------- INCLUDES ---------
#include <iostream>
#include "BinaryFileProveider.h"
#include "../AssetHandle.h"
#include "BinaryFile.h"


BinaryFileProvider::BinaryFileProvider()
	: mbCreateFile(false)
{
	// 処理なし
}


BinaryFileProvider::~BinaryFileProvider()
{
	// 処理なし
}

std::shared_ptr<IAsset> BinaryFileProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<BinaryFile> newFile = std::make_shared<BinaryFile>();

	// ファイルパスが正しいかを確認するためにファイルを開く
	std::ifstream stream;
	stream.open(_filePath, std::ios_base::binary);

	// ファイルが正常に開けているか確認する
	if (!stream.is_open())
	{
		// ファイル作成する設定なら作成する
		if (mbCreateFile)
		{
			stream.open(_filePath);
			stream.close();
			stream.open(_filePath, std::ios_base::binary);
		}
		// 作成しないならエラーメッセージを出す
		else 
		{
			std::cout << _filePath << "を開くことができませんでした" << std::endl;
			return nullptr;
		}
	}

	// ファイルのサイズを取得
	stream.seekg(0,std::ios::end);
	newFile->mStreamSize = stream.tellg();
	newFile->mFilePath = _filePath;
	
	// ファイルを閉じる
	stream.close();
	return newFile;
}

void BinaryFileProvider::Setting()
{
	// セッティングデータを取得する
	std::memcpy(&mbCreateFile, mLoadSetting.data(), sizeof(bool));
}
