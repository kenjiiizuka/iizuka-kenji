//--------- INCLUDES ----------
#include <fstream>
#include "JsonFile.h"

JsonFile::JsonFile()
{
	// �����Ȃ�
}

JsonFile::~JsonFile()
{
	// �����Ȃ�
}

void JsonFile::WriteFile() const
{
	std::ofstream stream;
	stream.open(mFilePath, std::ios_base::out);
	stream << mJson.dump() << std::endl;
}