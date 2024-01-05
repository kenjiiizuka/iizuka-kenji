//--------- INCLUDES ----------
#include "EnemyEditScene.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../SceneManager.h"
#include "../DebugScene/DebugScene.h"
#include "../../GameObject/Enemy/Bear/BearEnemy.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Player/PlayerCamera/PlayerCamera.h"
#include "../../GameObject/Camera/CameraManager.h"
#include "../../../System/CollisionSystem/CollisionSystem.h"
#include "../../GameObject/Camera/CinematicCamera.h"

EnemyEditScene::EnemyEditScene()
{
	// 処理なし
}

EnemyEditScene::~EnemyEditScene()
{
	// 処理なし
}

void EnemyEditScene::Initialize()
{
	std::shared_ptr<BearEnemy> enemy = AddGameObject<BearEnemy>(ELayer::ObjectLayer);
	enemy->SetRotation({ 0.0f,3.14f,0.0f });

	// プレイヤーの生成
	std::weak_ptr<Player> player = AddGameObject<Player>(ELayer::ObjectLayer);
	std::weak_ptr<TransformComponent> playerTrans = player.lock()->GetComponent<TransformComponent>();
	player.lock()->SetPosition({ 0,0,-20 });
	player.lock()->BattleStart();

	// 敵の死亡時のカメラ
	mEnemyDeathCamera = mpCameraManager->CreateCamera<CinematicCamera>("DeathCamera");
	mEnemyDeathCamera.lock()->Init("assets/Enemy/Config/DeathCamera.json");

	// 追従カメラの生成
	std::shared_ptr<PlayerCamera> playerCamera = mpCameraManager->CreateCamera<PlayerCamera>("PlayerCamera");
	playerCamera->Init(player);

	mEditor = std::make_shared<BearEnemyEditor>();
	mEditor->Initialize(enemy);
	mEditor->SetDeathCamera(mEnemyDeathCamera.lock());
	// コリジョンをオンにする
	CollisionSystem::GetInstance().SwitchActive(true);
}

void EnemyEditScene::Update()
{
	ImGui::Begin("SceneSelect");
	if (ImGui::Button("DebugScene"))
	{
		SceneManager::GetInstance().SceneEntry<DebugScene>();
	}
	ImGui::End();

	mEditor->Update();
}

void EnemyEditScene::Uninitialize()
{
}
