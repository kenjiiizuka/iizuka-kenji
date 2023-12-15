//---------- INCLUDES -----------
#include "TitleScene.h"
#include "../SceneManager.h"
#include "../GameScene/GameScene.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../GameObject/GameObject.h"
#include "../../GameObject/TitleObject/TitleEnemy.h"
#include "../../GameObject/TitleObject/TitleBackGround.h"
#include "../../GameObject/Fade/Fade.h"
#include "../../GameObject/LoseLogo/LoseLogo.h"
#include "../../GameObject/Command/CommandObject.h"
#include "../../GameObject/CommandSelector/CommandSelector.h"
#include "../../../Manager.h"
#include "../../GameObject/Camera/CameraManager.h"
#include "../../GameObject/StaticMeshObject/StaticMeshObject.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../GameObject/Light/LightBase.h"

TitleScene::TitleScene()
	: mbTransitionScene(false)
	, mbEnd(false)
	, mFadeSpeed(1.0f)
{
	// �����Ȃ�
}

TitleScene::~TitleScene()
{
	// �����Ȃ�
}

void TitleScene::Initialize()
{
	// ���C�g�̈ʒu����
	GetGameObject<LightBase>(ELayer::BaseLayer)->SetPosition({ 72.0f,100.0f,61.0f });

	// �^�C�g���w�i�̒ǉ�(Title���S��)
	AddGameObject<TitleBackGround>(ELayer::ObjectLayer);
		
	// �J�����̐ݒ�
	std::shared_ptr<Camera> mainCamera = mpCameraManager->CreateCamera<Camera>("TitleCamera");
	mainCamera->SetPosition({3.682f + 100,14.8f, -31.38f + 100});
	mainCamera->SetRotation({0.38f, -0.565f, 0.0f});
	mpCameraManager->SetMainCamera("TitleCamera");

	// �R�}���h�Z���N�^�[�쐬
	std::shared_ptr<CommandSelector> commandSelector = AddGameObject<CommandSelector>(ELayer::ObjectLayer);

	// �R�}���h�쐬
	std::shared_ptr<CommandObject> startCommand =  AddGameObject<CommandObject>(ELayer::ObjectLayer);
	std::shared_ptr<CommandObject> endCommand = AddGameObject<CommandObject>(ELayer::ObjectLayer);

	// �������ɔz�u
	DirectX::SimpleMath::Vector2 startCommandPos = 
	{
		Renderer::GetInstance().GetWidth() / 2.0f - 310.0f / 2.0f,
		Renderer::GetInstance().GetHeight() * 0.7f 
	};
	startCommand->Init(startCommandPos, {310.0f,120.0f}, "assets/Title/Start.png");

	// �X�^�[�g�R�}���h��肷�������ɔz�u
	DirectX::SimpleMath::Vector2 endCommandPos =
	{
		Renderer::GetInstance().GetWidth() / 2.0f - 186.0f / 2.0f,
		Renderer::GetInstance().GetHeight() * 0.8f + 10.0f
	};

	endCommand->Init(endCommandPos, {186.0f, 120.0f}, "assets/Title/End.png");

	// �R�}���h�Z���N�^�[�̐ݒ�
	commandSelector->AddCommand(startCommand);	
	commandSelector->AddCommand(endCommand);
	commandSelector->ResetCursorPosition();

	mCommandSelector = commandSelector;

	// �t�F�[�h�I�u�W�F�N�g�̒ǉ�
	mFade = AddGameObject<Fade>(ELayer::ObjectLayer);
	// �t�F�[�h�C��
	mFade.lock()->FadeIn(mFadeSpeed * 0.8f); // �J�n�̃t�F�[�h�͂������x������

	// �^�C�g���p�̃G�l�~-
	std::shared_ptr<TitleEnemy> enemy = AddGameObject<TitleEnemy>(ELayer::ObjectLayer);
	enemy->SetPosition({ 100,0,100 });
	// �w�i�̏��� - 1
	{
		std::shared_ptr<StaticMeshObject> prop = AddGameObject<StaticMeshObject>(ELayer::ObjectLayer);
		prop->Init("assets/Player/Weapon/Katana.fbx");
		prop->SetPosition({ -15.0f + 100, 8.0f, -24.0f  + 100});
		prop->SetScale({ 0.1f });
		prop->SetRotation({ 3.1f,2.0f,0.1f });
		mProps.emplace_back(prop);
	}

	// �w�i�̏��� - 1
	{
		std::shared_ptr<StaticMeshObject> prop = AddGameObject<StaticMeshObject>(ELayer::ObjectLayer);
		prop->Init("assets/Title/Prop/Field.fbx");
		prop->SetPosition({ -40.0f + 100, -0.0f, 69.0f + 100 });
		prop->SetScale({ 0.1f });
		prop->SetRotation({ 0.0f,2.9f,0.0f });
		mProps.emplace_back(prop);
	}
}

void TitleScene::Update()
{
	if (mFade.lock()->IsFading())
	{
		return;
	}

	// �A�v���P�[�V�����I��
	if (mbEnd)
	{
		Manager::Inactive();
	}

	if (mbTransitionScene)
	{
		SceneManager::GetInstance().SceneEntry<GameScene>();
	}

	if (mCommandSelector.lock()->GetSelectCommandID() == CommandSelector::ID_1)
	{
		mbTransitionScene = true;
		mFade.lock()->FadeOut(mFadeSpeed);
	}
	else if (mCommandSelector.lock()->GetSelectCommandID() == CommandSelector::ID_2)
	{
		mFade.lock()->FadeOut(mFadeSpeed * 0.8f); // �Q�[���I���̃t�F�[�h�͂������x������
		mbEnd = true;
	}

#ifdef _DEBUG
	ImGui::Begin("Props");
	for (size_t i = 0; std::weak_ptr<StaticMeshObject> object : mProps)
	{
		std::string label = "Prop " + std::to_string(i); 
		std::shared_ptr<TransformComponent> transComp = object.lock()->GetComponent<TransformComponent>();
		Transform trans = transComp->GetTransform();
		ImGuiUtility::GetInstance().DragTransform(label, trans);
		transComp->SetTransform(trans);
		i++;
	}
	ImGui::End();
#endif

}