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
#include "../../Component/AudioComponent/AudioComponent.h"

TitleScene::TitleScene()
	: mbTransitionScene(false)
	, mbEnd(false)
	, mFadeSpeed(1.0f)
{
	// 処理なし
}

TitleScene::~TitleScene()
{
	// 処理なし
}

void TitleScene::Initialize()
{
	// ライトの位置調整
	GetGameObject<LightBase>()->SetPosition({ 72.0f,100.0f,61.0f });

	// タイトル背景の追加(Titleロゴつき)
	AddGameObject<TitleBackGround>();
			
	// カメラの設定
	std::shared_ptr<Camera> mainCamera = mpCameraManager->CreateCamera<Camera>("TitleCamera");
	mainCamera->SetPosition({3.682f + 100,14.8f, -31.38f + 100});
	mainCamera->SetRotation({0.38f, -0.565f, 0.0f});
	mpCameraManager->SetMainCameraByName("TitleCamera");

	// コマンドセレクター作成
	std::shared_ptr<CommandSelector> commandSelector = AddGameObject<CommandSelector>();

	// コマンド作成
	std::shared_ptr<CommandObject> startCommand =  AddGameObject<CommandObject>();
	std::shared_ptr<CommandObject> trainingCommand = AddGameObject<CommandObject>();
	std::shared_ptr<CommandObject> endCommand = AddGameObject<CommandObject>();

	// Startコマンド
	{
		DirectX::SimpleMath::Vector2 size = { 280.0f, 90.0f };
		DirectX::SimpleMath::Vector2 startCommandPos =
		{
			Renderer::GetInstance().GetWidth() / 2.0f - size.x / 2.0f, // 画面中央からサイズの半分左にずらした位置
			Renderer::GetInstance().GetHeight() * 0.6f // 0.7f 画面を10分割した時に下から７番目の位置
		};
		startCommand->Init(startCommandPos, size, "assets/Title/Start.png");

	}
	
	// Endコマンド
	{
		DirectX::SimpleMath::Vector2 size = { 156.0f, 90.0f };
		DirectX::SimpleMath::Vector2 endCommandPos =
		{
			Renderer::GetInstance().GetWidth() / 2.0f - size.x / 2.0f, // 画面中央からサイズの半分左にずらした位置
			Renderer::GetInstance().GetHeight() * 0.7f + 10.0f         // 0.6f + 10.0f 画面を10分割した時に下から6番目の位置で少し下にして余白を作る
		};
		endCommand->Init(endCommandPos, size, "assets/Title/End.png");
	}
	
	// コマンドセレクターの設定
	commandSelector->AddCommand(startCommand);	
	// commandSelector->AddCommand(trainingCommand);
	commandSelector->AddCommand(endCommand);
	commandSelector->ResetCursorPosition();
	mCommandSelector = commandSelector;

	// フェードオブジェクトの追加
	mFade = AddGameObject<Fade>();
	// フェードイン
	mFade.lock()->FadeIn(mFadeSpeed * 0.8f); // 開始のフェードはすこし遅くする

	// タイトル用のエネミ-
	std::shared_ptr<TitleEnemy> enemy = AddGameObject<TitleEnemy>();
	enemy->SetPosition({ 100,0,100 });
	// 背景の小物 - 1
	{
		std::shared_ptr<StaticMeshObject> prop = AddGameObject<StaticMeshObject>();
		prop->Init("assets/Player/Weapon/Katana.fbx");
		prop->SetPosition({ -15.0f + 100, 8.0f, -24.0f  + 100});
		prop->SetScale({ 0.1f });
		prop->SetRotation({ 3.1f,2.0f,0.1f });
		mProps.emplace_back(prop);
	}

	// 背景の小物 - 1
	{
		std::shared_ptr<StaticMeshObject> prop = AddGameObject<StaticMeshObject>();
		prop->Init("assets/Title/Prop/Field.fbx");
		prop->SetPosition({ -40.0f + 100, -0.0f, 69.0f + 100 });
		prop->SetScale({ 0.1f });
		prop->SetRotation({ 0.0f,2.9f,0.0f });
		mProps.emplace_back(prop);
	}

	// オーディオ再生用のオブジェクト
	std::shared_ptr<GameObject> audioObject = AddGameObject<GameObject>();
	std::shared_ptr<AudioComponent> audioComp = audioObject->AddComponent<AudioComponent>();
	audioComp->Init("assets/Title/Audio/TitleBGM.wav", true);
	audioComp->PlaySound2D(0.08f, true);
	mBGM = audioComp;
}

void TitleScene::Update()
{
	if (mFade.lock()->IsFading())
	{
		return;
	}

	// アプリケーション終了
	if (mbEnd)
	{
		Manager::Inactive();
		return;
	}

	if (mbTransitionScene)
	{
		SceneManager::GetInstance().SceneEntry<GameScene>();
	}

	if (mCommandSelector.lock()->GetSelectCommandID() == CommandSelector::ID_1)
	{
		mbTransitionScene = true;
		mFade.lock()->FadeOut(mFadeSpeed);
		mBGM.lock()->Stop(true, 1.0);
	}
	else if (mCommandSelector.lock()->GetSelectCommandID() == CommandSelector::ID_2)
	{
		mFade.lock()->FadeOut(mFadeSpeed * 0.5f); // ゲーム終了のフェードはすこし遅くする
		mBGM.lock()->Stop(true, 2.0);
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