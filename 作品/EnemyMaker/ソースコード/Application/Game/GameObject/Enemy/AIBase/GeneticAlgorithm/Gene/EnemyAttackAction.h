#pragma once
#include <numeric>
#include "EnemyAction.h"
#include "../GeneticInfomation.h"

//---------- 前方宣言 ----------
class EnemyAttackHitSensor;

/** エネミーのダメージが発生する行動 */
class EnemyAttackAction : public EnemyAction
{
public:
	/**
	* コンストラクタ
	* 
	* @param std::shared_ptr<BlackBoard> (_blackBoard)
	*/
	EnemyAttackAction(std::shared_ptr<BlackBoard> _blackBoard);

private:
	/** 評価項目 この攻撃の有効度 */
	float mEffectivenessToPlayer;

	/** 評価項目　プレイヤーがこの攻撃に対してどのくらい慣れているのか */
	float mReceptivityToPlayer;

	/** 与えたダメージ */
	std::vector<float> mDamageInflicted;

	/** 実行中に食らったダメージ */
	std::vector<float> mDamageTakenDuringExecution;

	/** 実行ごとの開始から終了までの時間 */
	std::vector<float> mExecutionTime;

protected:
	/** 攻撃がヒットしたかを観察するセンサー */
	std::shared_ptr<EnemyAttackHitSensor> mHitSensor;
	
	/** 攻撃のID */
	uint8_t mAttackID;

	/** 今のプレイヤーにとってこの行動がどんなものなのか 初回のみ手動で設定する必要がある */
	GeneticAlgorithmInf::AttackActionRiskType mRiskType;
public:
	/**
	 * @fn DuplicateFromSelfType
	 * @brief 自身と同じ型を引数で渡された値に新たに生成する
	 * @param std::shared_ptr<EnemyAttackAction>& (_destination)
	 * @return void
	*/
	virtual void DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination) = 0;

	/**
	 * @fn Evaluate
	 * @brief 評価関数
	 * @param std::shared_ptr<BlackBoard> (_blackboard) 
	 * @return void
	*/
	virtual void Evaluate(std::shared_ptr<BlackBoard> _blackboard) override;

	/**
	 * @fn Evaluate
	 * @brief 評価関数
	 * @param std::shared_ptr<BlackBoard> (_blackboard)
	 * @param const AttackEvaluationThreshold& (_threshold)
	 * @return void
	*/
	virtual void Evaluate(std::shared_ptr<BlackBoard> _blackboatd, const AttackEvaluationThreshold& _thrshold);

	/**
	 * @fn BeginActionExecution
	 * @brief 行動の開始処理
	 * @return void
	*/
	virtual void BeginActionExecution(EnemyBase* _enemy);

	/**
	 * @fn UpdateActionExecution
	 * @brief 行動の更新処理
	 * @return EnemyActionResult
	*/
	virtual EnemyActionResult UpdateActionExecution();

	/**
	 * @fn EndActionExecution
	 * @brief 行動の終了処理
	 * @return void
	*/
	virtual void EndActionExecution(){}

	/**
	 * @fn GetAveragedDamageTakenExecution
	 * @brief 実行中に食らったダメージの平均
	 * @return float
	*/
	inline float GetAveragedDamageTakenExecution();

	/**
	 * @fn GetAveragedExecutionTime
	 * @brief 平均実行時間を返す
	 * @return float
	*/
	inline float GetAveragedExecutionTime();

	/**
	 * @fn GetAveragedDamageInflicted
	 * @brief 与えたダメージの平均を返す
	 * @return float
	*/
	inline float GetAveragedDamageInflicted();

	/**
	 * @fn GetAttackActionRiskType
	 * @brief この行動の攻撃のリスクタイプを返す
	 * @return GeneticAlgorithmInf::AttackActionRiskType
	*/
	inline GeneticAlgorithmInf::AttackActionRiskType GetAttackActionRiskType() const noexcept;

	/**
	 * @fn SetAttackActionRiskType
	 * @brief リスクタイプをセットする
	 * @param const GeneticAlgorithmInf::AttackActionRiskType (_riskType)
	 * @return void
	*/
	inline void SetAttackActionRiskType(const GeneticAlgorithmInf::AttackActionRiskType _riskType) noexcept;

	/**
	 * @fn AddTakenDamage
	 * @brief 実行中にくらったダメージを追加する
	 * @param float (_takenDamage)
	 * @return void
	*/
	inline void AddDamageTakenDuringExecution(const float _takenDamage);

	/**
	 * @fn GetEffectivenessToPlayer
	 * @brief プレイヤーに対しての有効度を返す
	 * @return float
	*/
	inline float GetEffectivenessToPlayer() const noexcept;

	/**
	 * @fn GetReceptivityToPlayer
	 * @brief プレイヤーがこの行動に対してどのくらい慣れているのかを返す
	 * @return float
	*/
	inline float GetReceptivityToPlayer() const noexcept;

	/**
	* @fn SetEffectivenessToPlayer
	* @brief プレイヤーに対しての有効度をセットする
	* @param const float (_effectiveness)
	* @return void
	*/
	inline void SetEffectivenessToPlayer(const float _effectiveness) noexcept;

	/**
	* @fn SetEffectivenessToPlayer
	* @brief プレイヤーがこの行動に対してどのくらい慣れているのかをセットする
	* @param const float (_receptivity)
	* @return void
	*/
	inline void SetReceptivityToPlayer(const float _receptivity) noexcept;

	/**
	* @fn GetDamageInflicted
	* @brief 与えたダメージを保持する配列を返す
	* @return std::vector<float>
	*/
	inline std::vector<float> GetDamageInflicted() const noexcept;

	/**
	* @fn SetDamageInflicted
	* @brief 与えたダメージを保持する配列を返す
	* @param const std::vector<float>& (_damageInflicted)
	* @return void
	*/
	inline void SetDamageInflicted(const std::vector<float>& _damageInflicted) noexcept;

	/**
	* @fn GetDamageTakenDuringExecution
	* @brief 実行中にくらったダメージを保持する配列を返す
	* @return std::vector<float> 
	*/
	inline std::vector<float> GetDamageTakenDuringExecution() const noexcept;

	/**
	* @fn SetDamageTakenDuringExecution
	* @brief 実行中にくらったダメージの配列をセットする
	* @param const std::vector<float>& (_damageTakenDuringExecution)
	* @return void
	*/
	inline void SetDamageTakenDuringExecution(const std::vector<float>& _damageTakenDuringExecution) noexcept;

	/**
	* @fn GetExecutionTime
	* @brief 実行時間を保持する配列を返す
	* @return std::vectot<float>
	*/
	inline std::vector<float> GetExecutionTime() const noexcept;

	/**
	* @fn SetExecuteTime
	* @brief 行動の実行時間を保持する配列をセットする
	* @param const std::vector<float>& (_executeTime)
	* @return void
	*/
	inline void SetExecuteTime(std::vector<float> _executeTime) noexcept;

	/**
	* @fn GetAttackID
	* @brief 攻撃のIDを返す
	* @return uint8_t 
	*/
	inline uint8_t GetAttackID() const noexcept;

};

