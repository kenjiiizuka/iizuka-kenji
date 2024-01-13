/**
* @file GeneticAlgorithmDebugger.h
* @brief GeneticAlgorithmDebugger�N���X�̒�`
*/


#pragma once

//--------- INCLUDES -----------
#include <memory>
#include <string>
#include <SimpleMath.h>
#include "../../../../../System/Singleton.h"
#include "GeneticInfomation.h"
#include "../GeneticAlgorithm/EnemyGeneticAlgorithm.h"


//--------- �O���錾 -----------
class EnemyAttackAction;
class EnemyMoveAction;

/**
* @class GeneticAlgorithmDebugger
* @brief ��`�w�K�A���S���Y���̃f�o�b�K�|
*/
class GeneticAlgorithmDebugger final : public Singleton<GeneticAlgorithmDebugger>
{
   /**----------------------------------------------------------------------------------------------
   * ���N���X��Singleton�N���X����R���X�g���N�^�ƁA�f�X�g���N�^�ɃA�N�Z�X���邽�߂ɕK�v�ł���
   * �N���X�O���琶���A�j���ł��Ȃ��悤�ɂ��邽�߂Ƀt�����h�w�肷��
   ------------------------------------------------------------------------------------------------*/
	friend class Singleton<GeneticAlgorithmDebugger>;

private:
	/**
	 * �f�t�H���g�R���X�g���N�^
	*/
	GeneticAlgorithmDebugger();

	/**
	 * �f�X�g���N�^
	*/
	~GeneticAlgorithmDebugger()
	{
		// �����Ȃ�
	}

	/**
	* �R�s�[�R���X�g���N�^
	* �R�s�[�֎~�̂��ߑ���֎~
	*/
	GeneticAlgorithmDebugger(const GeneticAlgorithmDebugger&) = delete;
	
	/**
	* ������Z�q�̃I�[�o�[���[�h
	* ����֎~�̂��� delete�w��
	*/
	void operator= (const GeneticAlgorithmDebugger&) = delete;

private:
	/** ��`�q�f�[�^ */
	std::vector<std::shared_ptr<Gene>> mGenes;

	/** �\�������`�q�̓Y���� */
	size_t mDisplayGeneticIndex;

	/** ���ݎg�p���Ă����`�q�̓Y���� */
	size_t mCurrentGeneIndex;

	/** ���̈�`�q�̐��� */
	size_t mGenerationCount;

	/** �U����`�q�̕]���l��\�����邩 */
	bool mbDisplayAttackGeneEvaluation;

	/** �U����`�q�̕]���l�̂��߂̃f�[�^��\�����邩 */
	bool mbDisplayAttackGeneEvaluationData;

	/** �ړ���`�q�̕]���l��\�����邩 */
	bool mbDisplayMoveGeneEvaluation;

	/** �ړ���`�q�̕]���l�̂��߂̃f�[�^��\�����邩 */
	bool mbDisplayMoveGeneEvaluationData;

public:
	/**
	* @fn DisplayGeneticDebug
	* @brief �f�o�b�O�p��Window��`��
	* @return void
	*/
	void DisplayGeneticDebug();

private:
	/**
	* @fn DisplayGenetic
	* @brief ��`�q�̓��e��\������
	* @param const std::shared_ptr<Gene>& (_genetic)
	* @return void
	*/
	void DisplayGenetic(const std::shared_ptr<Gene>& _genetic);

	/**
	* @fn DisplaySituation
	* @brief �󋵈�`�q�̃f�[�^��\������
	* @param const std::shared_ptr<Gene>& _genetic
	* @return void
	*/
	void DisplaySituation(const std::shared_ptr<Gene>& _genetic);

	/**
	* @fn DisplayAttackGeneEvaluation
	* @brief �U����`�q�̕]���l��\������
	* @param const AttackGenes& (_attackGenes) �]���l���f�o�b�O�\���������U����`�q
	* @return void
	*/
	void DisplayAttackGeneEvaluation(const AttackGenes& _attackGenes);

	/**
	* @fn DisplayAttackGeneEvaluationData
	* @brief �U����`�q��]�����邽�߂̃f�[�^���f�o�b�O�\������
	* @param const const AttackGenes& (_attackGenes) �]���l�����߂邽�߂̃f�[�^��\���������U����`�q
	* @return void
	*/
	void DisplayAttackGeneEvaluationData(const AttackGenes& _attackGenes);

	/**
	* @fn DisplayMoveGeneEvaluationData
	* @brief �ړ���`�q��]�����邽�߂̃f�[�^���f�o�b�O�\������
	* @param const std::vector<std::weak_ptr<EnemyAttackAction>> (_moveGenes) �]���l�����߂邽�߂̃f�[�^��\���������ړ���`�q
	* @return void
	*/
	void DisplayMoveGeneEvaluationData(const MoveGenes& _moveGenes);

public:
	/**
	* @fn SetDisplayGenetic
	* @brief �\����������`�q�f�[�^���Z�b�g����
	* @param const std::vector<Genetic>& (_genetic)
	*/
	inline void SetDisplayGenetic(const std::vector<std::shared_ptr<Gene>>& _genetic) noexcept;

	/**
	* @fn SetCurrentGenerationCount
	* @brief ���݂̈�`�q�̐��㐔���Z�b�g����
	* @param const size_t (_count)
	* @return void
	*/
	inline void SetCurrentGenerationCount(const size_t _count) noexcept;

	/**
	* @fn SetCurrentGeneIndex
	* @brief ���ݎg�p���Ă����`�q�̓Y����
	* @param const size_t& (_index)
	* @return void
	*/
	inline void SetCurrentGeneIndex(const size_t& _index) noexcept;

	/**
	* @fn SetDisplayGeneIndex
	* @brief �\����������`�q�̓Y�������Z�b�g����
	* @param const size_t& (_index)
	* @return void
	*/
	inline void SetDisplayGeneIndex(const size_t& _index) noexcept;

};

//----------- INLINES -------------

inline void GeneticAlgorithmDebugger::SetDisplayGenetic(const std::vector<std::shared_ptr<Gene>>& _genetic) noexcept
{
	mGenes = _genetic;
}

inline void GeneticAlgorithmDebugger::SetCurrentGenerationCount(const size_t _count) noexcept
{
	mGenerationCount = _count;
}

inline void GeneticAlgorithmDebugger::SetCurrentGeneIndex(const size_t& _index) noexcept
{
	mCurrentGeneIndex = _index;
}

inline void GeneticAlgorithmDebugger::SetDisplayGeneIndex(const size_t& _index) noexcept
{
	mDisplayGeneticIndex = _index;
}
