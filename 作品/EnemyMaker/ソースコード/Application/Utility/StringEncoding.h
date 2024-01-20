#pragma once

//--------- INCLUDES ----------
#include <string>

/**
* @fn SJIS_To_Wide 
* @brief SJISからWide文字に変換する
* @param std::string const& (src)
* @return std::wstring
*/
std::wstring SJIS_To_Wide(std::string const& src);