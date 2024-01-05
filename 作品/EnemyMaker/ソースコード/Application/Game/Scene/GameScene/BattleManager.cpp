//-------- INCLUDES ---------
#include "BattleManager.h"
#include "GameScene.h"
#include "../TitleScene/TitleScene.h"
#include "../SceneManager.h"
#include "../../GameObject/WinLogo/WinLogo.h"
#include "../../GameObject/LoseLogo/LoseLogo.h"
#include "../../GameObject/BattleStartLogo/BattleStartLogo.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Enemy/EnemyBase.h"
#include "../../GameObject/Camera/CameraIncludes.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Resource/SkeletalMesh.h"
#include "../../Resource/Skeleton.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../../System/FPSController/FPSController.h"
#include "../../Component/AudioComponent/AudioComponent.h"
#include "../../../ImGui/ImGuiUtility.h"

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

void BattleManager::Init(const std::shared_ptr<Player> _player, const std::shared_ptr<EnemyBase> _enemy)
{
	mPlayer = _player;
	mEnemy = _enemy;

	// バトル開始ステート処理をバインド	
	mCurrentStateUpdate = std::bind(&BattleManager::StartStateUpdate, this);
	mStartLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<BattleStartLogo>(ELayer::ObjectLayer);

	// BGM,SEの初期化	
	std::shared_ptr<AudioComponent> battleBGM = AddComponent<AudioComponent>();
	battleBGM->Init("assets/Battle/Audio/Battle.wav",true);
	mBattleBGM = battleBGM;

	std::shared_ptr<AudioComponent> clear = AddComponent<AudioComponent>();
	clear->Init("assets/Battle/Audio/Clear.wav");
	mClearSE = clear;
	
}

void BattleManager::Update(const double _deltaTime)
{
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
	mBattleBGM.lock()->PlaySound2D(0.1f, true, 5.0);

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
		mBattleBGM.lock()->Stop();

		if (mResult == Result_Win)
		{
			mClearSE.lock()->PlaySound2D(0.2f);
		}
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
		// CinematicCameraの生成と再生
		mResultCamera =  SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->CreateCamera<CinematicCamera>("DeathCamera");
		mResultCamera.lock()->Init("assets/Enemy/Config/DeathCamera.json");

		// ボーンのセット
		std::shared_ptr<SkeletalMesh> mesh = mEnemy.lock()->GetComponent<SkeletalMeshComponent>()->GetSkeletalMesh().lock();
		mResultCamera.lock()->SetTargetBone(mesh->GetSkeleton().lock()->GetBoneByName("mixamorig:Head").lock());

		// 再生
		mResultCamera.lock()->Play();

		return BattleResult::Result_Win;
	}
	else if (!mPlayer.lock()->IsAlive())
	{	
		// CinematicCameraの生成と再生
		mResultCamera = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->CreateCamera<CinematicCamera>("DeathCamera");
		mResultCamera.lock()->Init("assets/Player/Config/DeathCamera.json");

		// ボーンのセット
		std::shared_ptr<SkeletalMesh> mesh = mPlayer.lock()->GetComponent<SkeletalMeshComponent>()->GetSkeletalMesh().lock();
		mResultCamera.lock()->SetTargetBone(mesh->GetSkeleton().lock()->GetBoneByName("mixamorig:Head").lock());

		// 再生
		mResultCamera.lock()->Play();

		return BattleResult::Result_Lose;
	}

	return BattleResult::Result_InProgress;
}

void BattleManager::LoseUpdate()
{
	std::shared_ptr<CinematicCamera> camera = mResultCamera.lock();
	if (camera->GetCurrentPlayTime() < camera->GetDuration() * 0.5f)
	{
		return;
	}

	// リザルトロゴの生成
	if (!mResultLogo.lock())
	{
		mResultLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<LoseLogo>(ELayer::ObjectLayer);
	}

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
	std::shared_ptr<CinematicCamera> camera = mResultCamera.lock();
	if (camera->GetCurrentPlayTime() < camera->GetDuration() * 0.6f )
	{
		return;
	}

	// リザルトロゴの生成
	if (!mResultLogo.lock())
	{
		mResultLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<WinLogo>(ELayer::ObjectLayer);
	}
	
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
