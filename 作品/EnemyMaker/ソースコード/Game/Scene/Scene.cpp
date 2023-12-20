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
	 AddGameObject<LightBase>(ELayer::BaseLayer);
	 
	// スカイボックスの作成
	std::shared_ptr<GameObject> obj = AddGameObject<SkyBox>(ELayer::ObjectLayer);
	obj->SetPosition({ 0,30,0 });

	// オーディオリスナーの作成
	std::shared_ptr<AudioListener> listener = AddGameObject<AudioListener>(ELayer::ObjectLayer);
	
	// リスナーのセット
	AudioSystem::GetInstance().SetListener(listener);

	Initialize();	
}

void Scene::UninitBase()
{
	mpCameraManager->Uninit();
	for (auto& objectList : mpGameObjectList) 
	{
		for (std::weak_ptr<GameObject> obj : objectList) 
		{
			obj.lock()->UninitBase();
		}
		objectList.clear();
	}
	Uninitialize();	

	// オーディオクリア
	AudioSystem::GetInstance().ClearAudio();
}

void Scene::UpdateBase()
{
	double deltaTime = FPSController::GetDeltaTime();

	mpCameraManager->Update(deltaTime);
	for (auto& objectList : mpGameObjectList)
	{
		for (std::weak_ptr<GameObject> obj : objectList)
		{
			obj.lock()->UpdateBase(deltaTime);
		}
	}
	Update();
}

void Scene::LastUpdateBase()
{
	for (std::list<std::shared_ptr<GameObject>>& list : mpGameObjectList)
	{
		for (std::weak_ptr<GameObject> obj : list)
		{
			obj.lock()->LastUpdateBase();
		}
	}
	LastUpdate();
}

void Scene::DrawBase()
{
	for (auto& objectList : mpGameObjectList) 
	{
		for (std::weak_ptr<GameObject> obj : objectList) 
		{
			obj.lock()->DrawBase(DirectX::SimpleMath::Matrix::Identity);
		}
	}
	Draw();	
}

void Scene::Initialize()
{	
	AddGameObject<Camera2D>(ELayer::UILayer); // 2Dカメラオブジェクト
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
