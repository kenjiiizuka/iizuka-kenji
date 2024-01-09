//------------- INCLUDES ------------
#include "GeneDataSaver.h"
#include "../../../../../System/AssetSystem/AssetManager.h"
#include "../../../../../System/AssetSystem/BinaryFile/BinaryFileProveider.h"
#include "../../../../../System/AssetSystem/BinaryFile/BinaryFile.h"
#include "../../../../../System/AssetSystem/AssetHandle.h"
#include "../GeneticAlgorithm/Gene/Gene.h"
#include "../../../../../Utility/Utility.h"
#include "../GeneticAlgorithm/Gene/EnemyAttackAction.h"
#include "../GeneticAlgorithm/Gene/EnemyMoveAction.h"

void GeneDataSaver::SaveGene(const GeneticAlgorithmInf::GeneSaveData& _saveData)
{
	// ファイルが存在しなかったら作成する
	AssetManager::GetInstance().ProviderSetting<BinaryFileProvider>(true);

	// アセットマネージャーからファイルのハンドルを取得する
	std::shared_ptr<AssetHandle> fileHandle = AssetManager::GetInstance().Load<BinaryFileProvider>("assets/Genetic/Gene.bin");
	
	// バックアップ用ファイルの作成
	std::shared_ptr<AssetHandle> backUpFileHandle = AssetManager::GetInstance().Load<BinaryFileProvider>("assets/Genetic/GeneBackUp.bin");

	if (!fileHandle->IsValid())
	{
		std::cout << "遺伝学習データ保存用のファイルが開けません" << std::endl;
		return;
	}
	
	std::vector<std::shared_ptr<Gene>> genetics = _saveData.mGenes;

	// 書き込み用データ
	std::vector<char> writeData;
	
	// 遺伝子のアーカイブ
	AllGeneArchive allGeneArchive(_saveData.mCurrentGenerationGenesSize);
	for (size_t gene_i = 0; GeneArchive& geneArchive : allGeneArchive)
	{
		// 状況遺伝子をアーカイブする

		ArchiveSituationGene(geneArchive, genetics[gene_i]);
		gene_i++;
	}

	// 現在のサイズ＋アーカイブされた状況遺伝子のサイズ分確保
	writeData.resize(CalucAllGeneArchiveSize(allGeneArchive));
	
	// 書き込むデータの位置をしめすポインタ
	char* writePtr = writeData.data();

	// 今の世代数を書き込み
	Utility::MemCpyAndShiftWritePointer(writePtr, &_saveData.mGenerationCount, SIZE_TBYTESIZE);

	// 遺伝子の数を書き込み
	Utility::MemCpyAndShiftWritePointer(writePtr, &_saveData.mCurrentGenerationGenesSize, SIZE_TBYTESIZE);

	// 現在の評価回数を書き込み
	Utility::MemCpyAndShiftWritePointer(writePtr, &_saveData.mDataCollectionCount, SIZE_TBYTESIZE);

	// 現在データ収集をしている遺伝子の添え字
	Utility::MemCpyAndShiftWritePointer(writePtr, &_saveData.mCurrentCollectionGene_i, SIZE_TBYTESIZE);

	// アーカイブした遺伝子をメモリに書き込み
	for (GeneArchive& geneArchive : allGeneArchive)
	{
		MemCpyArchiveSituationGene(writePtr, geneArchive);
	}

	// ファイル書き込み
	fileHandle->Get<BinaryFile>().WriteData(writeData.data(), writeData.size(), WriteMode::Override);
	backUpFileHandle->Get<BinaryFile>().WriteData(writeData.data(), writeData.size(), WriteMode::Override);
}

