/**
* @file BearEnemyAttackData.h
* @brief BearEnemyAttackDataクラスの定義
*/
#pragma once

//--------- INCLUDES ----------
#include "../IEnemyAttackData.h"
#include <nlohmann/json.hpp>

/**
* @class BearEnemyAttackData
* @brief 熊の敵の攻撃の情報を持つクラス
*/
class BearEnemyAttackData : public IEnemyAttackData
{
public:
	/**
	* @enum
	* @brief 熊の敵の攻撃のID
	* @detail BearEnemyAttackData内に定義して配列の添え字として使いやすいようにしている
	*/
	enum AttackID : uint8_t
	{
		ArmSmash = 0,          /**< 腕で殴る攻撃 */
		ArmUpperSmash,         /**< 武器を振る攻撃 弱 */
		DownwardSlash,         /**< 武器を振り下ろす攻撃 */
		DownwardSlashStrong,   /**< 武器振り下ろし 強 */
		UpwardSlash,           /**< 武器を振り上げる攻撃 */
		DoubleSlash,           /**< 武器を2回振る攻撃 */
		DoubleSlash_Strong,    /**< 武器を2回振る攻撃 強 */
		DoubleSlash_StrongLow, /**< 武器を二回地面を這うように振る攻撃 強 */
		TripleSlash,           /**< 武器を3回振る攻撃 */
		JumpSlash,             /**< ジャンプして武器を振る攻撃 */
		BackAndFrontSlash,     /**< 後ろと前に武器を攻撃 */
		Kick,                  /**< 蹴り攻撃 */
		BackJumpSlash,         /**< 切り下がり */
		Max,                   /**< 最大数 */
	};


public:
	/**
	* デフォルトコンストラクタ
	*/
	BearEnemyAttackData();

	/**
	* デストラクタ
	*/
	~BearEnemyAttackData();

private:
	/** 攻撃のデータをセーブするファイルパス */
	const std::string mSaveDataFilePath = "assets/Enemy/Config/AttackData.json";

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail 攻撃の情報を設定しています
	*/
	void Initialize() override;

	/**
	* @fn SaveData
	* @brief 攻撃データの保存
	* @return void
	*/
	void SaveData() override;

private:
	/**
	* @fn AddAttackDataToJson
	* @brief jsonオブジェクトに攻撃のデータを追加する
	* @param nlohmann::json&  (_json)
	* @param const AttackID&  (_id)
	* @param std::string_view (_dataName)
	* @return void
	*/
	void AddAttackDataToJson(nlohmann::json& _json, const AttackID& _id, std::string_view _dataName);

	/**
	* @fn LoadData
	* @brief データの読み込みをする
	* @return bool true 読み込み成功 false 読み込み失敗
	*/
	bool LoadData();

	/**
	* @fn GetAttackDataFromJson
	* @brief Jsonファイルから攻撃のデータを読み込み
	* @param nlohmann::json& (_json)
	* @param const AttackID& (_id)
	* @param std::string_view (_dataName)
	* @return void
	*/
	void GetAttackDataFromJson(nlohmann::json& _json, const AttackID& _id, std::string_view _dataName);

};

