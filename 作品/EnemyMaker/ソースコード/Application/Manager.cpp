//----------- INCLUDES -------------
#include "Manager.h"
#include "Application.h"
#include "System/InputSystem/Input.h"
#include "System/RendererSystem/Renderer.h"
#include "Game/Scene/Scene.h"
#include "Game/Scene/DebugScene/DebugScene.h"
#include "Game/Scene/TitleScene/TitleScene.h"
#include "System/AudioSystem/AudioSystem.h"
#include "System/CollisionSystem/CollisionSystem.h"
#include "System/InputSystem/XInput.h"
#include "System/RendererSystem/RendererManager.h"
#include "Game/Scene/SceneManager.h"
#include "System/RendererSystem/DebugRenderer/DebugRendererManager.h"
#include "System/AssetSystem/Texture/TextureProvider.h"
#include "System/AssetSystem/AssetManager.h"
#include "System/AssetSystem/BinaryFile/BinaryFileProveider.h"
#include "System/AssetSystem/SkeletalMesh/SkeletalMeshAnimationProvider.h"
#include "System/AssetSystem/SkeletalMesh/SkeletalMeshProvider.h"
#include "System/AssetSystem/JsonFile/JsonFileProvider.h"
#include "System/AssetSystem/StaticMesh/StaticMeshProvider.h"
#include "System/AssetSystem/Audio/AudioProvider.h"
#include "System/Effekseer/EffectSystem.h"
#include "System/AssetSystem/Effect/EffekseerEffectProvider.h"
#include "System/FPSController/FPSController.h"
#include "ImGui/ImGuiUtility.h"

// デフォルトはtrue
bool Manager::mbActive = true;

void Manager::Initialize(Application* _app)
{
	// アセットマネージャーの初期化
	AssetManager& assetManager = AssetManager::GetInstance();
	assetManager.RegisterAssetProvider<BinaryFileProvider>();
	assetManager.RegisterAssetProvider<SkeletalMeshProvider>();
	assetManager.RegisterAssetProvider<SkeletalMeshAnimationProvider>();
	assetManager.RegisterAssetProvider<StaticMeshProvider>();
	assetManager.RegisterAssetProvider<JsonFileProvider>();
	assetManager.RegisterAssetProvider<AudioProvider>();
	assetManager.RegisterAssetProvider<EffekseerEffectProvider>();
	assetManager.RegisterAssetProvider<TextureProvider>();

	// レンダリングAPIの初期化
	Renderer::GetInstance().Initialize(_app);

	// レンダラーマネージャー初期化
	RendererManager::GetInstance().Init();
	
	// 入力機能の初期化
	Input::Init();
	XInput::Init();

	// Audio初期化
	AudioSystem::GetInstance().Initialize();

	// シーンマネージャーの初期化処理
	SceneManager::GetInstance().Init();
#ifdef _DEBUG
	SceneManager::GetInstance().SceneEntry<DebugScene>();
#else 
	SceneManager::GetInstance().SceneEntry<TitleScene>();
#endif

	// コリジョンシステムの初期化
	CollisionSystem::GetInstance().Init();

	// デバッグ機能の初期化
#ifdef _DEBUG
	 DebugRendererManager::GetInstance().Init();
#endif

	// エフェクトシステム初期化
	EffectSystem::GetInstance().Initialize();

	// ImGuiの初期化
	const HWND& windowHandle = _app->GetWindow();
	ImGuiUtility::GetInstance().Initialize(windowHandle);
}

void Manager::Uninitialize()
{
	/** ImGuiの終了処理 */
	ImGuiUtility::GetInstance().Uninitialize();

	// シーンマネージャーの終了処理
	SceneManager::GetInstance().Uninit();

	// レンダラーマネージャーの終了処理
	RendererManager::GetInstance().Uninit();

	// Audioの終了処理
	AudioSystem::GetInstance().Uninitialize();

	// レンダラーの終了
	Renderer::GetInstance().Uninitialize();
	
	// 生成したSingletonクラスの破棄
	SingletonFinalizer::Finalize();
}

void Manager::Update()
{
	// 入力の更新処理
	Input::Update();
	XInput::Update();

	// ImGuiの更新処理
	ImGuiUtility::GetInstance().Update();

	// FPSコントローラー更新処理
	FPSController::Update();

	// オーディオシステムの更新
	AudioSystem::GetInstance().Update();

	// シーンの更新処理
	SceneManager::GetInstance().Update();

	// コリジョンシステムの更新処理
	CollisionSystem::GetInstance().Update();

	// レンダリングマネージャーの更新処理
	RendererManager::GetInstance().Update();

	// デバッグ機能の初期化
#ifdef _DEBUG
	DebugRendererManager::GetInstance().Update();
#endif
}

void Manager::Draw()
{
	// 描画開始
	Renderer::GetInstance().BeginRenderer();

	// シーンの描画処理
	SceneManager::GetInstance().Draw();

	// 画面に描画
	RendererManager::GetInstance().Draw();

	// エフェクトの描画
	EffectSystem::GetInstance().Draw();
			
#ifdef _DEBUG
	// デバッグ描画
	DebugRendererManager::GetInstance().Draw();
#endif

	// ImGuiの描画処理
	ImGuiUtility::GetInstance().Draw();

	// 描画終了
	Renderer::GetInstance().EndRenderer();
}