size_t GeneDataSaver::CalucAllGeneArchiveSize(const AllGeneArchive& _saveGene)
{
	// 現在の世代数、遺伝子の数、,現在の評価回数、遺伝子の数, 現在データ収集をしている遺伝子の絵添え字分のサイズを追加
	size_t size = sizeof(size_t) * 4;

	// Situationを複数持つ場合はstd::functionも保存する
	
	for (GeneArchive geneArchive : _saveGene)
	{
		// それぞれの遺伝子のシチュエーションアーカイブの数を示すサイズを追加
		size += geneArchive.size() * sizeof(size_t);
		// シチュエーションアーカイブのサイズを追加する
		for (SituationGeneArchive situationGeneArchive : geneArchive)
		{
			// 攻撃遺伝子と移動遺伝子の数を書き込むサイズを追加
			size += SIZE_TBYTESIZE * 2;

			// 評価済みかどうかを判断するフラグを書き込むサイズを追加
			size += BOOLBYTESIZE;

			// 状況遺伝子に必要な値分サイズを追加
			size += sizeof(SituationRiskTypeRatio) * 2; // *2はゴールとなる比率と現在の比率の二つを保存するから
			size += sizeof(AttackEvaluationThreshold);
			size += sizeof(MoveEvaluationThreshold);
			size += sizeof(float); // 評価の値

			// 型のサイズ判別用変数の数分サイズを追加
	 		size += situationGeneArchive.mAttackGeneTypeSize.size() * sizeof(size_t);
			size += situationGeneArchive.mMoveGeneTypeSize.size() * sizeof(size_t);

			// 攻撃遺伝子の数
			size_t attackGeneNum = situationGeneArchive.mAttackGeneArchive.size();

			// 攻撃遺伝子の評価値とリスクタイプを格納するサイズを追加	
			size += sizeof(GeneticAlgorithmInf::AttackActionRiskType) * attackGeneNum;
			size += sizeof(float) * 2 * attackGeneNum; // * 2.0fは、float型の評価値が二つあるから
			// 攻撃遺伝子の実行回数とその状況に適しているかの評価のサイズを追加
			size += sizeof(float) * attackGeneNum;
			size += sizeof(uint32_t) * attackGeneNum;

			// 評価に必要な値を保存するためのサイズを確保
			size += sizeof(size_t) * 3 * attackGeneNum; // * 3.0fは評価に必要な値を持つ配列が三つあるから
			
			// 評価値をもつ配列の数サイズを確保
			for (size_t atkGene_i = 0; const AttackGeneArchive& atkGeneArchive : situationGeneArchive.mAttackGeneArchive)
			{
				size += sizeof(float) * atkGeneArchive.mDamageInflictedSize;
				size += sizeof(float) * atkGeneArchive.mDamageTakenDuringExecutionSize;
				size += sizeof(float) * atkGeneArchive.mExecutionTimeSize;
			}

			// 型判別用文字列を格納するためのサイズを追加  攻撃遺伝子
			for (const size_t stringSize : situationGeneArchive.mAttackGeneTypeSize)
			{
				size += stringSize;
			}

			// TODO: 移動遺伝子の評価値と評価値のためのデータを保存する

			// 型判別用文字列を格納するためのサイズを追加  移動遺伝子
			for (const size_t stringSize : situationGeneArchive.mMoveGeneTypeSize)
			{
				size += stringSize;
			}
		}
	}
	return size;
}

void GeneDataSaver::ArchiveSituationGene(std::vector<SituationGeneArchive>& _situationArchive, std::shared_ptr<Gene>& _genetic)
{
	// 配列の確保
	std::vector<std::shared_ptr<Situation>> situations = _genetic->GetSituations();
	_situationArchive.resize(situations.size());

	// 遺伝子に含まれるシチュエーション遺伝子の数分ループする
	for (size_t situation_i = 0; std::shared_ptr<Situation> situation : situations)
	{
		// 評価済みかどうか
		_situationArchive[situation_i].mbIsEvaluated = situation->IsEvaluated();

		// 目標のリスクタイプ
		_situationArchive[situation_i].mActionRiskTypeTargetRatio = situation->GetRiskTypeTargetRatio();

		// 現在のリスクタイプ
		_situationArchive[situation_i].mCurrentRiskTypeRatio = situation->GetCurrentRiskTypeRatio();

		// 攻撃遺伝子の評価が高いか低いかを分ける閾値
		_situationArchive[situation_i].mAttackEvaluationThreshold = situation->GetAttackEvaluationThreshold();

		// 移動遺伝子の評価が高いか低いかを分ける閾値
		_situationArchive[situation_i].mMoveEvaluationThreshold = situation->GetMoveEvaluationThreshold();

		// 評価値
		_situationArchive[situation_i].mTotalEvaluationOfActions = situation->GetGoalAchievement();

		// 攻撃遺伝子の数
		_situationArchive[situation_i].mAttackGeneCount = situation->GetAttackGenes().size();

		// 攻撃遺伝子をセーブできる形式にする
		ArchiveAttackGene(_situationArchive[situation_i].mAttackGeneTypeSize, _situationArchive[situation_i].mAttackGeneArchive, situation->GetAttackGenes());

		// 移動遺伝子の数
		_situationArchive[situation_i].mMoveGeneCount = situation->GetMoveGenes().size();

		// 移動遺伝子をセーブできる形式する
		ArchiveMoveGene(_situationArchive[situation_i].mMoveGeneTypeSize, _situationArchive[situation_i].mMoveGeneArchive, situation->GetMoveGenes());
	}
}

