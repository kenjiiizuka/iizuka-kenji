/**
* @file BattleManager.h
* @brief BattleManagerクラスの定義
*/

#pragma once
//------- INCLUDES --------
#include <memory>
#include <functional>

//------- 前方宣言 ----------
class Player;
class EnemyBase;
class GameObject;
class BattleStartLogo;
class BattleSoundManager;

/**
* @class BattleManager
* @brief バトルの進行を管理する
* @detail バトル中の開始やリザルトなどの処理を実行する
*         プレイヤーと敵の体力を監視して勝利、敗北を判断する
*/
class BattleManager
{
public:
	/**
	* @enum BattleState
	* @brief バトルの状態を示すための列挙型
	*/
	enum BattleState : uint8_t
	{
		Battle_Start = 0,    /**< バトル開始ステート */
		Battle_InProgress,   /**< バトル進行中 */
		Battle_Result,       /**< バトルリザルト */
	};

	/**
	* @enum BattleResult
	* @brief 戦闘の結果を示すための列挙型
	*/
	enum BattleResult : uint8_t
	{
		Result_Win = 0,    /**< プレイヤーの勝利 */
		Result_Lose,       /**< プレイヤーの負け */
		Result_InProgress, /**< 戦闘中 */
	};

public:
	/**
	* デフォルトコントラクタ
	*/
	BattleManager();

	/**
	* デストラクタ
	*/
	~BattleManager();

private:
	/** バトルをしているプレイヤー */
	std::weak_ptr<Player> mPlayer;

	/** バトルをしているエネミー */
	std::weak_ptr<EnemyBase> mEnemy;

	/** リザルトのロゴオブジェクト */
	std::weak_ptr<GameObject> mResultLogo;

	/** 戦闘開始のロゴ */
	std::weak_ptr<BattleStartLogo> mStartLogo;

	/** バトルステート */
	BattleState mState;

	/** 今のステートの更新処理関数 */
	std::function<void()> mCurrentStateUpdate;

	/** 戦闘の経過時間 */
	double mBattleElapsedTime;

	/** 戦闘の勝敗 */
	BattleResult mResult;

	/** 戦闘にかかわるサウンドを管理再生するクラス */
	std::shared_ptr<BattleSoundManager> mBattleSoundManager;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail プレイヤーとエネミーの参照を取得し、開始演出処理の準備をする
	* @param const std::shared_ptr<Player>      (_player)
	* @param const std::shared_ptr<EnemyBase>   (_enemy)
	* @return void
	*/
	void Initialize(const std::shared_ptr<Player> _player, const std::shared_ptr<EnemyBase> _enemy);

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update();

private:
	/**
	* @fn StartStateUpdate
	* @brief スタートステートの更新処理
	* @return void
	*/
	void StartStateUpdate();

	/**
	* @fn BattleStateUpdate
	* @brief 戦闘ステートの更新処理
	* @return void
	*/
	void BattleStateUpdate();

	/**
	* @fn ResultStateUpdate
	* @brief リザルトステートの更新処理
	* @return void
	*/
	void ResultStateUpdate();
	
	/**
	* @fn TransitionState
	* @brief ステート切り替え関数
	* @param std::function<void()> (_stateFunc)
	* @param const BattleState     (_state)
	* @return void
	*/
	void TransitionState(std::function<void()> _stateFunc, const BattleState _state);

	/**
	* @fn CheckBattleResult
	* @brief 戦闘のリザルトを確認する
	* @return BattleResult
	*/
	BattleResult CheckBattleResult();

	/**
	* @fn LoseUpdate
	* @brief 敗北した時の更新処理
	* @return void
	*/
	void LoseUpdate();

	/**
	* @fn WinUpdate
	* @brief 勝利した時の更新処理
	* @return void
	*/
	void WinUpdate();

public:
	/**
	* @fn GetBattleState
	* @brief バトルの状態を返す
	* @return BattleState バトルの状態
	*/
	inline BattleState GetBattleState() const noexcept;

};

//-------- INLINES ----------

inline BattleManager::BattleState BattleManager::GetBattleState() const noexcept
{
	return mState;
}
