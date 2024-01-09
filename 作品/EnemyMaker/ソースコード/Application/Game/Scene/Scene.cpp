//------------ INCLUDES -------------
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Camera/Camera2D.h"
#include "../GameObject/Camera/CameraManager.h"
#include "../../System/FPSController/FPSController.h"
#include "../GameObject/Light/LightBase.h"
#include "../GameObject/SkyBox/SkyBox.h"
#include "../GameObject/AudioLisner/AudioListener.h"
#include "../../System/AudioSystem/AudioSystem.h"

Scene::Scene()
{
	// 処理なし
}

Scene::~Scene()
{
	// 処理なし
}

void Scene::InitBase()
{	
	// カメラマネージャーの作成
	mpCameraManager = std::make_shared<CameraManager>();
	mpCameraManager->Init();

	// ライトを作成
	AddGameObject<LightBase>();
	 
	// スカイボックスの作成
	std::shared_ptr<GameObject> obj = AddGameObject<SkyBox>();
	obj->SetPosition({ 130,120,130 });

	// オーディオリスナーの作成
	std::shared_ptr<AudioListener> listener = AddGameObject<AudioListener>();
	
	// リスナーのセット
	AudioSystem::GetInstance().SetListener(listener);

	Initialize();	
}

void Scene::UninitBase()
{
	mpCameraManager->Uninit();	
	for (std::shared_ptr<GameObject> obj : mpGameObjectList)
	{
		obj->UninitBase();
	}
	mpGameObjectList.clear();	
	Uninitialize();	
	// オーディオクリア
	AudioSystem::GetInstance().ClearAudio();
}

void Scene::UpdateBase()
{
	double deltaTime = FPSController::GetDeltaTime();
	mpCameraManager->Update(deltaTime);	
	for (std::shared_ptr<GameObject> obj : mpGameObjectList)
	{
		obj->UpdateBase(deltaTime);
	}
	Update();
}

void Scene::LastUpdateBase()
{	
	for (std::shared_ptr<GameObject> obj : mpGameObjectList)
	{
		obj->LastUpdateBase();
	}	
	LastUpdate();
}

void Scene::DrawBase()
{
	
	for (std::shared_ptr<GameObject> obj : mpGameObjectList)
	{
		obj->DrawBase(DirectX::SimpleMath::Matrix::Identity);
	}	
	Draw();	
}

void Scene::Initialize()
{	
	AddGameObject<Camera2D>(); // 2Dカメラオブジェクト
	mpCameraManager->CreateCamera<Camera>("DefaultCamera");
}

void Scene::Uninitialize()
{
	// 処理なし
}

void Scene::Update()
{
	// 処理なし
}

void Scene::LastUpdate()
{
	// 処理なし
}

void Scene::Draw()
{
	// 処理なし
}
