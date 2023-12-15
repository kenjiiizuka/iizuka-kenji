//------------- INCLUDES -----------
#include "GeneticInfomation.h"


GeneticAlgorithmInf::GeneSaveData::GeneSaveData()
	: mGenerationCount(0)
	, mCurrentGenerationGenesSize(0)
	, mDataCollectionCount(0)
	, mCurrentCollectionGene_i(0)
{
	// ˆ—‚È‚µ
}

GeneticAlgorithmInf::GeneSaveData::GeneSaveData(const std::vector<std::shared_ptr<Gene>>& _genes, const size_t _generationCount, const size_t _currentGenerationGeneSize, const size_t _evaluateCount, const size_t _collectionGene_i)
	: mGenes(_genes)
	, mGenerationCount(_generationCount)
	, mCurrentGenerationGenesSize(_currentGenerationGeneSize)
	, mDataCollectionCount(_evaluateCount)
	, mCurrentCollectionGene_i(_collectionGene_i)
{
	// ˆ—‚È‚µ	
}
