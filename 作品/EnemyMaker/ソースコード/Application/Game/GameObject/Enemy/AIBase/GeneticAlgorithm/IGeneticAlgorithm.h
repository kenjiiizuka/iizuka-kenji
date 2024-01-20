/**
* @file IGeneticAlgorithm.h
* @brief 遺伝学習クラスのインターフェースクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include<memory>
#include "GeneticInfomation.h"

//-------- 前方宣言 --------
class BlackBoard;

/** 遺伝学習のインターフェースクラス */
class IGeneticAlgorithm
{
public:
	IGeneticAlgorithm() {};
	virtual ~IGeneticAlgorithm() {};

public:
	/**
	 * @fn Init
	 * @brief 初期化関数
	 * @return void
	*/
	virtual void Init() = 0;

	/**
	 * @fn CreateFirstGeneration
	 * @brief 第一世代の遺伝子を生成する
	 * @return void
	*/
	virtual void GenerateFirstGenes() = 0;

	/**
	 * @fn Evaluate
	 * @brief 遺伝子の評価関数
	 * @return void
	*/
	virtual void Evaluate() = 0; 

	/**
	 * @fn Evaluate
	 * @brief 遺伝子の評価関数 デバッグ
	 * @return void
	*/
	virtual void DebugEvaluate() = 0;

	/**
	 * @fn GeneSave
	 * @brief 遺伝子のセーブ
	 * @return void
	*/
	virtual void GeneSave() = 0;

	/**
	 * @fn GeneratingNextGeneration
	 * @brief 次の世代の生成関数
	 * @return void
	*/
	virtual void GenerateGenetic() = 0;

	/**
	* @fn Genetics
	* @brief 遺伝させる関数
	* @return void
	*/
	virtual void Genetics() = 0;

	/**
	 * @fn GetGenetic
	 * @brief 遺伝子の取得関数
	 * @return std::shared_ptr<Gene>
	*/
	virtual inline std::shared_ptr<Gene> GetGene() const = 0;
};

