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
	// �����Ȃ�
}

GeneDataLoader::~GeneDataLoader()
{
	// �����Ȃ�
}

bool GeneDataLoader::GeneDataLoad(GeneticAlgorithmInf::GeneSaveData& _geneData, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes)
{
	std::shared_ptr<AssetHandle> handle = AssetManager::GetInstance().Load<BinaryFileProvider>("assets/Genetic/Gene.bin");

	// �t�@�C�����J���Ă��邩�`�F�b�N
	if (!handle->IsValid())
	{
		std::cout << "��`�q�f�[�^�t�@�C�����J���܂���B�f�[�^��ǂݍ��ނ��Ƃ��ł��܂���" << std::endl;
		return false;
	}

	size_t size_tSize = sizeof(size_t);

	// �f�[�^�̓ǂݍ���
	std::vector<char> readGeneData;
	handle->Get<BinaryFile>().ReadAllData(readGeneData);

	// �f�[�^���Ȃ���΃��^�[��
	if (readGeneData.size() == 0)
	{
		return false;
	}

	// �ǂݍ��݈ʒu�̃|�C���^�[
	char* readPtr = readGeneData.data();
	
	// ���㐔��ǂݎ��
	std::memcpy(&_geneData.mGenerationCount, readPtr, SIZE_TBYTESIZE);
	readPtr += SIZE_TBYTESIZE; // �ǂݎ��ʒu��i�߂�

	// ��`�q�̐���ǂݎ��
	std::memcpy(&_geneData.mCurrentGenerationGenesSize, readPtr, SIZE_TBYTESIZE);
	readPtr += SIZE_TBYTESIZE; // �ǂݎ��ʒu��i�߂�

	// ���̈�`�q�̃f�[�^�̎��W�񐔂�ǂݎ��
	Utility::MemCpyAndShiftReadPointer(&_geneData.mDataCollectionCount, readPtr, SIZE_TBYTESIZE);

	// ���݃f�[�^���W�����Ă����`�q�̓Y������ǂݎ��
	Utility::MemCpyAndShiftReadPointer(&_geneData.mCurrentCollectionGene_i, readPtr, SIZE_TBYTESIZE);

	// ��`�q�f�[�^�̔z����m��
	_geneData.mGenes.resize(_geneData.mCurrentGenerationGenesSize);
	
	// ��`�q�̐��������[�v����
	for (std::shared_ptr<Gene>& genetic : _geneData.mGenes)
	{
		// �󋵈�`�q�̐����擾
		size_t situationNum;
		std::memcpy(&situationNum, readPtr, size_tSize);
		readPtr += size_tSize;
	
		// �󋵈�`�q�̓ǂݍ���
		genetic = std::make_shared<Gene>();
		ReadSituationGene(readPtr, genetic, situationNum,_attackGeneTypes, _moveGeneTypes);
	}
	return true;
}

