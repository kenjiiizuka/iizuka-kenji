#pragma once
#include <type_traits>
#include <memory>
#include <vector>
#include <functional>
#include <SimpleMath.h>
#include "../EnemyData.h"
#include "GeneticAlgorithm/GeneticInfomation.h"

/**
* @file  EnemyActionSelector.h
* @brief EnemyActionSelectorクラス定義
*/

class EnemyAction;
class BlackBoard;

/** エネミーの行動を選択するクラス */
class EnemyActionSelector
{
public:
	/**
	* コンストラクタ
	* 
	* @param std::shared_ptr<BlackBoard> (_blackBoard)
	*/
	EnemyActionSelector(std::shared_ptr<BlackBoard> _blackBoard);

private:
	/** 選択した行動のID */
	std::shared_ptr<EnemyAction> mSelectedAction;

	/** 意思決定データ */
	std::shared_ptr<Gene> mDecisionGene;

	/** 同じ攻撃を連続で選択した回数 */
	float mSameAttackCount;

	/** 同じ攻撃が連続して実行できる最大回数 */
	const float mMaxSameAttackExecuteCount = 3;

	/** 前回選択した攻撃行動の名前 */
	std::string mPrevSelectAttackActionName;
		  
protected:
	/** 選択対象の行動を格納する配列 */
	std::vector<std::shared_ptr<EnemyAction>> mActions;

	/** ブラックボード */
	std::shared_ptr<BlackBoard> mBlackBoard;

public:

	/**
	 * @fn Update
	 * @brief 更新処理
	 * @return void
	*/
	virtual void Update();

private:
	/**
	 * @fn FindExecutableAttackGenes
	 * @brief 渡された攻撃遺伝子から実行可能な攻撃遺伝子を探し、返す
	 * @param const AttackGenetic& (_attackGenetic) 攻撃遺伝子
	 * @return AttackGenes 実行可能な攻撃遺伝子
	*/
	AttackGenes FindExecutableAttackGenes(const AttackGenes& _attackGenetic);
 
	/**
	* @fn SelectAttack
	* @brief 実行可能な攻撃遺伝子を探し、実行する攻撃遺伝子を選択する関数
	* @param const AttackGenetic&          (_attackGenetic)         攻撃遺伝子
	* @param std::shared_ptr<EnemyAction>& (_outputSelectedAction)  選択した攻撃遺伝子
	* @return bool true 選択 false 選択していない
	*/
	bool SelectAttack(const AttackGenes& _attackGenetic, std::shared_ptr<EnemyAction>& _outputSelectedAction);

	/**
	 * @fn FindExecutableMoveGenes
	 * @brief 渡された移動遺伝子から実行可能な移動遺伝子を探し、返す
	 * @param const MoveGenes& (_moveGenetic) 移動遺伝子
	 * @return MoveGenes 実行可能な移動遺伝子
	*/
	MoveGenes FindExecutableMoveGenes(const MoveGenes& _moveGenetic);

	/**
	* @fn SelectMove
	* @brief 実行可能な移動遺伝子を探し、実行する移動遺伝子を選択する関数
	* @param const MoveGenes&              (_attackGenetic)
	* @param std::shared_ptr<EnemyAction>& (_outputSelectedAction)
	* @return true 選択 false 選択していない
	*/
	bool SelectMove(const MoveGenes& _attackGenetic, std::shared_ptr<EnemyAction>& _outputSelectedAction);

	/**
	* @fn RandomSelectMove
	* @brief ランダムに移動遺伝子を選択する
	* @param const MoveGenes& (_moveGenes) 選択候補の移動遺伝子
	* @return std::shared_ptr<EnemyAction>
	*/
	std::shared_ptr<EnemyAction> RandomSelectMove(const MoveGenes& _moveGenes);

	/**
	* @fn RandomSelectAttack
	* @brief ランダムに攻撃を選択する
	* @param const AttackGenes& (_attackGenes) 選択候補の攻撃遺伝子
	* @return std::shared_ptr<EnemyAction>
	*/
	std::shared_ptr<EnemyAction> RandomSelectAttack(const AttackGenes& _attackGenes);

	/**
	* @fn FindSuitable
	* @brief 今の状況に適している状況遺伝子を取得する関数
	* @param const std::shared_ptr<Gene>& (_gene)
	* @return std::shared_ptr<Situation> 状況にてきしている状況遺伝子
	*/
	std::shared_ptr<Situation> FindSuitableSituation(const std::shared_ptr<Gene>& _gene);

	/**
	* @fn CheckConsecutiveAttackActionSelection
	* @brief 連続で同じ攻撃遺伝子を選択しているかを確認する関数
	* @param const std::string& (_selectActionName)
	* @return bool true 連続で選択している false 連続選択していない
	*/
	bool CheckConsecutiveAttackActionSelection(const std::string& _selectActionName);

	/**
	* @fn ShouldExecuteAttack
	* @brief 攻撃を実行するかしないかを判断する関数
	* @return void
	*/
	bool ShouldExecuteAttack() const noexcept;

public:
	/**
	 * @fn GetSelectAction
	 * @brief 選択した行動IDを返す関数
	 * @return std::shared_ptr<EnemyAction>
	*/
	inline std::shared_ptr<EnemyAction> GetSelectAction();

	/**
	 * @fn SetGene
	 * @brief 遺伝子をセットする
	 * @param const std::shared_ptr<Gene>& (_gene)
	 * @void
	*/
	inline void SetGene(const std::shared_ptr<Gene>& _gene);

	/**
	* @fn GetGene
	* @brief 遺伝子を返す
	* @return void
	*/
	inline std::weak_ptr<Gene> GetGene() const noexcept;

};

// ------------------------ INLINES --------------------------

inline std::shared_ptr<EnemyAction> EnemyActionSelector::GetSelectAction()
{
	return mSelectedAction;
}

inline void EnemyActionSelector::SetGene(const std::shared_ptr<Gene>& _gene)
{
	mDecisionGene = _gene;
}

inline std::weak_ptr<Gene> EnemyActionSelector::GetGene() const noexcept
{
	return mDecisionGene;
}
