//------------ INCLUDES -----------
#include "GeneDataLoader.h"
#include "../../../../../System/AssetSystem/AssetManager.h"
#include "../../../../../System/AssetSystem/AssetHandle.h"
#include "../../../../../System/AssetSystem/BinaryFile/BinaryFileProveider.h"
#include "../../../../../System/AssetSystem/BinaryFile//BinaryFile.h"
#include "../GeneticAlgorithm/Gene/EnemyAttackAction.h"
#include "../GeneticAlgorithm/Gene/EnemyMoveAction.h"
#include "../GeneticAlgorithm/Gene/Gene.h"
#include "../../../../../Utility/Utility.h"

GeneDataLoader::GeneDataLoader()
{
	// 処理なし
}

GeneDataLoader::~GeneDataLoader()
{
	// 処理なし
}

bool GeneDataLoader::GeneDataLoad(GeneticAlgorithmInf::GeneSaveData& _geneData, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes)
{
	std::shared_ptr<AssetHandle> handle = AssetManager::GetInstance().Load<BinaryFileProvider>("assets/Genetic/Gene.bin");

	// ファイルが開けているかチェック
	if (!handle->IsValid())
	{
		std::cout << "遺伝子データファイルが開けません。データを読み込むことができません" << std::endl;
		return false;
	}

	size_t size_tSize = sizeof(size_t);

	// データの読み込み
	std::vector<char> readGeneData;
	handle->Get<BinaryFile>().ReadAllData(readGeneData);

	// データがなければリターン
	if (readGeneData.size() == 0)
	{
		return false;
	}

	// 読み込み位置のポインター
	char* readPtr = readGeneData.data();
	
	// 世代数を読み取る
	std::memcpy(&_geneData.mGenerationCount, readPtr, SIZE_TBYTESIZE);
	readPtr += SIZE_TBYTESIZE; // 読み取り位置を進める

	// 遺伝子の数を読み取る
	std::memcpy(&_geneData.mCurrentGenerationGenesSize, readPtr, SIZE_TBYTESIZE);
	readPtr += SIZE_TBYTESIZE; // 読み取り位置を進める

	// 今の遺伝子のデータの収集回数を読み取る
	Utility::MemCpyAndShiftReadPointer(&_geneData.mDataCollectionCount, readPtr, SIZE_TBYTESIZE);

	// 現在データ収集をしている遺伝子の添え字を読み取る
	Utility::MemCpyAndShiftReadPointer(&_geneData.mCurrentCollectionGene_i, readPtr, SIZE_TBYTESIZE);

	// 遺伝子データの配列を確保
	_geneData.mGenes.resize(_geneData.mCurrentGenerationGenesSize);
	
	// 遺伝子の数だけループする
	for (std::shared_ptr<Gene>& genetic : _geneData.mGenes)
	{
		// 状況遺伝子の数を取得
		size_t situationNum;
		std::memcpy(&situationNum, readPtr, size_tSize);
		readPtr += size_tSize;
	
		// 状況遺伝子の読み込み
		genetic = std::make_shared<Gene>();
		ReadSituationGene(readPtr, genetic, situationNum,_attackGeneTypes, _moveGeneTypes);
	}
	return true;
}

