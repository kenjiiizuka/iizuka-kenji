//------------ INCLUDES -----------
#include <random>
#include <typeindex>
#include "GeneticDecisionDataGenerator.h"
#include "Gene/Gene.h"
#include "../BlackBoard.h"
#include "Gene/EnemyAttackAction.h"
#include "Gene/EnemyMoveAction.h"
#include "../../../../../Utility/Utility.h"
#include "../../../../../System/Logger/Logger.h"

GeneticDecisionDataGenerator::GeneticDecisionDataGenerator(std::shared_ptr<BlackBoard> _blackboard)
	: mBlackboard(_blackboard)
{
	// 処理なし
}

GeneticDecisionDataGenerator::~GeneticDecisionDataGenerator()
{
	// 処理なし
}

void GeneticDecisionDataGenerator::GenerateFirstGenetic(const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes, const size_t generateNum)
{
	for (size_t generatedCount = 0; generatedCount < generateNum; generatedCount++)
	{
		std::shared_ptr<Gene> newGene;
		RandomGenerateGene(_attackGeneTypes, _moveGeneTypes, newGene);	
		mNextGenerationGenes.emplace_back(newGene);
	}
}

void GeneticDecisionDataGenerator::Genetics(std::vector<std::shared_ptr<Gene>> _gene, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes)
{		
	std::vector<std::shared_ptr<Gene>> nextGenerationGene;

	// 遺伝子を評価値の高い順に並べ替える
	std::vector<std::shared_ptr<Gene>> sortedGene = SortByEvaluation(_gene);
	
	// 遺伝させる回数を求める
	// 遺伝子の半分の数 -1 の回数遺伝させる　
	uint8_t passOnGeneNum = static_cast<uint8_t>(_gene.size() / 2 - 1);

	// 先頭から二組ずつ遺伝させる
	// 二つずつ遺伝させていくので passOnGene_i += 2
	for (size_t passOnGene_i = 0; passOnGene_i < passOnGeneNum; passOnGene_i += 2)
	{
		Logger::GetInstance().WriteLog(
			"EvaluateValue : Parent1" + std::to_string(sortedGene[passOnGene_i]->GetEvaluationValue())
			+ "  Parent2" + std::to_string(sortedGene[passOnGene_i + 1]->GetEvaluationValue())
		);

		std::array<std::shared_ptr<Gene>, 2> newGene;
		PassOnGene(sortedGene[passOnGene_i], sortedGene[passOnGene_i + 1], newGene);
		nextGenerationGene.emplace_back(newGene[0]);
		nextGenerationGene.emplace_back(newGene[1]);
	}

	// 残りの数はランダムで生成する
	uint8_t randomGenerateNum = static_cast<uint8_t>(_gene.size() - nextGenerationGene.size());
	for (size_t generatedCount = 0; generatedCount < randomGenerateNum; generatedCount++)
	{
		std::shared_ptr<Gene> newGene;
		RandomGenerateGene(_attackGeneTypes, _moveGeneTypes, newGene);
		nextGenerationGene.emplace_back(newGene);
	}

	mNextGenerationGenes = nextGenerationGene;
}

std::vector<std::shared_ptr<Gene>> GeneticDecisionDataGenerator::SortByEvaluation(const std::vector<std::shared_ptr<Gene>>& _gene)
{
	// ソートの為に評価値と添え字をを配列に格納する
	std::vector<std::pair<float, size_t>> evaluateAndIndex(_gene.size());
	for (size_t gene_i = 0; const std::shared_ptr<Gene>& gene : _gene)
	{
		evaluateAndIndex[gene_i].first = gene->GetEvaluationValue();
		evaluateAndIndex[gene_i].second = gene_i;
	}

	Utility::QuickSort(evaluateAndIndex, 0, evaluateAndIndex.size() - 1);

	// 遺伝子並べ替え
	std::vector<std::shared_ptr<Gene>> sortedGene(_gene.size());
	for (size_t gene_i = 0; std::shared_ptr<Gene>& gene : sortedGene)
	{
		gene = _gene[evaluateAndIndex[gene_i].second];
		gene_i++;
	}
	return sortedGene;
}


void GeneticDecisionDataGenerator::PassOnGene(const std::shared_ptr<Gene>& _gene1, const std::shared_ptr<Gene>& _gene2, std::array<std::shared_ptr<Gene>, 2>& _newGene)
{
	_newGene[0] = std::make_shared<Gene>();
	_newGene[1] = std::make_shared<Gene>();

	// 同じ状況の状況遺伝子どうしを遺伝させる
	std::vector<std::shared_ptr<Situation>> situations1 = _gene1->GetSituations();
	std::vector<std::shared_ptr<Situation>> situations2 = _gene1->GetSituations();
	
	std::vector<std::shared_ptr<Situation>> newSituations1(situations1.size());
	std::vector<std::shared_ptr<Situation>> newSituations2(situations2.size());
	for (size_t situation_i = 0;  situation_i < situations1.size(); situation_i++)
	{
		std::array<std::shared_ptr<Situation>, 2> newSituation;
		PassOnSituation(situations1[situation_i], situations2[situation_i], newSituation);
		_newGene[0]->AddSituation(newSituation[0]);
		_newGene[1]->AddSituation(newSituation[1]);
	}
}

