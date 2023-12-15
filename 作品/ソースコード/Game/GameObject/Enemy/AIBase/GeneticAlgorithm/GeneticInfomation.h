/**
* @file GeneticInfomation.h
* @brief 遺伝学習に必要な型のエイリアスや、列挙型、構造体の定義
*/

#pragma once


//----------- INCLUDES ----------
#include <stdint.h>
#include <array>
#include <vector>
#include <memory>


//------------ 前方宣言 ---------
class Situation;
class EnemyAttackAction;
class EnemyMoveAction;
class Gene;

/** 遺伝子となる型 Situationの集合が遺伝子となる */
using Genetic = std::vector<std::shared_ptr<Situation>>;

/** 攻撃行動遺伝子 */
using AttackGenes = std::vector<std::shared_ptr<EnemyAttackAction>>;

/** 移動行動遺伝子 */
using MoveGenes = std::vector<std::shared_ptr<EnemyMoveAction>>;


/** 遺伝学習に使うデータを定義した名前空間 */
namespace GeneticAlgorithmInf
{
	/** 意思決定データ(Situation)の評価項目 */
	enum SituationEvaluateItem : uint8_t
	{
		Situation_Effective = 0 /**< このSituationは効果的だったか */
	};

	/** その攻撃をした時のエネミーにとってのリスクとリターンの度合い */
	enum AttackActionRiskType : uint8_t
	{
		AttackAction_HighRisk_HighReturn = 0, /**< プレイヤー、エネミーどちらにとっても挑戦的な攻撃 */
		AttackAction_LowRisk_HighReturn = 1,  /**< エネミーはリスクが低く、プレイヤーにダメージを与えやすい行動 理不尽な攻撃かプレイヤーが苦手としている行動 */
		AttackAction_HighRisk_LowReturn = 2,  /**< プレイヤーにとってチャンスとなるk攻撃 隙が多いか、プレイヤーがうまく対処できる攻撃 */
		AttackAction_LowRisk_LowReturn = 3,   /**< プレイヤーにとっても被弾しても大きなミスではない攻撃 シンプルに弱攻撃 */
		AttackAction_None,                    /**< 評価前の値としてNone */
		AttackAction_Max,                     /**< 最大数 */
	};

	/** 意思決定データ_攻撃_の評価項目 */
	enum AttackActionEvaluateItem : uint8_t
	{
		Attack_Necessary = 0,         /**< この行動がそのSituationに必要なのか */
		Attack_Effective = 1,         /**< この行動がそのSituationでプレイヤーに対して有効なのか */
		Attack_PlayerReceptivity = 2, /**< この行動がプレイヤーにどのくらい適応されているのか */
		Attack_Max,                   /**< 最大数 */
	};

	/** 意思決定データ_移動_の評価項目 */
	enum MoveActionEvaluteItem : uint8_t
	{
		Move_Necessary = 0,         /**< 移動が必要なのかを判断する項目 */
		Move_PlayerReceptivity = 1, /**< 移動がプレイヤーに適切に対処されているか判断する */
		Move_Max,                   /**< 最大数 */
	};

	/**
	* @struct GeneSaveData
	* @brief 遺伝学習で使用するデータを必要するデータ構造体
	*/
	struct GeneSaveData
	{
		std::vector<std::shared_ptr<Gene>> mGenes;        /**< 遺伝子 */
		size_t mGenerationCount;            /**< 現在の世代 */
		size_t mCurrentGenerationGenesSize; /**< 今の世代の遺伝子の数 */
		size_t mDataCollectionCount;        /**< 今の遺伝子データを収集した回数 */
		size_t mCurrentCollectionGene_i;    /**< 現在データ収集をしている遺伝子の添え字 */

		/**
		* デフォルトコンストラクタ
		*/
		GeneSaveData();

		/**
		* 引数ありコンストラクタ
		*/
		GeneSaveData(const std::vector<std::shared_ptr<Gene>>& _genes, const size_t _generationCount, const size_t _currentGenerationGeneSize, const size_t _evaluateCount, const size_t _collectionGene_i);
	};
}

/** そのSituationの目標となる各行動の比率 */
using SituationRiskTypeRatio = std::array<float, GeneticAlgorithmInf::AttackAction_None>;

/** 攻撃の評価値を高いか低いかを分ける閾値 */
using AttackEvaluationThreshold = std::array<float, GeneticAlgorithmInf::Attack_Max>;

/** 移動の評価値を高いか低いかを分ける閾値 */
using MoveEvaluationThreshold = std::array<float, GeneticAlgorithmInf::Move_Max>;