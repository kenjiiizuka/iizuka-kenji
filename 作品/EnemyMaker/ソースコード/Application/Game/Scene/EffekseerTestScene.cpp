//------------- INCLUDES -------------
#include "EffekseerTestScene.h"
#include "../../System/Effekseer/EffectSystem.h"
#include "../../System/FPSController/FPSController.h"
#include "../Component/EffectComponent/EffectComponent.h"
#include "../GameObject/GameObject.h"
#include "../../System/InputSystem/Input.h"
#include "../../ImGui/ImGuiUtility.h"

void EffekseerTestScene::Initialize()
{
	auto effect = AddGameObject<GameObject>()->AddComponent<EffectComponent>();
	effect->Init("assets/Player/Effect/Guard.efkefc");
	effectComp = effect;
}

void EffekseerTestScene::Update()
{	
	ImGui::Begin("Test");

	static DirectX::SimpleMath::Vector3 rotation = {0,0,0};
	static float angle = 0.0f;
	ImGuiUtility::GetInstance().InputVector3("Rotation", rotation);
	ImGui::InputFloat("Angle", &angle);

	static float x = 0;
	// EffectSystem::GetInstance().Update(FPSController::GetDeltaTime());
	if (ImGui::Button("Effect"))
	{
		effectComp.lock()->PlayEffect({ x,10,0 }, {rotation}, angle);
	}

	ImGui::End();
}

void EffekseerTestScene::Draw()
{
	// EffectSystem::GetInstance().Draw();
}