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
	// �t�@�C�������݂��Ȃ�������쐬����
	AssetManager::GetInstance().ProviderSetting<BinaryFileProvider>(true);

	// �A�Z�b�g�}�l�[�W���[����t�@�C���̃n���h�����擾����
	std::shared_ptr<AssetHandle> fileHandle = AssetManager::GetInstance().Load<BinaryFileProvider>("assets/Genetic/Gene.bin");
	
	// �o�b�N�A�b�v�p�t�@�C���̍쐬
	std::shared_ptr<AssetHandle> backUpFileHandle = AssetManager::GetInstance().Load<BinaryFileProvider>("assets/Genetic/GeneBackUp.bin");

	if (!fileHandle->IsValid())
	{
		std::cout << "��`�w�K�f�[�^�ۑ��p�̃t�@�C�����J���܂���" << std::endl;
		return;
	}
	
	std::vector<std::shared_ptr<Gene>> genetics = _saveData.mGenes;

	// �������ݗp�f�[�^
	std::vector<char> writeData;
	
	// ��`�q�̃A�[�J�C�u
	AllGeneArchive allGeneArchive(_saveData.mCurrentGenerationGenesSize);
	for (size_t gene_i = 0; GeneArchive& geneArchive : allGeneArchive)
	{
		// �󋵈�`�q���A�[�J�C�u����

		ArchiveSituationGene(geneArchive, genetics[gene_i]);
		gene_i++;
	}

	// ���݂̃T�C�Y�{�A�[�J�C�u���ꂽ�󋵈�`�q�̃T�C�Y���m��
	writeData.resize(CalucAllGeneArchiveSize(allGeneArchive));
	
	// �������ރf�[�^�̈ʒu�����߂��|�C���^
	char* writePtr = writeData.data();

	// ���̐��㐔����������
	Utility::MemCpyAndShiftWritePointer(writePtr, &_saveData.mGenerationCount, SIZE_TBYTESIZE);

	// ��`�q�̐�����������
	Utility::MemCpyAndShiftWritePointer(writePtr, &_saveData.mCurrentGenerationGenesSize, SIZE_TBYTESIZE);

	// ���݂̕]���񐔂���������
	Utility::MemCpyAndShiftWritePointer(writePtr, &_saveData.mDataCollectionCount, SIZE_TBYTESIZE);

	// ���݃f�[�^���W�����Ă����`�q�̓Y����
	Utility::MemCpyAndShiftWritePointer(writePtr, &_saveData.mCurrentCollectionGene_i, SIZE_TBYTESIZE);

	// �A�[�J�C�u������`�q���������ɏ�������
	for (GeneArchive& geneArchive : allGeneArchive)
	{
		MemCpyArchiveSituationGene(writePtr, geneArchive);
	}

	// �t�@�C����������
	fileHandle->Get<BinaryFile>().WriteData(writeData.data(), writeData.size(), WriteMode::Override);
	backUpFileHandle->Get<BinaryFile>().WriteData(writeData.data(), writeData.size(), WriteMode::Override);
}

