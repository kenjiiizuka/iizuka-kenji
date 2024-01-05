/**
* @file CurveFloat.h
* @brief CurveFloatクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include <string>
#include <vector>
#include "../ImGui/ImGuiUtility.h"

/**
* @class CurveFloat
* @brief カーブクラス
* @detail 横軸:時間 縦軸:値
*/
class CurveFloat
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	CurveFloat();

	/**
	* デストラクタ
	*/
	~CurveFloat();

private:
	/** データを保存するファイルパス */
	std::string mFilePath;

	/** カーブ上のキー */
	std::vector<ImVec2> mCurveKey;

	/** カーブウィンドウのサイズ */
	ImVec2 mSize;

public:
	/**
	* @fn Initialize
	* @brief ファイルを開きデータがあれば読み込む
	* @param std::string_view (_filePath)
	* @return void
	*/
	void Initialize(std::string_view _filePath);

	/**
	* @fn Edit
	* @brief カーブを編集する関数
	* @param std::string_view (_label)
	* @return void
	*/
	void Edit(std::string_view _label);

	/**
	* @fn GetValue
	* @brief 時間に応じた値を返す
	* @detail _timeは 0 ～ 1の範囲 範囲外の値でも関数内で01にクランプしている
	* @param const float (_time)
	* @return float 
	*/
	float GetValueByTime(const float _time);

private:
	/**
	* @fn Save
	* @brief キーの値を保存する
	* @return void
	*/
	void Save();

};

