//---------- INCLUDES -----------
#include <fstream>
#include "JsonFile.h"
#include "JsonFileProvider.h"

JsonFileProvider::JsonFileProvider()
	: mbCreateFile(false)
{
	// 処理なし
}

JsonFileProvider::~JsonFileProvider()
{
	// 処理なし
}

std::shared_ptr<IAsset> JsonFileProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<JsonFile> newJson = std::make_shared<JsonFile>();

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
		}
		// 作成しないならエラーメッセージを出す
		else
		{
			std::cout << _filePath << "を開くことができませんでした" << std::endl;
			return nullptr;
		}
	}

	// ファイルのサイズを取得 シークを末尾に移動→サイズを取得→シークを先頭に移動
	std::streamsize size;
	stream.seekg(0, std::ios::end);
	size = stream.tellg();
	stream.seekg(0, std::ios::beg);
	// ファイルサイズが0より大きければjsonオブジェクトに代入する
	if (size > 0)
	{
		stream >> newJson->mJson;
	}

	// ファイルを閉じる
	stream.close();

	newJson->mFilePath = _filePath;

	return newJson;
}

void JsonFileProvider::Setting()
{
	// セッティングデータを取得する
	std::memcpy(&mbCreateFile, mLoadSetting.data(), sizeof(bool));
}

