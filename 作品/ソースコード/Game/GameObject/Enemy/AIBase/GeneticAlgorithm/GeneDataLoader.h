/**
* @file GeneDataLoader.h
* @brief GeneDataLoader�N���X�̒�`
*/

#pragma once

//-------------- INCLUDES ------------
#include <string>
#include "GeneticInfomation.h"


/**
* @class GeneDataLoader
* @brief ��`�q�f�[�^���t�@�C������ǂݍ��ދ@�\�����N���X
*/
class GeneDataLoader
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	GeneDataLoader();

	/**
	* �f�t�H���g�f�X�g���N�^
	*/
	~GeneDataLoader();

public:
	/**
	* @fn GeneDataLoad
	* @brief �t�@�C�������`�q�f�[�^��ǂݍ���ł���
	* @param GeneticAlgorithmInf::GeneSaveData& (_geneData)
	* @param const AttackGenes&                 (_attackGeneTypes) �U����`�q�𐶐����邽�߂Ɏg���^��񔻕ʗp����
	* @param const MoveGenes&                   (_moveGeneTypes)   �ړ���`�q�𐶐����邽�߂Ɏg���^��񔻕ʗp����
	* @return bool �f�[�^�����邩�ǂ�����Ԃ�
	*/
	bool GeneDataLoad(GeneticAlgorithmInf::GeneSaveData& _geneData, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes);

private:
	/**
	* @fn ReadSituationGene
	* @brief �󋵈�`�q��ǂݍ���
	* @param char*&             (_readPtr)
	* @param Genetic&           (_genetic)
	* @param const size_t       (_situationNum)
	* @param const AttackGenes& (_attackGeneTypes)
	* @param const MoveGenes&   (_moveGeneTypes)
	* @void 
	*/
	void ReadSituationGene(char*& _readPtr, std::shared_ptr<Gene>& _genetic, const size_t _situationNum, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes);

	/**
	* @fn ReadAttackGene
	* @brief �U����`�q��ǂݍ���
	* @detail �����Ŏw�肳�ꂽ�񐔓ǂݍ��݂̏��������āA�ǂݍ��񂾌^��񂩂琶�����A�����ɑ�����Ă��܂�
	* @param char*&             (_readPtr)         �f�[�^�̓ǂݍ��݈ʒu�������|�C���^
	* @param AttackGenes&       (_attackGene)      �U����`�q�̐�����
	* @param const size_t       (attackGeneNum)    �U����`�q�̐�
	* @param const AttackGenes& (_attackGeneTypes) �U����`�q�𐶐����邽�߂Ɏg���^��񔻕ʗp����
	* @return void
	*/
	void ReadAttackGene(char*& _readPtr, AttackGenes& _attackGene, const size_t attackGeneNum, const AttackGenes& _attackGeneTypes);
	
	/**
	* @fn ReadMoveGene
	* @brief �ړ���`�q��ǂݍ���
	* @detail �����Ŏw�肳�ꂽ�񐔓ǂݍ��݂̏��������āA�ǂݍ��񂾌^��񂩂琶�����A�����ɑ�����Ă��܂�
	* @param char*&           (_readPtr)       �f�[�^�̓ǂݍ��݈ʒu�������|�C���^
	* @param AttackGenes&     (_moveGene)      �ړ���`�q�̐�����
	* @param const size_t     (_moveGeneNum)   �ړ���`�q�̐�
	* @param const MoveGenes& (_moveGeneTypes) �ړ���`�q�𐶐����邽�߂Ɏg���^��񔻕ʗp����
	* @return void
	*/
	void ReadMoveGene(char*& _readPtr, MoveGenes& _moveGene, const size_t _moveGeneNum, const MoveGenes& _moveGeneTypes);

	/**
	* @fn CreateAttackGene
	* @brief �n���ꂽ�^�̖��O�ƈ�v����U����`�q�𐶐�����֐�
	* @param const AttackGenes& (_attackGeneTypes)    �������邽�߂̌^���ʗp����
	* @param const std::string& (_attackGeneTypeName) �����������^��
	*/
	std::shared_ptr<EnemyAttackAction> CreateAttackGene(const AttackGenes& _attackGeneTypes, const std::string& _attackGeneTypeName);

	/**
	* @fn CreateMoveGene
	* @brief �n���ꂽ�^�̖��O�ƈ�v����ړ���`�q�𐶐�����֐�
	* @param const AttackGenes& (_moveGeneTypes)    �������邽�߂̌^���ʗp����
	* @param const std::string& (_moveGeneTypeName) �����������^��
	*/
	std::shared_ptr<EnemyMoveAction> CreateMoveGene(const MoveGenes& _moveGeneTypes, const std::string& _moveGeneTypeName);

};
