/**
* @file GeneDataLoader.h
* @brief GeneDataLoaderクラスの定義
*/

#pragma once

//-------------- INCLUDES ------------
#include <string>
#include "GeneticInfomation.h"


/**
* @class GeneDataLoader
* @brief 遺伝子データをファイルから読み込む機能を持つクラス
*/
class GeneDataLoader
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	GeneDataLoader();

	/**
	* デフォルトデストラクタ
	*/
	~GeneDataLoader();

public:
	/**
	* @fn GeneDataLoad
	* @brief ファイルから遺伝子データを読み込んでくる
	* @param GeneticAlgorithmInf::GeneSaveData& (_geneData)
	* @param const AttackGenes&                 (_attackGeneTypes) 攻撃遺伝子を生成するために使う型情報判別用引数
	* @param const MoveGenes&                   (_moveGeneTypes)   移動遺伝子を生成するために使う型情報判別用引数
	* @return bool データがあるかどうかを返す
	*/
	bool GeneDataLoad(GeneticAlgorithmInf::GeneSaveData& _geneData, const AttackGenes& _attackGeneTypes, const MoveGenes& _moveGeneTypes);

private:
	/**
	* @fn ReadSituationGene
	* @brief 状況遺伝子を読み込む
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
	* @brief 攻撃遺伝子を読み込む
	* @detail 引数で指定された回数読み込みの処理をして、読み込んだ型情報から生成し、引数に代入しています
	* @param char*&             (_readPtr)         データの読み込み位置を示すポインタ
	* @param AttackGenes&       (_attackGene)      攻撃遺伝子の生成先
	* @param const size_t       (attackGeneNum)    攻撃遺伝子の数
	* @param const AttackGenes& (_attackGeneTypes) 攻撃遺伝子を生成するために使う型情報判別用引数
	* @return void
	*/
	void ReadAttackGene(char*& _readPtr, AttackGenes& _attackGene, const size_t attackGeneNum, const AttackGenes& _attackGeneTypes);
	
	/**
	* @fn ReadMoveGene
	* @brief 移動遺伝子を読み込む
	* @detail 引数で指定された回数読み込みの処理をして、読み込んだ型情報から生成し、引数に代入しています
	* @param char*&           (_readPtr)       データの読み込み位置を示すポインタ
	* @param AttackGenes&     (_moveGene)      移動遺伝子の生成先
	* @param const size_t     (_moveGeneNum)   移動遺伝子の数
	* @param const MoveGenes& (_moveGeneTypes) 移動遺伝子を生成するために使う型情報判別用引数
	* @return void
	*/
	void ReadMoveGene(char*& _readPtr, MoveGenes& _moveGene, const size_t _moveGeneNum, const MoveGenes& _moveGeneTypes);

	/**
	* @fn CreateAttackGene
	* @brief 渡された型の名前と一致する攻撃遺伝子を生成する関数
	* @param const AttackGenes& (_attackGeneTypes)    生成するための型判別用引数
	* @param const std::string& (_attackGeneTypeName) 生成したい型名
	*/
	std::shared_ptr<EnemyAttackAction> CreateAttackGene(const AttackGenes& _attackGeneTypes, const std::string& _attackGeneTypeName);

	/**
	* @fn CreateMoveGene
	* @brief 渡された型の名前と一致する移動遺伝子を生成する関数
	* @param const AttackGenes& (_moveGeneTypes)    生成するための型判別用引数
	* @param const std::string& (_moveGeneTypeName) 生成したい型名
	*/
	std::shared_ptr<EnemyMoveAction> CreateMoveGene(const MoveGenes& _moveGeneTypes, const std::string& _moveGeneTypeName);

};