void GeneDataLoader::ReadSituationGene(char*& _readPtr, std::shared_ptr<Gene>& _genetic, const size_t _situationNum, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes)
{
	size_t size_tSize = sizeof(size_t);

	// �󋵈�`�q�����ׂēǂݎ��
	for (size_t situation_i = 0; situation_i < _situationNum; situation_i++)
	{
		// �󋵈�`�q����
		std::shared_ptr<Situation> situation = std::make_shared<Situation>();

		// �]���ς݂��ǂ�����ǂݎ��
		bool evaluated;
		Utility::MemCpyAndShiftReadPointer(&evaluated, _readPtr, BOOLBYTESIZE);

		// �ڕW�Ƃ��Ă���U����`�q�̃��X�N�^�C�v�̔䗦
		SituationRiskTypeRatio riskTypeRatio;
		std::memcpy(&riskTypeRatio, _readPtr, sizeof(SituationRiskTypeRatio));
		_readPtr += sizeof(SituationRiskTypeRatio);

		// ���݂̃��X�N�^�C�v�̔䗦
		SituationRiskTypeRatio currentRiskTypeRatio;
		std::memcpy(&currentRiskTypeRatio, _readPtr, sizeof(SituationRiskTypeRatio));
		_readPtr += sizeof(SituationRiskTypeRatio);

		// �U����`�q�̕]���l���������Ⴂ���𔻒f����臒l
		AttackEvaluationThreshold attackEvaluationThreshold;
		std::memcpy(&attackEvaluationThreshold, _readPtr, sizeof(AttackEvaluationThreshold));
		_readPtr += sizeof(AttackEvaluationThreshold);

		// �ړ���`�q�̕]���l���������Ⴂ����臒l
		MoveEvaluationThreshold moveEvaluationThreshold;
		std::memcpy(&moveEvaluationThreshold, _readPtr, sizeof(MoveEvaluationThreshold));
		_readPtr += sizeof(MoveEvaluationThreshold);

		// �]���l�擾
		float totalEvaluationOfActions;
		std::memcpy(&totalEvaluationOfActions, _readPtr, sizeof(float));
		_readPtr += sizeof(float);

		// �U����`�q�̐���ǂݍ���
		size_t attackGeneNum;
		std::memcpy(&attackGeneNum, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// �ړ���`�q�̐����擾����
		size_t moveGeneNum;
		std::memcpy(&moveGeneNum, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// �U����`�q��ǂݍ���
		AttackGenes attackGenes;
		ReadAttackGene(_readPtr, attackGenes, attackGeneNum, _attackGeneTypes);

		// �ړ���`�q��ǂݍ���
		MoveGenes moveGenes;
		ReadMoveGene(_readPtr, moveGenes, moveGeneNum, _moveGeneTypes);

		// ����������`�q�̃Z�b�g
		situation->SetEvaluated(evaluated);
		situation->SetAttackGenes(attackGenes);
		situation->SetMoveGenes(moveGenes);
		situation->SetActionRiskTypeTargetRatio(riskTypeRatio);
		situation->SetCurrentRiskTypeRatio(currentRiskTypeRatio);
		situation->SetAttackEvaluationThreshold(attackEvaluationThreshold);
		situation->SetMoveEvaluationThreshold(moveEvaluationThreshold);
		situation->SetGoalAchievement(totalEvaluationOfActions);

		// �󋵈�`�q�̒ǉ�
		_genetic->AddSituation(situation);
	}
}

void GeneDataLoader::ReadAttackGene(char*& _readPtr, AttackGenes& _attackGene, const size_t attackGeneNum, const AttackGenes& _attackGeneTypes)
{
	size_t size_tSize = sizeof(size_t);
	// �U���ň�`�q��ǂݍ���
	for (size_t attackGene_i = 0; attackGene_i < attackGeneNum; attackGene_i++)
	{
		// �^���ʕ�����̃T�C�Y���擾����
		size_t attackGeneTypeSize;
		std::memcpy(&attackGeneTypeSize, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// �^���ʕ�������擾����
		std::string typeName;
		typeName.resize(attackGeneTypeSize);
		std::memcpy(typeName.data(), _readPtr, attackGeneTypeSize);
		_readPtr += attackGeneTypeSize;

		// �^����
	 	std::shared_ptr<EnemyAttackAction> newAttackGene = CreateAttackGene(_attackGeneTypes, typeName);
	
		// ����ɐ����ł��Ă��邩�`�F�b�N
		if (!newAttackGene)
		{	
			std::cout << "�U����`�q�������s" << "  �^�� : " << typeName << std::endl;
			return;
		}

		// ���X�N�^�C�v�擾
		GeneticAlgorithmInf::AttackActionRiskType riskType;
		std::memcpy(&riskType, _readPtr, sizeof(GeneticAlgorithmInf::AttackActionRiskType));
		_readPtr += sizeof(GeneticAlgorithmInf::AttackActionRiskType);

		// �v���C���[�ɑ΂��Ă̗L���x���擾
		float effectiveness;
		std::memcpy(&effectiveness, _readPtr, sizeof(float));
		_readPtr += sizeof(float);

		// �v���C���[���U���ɂǂ̂��炢����Ă���̂��擾
		float receptivity;
		std::memcpy(&receptivity, _readPtr, sizeof(float));
		_readPtr += sizeof(float);
	
		// �󋵂ɓK���Ă��邩���擾
		float suitable;
		std::memcpy(&suitable, _readPtr, sizeof(float));
		_readPtr += sizeof(float);

		// ���s�񐔂��擾
		uint32_t executeCount;
		std::memcpy(&executeCount, _readPtr, sizeof(uint32_t));
		_readPtr += sizeof(uint32_t);

		// �^�����_���[�W��ێ�����z��̃T�C�Y
		size_t damageInflictedSize;
		std::memcpy(&damageInflictedSize, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// �^�����_���[�W��ێ�����z��
		std::vector<float> damageInflicted(damageInflictedSize);
		// �T�C�Y��0�łȂ��Ȃ�擾����
		if (damageInflictedSize != 0)
		{
			std::memcpy(damageInflicted.data(), _readPtr, FLOATBYTESIZE * damageInflictedSize);
			_readPtr += FLOATBYTESIZE * damageInflictedSize;
		}

		// ���s���ɂ�������_���[�W��ێ�����z��̃T�C�Y���擾
		size_t damageTakenDuringExecutionSize;
		std::memcpy(&damageTakenDuringExecutionSize, _readPtr, SIZE_TBYTESIZE);
		_readPtr += SIZE_TBYTESIZE;

		// ���s���ɂ�������_���[�W��ێ�����z��
		std::vector<float> damageTakenDuringExecution(damageTakenDuringExecutionSize);
		// �T�C�Y��0�łȂ��Ȃ�z����擾
		if (damageTakenDuringExecutionSize != 0)
		{
			std::memcpy(damageTakenDuringExecution.data(), _readPtr, FLOATBYTESIZE * damageTakenDuringExecutionSize);
			_readPtr += FLOATBYTESIZE * damageTakenDuringExecutionSize;
		}

		// ���s���Ƃ̎��s���Ԃ�ێ����鐔���擾
		size_t executionTimeSize;
		std::memcpy(&executionTimeSize, _readPtr, SIZE_TBYTESIZE);
		_readPtr += SIZE_TBYTESIZE;

		// ���s���Ƃ̎��s���Ԃ�ێ�����z��
		std::vector<float> executionTime(executionTimeSize);
		if (executionTimeSize != 0)
		{
			std::memcpy(executionTime.data(), _readPtr, FLOATBYTESIZE * executionTimeSize);
			_readPtr += FLOATBYTESIZE * executionTimeSize;
		}

        // �ǂݍ��񂾃f�[�^���Z�b�g���A�z��ɒǉ�
		newAttackGene->SetAttackActionRiskType(riskType);
		newAttackGene->SetReceptivityToPlayer(receptivity);
		newAttackGene->SetEffectivenessToPlayer(effectiveness);
		newAttackGene->SetSuitable(suitable);
		newAttackGene->SetExecuteCount(executeCount);
		newAttackGene->SetDamageInflicted(damageInflicted);
		newAttackGene->SetDamageTakenDuringExecution(damageTakenDuringExecution);
		newAttackGene->SetExecuteTime(executionTime);

		_attackGene.emplace_back(newAttackGene);

		// �Ƃ肠�����m�F�̂��߂ɕ\������
		std::cout << " �U����`�q " << typeName << std::endl;
	}
}

void GeneDataLoader::ReadMoveGene(char*& _readPtr, MoveGenes& _moveGene, const size_t _moveGeneNum, const MoveGenes& _moveGeneTypes)
{
	size_t size_tSize = sizeof(size_t);
	// �ړ���`�q��ǂݍ���
	for (size_t moveGene_i = 0; moveGene_i < _moveGeneNum; moveGene_i++)
	{
		// �^���ʗp������̃T�C�Y���擾����
		size_t moveGeneTypeSize;
		std::memcpy(&moveGeneTypeSize, _readPtr, size_tSize);
		_readPtr += size_tSize;

		// �^���ʗp��������擾����
		std::string typeName;
		typeName.resize(moveGeneTypeSize);
		std::memcpy(typeName.data(), _readPtr, moveGeneTypeSize);
		_readPtr += moveGeneTypeSize;

		// �^�̐���
		std::shared_ptr<EnemyMoveAction> newMoveGene = CreateMoveGene(_moveGeneTypes, typeName);

		// �����ł��Ă��邩�`�F�b�N
		if (newMoveGene)
		{
			_moveGene.emplace_back(newMoveGene);
		}

		std::cout << " �ړ���`�q " << typeName << std::endl;
	}
}

std::shared_ptr<EnemyAttackAction> GeneDataLoader::CreateAttackGene(const AttackGenes& _attackGeneTypes, const std::string& _attackGeneTypeName)
{
	// ������T�������Ĉ�v����^��T��
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
	// ������T�������Ĉ�v����^��T��
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
