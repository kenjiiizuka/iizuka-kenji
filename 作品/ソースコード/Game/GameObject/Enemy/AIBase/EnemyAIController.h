/**
* @file EnemyAIController.h
* @brief EnemyAIControllerクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include <memory>

/**
* @file  EnemyAIController.h
* @brief EnemyAIControllerクラス定義
*/

//---------- 前方宣言 ----------
class EnemyBase;
class EnemyActionSelector;
class EnemyActionProcessor;
class BlackBoard;
class IGeneticAlgorithm;

/** エネミーのAIクラス */
class EnemyAIController
{
public:
	/**
	* 値の初期化
	* @param[in] EnemyBase* (_controlledEnemy)
	*/
	EnemyAIController(EnemyBase* _controlledEnemy);

private:
	/** 制御を止めるか */
	bool mbRunAI;

protected:
	/** 行動選択クラス */
	std::shared_ptr<EnemyActionSelector> mActionSelector;

	/** 行動実行クラス */
	std::shared_ptr<EnemyActionProcessor> mActionProcessor;

	/** 制御しているエネミー */
	EnemyBase* mControlledEnemy;

	/** ブラックボード */
	std::shared_ptr<BlackBoard> mBlackBoard;

	/** 遺伝学習クラス */
	std::shared_ptr<IGeneticAlgorithm> mGeneticAlgorithm;

public:
	/**
	 * @fn Init
	 * @brief 初期化処理 ※ Selector生成後に呼び出すように
	 * @return void
	*/
	virtual void Init();

	/**
	 * @fn Update
	 * @brief 更新処理
	 * @return void
	*/
	virtual void Update();

	/**
	 * @fn StopController
	 * @brief 制御をやめる関数
	 * @return void
	*/
	void StopController();

	/**
	* @fn RunController
	* @brief 制御を開始する関数
	* @return void
	*/
	void RunController();

private:
	/**
	* @fn GeneticAlgorithmEnd
	* @brief 遺伝学習の終了処理
	* @detail 遺伝子の評価、次世代遺伝子の生成、遺伝子子の保存関数を実行する
	* @return void
	*/
	void GeneticAlgorithmEnd();

public:
	/**
	 * @fn SetTakenDamageToCurrentExecuteAttackAction
	 * @brief 現在実行している攻撃行動にくらったダメージをセットする関数
	 * @param const float (_takenDamage)
	 * @return void
	*/
	void SetTakenDamageToCurrentExecuteAttackAction(const float _takenDamage);

	/**
	* @fn GetActionSelector
	* @brief アクションセレクターを返す
	* @return std::weak_ptr<EnemyActionSelector>
	*/
	inline std::weak_ptr<EnemyActionSelector> GetActionSelector() const noexcept;

	/**
	* @fn GetBlackboard
	* @brief ブラックボードを返す
	* @return std::weak_ptr<BlackBoard>
	*/
	inline std::weak_ptr<BlackBoard> GetBlackboard() const noexcept;

};

//-------------- INLINES ---------------

inline std::weak_ptr<EnemyActionSelector> EnemyAIController::GetActionSelector() const noexcept
{
	return mActionSelector;
}

inline std::weak_ptr<BlackBoard> EnemyAIController::GetBlackboard() const noexcept
{
	return mBlackBoard;
}
