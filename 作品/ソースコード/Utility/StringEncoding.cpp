#include "StringEncoding.h"
#include <string>
#include <Windows.h>

std::wstring SJIS_To_Wide(std::string const& _string)
{
	int byteSize = ::MultiByteToWideChar(CP_ACP, 0, _string.c_str(), -1, nullptr, 0); // •ÏŠ·Œã‚ÌƒTƒCƒY‚ðŽæ“¾
	std::wstring wideString;
	wideString.resize(byteSize);
	::MultiByteToWideChar(CP_ACP, 0, _string.c_str(), -1, &wideString[0], byteSize);
	return wideString;
}
