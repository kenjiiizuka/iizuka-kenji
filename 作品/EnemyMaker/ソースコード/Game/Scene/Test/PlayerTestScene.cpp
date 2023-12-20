#include "PlayerTestScene.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Player/PlayerCamera/PlayerCamera.h"
#include "../../GameObject/Camera/CameraManager.h"
#include "../../../System/InputSystem/Input.h"
#include "../SceneManager.h"
#include "../DebugScene/DebugScene.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../System/AudioSystem/AudioSystemIncludes.h"
#include "../../Component/CollisionComponent/CapsuleCollisionComponent.h"
#include "../../../System/CollisionSystem/CollisionSystem.h"
#include"../../Component/EffectComponent/EffectComponent.h"

void PlayerTestScene::Initialize()
{
	// プレイヤーの生成
	std::weak_ptr<Player> player = AddGameObject<Player>(ELayer::ObjectLayer);
	std::weak_ptr<TransformComponent> playerTrans = player.lock()->GetComponent<TransformComponent>();
	player.lock()->SetPosition({ 100,0,30 });

	// 追従カメラの生成
	std::shared_ptr<PlayerCamera> playerCamera = mpCameraManager->CreateCamera<PlayerCamera>("PlayerCamera");
	mpCameraManager->SetMainCamera("PlayerCamera");
	playerCamera->FixInit(player);

	AudioSystem::GetInstance().GetAudioListenerObject().lock()->SwitchListenerObject(playerCamera);

	player.lock()->BattleStart();
	mPlayerEditor = std::make_shared<PlayerEditor>();
	mPlayerEditor->Initialize(player.lock());

	std::shared_ptr<GameObject> collision = AddGameObject<GameObject>(ELayer::ObjectLayer);
	std::shared_ptr<CapsuleCollisionComponent> capsule = collision->AddComponent<CapsuleCollisionComponent>();
	capsule->Init(7,5);
	capsule->SetDebugDraw(true);
	capsule->SetCollisionChannel(Collision::Channel_Enemy);
	capsule->SetCollisionTypes(Collision::Channel_Player, Collision::Type_Block);
	collision->SetPosition({ 100,4, 50 });

	CollisionSystem::GetInstance().SwitchActive(true);

	auto effect = AddGameObject<GameObject>(ELayer::ObjectLayer)->AddComponent<EffectComponent>();
	effect->Init("assets/Effect/HitEffect.efkefc");

	effectComp = effect;
}

void PlayerTestScene::Update()
{
	mPlayerEditor->Update();

	ImGui::Begin("SceneSelect");
	if(ImGui::Button("DebugScene"))
	{
		SceneManager::GetInstance().SceneEntry<DebugScene>();
	}
	ImGui::End();

	ImGui::Begin("Test");

	static float x = 0;
	// EffectSystem::GetInstance().Update(FPSController::GetDeltaTime());
	if (ImGui::Button("Effect"))
	{
		effectComp.lock()->PlayEffect({ x,10,0 });
	}

	ImGui::End();

}