size_t GeneDataSaver::CalucAllGeneArchiveSize(const AllGeneArchive& _saveGene)
{
	// ���݂̐��㐔�A��`�q�̐��A,���݂̕]���񐔁A��`�q�̐�, ���݃f�[�^���W�����Ă����`�q�̊G�Y�������̃T�C�Y��ǉ�
	size_t size = sizeof(size_t) * 4;

	// Situation�𕡐����ꍇ��std::function���ۑ�����
	
	for (GeneArchive geneArchive : _saveGene)
	{
		// ���ꂼ��̈�`�q�̃V�`���G�[�V�����A�[�J�C�u�̐��������T�C�Y��ǉ�
		size += geneArchive.size() * sizeof(size_t);
		// �V�`���G�[�V�����A�[�J�C�u�̃T�C�Y��ǉ�����
		for (SituationGeneArchive situationGeneArchive : geneArchive)
		{
			// �U����`�q�ƈړ���`�q�̐����������ރT�C�Y��ǉ�
			size += SIZE_TBYTESIZE * 2;

			// �]���ς݂��ǂ����𔻒f����t���O���������ރT�C�Y��ǉ�
			size += BOOLBYTESIZE;

			// �󋵈�`�q�ɕK�v�Ȓl���T�C�Y��ǉ�
			size += sizeof(SituationRiskTypeRatio) * 2; // *2�̓S�[���ƂȂ�䗦�ƌ��݂̔䗦�̓��ۑ����邩��
			size += sizeof(AttackEvaluationThreshold);
			size += sizeof(MoveEvaluationThreshold);
			size += sizeof(float); // �]���̒l

			// �^�̃T�C�Y���ʗp�ϐ��̐����T�C�Y��ǉ�
	 		size += situationGeneArchive.mAttackGeneTypeSize.size() * sizeof(size_t);
			size += situationGeneArchive.mMoveGeneTypeSize.size() * sizeof(size_t);

			// �U����`�q�̐�
			size_t attackGeneNum = situationGeneArchive.mAttackGeneArchive.size();

			// �U����`�q�̕]���l�ƃ��X�N�^�C�v���i�[����T�C�Y��ǉ�	
			size += sizeof(GeneticAlgorithmInf::AttackActionRiskType) * attackGeneNum;
			size += sizeof(float) * 2 * attackGeneNum; // * 2.0f�́Afloat�^�̕]���l������邩��
			// �U����`�q�̎��s�񐔂Ƃ��̏󋵂ɓK���Ă��邩�̕]���̃T�C�Y��ǉ�
			size += sizeof(float) * attackGeneNum;
			size += sizeof(uint32_t) * attackGeneNum;

			// �]���ɕK�v�Ȓl��ۑ����邽�߂̃T�C�Y���m��
			size += sizeof(size_t) * 3 * attackGeneNum; // * 3.0f�͕]���ɕK�v�Ȓl�����z�񂪎O���邩��
			
			// �]���l�����z��̐��T�C�Y���m��
			for (size_t atkGene_i = 0; const AttackGeneArchive& atkGeneArchive : situationGeneArchive.mAttackGeneArchive)
			{
				size += sizeof(float) * atkGeneArchive.mDamageInflictedSize;
				size += sizeof(float) * atkGeneArchive.mDamageTakenDuringExecutionSize;
				size += sizeof(float) * atkGeneArchive.mExecutionTimeSize;
			}

			// �^���ʗp��������i�[���邽�߂̃T�C�Y��ǉ�  �U����`�q
			for (const size_t stringSize : situationGeneArchive.mAttackGeneTypeSize)
			{
				size += stringSize;
			}

			// TODO: �ړ���`�q�̕]���l�ƕ]���l�̂��߂̃f�[�^��ۑ�����

			// �^���ʗp��������i�[���邽�߂̃T�C�Y��ǉ�  �ړ���`�q
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
	// �z��̊m��
	std::vector<std::shared_ptr<Situation>> situations = _genetic->GetSituations();
	_situationArchive.resize(situations.size());

	// ��`�q�Ɋ܂܂��V�`���G�[�V������`�q�̐������[�v����
	for (size_t situation_i = 0; std::shared_ptr<Situation> situation : situations)
	{
		// �]���ς݂��ǂ���
		_situationArchive[situation_i].mbIsEvaluated = situation->IsEvaluated();

		// �ڕW�̃��X�N�^�C�v
		_situationArchive[situation_i].mActionRiskTypeTargetRatio = situation->GetRiskTypeTargetRatio();

		// ���݂̃��X�N�^�C�v
		_situationArchive[situation_i].mCurrentRiskTypeRatio = situation->GetCurrentRiskTypeRatio();

		// �U����`�q�̕]�����������Ⴂ���𕪂���臒l
		_situationArchive[situation_i].mAttackEvaluationThreshold = situation->GetAttackEvaluationThreshold();

		// �ړ���`�q�̕]�����������Ⴂ���𕪂���臒l
		_situationArchive[situation_i].mMoveEvaluationThreshold = situation->GetMoveEvaluationThreshold();

		// �]���l
		_situationArchive[situation_i].mTotalEvaluationOfActions = situation->GetGoalAchievement();

		// �U����`�q�̐�
		_situationArchive[situation_i].mAttackGeneCount = situation->GetAttackGenes().size();

		// �U����`�q���Z�[�u�ł���`���ɂ���
		ArchiveAttackGene(_situationArchive[situation_i].mAttackGeneTypeSize, _situationArchive[situation_i].mAttackGeneArchive, situation->GetAttackGenes());

		// �ړ���`�q�̐�
		_situationArchive[situation_i].mMoveGeneCount = situation->GetMoveGenes().size();

		// �ړ���`�q���Z�[�u�ł���`������
		ArchiveMoveGene(_situationArchive[situation_i].mMoveGeneTypeSize, _situationArchive[situation_i].mMoveGeneArchive, situation->GetMoveGenes());
	}
}

void GeneDataSaver::ArchiveAttackGene(std::vector<size_t>& _attackGeneSize, std::vector<AttackGeneArchive>& _attackGeneArchive, const AttackGenes& _attackGene)
{
	// �f�[�^�̃T�C�Y���m��(�v�f��)
	size_t attackGeneSize = _attackGene.size();
	_attackGeneSize.resize(attackGeneSize);
	_attackGeneArchive.resize(attackGeneSize);

	// �U����`�q�̃f�[�^���A�[�J�C�u����
	for (size_t atkGene_i = 0; const std::shared_ptr<EnemyAttackAction> attack : _attackGene)
	{
		// �^���擾
		_attackGeneArchive[atkGene_i].mTypeName = attack->GetTypeName();

		// �^���̃T�C�Y���擾
		_attackGeneSize[atkGene_i] = _attackGeneArchive[atkGene_i].mTypeName.size();
	
		// ���X�N�^�C�v�擾
		_attackGeneArchive[atkGene_i].mRiskType = attack->GetAttackActionRiskType();

		// �v���C���[�ɑ΂��Ă̗L���x���擾
		_attackGeneArchive[atkGene_i].mEffectivenessToPlayer = attack->GetEffectivenessToPlayer();

		// �v���C���[���U���ɂǂ̂��炢����Ă���̂��擾
		_attackGeneArchive[atkGene_i].mReceptivityToPlayer = attack->GetReceptivityToPlayer();

		// �V�`���G�[�V�����ɓK���Ă��邩
		_attackGeneArchive[atkGene_i].mSuitable = attack->GetSuitable();

		// ���s�񐔂��擾
		_attackGeneArchive[atkGene_i].mExecuteCount = attack->GetExecuteCount();

		// �^�����_���[�W��ێ�����z��̔z��Ɛ����擾
		_attackGeneArchive[atkGene_i].mDamageInflicted = attack->GetDamageInflicted();
		_attackGeneArchive[atkGene_i].mDamageInflictedSize = _attackGeneArchive[atkGene_i].mDamageInflicted.size();

		// �������ꂽ�_���[�W��ێ�����z��Ɛ����擾
		_attackGeneArchive[atkGene_i].mDamageTakenDuringExecution = attack->GetDamageTakenDuringExecution();
		_attackGeneArchive[atkGene_i].mDamageTakenDuringExecutionSize = _attackGeneArchive[atkGene_i].mDamageTakenDuringExecution.size();

		// ���s���Ƃ̎��s���Ԃ���ێ�����z��Ɛ����擾
		_attackGeneArchive[atkGene_i].mExecutionTime = attack->GetExecutionTime();
		_attackGeneArchive[atkGene_i].mExecutionTimeSize = _attackGeneArchive[atkGene_i].mExecutionTime.size();

		atkGene_i++;
	}
}

void GeneDataSaver::ArchiveMoveGene(std::vector<size_t>& _moveGeneSize, std::vector<MoveGeneArchive>& _moveGeneArchive, const MoveGenes& _moveGenes)
{
	// �f�[�^�̃T�C�Y���m�ۂ���
	size_t moveGeneSize = _moveGenes.size();
	_moveGeneArchive.resize(moveGeneSize);
	_moveGeneSize.resize(moveGeneSize);

	// �A�[�J�C�u����
	for (size_t moveGene_i = 0; const std::shared_ptr<EnemyMoveAction> move : _moveGenes)
	{
		// �^�����擾
		_moveGeneArchive[moveGene_i].mTypeName = move->GetTypeName();

		// �^���̃T�C�Y���擾
		_moveGeneSize[moveGene_i] = _moveGeneArchive[moveGene_i].mTypeName.size();

		moveGene_i++;
	}
}

void GeneDataSaver::MemCpyArchiveSituationGene(char*& _writePtr, std::vector<SituationGeneArchive>& _situationGeneArchive)
{
	// �󋵈�`�q�̐�����������
	size_t situationNum = _situationGeneArchive.size();
	Utility::MemCpyAndShiftWritePointer(_writePtr, &situationNum, SIZE_TBYTESIZE);

	// �A�[�J�C�u���ꂽ�󋵈�`�q���������ɏ�������
	for (SituationGeneArchive situationArchive : _situationGeneArchive)
	{
		// �]���ς݂��ǂ�������������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mbIsEvaluated, BOOLBYTESIZE);

		// �ڕW�̃��X�N�^�C�v�̔䗦����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mActionRiskTypeTargetRatio, sizeof(SituationRiskTypeRatio));
	
		// ���݂̃��X�N�^�C�v�̔䗦����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mCurrentRiskTypeRatio, sizeof(SituationRiskTypeRatio));

		// �U����`�q�̕]���l��臒l����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mAttackEvaluationThreshold, sizeof(AttackEvaluationThreshold));

		// �ړ���`�q�̕]���l��臒l����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mMoveEvaluationThreshold, sizeof(MoveEvaluationThreshold));

		// �]���l��������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mTotalEvaluationOfActions, FLOATBYTESIZE);

		// �U����`�q�̐�����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mAttackGeneCount, SIZE_TBYTESIZE);
	
		// �ړ���`�q�̐�����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &situationArchive.mMoveGeneCount, SIZE_TBYTESIZE);
	
		// �^���ʗp������̃T�C�Y��ێ�����z��̃f�[�^�A�[�J�C�u���ꂽ�U����`�q����������
		MemCpyArchivedAttackGene(_writePtr, situationArchive.mAttackGeneTypeSize, situationArchive.mAttackGeneArchive);

		// �^���ʗp������̃T�C�Y��ێ�����z��̃f�[�^�ƃA�[�J�C�u���ꂽ�ړ���`�q����������
		MemCpyArchivedMoveGene(_writePtr, situationArchive.mMoveGeneTypeSize, situationArchive.mMoveGeneArchive);
	}
}

void GeneDataSaver::MemCpyArchivedAttackGene(char*& _writePtr, const std::vector<size_t>& _attackGeneSize, const std::vector<AttackGeneArchive>& _attackGeneArchive)
{
	for (size_t atkGene_i = 0; AttackGeneArchive atkGene : _attackGeneArchive)
	{
		// �^���ʗp������̃T�C�Y����������	
		Utility::MemCpyAndShiftWritePointer(_writePtr, &_attackGeneSize[atkGene_i], SIZE_TBYTESIZE);
		
		// �^���ʗp���������������
		Utility::MemCpyAndShiftWritePointer(_writePtr, atkGene.mTypeName.data(), _attackGeneSize[atkGene_i]);
		
		// ���X�N�^�C�v��������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mRiskType, sizeof(GeneticAlgorithmInf::AttackActionRiskType));

		// �v���C���[�ւ̗L���x����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mEffectivenessToPlayer, FLOATBYTESIZE);

		// �v���C���[���U���ɂǂ̂��炢����Ă���̂�����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mReceptivityToPlayer, FLOATBYTESIZE);

		// �󋵂ɓK���Ă��邩����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mSuitable, FLOATBYTESIZE);

		// ���s�񐔂���������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mExecuteCount, sizeof(uint32_t));

		// �_���[�W��^�����z��̐�����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mDamageInflictedSize, SIZE_TBYTESIZE);

		// �T�C�Y��0�łȂ��Ȃ�z�����������
		if (atkGene.mDamageInflictedSize != 0)
		{
			// �_���[�W��^�����z�����������
			Utility::MemCpyAndShiftWritePointer(_writePtr, atkGene.mDamageInflicted.data(), FLOATBYTESIZE * atkGene.mDamageInflictedSize);
		}
		
		// �������ꂽ�_���[�W��ێ�����z��̐�����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mDamageTakenDuringExecutionSize, SIZE_TBYTESIZE);

		// �T�C�Y��0�łȂ��Ȃ�z�����������
		if (atkGene.mDamageTakenDuringExecutionSize != 0)
		{
			// �������ꂽ�_���[�W��ێ�����z�����������
			Utility::MemCpyAndShiftWritePointer(_writePtr, atkGene.mDamageTakenDuringExecution.data(), sizeof(float) * atkGene.mDamageTakenDuringExecutionSize);
		}

		// ���s���Ԃ�ێ�����z��̐�����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &atkGene.mExecutionTimeSize, SIZE_TBYTESIZE);

		// �T�C�Y��0�łȂ��Ȃ�z��ɏ�������
		if (atkGene.mExecutionTimeSize != 0)
		{
			// ���s���Ԃ�ێ�����z�����������
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
		// �^���ʗp������̃T�C�Y����������
		Utility::MemCpyAndShiftWritePointer(_writePtr, &_moveGeneTypeSize[moveGene_i], SIZE_TBYTESIZE);

		// �^���ʗp���������������
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
