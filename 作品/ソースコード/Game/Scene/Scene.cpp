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
	// �����Ȃ�
}

Scene::~Scene()
{
	// �����Ȃ�
}

void Scene::InitBase()
{	
	// �J�����}�l�[�W���[�̍쐬
	mpCameraManager = std::make_shared<CameraManager>();
	mpCameraManager->Init();

	// ���C�g���쐬
	 AddGameObject<LightBase>(ELayer::BaseLayer);
	 
	// �X�J�C�{�b�N�X�̍쐬
	std::shared_ptr<GameObject> obj = AddGameObject<SkyBox>(ELayer::ObjectLayer);
	obj->SetPosition({ 0,30,0 });

	// �I�[�f�B�I���X�i�[�̍쐬
	std::shared_ptr<AudioListener> listener = AddGameObject<AudioListener>(ELayer::ObjectLayer);
	
	// ���X�i�[�̃Z�b�g
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

	// �I�[�f�B�I�N���A
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
	AddGameObject<Camera2D>(ELayer::UILayer); // 2D�J�����I�u�W�F�N�g
	mpCameraManager->CreateCamera<Camera>("DefaultCamera");
}

void Scene::Uninitialize()
{
	// �����Ȃ�
}

void Scene::Update()
{
	// �����Ȃ�
}

void Scene::LastUpdate()
{
	// �����Ȃ�
}

void Scene::Draw()
{
	// �����Ȃ�
}