void GeneDataSaver::ArchiveAttackGene(std::vector<size_t>& _attackGeneSize, std::vector<AttackGeneArchive>& _attackGeneArchive, const AttackGenes& _attackGene)
{
	// データのサイズを確保(要素数)
	size_t attackGeneSize = _attackGene.size();
	_attackGeneSize.resize(attackGeneSize);
	_attackGeneArchive.resize(attackGeneSize);

	// 攻撃遺伝子のデータをアーカイブする
	for (size_t atkGene_i = 0; const std::shared_ptr<EnemyAttackAction> attack : _attackGene)
	{
		// 型名取得
		_attackGeneArchive[atkGene_i].mTypeName = attack->GetTypeName();

		// 型名のサイズを取得
		_attackGeneSize[atkGene_i] = _attackGeneArchive[atkGene_i].mTypeName.size();
	
		// リスクタイプ取得
		_attackGeneArchive[atkGene_i].mRiskType = attack->GetAttackActionRiskType();

		// プレイヤーに対しての有効度を取得
		_attackGeneArchive[atkGene_i].mEffectivenessToPlayer = attack->GetEffectivenessToPlayer();

		// プレイヤーが攻撃にどのくらい慣れているのか取得
		_attackGeneArchive[atkGene_i].mReceptivityToPlayer = attack->GetReceptivityToPlayer();

		// シチュエーションに適しているか
		_attackGeneArchive[atkGene_i].mSuitable = attack->GetSuitable();

		// 実行回数を取得
		_attackGeneArchive[atkGene_i].mExecuteCount = attack->GetExecuteCount();

		// 与えたダメージを保持する配列の配列と数を取得
		_attackGeneArchive[atkGene_i].mDamageInflicted = attack->GetDamageInflicted();
		_attackGeneArchive[atkGene_i].mDamageInflictedSize = _attackGeneArchive[atkGene_i].mDamageInflicted.size();

		// 反撃されたダメージを保持する配列と数を取得
		_attackGeneArchive[atkGene_i].mDamageTakenDuringExecution = attack->GetDamageTakenDuringExecution();
		_attackGeneArchive[atkGene_i].mDamageTakenDuringExecutionSize = _attackGeneArchive[atkGene_i].mDamageTakenDuringExecution.size();

		// 実行ごとの実行時間をを保持する配列と数を取得
		_attackGeneArchive[atkGene_i].mExecutionTime = attack->GetExecutionTime();
		_attackGeneArchive[atkGene_i].mExecutionTimeSize = _attackGeneArchive[atkGene_i].mExecutionTime.size();

		atkGene_i++;
	}
}

void GeneDataSaver::ArchiveMoveGene(std::vector<size_t>& _moveGeneSize, std::vector<MoveGeneArchive>& _moveGeneArchive, const MoveGenes& _moveGenes)
{
	// データのサイズを確保する
	size_t moveGeneSize = _moveGenes.size();
	_moveGeneArchive.resize(moveGeneSize);
	_moveGeneSize.resize(moveGeneSize);

	// アーカイブする
	for (size_t moveGene_i = 0; const std::shared_ptr<EnemyMoveAction> move : _moveGenes)
	{
		// 型名を取得
		_moveGeneArchive[moveGene_i].mTypeName = move->GetTypeName();

		// 型名のサイズを取得
		_moveGeneSize[moveGene_i] = _moveGeneArchive[moveGene_i].mTypeName.size();

		moveGene_i++;
	}
}

void GeneDataSaver::MemCpyArchiveSituationGene(char*& _writePtr, std::vector<SituationGeneArchive>& _situationGeneArchive)
{
	// 状況遺伝子の数を書き込む
	size_t situationNum = _situationGeneArchive.size();
	Utility::MemCpyAndShiftWritePointer(_writePtr, &situationNum, SIZE_TBYTESIZE);

	// アーカイブされた状況遺伝子をメモリに書き込む
	for (SituationGeneArchive situationArchive : _situationGeneArchive)
	{
		// 評価済みかどうかを書き込む
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mbIsEvaluated, BOOLBYTESIZE);

		// 目標のリスクタイプの比率を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mActionRiskTypeTargetRatio, sizeof(SituationRiskTypeRatio));
	
		// 現在のリスクタイプの比率を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mCurrentRiskTypeRatio, sizeof(SituationRiskTypeRatio));

		// 攻撃遺伝子の評価値の閾値を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mAttackEvaluationThreshold, sizeof(AttackEvaluationThreshold));

		// 移動遺伝子の評価値の閾値を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mMoveEvaluationThreshold, sizeof(MoveEvaluationThreshold));

		// 評価値書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mTotalEvaluationOfActions, FLOATBYTESIZE);

		// 攻撃遺伝子の数を書き込む
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mAttackGeneCount, SIZE_TBYTESIZE);
	
		// 移動遺伝子の数を書き込む
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mMoveGeneCount, SIZE_TBYTESIZE);
	
		// 型判別用文字列のサイズを保持する配列のデータアーカイブされた攻撃遺伝子を書き込む
		MemCpyArchivedAttackGene(_writePtr, situationArchive.mAttackGeneTypeSize, situationArchive.mAttackGeneArchive);

		// 型判別用文字列のサイズを保持する配列のデータとアーカイブされた移動遺伝子を書き込む
		MemCpyArchivedMoveGene(_writePtr, situationArchive.mMoveGeneTypeSize, situationArchive.mMoveGeneArchive);
	}
}

