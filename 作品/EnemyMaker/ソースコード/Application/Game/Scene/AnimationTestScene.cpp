//----------- INCLUDES ------------
#include "AnimationTestScene.h"
#include "../GameObject/AnimationTestObject/AnimationTestObject.h"
#include "../../ImGui/ImGuiUtility.h"
#include "DebugScene/DebugScene.h"
#include "SceneManager.h"

void AnimationTestScene::Initialize()
{
	AddGameObject<AnimationTestObject>();
}

void AnimationTestScene::Update()
{
	ImGui::Begin("SceneSelect");
	if(ImGui::Button("DebugScene"))
	{
		SceneManager::GetInstance().SceneEntry<DebugScene>();
	}

	ImGui::End();
}