void GeneticDecisionDataGenerator::PassOnSituation(const std::shared_ptr<Situation> _situation1, const std::shared_ptr<Situation> _situation2, std::array<std::shared_ptr<Situation>, 2>& _newSituation)
{
	AttackGenes attackGenes1 = _situation1->GetAttackGenes();
	AttackGenes attackGenes2 = _situation2->GetAttackGenes();
	std::array<AttackGenes,2> newAttackGenes = CrossoverSinglePointAttackGenetic(attackGenes1, attackGenes2);

	// 攻撃遺伝子をセットする
	_newSituation[0] = std::make_shared<Situation>();
	_newSituation[1] = std::make_shared<Situation>();
	_newSituation[0]->SetAttackGenes(newAttackGenes[0]);
	_newSituation[1]->SetAttackGenes(newAttackGenes[1]);

	// 移動遺伝子をセットする
	MoveGenes moveGenes1 = DuplicationMoveGenesFromSituation(_situation1);
	MoveGenes moveGenes2 = DuplicationMoveGenesFromSituation(_situation2);
	_newSituation[0]->SetMoveGenes(moveGenes1);
	_newSituation[1]->SetMoveGenes(moveGenes2);

	// 遺伝子の初期化
	_newSituation[0]->CalculateAllRiskTypeRatio();
	_newSituation[1]->CalculateAllRiskTypeRatio();
}

std::array<AttackGenes, 2> GeneticDecisionDataGenerator::CrossoverSinglePointAttackGenetic(const AttackGenes& _attackGene1, const AttackGenes& _attackGene2)
{
	// TODO: 攻撃遺伝子の遺伝アルゴリズムの見直し コードの整理をしないと保守できなさそう

    // 一点交叉するための位置を決める
	// 最小サイズを求める
	size_t minSize = _attackGene1.size();
	minSize = minSize < _attackGene2.size() ? minSize : _attackGene2.size();

	// 交叉する位置を求める ※ -1は配列の末尾を選択しないようにするため
	size_t singleCrossPoint = minSize / 2;

	// 交叉
	std::array<AttackGenes, 2> newAttackGenetics;
	// 優先度１の前半と、優先度２の後半をを交叉する
	{
		Logger::GetInstance().WriteLog("[Genetic AttackGenes 1]");

		AttackGenes priorityOneFirstHalf;
		for (size_t attack_i = 0; attack_i < singleCrossPoint; attack_i++)
		{
			priorityOneFirstHalf.push_back(_attackGene1[attack_i]);
		}
		AttackGenes priorityTwoSecondHalf;
		for (size_t attack_i = singleCrossPoint; attack_i < _attackGene2.size(); attack_i++)
		{
			priorityTwoSecondHalf.push_back(_attackGene2[attack_i]);
		}
		newAttackGenetics[0].resize(priorityOneFirstHalf.size() + priorityTwoSecondHalf.size());

		// 遺伝する攻撃を作成する
		for (size_t attack_i = 0l; attack_i < newAttackGenetics[0].size(); attack_i++)
		{
			// 前半
			if (attack_i < singleCrossPoint)
			{
				priorityOneFirstHalf[attack_i]->DuplicateFromSelfType(newAttackGenetics[0][attack_i]);
				Logger::GetInstance().WriteLog("Inherited Gene TypeName : " + newAttackGenetics[0][attack_i]->GetTypeName());
			}
			// 後半
			else
			{
				size_t index = attack_i - (priorityTwoSecondHalf.size());
				priorityTwoSecondHalf[index]->DuplicateFromSelfType(newAttackGenetics[0][attack_i]);
				Logger::GetInstance().WriteLog("Inherited Gene TypeName : " + newAttackGenetics[0][attack_i]->GetTypeName());
			}
		}
	}

	// 優先度１の後半と、優先度２の前半をを交叉する
	{
		Logger::GetInstance().WriteLog("[Genetic AttackGenes 2]");

		AttackGenes priorityOneSecondHalf;
		AttackGenes priorityTwoFirstHalf;

		for (size_t attack_i = 0; attack_i < singleCrossPoint; attack_i++)
		{
			priorityTwoFirstHalf.push_back(_attackGene2[attack_i]);
		}
		for (size_t attack_i = singleCrossPoint; attack_i < _attackGene2.size(); attack_i++)
		{
			priorityOneSecondHalf.push_back(_attackGene1[attack_i]);
		}

		newAttackGenetics[1].resize(priorityOneSecondHalf.size() + priorityTwoFirstHalf.size());

		// 遺伝する攻撃を作成する
		for (size_t attack_i = 0; attack_i < newAttackGenetics[1].size(); attack_i++)
		{
			// 前半
			if (attack_i < singleCrossPoint)
			{
				priorityTwoFirstHalf[attack_i]->DuplicateFromSelfType(newAttackGenetics[1][attack_i]);
				Logger::GetInstance().WriteLog("Inherited Gene TypeName : " + newAttackGenetics[1][attack_i]->GetTypeName());
			}
			// 後半
			else
			{
				size_t index = attack_i - (priorityOneSecondHalf.size());
				priorityOneSecondHalf[index]->DuplicateFromSelfType(newAttackGenetics[1][attack_i]);
				Logger::GetInstance().WriteLog("Inherited Gene TypeName : " + newAttackGenetics[1][attack_i]->GetTypeName());
			}
		}
	}
	return newAttackGenetics;
}

