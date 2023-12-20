/**
* @file BearEnemyEditor.h
* @brief EnemyEditorクラスの定義
*/

#pragma once

//-------- INCLUDES ----------
#include "../Enemy/EnemyBase.h"

//--------- 前方宣言 ----------
class EnemyAttackAction;
class EnemyActionProcessor;

/**
* @class EnemyEditor
* @brief エネミー用のエディター
*/
class BearEnemyEditor
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BearEnemyEditor();

	/**
	* デストラクタ
	*/
	~BearEnemyEditor();

private:
	/** 編集するエネミー */
	std::weak_ptr<EnemyBase> mEditEnemy;

	/** 攻撃を実行する用のプロセッサー */
	std::shared_ptr<EnemyActionProcessor> mActionProcessor;

	/** 編集したい攻撃行動 */
	std::vector<std::shared_ptr<EnemyAttackAction>> mAttackActions;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param std::shared_ptr<EnemyBase> (_enemy)
	* @return void
	*/
	void Initialize(std::shared_ptr<EnemyBase> _enemy);

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update();

private:
	/**
	* @fn AttackHeader
	* @brief 敵の攻撃を編集するヘッダー
	* @param std::shared_ptr<EnemyAttackAction>& (_attack)
	* @return void
	*/
	void AttackHeader();

	/**
	* @fn AttackNode
	* @brief 敵の攻撃を編集するノード
	* @param std::shared_ptr<EnemyAttackAction>& (_attack) 編集する攻撃
	* @return void
	*/
	void AttackNode(std::shared_ptr<EnemyAttackAction>& _attack);

	/** 
	* @fn CameraShakeNode
	* @brief カメラ振動を編集するノード
	* @param _attack
	*/
	void CameraShakeNode(EnemyAttack _attackData);

	/**
	* @fn PlayAttack
	* @brief 攻撃を実行する関数
	* @param std::shared_ptr<EnemyAttackAction>& (_attack)
	* @return void
	*/
	void PlayAttack(std::shared_ptr<EnemyAttackAction>& _attack);

};