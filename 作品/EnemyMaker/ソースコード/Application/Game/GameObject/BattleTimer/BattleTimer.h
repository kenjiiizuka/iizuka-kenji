/**
* @file BattleTimer.h
* @brief BattleTimerクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include "../GameObject.h"
#include <array>

//--------- 前方宣言 ---------
class SpriteComponent;
class AssetHandle;
class CurveFloat;

/**
* @enum TimerState
* @brief タイマーの状態を示す
*/
enum class TimerState : uint8_t
{
	Stop = 0, /**< 停止中 */
	Count ,   /**< 計測中 */
	End,      /**< 終了 */
};

/**
* @class BattleTimer
* @brief 戦闘時の時間を表示するタイマー
*/
class BattleTimer : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BattleTimer();

	/**
	* デストラクタ
	*/
	~BattleTimer();

private:
	/** 数字用テクスチャ */
	std::array<std::shared_ptr<AssetHandle>, 10> mNumberTextures;

	/** コロンテクスチャ */
	std::shared_ptr<AssetHandle> mKoronTexture;

	/** コンマテクスチャ */
	std::shared_ptr<AssetHandle> mCommaTexture;

	/** 数字表示用のスプライト 戦闘から [m(1桁) : s(2桁) : ms(2桁)]　の順番で使う : も含む*/
	std::array<std::weak_ptr<SpriteComponent>, 7> mSprites;
	
	/** 残り制限時間 */
	double mTimeLimitSec;

	/** 経過時間 */
	double mElapsedTimeSec;

	/** タイマーの状態 */
	TimerState mState;

	/** フラッシュ開始からの経過時間 */
	double mFlashElapsedTime;

	/** タイマー点滅用カーブ */
	std::shared_ptr<CurveFloat> mFlashCurve;

	/** タイマーの左端の位置 */
	DirectX::SimpleMath::Vector2 mInitialPosition;

	/** 表示する文字のサイズ */
	DirectX::SimpleMath::Vector2 mSize;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @param const double (_timeLimit) 計測する時間
	* @param const DirectX::SimpleMath::Vector2 (_pos) タイマーの初期位置
	* @return void
	*/
	void Init(const double _timeLimit, const DirectX::SimpleMath::Vector2 _pos = {530.0f, 5.0f});

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn SetupTexture
	* @brief 残り時間に合わせてテクスチャを設定する
	* @return void
	*/
	void SetupTexture();

	/**
	* @fn ConvertTimeToDrawFormat
	* @brief 残り時間を MSSSS の形式に変換する　分 秒(少数第２位)
	* @param const double (_second) 変換したい時間 (秒)
	* @return uint16_t
	*/
	uint16_t ConvertTimeToDrawFormat(const double _second);

	/**
	* @fn TimerFlash
	* @brief ラスト60秒になったら赤く点滅させる
	* @param const double (_deltaTime)
	* @return void
	*/
	void TimerFlash(const double _deltaTime);

	/**
	* @fn TimerVibration
	* @brief タイマーを振動させる
	* @param const double (_deltaTime)
	* @return void
	*/
	void TimerVibration(const double _deltaTime);

public:
	/**
	* @fn TimerStart
	* @brief タイマーをスタートさせる関数
	* @return void
	*/
	inline void TimerStart();

	/**
	* @fn TimerStop
	* @brief タイマーを停止させる
	* @return void
	*/
	inline void TimerStop();

	/**
	* @fn IsTimerEnd
	* @brief タイマーが終了したかを返す
	* @return bool true 終了 false 終了していない
	*/
	inline bool IsTimerEnd() const noexcept;

	/**
	* @fn GetElapsedTime
	* @brief 経過時間を返す
	* @return double 
	*/
	inline double GetElapsedTime() const noexcept;

};

//--------- INLINES -----------

inline bool BattleTimer::IsTimerEnd() const noexcept
{
	return mState == TimerState::End;
}

inline void BattleTimer::TimerStart()
{
	mState = TimerState::Count;

	// 残り時間に合わせてテクスチャを設定
	SetupTexture();
}

inline void BattleTimer::TimerStop()
{
	mState = TimerState::Stop;
}

inline double BattleTimer::GetElapsedTime() const noexcept
{
	return mElapsedTimeSec;
}