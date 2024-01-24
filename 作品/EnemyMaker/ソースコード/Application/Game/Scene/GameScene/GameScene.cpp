//---------- INCLUDES ---------
#include "GameScene.h"
#include "../TitleScene/TitleScene.h"
#include "../SceneManager.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../../System/CollisionSystem/CollisionSystem.h"
#include "../../../System/AudioSystem/AudioSystemIncludes.h"
#include "../../GameObject/Field/Field.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Player/PlayerCamera/PlayerCamera.h"
#include "../../GameObject/Camera/CameraManager.h"
#include "../../GameObject/Enemy/Bear/BearEnemy.h"
#include "../../GameObject/CircleBlockObject/CircleBlockObject.h"
#include "../../GameObject/Fade/Fade.h"


GameScene::GameScene()
	: mbTransitionScene(false)
{
	// 処理なし
}

GameScene::~GameScene()
{
	// 処理なし
}

void GameScene::Initialize()
{
	// プレイヤーの生成
	std::shared_ptr<Player> player = AddGameObject<Player>();
	std::weak_ptr<TransformComponent> playerTrans = player->GetComponent<TransformComponent>();
	player->SetPosition({ 100,0,70 });

	// 追従カメラの生成
	std::shared_ptr<PlayerCamera> playerCamera = mpCameraManager->CreateCamera<PlayerCamera>("PlayerCamera");
	mpCameraManager->SetMainCameraByName("PlayerCamera");
	playerCamera->Init(player);

	// エネミーの作成
	std::shared_ptr<BearEnemy> enemy = AddGameObject<BearEnemy>();
	enemy->SetPosition({ 100.f,0.f,100.f });
	enemy->SetRotation({ 0.0f,3.14f,0.0f });

	// 戦闘エリア外に行かないようにサークル型のオブジェクトの作成
	AddGameObject<CircleBlockObject>();

	// コリジョンをオン
	CollisionSystem::GetInstance().SwitchActive(true);

	// バトルマネージャーの生成	
	mBattleManager = AddGameObject<BattleManager>();
	mBattleManager.lock()->Init(player, enemy);

	// フェードインが終るまでは非アクティブ
	mBattleManager.lock()->SetActive(false);

	// フィールドの作成
	AddGameObject<Field>();

	// フェードオブジェクト生成
	mFade = AddGameObject<Fade>();
	mFade.lock()->FadeIn();

	// このシーンのオーディオリスナーを設定
	AudioSystem::GetInstance().GetAudioListenerObject().lock()->SwitchListenerObject(player);
	
}

void GameScene::Update()
{
	// フェード中は処理をしない
	if (mFade.lock()->IsFading())
	{
		return;
	}

	mBattleManager.lock()->SetActive(true);
	if (mbTransitionScene)
	{
		SceneManager::GetInstance().SceneEntry<TitleScene>();
	}
}
