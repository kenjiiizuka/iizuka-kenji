/**
* @file BattleSoundManager.h
* @brief BattleSoundManagerクラスの定義
*/

#pragma once

//--------- INCLUDES -----------
#include <memory>

//------ 前方宣言 -------
class AudioClip;

/**
* @class BattleSoundManager
* @brief 戦闘中のBGM、敗北、クリアなどのバトルに関するサウンドの再生、切り替えをするクラス
*/
class BattleSoundManager
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	BattleSoundManager();

	/**
	* デストラクタ
	*/
	~BattleSoundManager();

private:
	/** 戦闘開始の音 */
	std::shared_ptr<AudioClip> mBattleStartSE;

	/** 戦闘中のBGM */
	std::shared_ptr<AudioClip> mBattleBGM;
	
	/** クリアBGM */
	std::shared_ptr<AudioClip> mClearBGM;

	/** 敗北BGM */
	std::shared_ptr<AudioClip> mLoseBGM;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @return void
	*/
	void Initialize();

	/***/
	void Update();

	/**
	* @fn PlayBattleBGM
	* @brief 戦闘BGMを再生する
	* @return void
	*/
	void PlayBattleBGM();

	/**
	* @fn StopBGM
	* @brief 再生されているBGMを止める
	* @return void
	*/
	void StopBattleBGM();

};

