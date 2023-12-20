#include "DebugScene.h"
#include "../../../Manager.h"
#include "../TitleScene/TitleScene.h"
#include "../Test/PlayerTestScene.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../Scene/SceneManager.h"
#include "../EnemyEditScene/EnemyEditScene.h"
#include "../AudioTestScene/AudioTestScene.h"
#include "../AnimationTestScene.h"
#include "../EffekseerTestScene.h"

ImVec2 vec[10];

void DebugScene::Initialize()
{
}

void DebugScene::Update()
{	
	SceneManager& sceneManager = SceneManager::GetInstance();

	ImGui::Begin("SceneSelect");

	if (ImGui::Button("Title"))
	{
		sceneManager.SceneEntry<TitleScene>();
	}
	else if (ImGui::Button("PlayerTestScene"))
	{
		sceneManager.SceneEntry<PlayerTestScene>();
	}
	else if (ImGui::Button("EnemyEditScene"))
	{
		sceneManager.SceneEntry<EnemyEditScene>();
	}
	else if (ImGui::Button("AudioTestScene"))
	{
		sceneManager.SceneEntry<AudioTestScene>();
	}
	else if (ImGui::Button("AnimationTestScene"))
	{
		sceneManager.SceneEntry<AnimationTestScene>();
	}
	else if (ImGui::Button("EffectTestScene"))
	{
		sceneManager.SceneEntry<EffekseerTestScene>();
	}

	ImGui::End();
	
	/*ImGui::Begin("Curve");
	ImGui::Curve("test", {100,100}, 10, vec);
	ImGui::End();*/
}

void DebugScene::Uninitialize()
{
}