MoveGenes GeneticDecisionDataGenerator::DuplicationMoveGenesFromSituation(std::shared_ptr<Situation> _situation)
{
	MoveGenes moveGenes = _situation->GetMoveGenes();
	MoveGenes duplicationGenes(moveGenes.size());

	// 移動遺伝子を複製する
	for (size_t move_i = 0; std::shared_ptr<EnemyMoveAction> moveGene : moveGenes)
	{
		moveGene->DuplicateFromSelfType(duplicationGenes[move_i]);
		move_i++;
	}

	return duplicationGenes;
}

void GeneticDecisionDataGenerator::RandomGenerateGene(const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes, std::shared_ptr<Gene>& _newGene)
{
	Logger::GetInstance().WriteLog("[RadomGenerateGene]");

	std::shared_ptr<Gene> newGene = std::make_shared<Gene>();
	// Situationのランダム生成
	for (size_t situationGeneratedCount = 0; situationGeneratedCount < 1; situationGeneratedCount++)
	{
		std::shared_ptr<Situation> generatedSituation;
		RandomGenerateSituation(_attackGeneTypes, _moveGeneTypes, generatedSituation);
		newGene->AddSituation(generatedSituation);
	}
	_newGene = newGene;
}

void GeneticDecisionDataGenerator::RandomGenerateSituation(const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes, std::shared_ptr<Situation>& _generatedSituation)
{
	Logger::GetInstance().WriteLog("[RadomGenerateSituation]");

	// 攻撃遺伝子をランダムに生成する
	AttackGenes generatedAttackGene;
	RandomGenerateAttackGene(_attackGeneTypes, generatedAttackGene);

	// 移動遺伝子をランダムに生成する
	MoveGenes generatedMoveGenes;
	RandomGenerateMoveGene(_moveGeneTypes, generatedMoveGenes);

	// 生成された攻撃遺伝子Situationに設定する
	_generatedSituation = std::make_shared<Situation>();
	_generatedSituation->SetAttackGenes(generatedAttackGene);
	_generatedSituation->SetMoveGenes(generatedMoveGenes);
}


void GeneticDecisionDataGenerator::RandomGenerateAttackGene(const AttackGenes& _attackGeneTypes, AttackGenes& _generatedAttackGenes)
{
	Logger::GetInstance().WriteLog("[RadomGenerateAttackGenes]");

	AttackGenes geneTypes = _attackGeneTypes;
	float numAttackGeneType = static_cast<float>(geneTypes.size()); // 生成候補の遺伝子の種類の数

	// 生成する遺伝子の数を設定
	size_t maxAttackGeneNum = static_cast<size_t>(numAttackGeneType * 0.6f); // 最大数の半分６割以上の数を生成する
	_generatedAttackGenes.resize((maxAttackGeneNum));

	// 設定された最大数分攻撃遺伝子をランダムに生成する
	for (size_t newAttackGene_i = 0; newAttackGene_i < maxAttackGeneNum; newAttackGene_i++)
	{
		// どの遺伝子を生成するかランダムに設定
		size_t atttackGeneType_i = std::rand() % geneTypes.size();
		// 攻撃遺伝子の生成
		geneTypes[atttackGeneType_i]->DuplicateFromSelfType(_generatedAttackGenes[newAttackGene_i]);
		geneTypes.erase(geneTypes.begin() + atttackGeneType_i);

		Logger::GetInstance().WriteLog("GenerateAttackGene : " + _generatedAttackGenes[newAttackGene_i]->GetTypeName());
	}
}

void GeneticDecisionDataGenerator::RandomGenerateMoveGene(const MoveGenes& _moveGeneTypes, MoveGenes& _generatedMoveGenes)
{
	if (_moveGeneTypes.size() < 0)
	{
		return;
	}

	MoveGenes geneTypes = _moveGeneTypes;
	size_t numMoveGeneType = geneTypes.size(); // 生成候補の移動遺伝子の種類の数

	// 生成する遺伝子の数を設定
	size_t maxMoveGeneNum = numMoveGeneType;
	_generatedMoveGenes.resize(maxMoveGeneNum);

	// 設定された数分遺伝子を生成
	for (size_t moveGene_i = 0; moveGene_i < maxMoveGeneNum; moveGene_i++)
	{
		// 生成する遺伝子をランダムに決める
		size_t moveGeneType_i = std::rand() % geneTypes.size();

		// 移動遺伝子の生成
		geneTypes[moveGeneType_i]->DuplicateFromSelfType(_generatedMoveGenes[moveGene_i]);

		// 同じ遺伝子を生成しないように配列から除外
		geneTypes.erase(geneTypes.begin() + moveGeneType_i);
	}
}