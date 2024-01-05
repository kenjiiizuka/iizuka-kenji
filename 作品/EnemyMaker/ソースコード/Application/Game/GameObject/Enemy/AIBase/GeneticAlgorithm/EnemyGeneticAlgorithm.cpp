//------------- INCLUDES ------------
#include "EnemyGeneticAlgorithm.h"
#include "DecisionEvaluator.h"
#include "GeneticDecisionDataGenerator.h"
#include "../BlackBoard.h"
#include "GeneDataSaver.h"
#include "GeneDataLoader.h"
#include "Gene/Situation.h"
#include "Gene/EnemyAttackAction.h"
#include "Gene/EnemyMoveAction.h"
#include "GeneticAlgorithmDebugger.h"
#include "Gene/Gene.h"
#include "../../../../../System/Logger/Logger.h"

EnemyGeneticAlgorithm::EnemyGeneticAlgorithm(std::shared_ptr<BlackBoard>& _blackboard)
	: IGeneticAlgorithm()
	, mCurrentGenerationGenesSize(0)
	, mGenerationCount(0)
	, mCurrentDataCollectionCount(0)
	, mCurrentDataCollectionGene_i(0)
	, mGeneDataSaver(std::make_shared<GeneDataSaver>())
	, mGeneDataLoader(std::make_shared<GeneDataLoader>())
{
	mBlackBoard = _blackboard;
}

void EnemyGeneticAlgorithm::Init()
{
	// ログ書き出し用のファイルをオープン
	Logger::GetInstance().OpenLogFile("assets/Genetic/GeneDataLog.txt");

	mDecisionEvaluator = std::make_shared<DecisionEvaluator>(mBlackBoard);
	mGenerator = std::make_shared<GeneticDecisionDataGenerator>(mBlackBoard);
	
	// 遺伝子の型を判別するための変数を生成する
	SetupGeneType();

	// ここでロードして、ファイルデータを確認して必要があれば初期遺伝子し生成
	GeneticAlgorithmInf::GeneSaveData saveData;
	bool isValidSaveData = false;
	isValidSaveData = mGeneDataLoader->GeneDataLoad(saveData, mAttackGeneTypes, mMoveGeneTypes);

	// セーブデータがあろうがなかろうが、以下の二つの値は0で初期化されるのでチェックの前に代入しておく
	mGenerationCount = saveData.mGenerationCount;
	mCurrentGenerationGenesSize = saveData.mCurrentGenerationGenesSize;
	mCurrentDataCollectionCount = saveData.mDataCollectionCount;
	mCurrentDataCollectionGene_i = saveData.mCurrentCollectionGene_i;
	if (isValidSaveData)
	{
		// 読み込んできた遺伝子を取得
		mCurrentGenerationGenes = saveData.mGenes;
	}
	else
	{
		GenerateFirstGenes();
	}

	// デバッグ表示用処理　描画する遺伝子のセット
	GeneticAlgorithmDebugger::GetInstance().SetDisplayGenetic(mCurrentGenerationGenes);
	GeneticAlgorithmDebugger::GetInstance().SetCurrentGeneIndex(mCurrentDataCollectionGene_i);
	GeneticAlgorithmDebugger::GetInstance().SetDisplayGeneIndex(mCurrentDataCollectionGene_i);
}

void EnemyGeneticAlgorithm::GenerateFirstGenes()
{
	Logger::GetInstance().WriteLog("[GenerateFirstGenes]");

	// 一番最初の遺伝子を生成する
	mGenerator->GenerateFirstGenetic(mAttackGeneTypes, mMoveGeneTypes, mFirstGenerateGeneNum);
	// 生成した遺伝子を取得する
	mCurrentGenerationGenes = mGenerator->GetNextGenerationGene();
	mCurrentGenerationGenesSize = mCurrentGenerationGenes.size();
	// 一世代目に設定
	mGenerationCount = 1;
}

