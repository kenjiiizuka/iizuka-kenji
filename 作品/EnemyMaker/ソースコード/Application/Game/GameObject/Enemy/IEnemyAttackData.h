/**
* @file IEnemyAttackData.h
* @brief IEnemyAttackDataクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "EnemyData.h"

/**
* @class IEnemyAttackData
* @brief 敵の攻撃の情報を持ちそれにアクセスしやすいようにしたクラス
* @detail Initialize関数内で攻撃の情報を設定して、このクラスを持っている敵はこのクラスから攻撃の情報を取得
*         また、アクセスしやすいように派生先のクラスで各攻撃のIDとして列挙型を定義し使用する
*/
class IEnemyAttackData
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	IEnemyAttackData();

	/**
	* デストラクタ
	*/
	~IEnemyAttackData();

protected:
	/** 攻撃の情報 */
	std::vector<EnemyAttack> mAttackInformation;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail 攻撃の情報の設定を行っている
	* @return void
	*/
	virtual void Initialize() = 0;

	/**
	* @fn SaveData
	* @brief 攻撃データをセーブする
	* @return void 
	*/
	virtual void SaveData() = 0;

	/**
	* @fn GetAttackInformation
	* @brief 攻撃の情報を取得する関数
	* @detail 引数に攻撃のIDを渡すことでIDに対応して攻撃の情報を返す
	* @param const uint8_t (_attackID)
	* @return EnemyAttack
	*/
	inline virtual EnemyAttack GetAttack(const uint8_t _attackID) const noexcept;

	/**
	* @fn SetAttackInformation
	* @brief 攻撃のセッター
	* @param const uint8_t (_attackID)
	* @param const EnemyAttack (_newAttack)
	* @return void
	*/
	inline virtual void SetAttackInformation(const uint8_t _attackID, const EnemyAttack _newAttack) noexcept;
};

//---------- INLINES ----------

inline EnemyAttack IEnemyAttackData::GetAttack(const uint8_t _attackID) const noexcept
{
	// 配列外参照しないようにチェック
	if (mAttackInformation.size() < _attackID)
	{
		return EnemyAttack();
	}

	return mAttackInformation[_attackID];	
}

inline void IEnemyAttackData::SetAttackInformation(const uint8_t _attackID, const EnemyAttack _newAttack) noexcept
{
	// サイズチェック
	if (mAttackInformation.size() <= _attackID)
	{
		return;
	}

	mAttackInformation[_attackID] = _newAttack;
}


