/**
* @file BlackBoard
* @brief BlackBoardクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include <unordered_map>
#include <any>
#include <string>

/**
* @class BlackBoard
* @brief AIが使用する情報を書き込み、保持するクラス
*/
class BlackBoard final
{
public:
	/**
	* コンストラクタ
	*/
	BlackBoard() {};

private:
	/** 書き込まれた情報 */
	std::unordered_map<std::string, std::any> mData;

public:
	/**
	 * @fn GetValue
	 * @brief 書き込まれたデータを取得する関数
	 * @param const std::string& (_key) 取得したいデータのキー
	 * @return T 
	*/
	template<typename T>
	inline T GetValue(const std::string& _key);

	/**
	 * @fn SetValue
	 * @brief データをセットする関数
	 * @param const T (_data) セットするデータ
	 * @param const std::string& (_key) セットするデータのキー
	 * @return T
	*/
	template<typename T>
	inline void SetValue(const T _data, const std::string& _key);
};

//-------------- INLINES -----------------

template<typename T>
inline T BlackBoard::GetValue(const std::string& _key)
{
	if (!mData.contains(_key))
	{
		return T();
	}
	return std::any_cast<T>(mData[_key]);
}

template<typename T>
inline void BlackBoard::SetValue(const T _data, const std::string& _key)
{
	mData[_key] = _data;
}