//---------------- INLINES ------------------

inline float EnemyAttackAction::GetAveragedDamageTakenExecution()
{
	return std::accumulate(mDamageTakenDuringExecution.begin(), mDamageTakenDuringExecution.end(), 0.0f) / mDamageTakenDuringExecution.size();
}

inline float EnemyAttackAction::GetAveragedExecutionTime()
{
	return std::accumulate(mExecutionTime.begin(), mExecutionTime.end(), 0.0f) / mExecutionTime.size();
}

inline float EnemyAttackAction::GetAveragedDamageInflicted()
{
	return std::accumulate(mDamageInflicted.begin(), mDamageInflicted.end(), 0.0f) / mDamageInflicted.size();
}

inline GeneticAlgorithmInf::AttackActionRiskType EnemyAttackAction::GetAttackActionRiskType() const noexcept
{
	return mRiskType;
}

inline void EnemyAttackAction::SetAttackActionRiskType(const GeneticAlgorithmInf::AttackActionRiskType _riskType) noexcept
{
	mRiskType = _riskType;
}

inline void EnemyAttackAction::AddDamageTakenDuringExecution(const float _takenDamage)
{
	// 現在の実行回数を取得する
	uint32_t executeCount_i = GetExecuteCount();

	// 配列外参照しないように値をチェックする
	executeCount_i = executeCount_i > 0 ? executeCount_i - 1 : 0;

	// 受けたダメージを加算する
	mDamageTakenDuringExecution[executeCount_i] += _takenDamage;
}

inline float EnemyAttackAction::GetEffectivenessToPlayer() const noexcept
{
	return mEffectivenessToPlayer;
}

inline float EnemyAttackAction::GetReceptivityToPlayer() const noexcept
{
	return mReceptivityToPlayer;
}

inline void EnemyAttackAction::SetEffectivenessToPlayer(const float _effectiveness) noexcept
{
	mEffectivenessToPlayer = _effectiveness;
}

inline void EnemyAttackAction::SetReceptivityToPlayer(const float _receptivity) noexcept
{
	mReceptivityToPlayer = _receptivity;
}

inline std::vector<float> EnemyAttackAction::GetDamageInflicted() const noexcept
{
	return mDamageInflicted;
}

inline void EnemyAttackAction::SetDamageInflicted(const std::vector<float>& _damageInflicted) noexcept
{
	mDamageInflicted = _damageInflicted;
}

inline std::vector<float> EnemyAttackAction::GetDamageTakenDuringExecution() const noexcept
{
	return mDamageTakenDuringExecution;
}

inline void EnemyAttackAction::SetDamageTakenDuringExecution(const std::vector<float>& _damageTakenDuringExecution) noexcept
{
	mDamageTakenDuringExecution = _damageTakenDuringExecution;
}

inline std::vector<float> EnemyAttackAction::GetExecutionTime() const noexcept
{
	return mExecutionTime;
}

inline void EnemyAttackAction::SetExecuteTime(std::vector<float> _executeTime) noexcept
{
	mExecutionTime = _executeTime;
}

inline uint8_t EnemyAttackAction::GetAttackID() const noexcept
{
	return mAttackID;
}


