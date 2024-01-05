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
#include "../../GameObject/Camera/CinematicCamera.h"
#include "../../GameObject/Camera/CameraManager.h"
#include "../../GameObject/StaticMeshObject/StaticMeshObject.h"
#include "../../Component/MoveComponent/DebugMoveComponent.h"
#include "../../../Utility/MathLibrary.h"

std::weak_ptr<StaticMeshObject> mFrustumTest;

void DebugScene::Initialize()
{
	std::shared_ptr<StaticMeshObject> mesh = AddGameObject<StaticMeshObject>(ELayer::ObjectLayer);
	mesh->AddComponent<DebugMoveComponent>();
	mesh->Init("assets/Player/Weapon/weapon.FBX");
	mesh->SetScale(0.1f);
	mesh->SetPosition({10,0,10});
	mFrustumTest = mesh;
}

void DebugScene::Update()
{	
	std::shared_ptr<Camera> mainCam = mpCameraManager->GetMainCamera();
	DirectX::SimpleMath::Matrix fm = mainCam->GetViewMatrix() * mainCam->GetProjectionMatrix();
	fm = fm.Transpose();
	ImGui::Begin("Frustum");
	DirectX::SimpleMath::Vector3 pos = {7.9504f, 29.7567f, -3.66f};

	DirectX::SimpleMath::Matrix mat;
	MathLibrary::CreateTranslationMatrix(pos, mat);
	mat *= mFrustumTest.lock()->GetComponent<TransformComponent>()->GetWorldMatrix().Transpose();
	MathLibrary::GetTranslationFromMatrix(mat, pos);

	/*DirectX::SimpleMath::Vector4 fpos = 
	{
		pos.x * fm._11 + pos.y * fm._21 + pos.z * fm._31 + 1 * fm._41,
		pos.x * fm._12 + pos.y * fm._22 + pos.z * fm._32 + 1 * fm._42,
		pos.x * fm._13 + pos.y * fm._23 + pos.z * fm._33 + 1 * fm._43,
		pos.x * fm._14 + pos.y * fm._24 + pos.z * fm._34 + 1 * fm._44
	};*/

	DirectX::SimpleMath::Vector4 fpos =
	{
		pos.x * fm._11 + pos.y * fm._12 + pos.z * fm._13 + 1 * fm._14,
		pos.x * fm._21 + pos.y * fm._22 + pos.z * fm._23 + 1 * fm._24,
		pos.x * fm._31 + pos.y * fm._32 + pos.z * fm._33 + 1 * fm._34,
		pos.x * fm._41 + pos.y * fm._42 + pos.z * fm._43 + 1 * fm._44
	};

	bool draw = true;
	// -w < x < w ではないならフラスタム外
	if (!(fpos.x > -fpos.w && fpos.x < fpos.w))
	{
		draw = false;
	}
	// -w < y < w ではないならフラスタム外
	if (!(fpos.y > -fpos.w && fpos.y < fpos.w))
	{
		draw = false;
	}
	// 0 < z < w ではないならフラスタム外
	if (!(fpos.z > 0 && fpos.z < fpos.w))
	{
		draw = false;
	}

	ImGui::Text("X range  %f < %f < %f  ", -fpos.w, fpos.x, fpos.w);
	ImGui::Text("Y range  %f < %f < %f  ", -fpos.w, fpos.y, fpos.w);
	ImGui::Text("Z range  %f < %f < %f  ", 0, fpos.z, fpos.w);


	ImGui::Checkbox("Draw", &draw);

	ImGui::End();


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
}

void DebugScene::Uninitialize()
{
}
