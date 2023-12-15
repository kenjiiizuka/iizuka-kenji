//--------- INCLUDES ----------
#include <fstream>
#include "JsonFile.h"

JsonFile::JsonFile()
{
	// 処理なし
}

JsonFile::~JsonFile()
{
	// 処理なし
}

void JsonFile::WriteFile() const
{
	std::ofstream stream;
	stream.open(mFilePath, std::ios_base::out);
	stream << mJson.dump() << std::endl;
}