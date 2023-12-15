#include "EffekseerTestScene.h"
#include "../../System/Effekseer/EffectSystem.h"
#include "../../System/FPSController/FPSController.h"
#include "../Component/EffectComponent/EffectComponent.h"
#include "../GameObject/GameObject.h"
#include "../../System/InputSystem/Input.h"
#include "../../ImGui/ImGuiUtility.h"

void EffekseerTestScene::Initialize()
{
	auto effect = AddGameObject<GameObject>(ELayer::ObjectLayer)->AddComponent<EffectComponent>();
	effect->Init("assets/Effect/HitEffect.efkefc");

	effectComp = effect;

	// EffectSystem::GetInstance().Initialize();
}

void EffekseerTestScene::Update()
{	
	ImGui::Begin("Test");

	static float x = 0;
	// EffectSystem::GetInstance().Update(FPSController::GetDeltaTime());
	if (ImGui::Button("Effect"))
	{
		effectComp.lock()->PlayEffect({ x,10,0 });
	}

	ImGui::End();
}

void EffekseerTestScene::Draw()
{
	// EffectSystem::GetInstance().Draw();
}