void EnemyGeneticAlgorithm::Evaluate()
{	
	mCurrentDataCollectionCount++;
	Logger& logger = Logger::GetInstance();
	logger.WriteLog("DataCollectionCount : " + std::to_string(mCurrentDataCollectionCount));

	// 評価に必要な回数データを収集していれば評価する
	if (mCurrentDataCollectionCount > mNeedCurrentDataCollectionCont - 1)
	{
		// 遺伝子の評価
		mDecisionEvaluator->EvaluateGenetics(mBlackBoard, mCurrentGenerationGenes, mCurrentDataCollectionGene_i);
		mCurrentDataCollectionCount = 0;
		mCurrentDataCollectionGene_i = mCurrentGenerationGenes.size() < mCurrentDataCollectionGene_i ? mCurrentGenerationGenes.size() : mCurrentDataCollectionGene_i + 1;
		logger.WriteLog("[EvaluateGene] GeneIndex : " + std::to_string(mCurrentDataCollectionGene_i));
	}
}

void EnemyGeneticAlgorithm::DebugEvaluate()
{
	mDecisionEvaluator->EvaluateGenetics(mBlackBoard, mCurrentGenerationGenes, mCurrentDataCollectionGene_i);
}

void EnemyGeneticAlgorithm::GeneSave()
{
	GeneticAlgorithmInf::GeneSaveData  saveData(mCurrentGenerationGenes, mGenerationCount, mCurrentGenerationGenesSize, mCurrentDataCollectionCount, mCurrentDataCollectionGene_i);
	mGeneDataSaver->SaveGene(saveData);
}

void EnemyGeneticAlgorithm::GenerateGenetic()
{
	// 現在データ収集をしている遺伝子が最後の遺伝子でかつ、遺伝子のすべての状況遺伝子を評価していたら遺伝させる
	if (mCurrentDataCollectionGene_i < mCurrentGenerationGenes.size() - 1)
	{	
		return;
	}

	// すべての遺伝子を評価しているか
	std::vector<std::shared_ptr<Situation>> situations = mCurrentGenerationGenes[mCurrentGenerationGenes.size() - 1]->GetSituations();
	for ( std::shared_ptr<Situation> situation : situations)
	{
		if (!situation->IsEvaluated())
		{
			return;
		}
	}

	// ログ書き込み
	Logger& logger = Logger::GetInstance();
	logger.WriteLog(" [Genetic] ");

	// 遺伝させる
	mGenerator->Genetics(mCurrentGenerationGenes, mAttackGeneTypes, mMoveGeneTypes);
	mCurrentGenerationGenes = mGenerator->GetNextGenerationGene();
	
	// 遺伝したら先頭の遺伝子からデータ収集を開始する
	mCurrentDataCollectionGene_i = 0;
}

void EnemyGeneticAlgorithm::Genetics()
{
	// 遺伝させる
	mGenerator->Genetics(mCurrentGenerationGenes, mAttackGeneTypes, mMoveGeneTypes);
	mCurrentGenerationGenes = mGenerator->GetNextGenerationGene();

	// データ収集カウントを0にする
	mCurrentDataCollectionGene_i = 0; 

	// デバッグ表示を更新
	GeneticAlgorithmDebugger::GetInstance().SetDisplayGenetic(mCurrentGenerationGenes);
	GeneticAlgorithmDebugger::GetInstance().SetDisplayGeneIndex(mCurrentDataCollectionGene_i);
	GeneticAlgorithmDebugger::GetInstance().SetCurrentGeneIndex(mCurrentDataCollectionGene_i);
}

std::shared_ptr<Gene> EnemyGeneticAlgorithm::GetGene() const
{
	// 現在データ収集に使用する遺伝子を返す
	if (mCurrentDataCollectionGene_i < mCurrentGenerationGenes.size())
	{
		return mCurrentGenerationGenes[mCurrentDataCollectionGene_i];
	}
	return std::shared_ptr<Gene>();
}