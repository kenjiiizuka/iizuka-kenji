//--------- INCLUDES ----------
#include <fstream>
#include "JsonFile.h"

JsonFile::JsonFile()
{
	// ˆ—‚È‚µ
}

JsonFile::~JsonFile()
{
	// ˆ—‚È‚µ
}

void JsonFile::WriteFile() const
{
	std::ofstream stream;
	stream.open(mFilePath, std::ios_base::out);
	stream << mJson.dump() << std::endl;
}