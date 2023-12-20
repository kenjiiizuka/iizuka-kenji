//-------- INCLUDES ---------
#include "BattleManager.h"
#include "GameScene.h"
#include "BattleSoundManager.h"
#include "../TitleScene/TitleScene.h"
#include "../SceneManager.h"
#include "../../GameObject/WinLogo/WinLogo.h"
#include "../../GameObject/LoseLogo/LoseLogo.h"
#include "../../GameObject/BattleStartLogo/BattleStartLogo.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Enemy/EnemyBase.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../../System/FPSController/FPSController.h"

BattleManager::BattleManager()
	: mState(Battle_Start)
	, mBattleElapsedTime(0.0f)
	, mResult(Result_InProgress)
{
	// 処理なし
}

BattleManager::~BattleManager()
{
	// 処理なし
}

void BattleManager::Initialize(const std::shared_ptr<Player> _player, const std::shared_ptr<EnemyBase> _enemy)
{
	mPlayer = _player;
	mEnemy = _enemy;

	// バトル開始ステート処理をバインド	
	mCurrentStateUpdate = std::bind(&BattleManager::StartStateUpdate, this);
	mStartLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<BattleStartLogo>(ELayer::ObjectLayer);

	// サウンドマネージャーを生成
	mBattleSoundManager = std::make_shared<BattleSoundManager>();
	mBattleSoundManager->Initialize();
}

void BattleManager::Update()
{
	mBattleSoundManager->Update();

	mCurrentStateUpdate();
}

void BattleManager::StartStateUpdate()
{
	if (!mStartLogo.lock()->IsAnimationFinish())
	{	
		return;
	}

	// プレイヤーとエネミーに戦闘開始を通知する
	mPlayer.lock()->BattleStart();
	mEnemy.lock()->BattleStart();
	mStartLogo.lock()->SetActive(false);

	// 戦闘BGMを再生する
	mBattleSoundManager->PlayBattleBGM();

	TransitionState
	(
		std::bind(&BattleManager::BattleStateUpdate, this),
		Battle_InProgress
	);
}

void BattleManager::BattleStateUpdate()
{
	// 戦闘時間を計測
	mBattleElapsedTime += FPSController::GetDeltaTime();

	// リザルトへの遷移のチェック
	mResult = CheckBattleResult();
	// 勝敗がついたらResultステートに遷移
	if (mResult != BattleResult::Result_InProgress)
	{
		TransitionState
		(
			std::bind(&BattleManager::ResultStateUpdate, this),
			Battle_Result
		);

		// BGMを止める
		mBattleSoundManager->StopBattleBGM();
	}
}

void BattleManager::ResultStateUpdate()
{
	// リザルトに応じた戦闘終了処理
	// 敗北処理
	if (mResult == Result_Lose)
	{
		mEnemy.lock()->BattleEnd();
		LoseUpdate();
	}
	// 勝利処理
	else if(mResult == Result_Win)
	{
		WinUpdate();
	}
	
}

void BattleManager::TransitionState(std::function<void()> _stateFunc, const BattleState _state)
{
	mCurrentStateUpdate = _stateFunc;
	mState = _state;
}

BattleManager::BattleResult BattleManager::CheckBattleResult()
{
	// プレイヤーとエネミーのHpをみて勝敗を判断する
	// 同じフレームないで同時にHpが0になった場合はプレイヤーの勝利を優先する
	if (!mEnemy.lock()->IsAlive())
	{	
		mResultLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<WinLogo>(ELayer::ObjectLayer);
		return BattleResult::Result_Win;
	}
	else if (!mPlayer.lock()->IsAlive())
	{	
		mResultLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<LoseLogo>(ELayer::ObjectLayer);	
		return BattleResult::Result_Lose;
	}

	return BattleResult::Result_InProgress;
}

void BattleManager::LoseUpdate()
{
	std::shared_ptr<LoseLogo> logo = std::static_pointer_cast<LoseLogo>(mResultLogo.lock());
	if (!logo->IsAnimationFinish())
	{
		return;
	}

	// なにかボタンが押されたらタイトルシーンにいく
	if (XInput::GetPressAnyKey())
	{
		SceneManager::GetInstance().SceneEntry<TitleScene>();
	}
}

void BattleManager::WinUpdate()
{
	std::shared_ptr<WinLogo> logo = std::static_pointer_cast<WinLogo>(mResultLogo.lock());
	if (!logo->IsAnimationFinish())
	{
		return;
	}

	// なにかボタンが押されたらタイトルシーンにいく
	if (XInput::GetPressAnyKey())
	{
		SceneManager::GetInstance().SceneEntry<TitleScene>();
	}
}
