/**
* @file GeneDataSever.h
* @brief GeneDataSeverクラスの定義
*/


#pragma once


//--------- INCLUDES ----------
#include <vector>
#include <string>
#include "GeneticInfomation.h"


/**
* @class GeneDataSever
* @brief 遺伝子データをファイルに書き込む機能を持つ
*/
class GeneDataSaver final
{
	/**
	* @struct AttackGeneArchive
	* @brief 攻撃遺伝子のアーカイブ
	*/
	struct AttackGeneArchive
	{
		std::string mTypeName;                               /**< 遺伝子の型名 */
		GeneticAlgorithmInf::AttackActionRiskType mRiskType; /**< リスクタイプ */
		float mEffectivenessToPlayer;                        /**< プレイヤーへの有効度 */
		float mReceptivityToPlayer;                          /**< プレイヤーがこの行動に対してどのくらい慣れているのか */
		float mSuitable;                                     /**< 状況に適しているか */
		uint32_t mExecuteCount;                              /**< 実行回数 */
		size_t mDamageInflictedSize;                         /**< 与えたダメージを保持する配列のサイズ */
		std::vector<float> mDamageInflicted;                 /**< 与えたダメージを保持する配列 */
		size_t mDamageTakenDuringExecutionSize;              /**< 反撃でくらったダメージを保持する配列のサイズ */
		std::vector<float> mDamageTakenDuringExecution;      /**< 反撃でくらったダメージを保持する配列 */
		size_t mExecutionTimeSize;                           /**< 実行時間を保持する配列のサイズ */
		std::vector<float> mExecutionTime;                   /**< 実行時間を保持する配列 */

		/**
		* デフォルトコンストラクタ
		*/
		AttackGeneArchive();
	};

	/**
	* @struct MoveGeneArchive
	* @brief 移動遺伝子のアーカイブ
	*/
	struct MoveGeneArchive
	{
		std::string mTypeName; /** 遺伝子の型名 */
	};

	/**
	* @struct SituationGeneArchive
	* @brief 状況遺伝子のアーカイブ
	*/
	struct SituationGeneArchive
	{
		bool mbIsEvaluated;                                   /**< 評価済みかどうか */
		size_t mAttackGeneCount;                              /**< 攻撃遺伝子の数 */
		size_t mMoveGeneCount;                                /**< 移動遺伝子の数 */
		SituationRiskTypeRatio mActionRiskTypeTargetRatio;    /**< 目標とするRiskTypeの比率 */	
		SituationRiskTypeRatio mCurrentRiskTypeRatio;         /**< 現在のリスクタイプの比率 */
		AttackEvaluationThreshold mAttackEvaluationThreshold; /**< このシチュエーションの攻撃の評価値を高いか低いかを分ける閾値 */	
		MoveEvaluationThreshold mMoveEvaluationThreshold;     /**< このシチュエーションの移動の評価値を高いか低いかを分ける閾値 */
		float mTotalEvaluationOfActions;                      /**< 攻撃行動の評価値 */
		std::vector<size_t> mAttackGeneTypeSize;              /**< 攻撃遺伝子の型判別文字列のサイズ*/
		std::vector<AttackGeneArchive> mAttackGeneArchive;    /**< 攻撃遺伝子アーカイブ */
		std::vector<size_t> mMoveGeneTypeSize;                /**< 移動遺伝子の型判別用文字列のサイズ */
		std::vector<MoveGeneArchive> mMoveGeneArchive;        /**< 移動遺伝子のアーカイブ */

		/**
		* デフォルトコンストラクタ
		*/
		SituationGeneArchive();
	};

	

	// 遺伝子のアーカイブ型
	using GeneArchive = std::vector<SituationGeneArchive>;

	// すべての遺伝子のアーカイブデータ型
	using AllGeneArchive = std::vector<GeneArchive>;

public:

	/**
	* デフォルトコンストラクタ
	*/
	GeneDataSaver()
	{
		// 処理なし
	}

