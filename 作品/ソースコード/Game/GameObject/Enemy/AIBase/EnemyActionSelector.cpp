//-------------- INCLUDES -------------
#include <random>
#include "EnemyActionSelector.h"
#include "GeneticAlgorithm/Gene/EnemyAction.h"
#include "GeneticAlgorithm/Gene/Gene.h"
#include "GeneticAlgorithm/Gene/EnemyAttackAction.h"
#include "GeneticAlgorithm/Gene/EnemyMoveAction.h"
#include "../../../../Utility/MathLibrary.h"

EnemyActionSelector::EnemyActionSelector(std::shared_ptr<BlackBoard> _blackBoard)
	: mBlackBoard(_blackBoard)
	, mSameAttackCount(0)
	, mPrevSelectAttackActionName("NoSelect")
{
	// 処理なし
}

void EnemyActionSelector::Update()
{
	// 今現在の状況に適しているシチュエーション
	std::shared_ptr<Situation> suitableSituation = FindSuitableSituation(mDecisionGene);
	
	// 攻撃遺伝子を選択する
	if(SelectAttack(suitableSituation->GetAttackGenes(), mSelectedAction))
	{
		// 前回選択した行動の名前を記録
		mPrevSelectAttackActionName = mSelectedAction->GetTypeName();
		return;
	}
	
	// 移動遺伝子を選択する
	if (SelectMove(suitableSituation->GetMoveGenes(), mSelectedAction))
	{
		return;
	}

	// なにも選ばれていなかったら移動遺伝子の中からランダムで選択する
	mSelectedAction = RandomSelectAttack(suitableSituation->GetAttackGenes());
}

AttackGenes EnemyActionSelector::FindExecutableAttackGenes(const AttackGenes& _attackGenes)
{
	AttackGenes executableAttacks; // 実行可能攻撃遺伝子を保持する配列
	
	// 実行可能な攻撃遺伝子を探す
	for (std::shared_ptr<EnemyAttackAction> attack : _attackGenes)
	{	
		if (attack->IsExecuteAble())
		{
			executableAttacks.push_back(attack);
		}		
	}
	return executableAttacks;
}

bool EnemyActionSelector::SelectAttack(const AttackGenes& _attackGenes, std::shared_ptr<EnemyAction>& _outputSelectedAction)
{
	// 発動条件を満たしている攻撃を探す	
	AttackGenes executableAttacks = FindExecutableAttackGenes(_attackGenes);

	// 実行可能な攻撃遺伝子があるか判断
	size_t actionsNum = executableAttacks.size();
	if (actionsNum == 0)
	{
		return false;
	}

	// 実行可能な攻撃からランダムで実行する行動を選択する
	size_t selectedAttack_i = std::rand() % actionsNum;
	_outputSelectedAction = executableAttacks[selectedAttack_i];

	std::string selectActionName = _outputSelectedAction->GetTypeName();
	// 連続して選択されていなければ処理終了
	if (!CheckConsecutiveAttackActionSelection(selectActionName)) 
	{ 
		return true; 
	}

	// 連続して選択されていれば、実行するかしないかを判断する
	// 実行するなら処理終了
	if (ShouldExecuteAttack())
	{
		return true;
	}

	// 実行しないなら他の行動からランダムに選択する
	_outputSelectedAction = RandomSelectAttack(_attackGenes);

	return true;
}

MoveGenes EnemyActionSelector::FindExecutableMoveGenes(const MoveGenes& _moveGenes)
{
	MoveGenes executableMoveGenes; // 実行可能な移動遺伝子を保持する配列

	// 実行可能な移動遺伝子を探す
	for (std::shared_ptr<EnemyMoveAction> move : _moveGenes)
	{	
		if (move->IsExecuteAble())
		{
			executableMoveGenes.push_back(move);
		}		
	}
	return executableMoveGenes;
}

bool EnemyActionSelector::SelectMove(const MoveGenes& _moveGenetic, std::shared_ptr<EnemyAction>& _outputSelectedAction)
{
	// 選択可能な移動遺伝子を探す
	MoveGenes executableMoveGenes = FindExecutableMoveGenes(_moveGenetic);

	// 実行可能な移動遺伝子があるかを確認する
	size_t actionsNum = executableMoveGenes.size();
	if (actionsNum == 0)
	{
		return false;
	}

	size_t selectedMove_i = std::rand() % actionsNum;
	_outputSelectedAction = executableMoveGenes[selectedMove_i];
	return true;
}

std::shared_ptr<EnemyAction> EnemyActionSelector::RandomSelectMove(const MoveGenes& _moveGenes)
{
	size_t selected_i = std::rand() % _moveGenes.size();
	return _moveGenes[selected_i];
}

std::shared_ptr<EnemyAction> EnemyActionSelector::RandomSelectAttack(const AttackGenes& _attackGenes)
{
	size_t selected_i = std::rand() % _attackGenes.size();
	return _attackGenes[selected_i];
}

std::shared_ptr<Situation> EnemyActionSelector::FindSuitableSituation(const std::shared_ptr<Gene>& _gene)
{
	std::shared_ptr<Situation> suitableSituation;
	std::vector<std::shared_ptr<Situation>> situations = mDecisionGene->GetSituations();
	for (std::shared_ptr<Situation> situation : situations)
	{
		// 現在の状況に適しているか判断する
		if (situation->IsSituationSuitable(mBlackBoard))
		{
			suitableSituation = situation;
		}
	}
	return suitableSituation;
}

bool EnemyActionSelector::CheckConsecutiveAttackActionSelection(const std::string& _selectActionName)
{
	if (_selectActionName == mPrevSelectAttackActionName)
	{
		mSameAttackCount++;
		return true;
	}
	
	mSameAttackCount = 0.0f;
	return false;
}

bool EnemyActionSelector::ShouldExecuteAttack() const noexcept
{
	// 実行確立を求める 
	float executionProbability = MathLibrary::Clamp01(mSameAttackCount / mMaxSameAttackExecuteCount);

	// 0 ～ 1.0の範囲でランダムな値を求める
	float randValue = static_cast<float>(std::rand() % 101) / 100.0f;

	// ランダムな値が 実行確立値以下ならtrueを返す
	return randValue < executionProbability;
}
