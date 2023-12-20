/**
* @file PlayerAttackData.h
* @brief PlayerAttackDataクラスの定義
*/

#pragma once

//---------- INCLUDES ---------
#include "PlayerData.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

/**
* @class PlayerAttackData
* @brief プレイヤーの攻撃のデータを持つクラス
* @detail プレイヤーの攻撃のデータにアクセスしやすいようにラップしたクラス
*/
class PlayerAttackData
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	PlayerAttackData();

	/**
	* デストラクタ
	*/
	~PlayerAttackData();

private:
	/** 攻撃の情報 */
	std::vector<PlayerAttack> mAttackInformation;

	/** 攻撃データファイルのファイルパス */
	const std::string mAttackDataFilePath = "assets/Player/Config/AttackData.json";

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail データの設定をしている
	* @return void
	*/
	void Initialize();

	/**
	* @fn SaveJsonFile
	* @brief Jsonファイルにセーブする
	* @return void
	*/
	void SaveJsonFile();

private:
	/**
	* @fn LoadAttackData
	* @brief 攻撃のデータを読み込む関数
	* @return bool true 読み込み成功 false 読み込み失敗
	*/
	bool LoadAttackData();

	/**
	* @fn AddAttackDataToJson
	* @brief Jsonオブジェクトに攻撃のデータを書き込む関数
	* @param nlohmann::json& (_json) 書き込み先のJsonオブジェクト
	* @param const AttackID& (_attackID) 書き込む攻撃のID
	* @param std::string_view (_attackName) 書き込む攻撃の名前
	* @return void
	*/
	void AddAttackDataToJson(nlohmann::json& _json, const PlayerData::AttackID& _attackID, std::string_view _attackName);

	/**
	* @fn GetAttackDataFromJson
	* @brief Jsonファイルから攻撃のデータを取得する
	* @param nlohmann::json& (_json) データがはいっているJsonオブジェクト
	* @param const AttackID& (_attackID) 読み込みたい攻撃のID
	* @param std::string_view (_attackName) 書き込んだときと同じ名前を指定するように
	* @return void
	*/
	void GetAttackDataFromJson(nlohmann::json& _json, const PlayerData::AttackID& _attackID, std::string_view _attackName);

public:
	/**
	* @fn GetAttackInformation
	* @brief 攻撃データの取得
	* @param const PlayerEntities::AttackID (_attackID)
	* @return 
	*/
	inline PlayerAttack GetAttack(const PlayerData::AttackID _attackID) const;

	/**
	* @fn GetNextAttackInformation
	* @brief 引数で指定された攻撃の次のYボタン攻撃を返す
	* @param const PlayerEntities::AttackID (_attackID)
	* @return PlayerAttack 次のYボタン攻撃
	*/
	inline PlayerAttack GetNextYAttackInformation(const PlayerData::AttackID _attackID) const;

	/**
	* @fn GetNextBAttackInformation
	* @brief 引数で指定された攻撃の次のBボタン攻撃を返す
	* @param const PlayerEntities::AttackID (_attackID)
	* @return PlayerAttack 次のBボタン攻撃
	*/
	inline PlayerAttack GetNextBAttackInformation(const PlayerData::AttackID _attackID) const;

	/**
	* @fn SetAttackInformation
	* @brief 攻撃データのセット
	* @param const PlayerEntities::AttackID (_attackID)
	* @param const PlayerAttack& (_newAttackData)
	* @return
	*/
	inline void SetAttackInformation(const PlayerData::AttackID _attackID, const PlayerAttack& _newAttackData);

};


//----------- INLINES ------------
inline PlayerAttack PlayerAttackData::GetAttack(const PlayerData::AttackID _attackID) const
{
	return mAttackInformation[_attackID];
}

inline PlayerAttack PlayerAttackData::GetNextYAttackInformation(const PlayerData::AttackID _attackID) const
{
	PlayerData::AttackID nextYID =  mAttackInformation[_attackID].mNextY;
	return mAttackInformation[nextYID];
}

inline PlayerAttack PlayerAttackData::GetNextBAttackInformation(const PlayerData::AttackID _attackID) const
{
	PlayerData::AttackID nextBID = mAttackInformation[_attackID].mNextB;
	return mAttackInformation[nextBID];
}

inline void PlayerAttackData::SetAttackInformation(const PlayerData::AttackID _attackID, const PlayerAttack& _newAttackData)
{
	mAttackInformation[_attackID] = _newAttackData;
}