void GeneDataSaver::MemCpyArchivedAttackGene(char*& _writePtr, const std::vector<size_t>& _attackGeneSize, const std::vector<AttackGeneArchive>& _attackGeneArchive)
{
	for (size_t atkGene_i = 0; AttackGeneArchive atkGene : _attackGeneArchive)
	{
		// 型判別用文字列のサイズを書き込む	
		Utility::MemCpyAndShiftWritePointer(_writePtr, &_attackGeneSize[atkGene_i], SIZE_TBYTESIZE);
		
		// 型判別用文字列を書き込む
		Utility::MemCpyAndShiftWritePointer(_writePtr, atkGene.mTypeName.data(), _attackGeneSize[atkGene_i]);
		
		// リスクタイプ書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mRiskType, sizeof(GeneticAlgorithmInf::AttackActionRiskType));

		// プレイヤーへの有効度を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mEffectivenessToPlayer, FLOATBYTESIZE);

		// プレイヤーが攻撃にどのくらい慣れているのかを書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mReceptivityToPlayer, FLOATBYTESIZE);

		// 状況に適しているかを書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mSuitable, FLOATBYTESIZE);

		// 実行回数を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mExecuteCount, sizeof(uint32_t));

		// ダメージを与えた配列の数を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mDamageInflictedSize, SIZE_TBYTESIZE);

		// サイズが0でないなら配列を書き込み
		if (atkGene.mDamageInflictedSize != 0)
		{
			// ダメージを与えた配列を書き込み
			Utility::MemCpyAndShiftWritePointer(_writePtr, atkGene.mDamageInflicted.data(), FLOATBYTESIZE * atkGene.mDamageInflictedSize);
		}
		
		// 反撃されたダメージを保持する配列の数を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mDamageTakenDuringExecutionSize, SIZE_TBYTESIZE);

		// サイズが0でないなら配列を書き込み
		if (atkGene.mDamageTakenDuringExecutionSize != 0)
		{
			// 反撃されたダメージを保持する配列を書き込み
			Utility::MemCpyAndShiftWritePointer(_writePtr, atkGene.mDamageTakenDuringExecution.data(), sizeof(float) * atkGene.mDamageTakenDuringExecutionSize);
		}

		// 実行時間を保持する配列の数を書き込み
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mExecutionTimeSize, SIZE_TBYTESIZE);

		// サイズが0でないなら配列に書き込み
		if (atkGene.mExecutionTimeSize != 0)
		{
			// 実行時間を保持する配列を書き込み
			Utility::MemCpyAndShiftWritePointer(_writePtr, atkGene.mExecutionTime.data(), sizeof(float) * atkGene.mExecutionTimeSize);
		}

		atkGene_i++;
	}
}

void GeneDataSaver::MemCpyArchivedMoveGene(char*& _writePtr, const std::vector<size_t>& _moveGeneTypeSize, const std::vector<MoveGeneArchive>& _moveGeneArchive)
{
	size_t size_tSize = sizeof(size_t);
	for (size_t moveGene_i = 0; MoveGeneArchive moveGene : _moveGeneArchive)
	{
		// 型判別用文字列のサイズを書き込む
		Utility::MemCpyAndShiftWritePointer(_writePtr, &_moveGeneTypeSize[moveGene_i], SIZE_TBYTESIZE);

		// 型判別用文字列を書き込む
		Utility::MemCpyAndShiftWritePointer(_writePtr, moveGene.mTypeName.data(), _moveGeneTypeSize[moveGene_i]);
	
		moveGene_i++;
	}
}

GeneDataSaver::SituationGeneArchive::SituationGeneArchive()
	: mbIsEvaluated(false)
	, mAttackGeneCount(0)
	, mMoveGeneCount(0)
	, mActionRiskTypeTargetRatio({0.0f,0.0f,0.0f,0.0f})
	, mCurrentRiskTypeRatio({0.0f,0.0f,0.0f,0.0f})
	, mAttackEvaluationThreshold({0.0f,0.0f,0.0f})
	, mMoveEvaluationThreshold({0.0f,0.0f})
	, mTotalEvaluationOfActions(0.0f)
{
}

GeneDataSaver::AttackGeneArchive::AttackGeneArchive()
	: mRiskType(GeneticAlgorithmInf::AttackAction_None)
	, mEffectivenessToPlayer(0.0f)
	, mReceptivityToPlayer(0.0f)
	, mSuitable(0.0f)
	, mExecuteCount(0)
	, mDamageInflictedSize(0)
	, mDamageTakenDuringExecutionSize(0)
	, mExecutionTimeSize(0)
{
}
