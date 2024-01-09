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
	AddGameObject<LightBase>();
	 
	// �X�J�C�{�b�N�X�̍쐬
	std::shared_ptr<GameObject> obj = AddGameObject<SkyBox>();
	obj->SetPosition({ 130,120,130 });

	// �I�[�f�B�I���X�i�[�̍쐬
	std::shared_ptr<AudioListener> listener = AddGameObject<AudioListener>();
	
	// ���X�i�[�̃Z�b�g
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
	// �I�[�f�B�I�N���A
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
	AddGameObject<Camera2D>(); // 2D�J�����I�u�W�F�N�g
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