	/**
	* デフォルトデストラクタ
	*/
	~GeneDataSaver()
	{
		// 処理なし
	}

public:
	/**
	* @fn SaveGene
	* @brief 遺伝子データをセーブする関数
	* @param const GeneticAlgorithmInf::GeneSaveData& (_saveData)
	* @return void
	*/
	void SaveGene(const GeneticAlgorithmInf::GeneSaveData& _saveData);


private:
	/**
	* @fn CalucSaveGeneDataSize
	* @brief 保存する遺伝子データのサイズを返す
	* @param const AllGeneArchive& (_saveGene)
	* @return size_t
	*/
	size_t CalucAllGeneArchiveSize(const AllGeneArchive& _saveGene);

	/**
	* @fn ArchiveSituationGene
	* @brief 状況遺伝子をアーカイブする
	* @param std::vector<SituationGeneArchive>& (_situationArchive) アーカイブした状況遺伝子を格納する配列
	* @param std::vector<Genetic>&              (_genetic)          アーカイブしたい状況遺伝子 
	* @return void
	*/
	void ArchiveSituationGene(std::vector<SituationGeneArchive>& _situationArchive, std::shared_ptr<Gene>& _genetic);

	/**
	* @fn ArchiveAttackGene
	* @brief 攻撃遺伝子のデータを保存できる形式する関数
	* @param std::vector<size_t>&         (_attackGeneTypeSize) 型判別用文字列のサイズ
	* @param std::vector<AttackGeneSave>& (_attackGeneArchive)  アーカイブしたデータを格納する配列
	* @param const AttackGenes&           (_attackGene)         アーカイブしたい攻撃遺伝子配列
	* @return void
	*/
	void ArchiveAttackGene(std::vector<size_t>& _attackGeneTypeSize, std::vector<AttackGeneArchive>& _attackGeneArchive, const AttackGenes& _attackGene);

	/**
    * @fn ArchiveMoveGene
    * @brief 攻撃遺伝子のデータを保存できる形式する関数
    * @param std::vector<size_t>&          (_moveGeneTypeSize) 型判別用文字列のサイズ
    * @param std::vector<MoveGeneArchive>& (_moveGeneArchive)  アーカイブしたデータを格納する配列
    * @param const MoveGenes&              (_moveGenes)        アーカイブしたい移動遺伝子の配列
	* @return void
    */
	void ArchiveMoveGene(std::vector<size_t>& _moveGeneTypeSize, std::vector<MoveGeneArchive>& _moveGeneArchive, const MoveGenes& _moveGenes);

	/**
	* @fn MemCpyArchiveSituationGene
	* @brief　アーカイブされた状況遺伝子をメモリに書き込む
	* @param char*&                             (_writePtr)             書き込む先のポインタ
	* @param std::vector<SituationGeneArchive>& (_situationGeneArchive) アーカイブされた状況遺伝子 
	*/
	void MemCpyArchiveSituationGene(char*& _writePtr, std::vector<SituationGeneArchive>& _situationGeneArchive);

	/**
	* @fn MemCpyArchiveAttackGene
	* @brief アーカイブされた攻撃遺伝子をメモリーに書き込む
	* @param char*&                                (_writePtr)            書き込み先のメモリーのポインタ
	* @param const std::vector<size_t>&            (_attackGeneTypeSize)  型判別用文字列のサイズ
	* @param const std::vector<AttackGeneArchive>& (_attackGeneArchive)   メモリに書き込むアーカイブされた攻撃遺伝子
	* @return void
	*/
	void MemCpyArchivedAttackGene(char*& _writePtr, const std::vector<size_t>& _attackGeneTypeSize, const std::vector<AttackGeneArchive>& _attackGeneArchive);

	/**
	* @fn MemCpyArchivedMoveGene
	* @brief アーカイブされた移動遺伝子をメモリーに書き込む
	* @param char*&                              (_writePtr)         書き込み先のメモリーのポインタ
	* @param const std::vector<size_t>&          (_moveGeneTypeSize) 型判別用文字列のサイズ
	* @param const std::vector<MoveGeneArchive>& (_moveGeneArchive)  メモリに書き込むアーカイブされた移動遺伝子
	* @return void
	*/
	void MemCpyArchivedMoveGene(char*& _writePtr, const std::vector<size_t>& _moveGeneTypeSize, const std::vector<MoveGeneArchive>& _moveGeneArchive);
};
