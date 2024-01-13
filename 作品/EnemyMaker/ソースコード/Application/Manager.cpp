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

// �f�t�H���g��true
bool Manager::mbActive = true;

void Manager::Initialize(Application* _app)
{
	// �A�Z�b�g�}�l�[�W���[�̏�����
	AssetManager& assetManager = AssetManager::GetInstance();
	assetManager.RegisterAssetProvider<BinaryFileProvider>();
	assetManager.RegisterAssetProvider<SkeletalMeshProvider>();
	assetManager.RegisterAssetProvider<SkeletalMeshAnimationProvider>();
	assetManager.RegisterAssetProvider<StaticMeshProvider>();
	assetManager.RegisterAssetProvider<JsonFileProvider>();
	assetManager.RegisterAssetProvider<AudioProvider>();
	assetManager.RegisterAssetProvider<EffekseerEffectProvider>();
	assetManager.RegisterAssetProvider<TextureProvider>();

	// �����_�����OAPI�̏�����
	Renderer::GetInstance().Initialize(_app);

	// �����_���[�}�l�[�W���[������
	RendererManager::GetInstance().Init();
	
	// ���͋@�\�̏�����
	Input::Init();
	XInput::Init();

	// Audio������
	AudioSystem::GetInstance().Initialize();

	// �V�[���}�l�[�W���[�̏���������
	SceneManager::GetInstance().Init();
#ifdef _DEBUG
	SceneManager::GetInstance().SceneEntry<DebugScene>();
#else 
	SceneManager::GetInstance().SceneEntry<TitleScene>();
#endif

	// �R���W�����V�X�e���̏�����
	CollisionSystem::GetInstance().Init();

	// �f�o�b�O�@�\�̏�����
#ifdef _DEBUG
	 DebugRendererManager::GetInstance().Init();
#endif

	// �G�t�F�N�g�V�X�e��������
	EffectSystem::GetInstance().Initialize();

	// ImGui�̏�����
	const HWND& windowHandle = _app->GetWindow();
	ImGuiUtility::GetInstance().Initialize(windowHandle);
}

void Manager::Uninitialize()
{
	/** ImGui�̏I������ */
	ImGuiUtility::GetInstance().Uninitialize();

	// �V�[���}�l�[�W���[�̏I������
	SceneManager::GetInstance().Uninit();

	// �����_���[�}�l�[�W���[�̏I������
	RendererManager::GetInstance().Uninit();

	// Audio�̏I������
	AudioSystem::GetInstance().Uninitialize();

	// �����_���[�̏I��
	Renderer::GetInstance().Uninitialize();
	
	// ��������Singleton�N���X�̔j��
	SingletonFinalizer::Finalize();
}

void Manager::Update()
{
	// ���͂̍X�V����
	Input::Update();
	XInput::Update();

	// ImGui�̍X�V����
	ImGuiUtility::GetInstance().Update();

	// FPS�R���g���[���[�X�V����
	FPSController::Update();

	// �I�[�f�B�I�V�X�e���̍X�V
	AudioSystem::GetInstance().Update();

	// �V�[���̍X�V����
	SceneManager::GetInstance().Update();

	// �R���W�����V�X�e���̍X�V����
	CollisionSystem::GetInstance().Update();

	// �����_�����O�}�l�[�W���[�̍X�V����
	RendererManager::GetInstance().Update();

	// �f�o�b�O�@�\�̏�����
#ifdef _DEBUG
	DebugRendererManager::GetInstance().Update();
#endif
}

void Manager::Draw()
{
	// �`��J�n
	Renderer::GetInstance().BeginRenderer();

	// �V�[���̕`�揈��
	SceneManager::GetInstance().Draw();

	// ��ʂɕ`��
	RendererManager::GetInstance().Draw();

	// �G�t�F�N�g�̕`��
	EffectSystem::GetInstance().Draw();
			
#ifdef _DEBUG
	// �f�o�b�O�`��
	DebugRendererManager::GetInstance().Draw();
#endif

	// ImGui�̕`�揈��
	ImGuiUtility::GetInstance().Draw();

	// �`��I��
	Renderer::GetInstance().EndRenderer();
}