void GeneDataLoader::ReadSituationGene(char*& _readPtr, std::shared_ptr<Gene>& _genetic, const size_t _situationNum, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes)
{
	size_t size_tSize = sizeof(size_t);

	// 状況遺伝子をすべて読み取る
	for (size_t situation_i = 0; situation_i < _situationNum; situation_i++)
	{
		// 状況遺伝子生成
		std::shared_ptr<Situation> situation = std::make_shared<Situation>();

		// 評価済みかどうかを読み取る
		bool evaluated;
		Utility::MemCpyAndShiftReadPointer(&evaluated, _readPtr, BOOLBYTESIZE);

		// 目標としている攻撃遺伝子のリスクタイプの比率
		SituationRiskTypeRatio riskTypeRatio;
		std::memcpy(&riskTypeRatio, _readPtr, sizeof(SituationRiskTypeRatio));
		_readPtr += sizeof(SituationRiskTypeRatio);

		// 現在のリスクタイプの比率
		SituationRiskTypeRatio currentRiskTypeRatio;
		std::memcpy(&currentRiskTypeRatio, _readPtr, sizeof(SituationRiskTypeRatio));
		_readPtr += sizeof(SituationRiskTypeRatio);

		// 攻撃遺伝子の評価値を高いか低いかを判断する閾値
		AttackEvaluationThreshold attackEvaluationThreshold;
		std::memcpy(&attackEvaluationThreshold, _readPtr, sizeof(AttackEvaluationThreshold));
		_readPtr += sizeof(AttackEvaluationThreshold);

		// 移動遺伝子の評価値を高いか低いかの閾値
		MoveEvaluationThreshold moveEvaluationThreshold;
		std::memcpy(&moveEvaluationThreshold, _readPtr, sizeof(MoveEvaluationThreshold));
		_readPtr += sizeof(MoveEvaluationThreshold);

		// 評価値取得
		float totalEvaluationOfActions;
		std::memcpy(&totalEvaluationOfActions, _readPtr, sizeof(float));
		_readPtr += sizeof(float);

		// 攻撃遺伝子の数を読み込む
		size_t attackGeneNum;
		std::memcpy(&attackGeneNum, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// 移動遺伝子の数を取得する
		size_t moveGeneNum;
		std::memcpy(&moveGeneNum, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// 攻撃遺伝子を読み込む
		AttackGenes attackGenes;
		ReadAttackGene(_readPtr, attackGenes, attackGeneNum, _attackGeneTypes);

		// 移動遺伝子を読み込む
		MoveGenes moveGenes;
		ReadMoveGene(_readPtr, moveGenes, moveGeneNum, _moveGeneTypes);

		// 生成した遺伝子のセット
		situation->SetEvaluated(evaluated);
		situation->SetAttackGenes(attackGenes);
		situation->SetMoveGenes(moveGenes);
		situation->SetActionRiskTypeTargetRatio(riskTypeRatio);
		situation->SetCurrentRiskTypeRatio(currentRiskTypeRatio);
		situation->SetAttackEvaluationThreshold(attackEvaluationThreshold);
		situation->SetMoveEvaluationThreshold(moveEvaluationThreshold);
		situation->SetGoalAchievement(totalEvaluationOfActions);

		// 状況遺伝子の追加
		_genetic->AddSituation(situation);
	}
}

void GeneDataLoader::ReadAttackGene(char*& _readPtr, AttackGenes& _attackGene, const size_t attackGeneNum, const AttackGenes& _attackGeneTypes)
{
	size_t size_tSize = sizeof(size_t);
	// 攻撃で遺伝子を読み込む
	for (size_t attackGene_i = 0; attackGene_i < attackGeneNum; attackGene_i++)
	{
		// 型判別文字列のサイズを取得する
		size_t attackGeneTypeSize;
		std::memcpy(&attackGeneTypeSize, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// 型判別文字列を取得する
		std::string typeName;
		typeName.resize(attackGeneTypeSize);
		std::memcpy(typeName.data(), _readPtr, attackGeneTypeSize);
		_readPtr += attackGeneTypeSize;

		// 型生成
	 	std::shared_ptr<EnemyAttackAction> newAttackGene = CreateAttackGene(_attackGeneTypes, typeName);
	
		// 正常に生成できているかチェック
		if (!newAttackGene)
		{	
			std::cout << "攻撃遺伝子生成失敗" << "  型名 : " << typeName << std::endl;
			return;
		}

		// リスクタイプ取得
		GeneticAlgorithmInf::AttackActionRiskType riskType;
		std::memcpy(&riskType, _readPtr, sizeof(GeneticAlgorithmInf::AttackActionRiskType));
		_readPtr += sizeof(GeneticAlgorithmInf::AttackActionRiskType);

		// プレイヤーに対しての有効度を取得
		float effectiveness;
		std::memcpy(&effectiveness, _readPtr, sizeof(float));
		_readPtr += sizeof(float);

		// プレイヤーが攻撃にどのくらい慣れているのか取得
		float receptivity;
		std::memcpy(&receptivity, _readPtr, sizeof(float));
		_readPtr += sizeof(float);
	
		// 状況に適しているかを取得
		float suitable;
		std::memcpy(&suitable, _readPtr, sizeof(float));
		_readPtr += sizeof(float);

		// 実行回数を取得
		uint32_t executeCount;
		std::memcpy(&executeCount, _readPtr, sizeof(uint32_t));
		_readPtr += sizeof(uint32_t);

		// 与えたダメージを保持する配列のサイズ
		size_t damageInflictedSize;
		std::memcpy(&damageInflictedSize, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// 与えたダメージを保持する配列
		std::vector<float> damageInflicted(damageInflictedSize);
		// サイズが0でないなら取得する
		if (damageInflictedSize != 0)
		{
			std::memcpy(damageInflicted.data(), _readPtr, FLOATBYTESIZE * damageInflictedSize);
			_readPtr += FLOATBYTESIZE * damageInflictedSize;
		}

		// 実行中にくらったダメージを保持する配列のサイズを取得
		size_t damageTakenDuringExecutionSize;
		std::memcpy(&damageTakenDuringExecutionSize, _readPtr, SIZE_TBYTESIZE);
		_readPtr += SIZE_TBYTESIZE;

		// 実行中にくらったダメージを保持する配列
		std::vector<float> damageTakenDuringExecution(damageTakenDuringExecutionSize);
		// サイズが0でないなら配列を取得
		if (damageTakenDuringExecutionSize != 0)
		{
			std::memcpy(damageTakenDuringExecution.data(), _readPtr, FLOATBYTESIZE * damageTakenDuringExecutionSize);
			_readPtr += FLOATBYTESIZE * damageTakenDuringExecutionSize;
		}

		// 実行ごとの実行時間を保持する数を取得
		size_t executionTimeSize;
		std::memcpy(&executionTimeSize, _readPtr, SIZE_TBYTESIZE);
		_readPtr += SIZE_TBYTESIZE;

		// 実行ごとの実行時間を保持する配列
		std::vector<float> executionTime(executionTimeSize);
		if (executionTimeSize != 0)
		{
			std::memcpy(executionTime.data(), _readPtr, FLOATBYTESIZE * executionTimeSize);
			_readPtr += FLOATBYTESIZE * executionTimeSize;
		}

        // 読み込んだデータをセットし、配列に追加
		newAttackGene->SetAttackActionRiskType(riskType);
		newAttackGene->SetReceptivityToPlayer(receptivity);
		newAttackGene->SetEffectivenessToPlayer(effectiveness);
		newAttackGene->SetSuitable(suitable);
		newAttackGene->SetExecuteCount(executeCount);
		newAttackGene->SetDamageInflicted(damageInflicted);
		newAttackGene->SetDamageTakenDuringExecution(damageTakenDuringExecution);
		newAttackGene->SetExecuteTime(executionTime);

		_attackGene.emplace_back(newAttackGene);

		// とりあえず確認のために表示する
		std::cout << " 攻撃遺伝子 " << typeName << std::endl;
	}
}

void GeneDataLoader::ReadMoveGene(char*& _readPtr, MoveGenes& _moveGene, const size_t _moveGeneNum, const MoveGenes& _moveGeneTypes)
{
	size_t size_tSize = sizeof(size_t);
	// 移動遺伝子を読み込む
	for (size_t moveGene_i = 0; moveGene_i < _moveGeneNum; moveGene_i++)
	{
		// 型判別用文字列のサイズを取得する
		size_t moveGeneTypeSize;
		std::memcpy(&moveGeneTypeSize, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// 型判別用文字列を取得する
		std::string typeName;
		typeName.resize(moveGeneTypeSize);
		std::memcpy(typeName.data(), _readPtr, moveGeneTypeSize);
		_readPtr += moveGeneTypeSize;

		// 型の生成
		std::shared_ptr<EnemyMoveAction> newMoveGene = CreateMoveGene(_moveGeneTypes, typeName);

		// 生成できているかチェック
		if (newMoveGene)
		{
			_moveGene.emplace_back(newMoveGene);
		}

		std::cout << " 移動遺伝子 " << typeName << std::endl;
	}
}

std::shared_ptr<EnemyAttackAction> GeneDataLoader::CreateAttackGene(const AttackGenes& _attackGeneTypes, const std::string& _attackGeneTypeName)
{
	// 文字列探索をして一致する型を探す
	for (std::shared_ptr<EnemyAttackAction> attackGene : _attackGeneTypes)
	{
		if (attackGene->GetTypeName() == _attackGeneTypeName)
		{
			std::shared_ptr<EnemyAttackAction> newAttackGene;
			attackGene->DuplicateFromSelfType(newAttackGene);
			return newAttackGene;
		}
	}
	return nullptr;
}

std::shared_ptr<EnemyMoveAction> GeneDataLoader::CreateMoveGene(const MoveGenes& _moveGeneTypes, const std::string& _moveGeneTypeName)
{
	// 文字列探索をして一致する型を探す
	for (std::shared_ptr<EnemyMoveAction> moveGene : _moveGeneTypes)
	{
		if (moveGene->GetTypeName() == _moveGeneTypeName)
		{
			std::shared_ptr<EnemyMoveAction> newMoveGene;
			moveGene->DuplicateFromSelfType(newMoveGene);
			return newMoveGene;
		}
	}
	return nullptr;
}
