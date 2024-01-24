//---------- INCLUDES ---------
#include "GameScene.h"
#include "../TitleScene/TitleScene.h"
#include "../SceneManager.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../../System/CollisionSystem/CollisionSystem.h"
#include "../../../System/AudioSystem/AudioSystemIncludes.h"
#include "../../GameObject/Field/Field.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Player/PlayerCamera/PlayerCamera.h"
#include "../../GameObject/Camera/CameraManager.h"
#include "../../GameObject/Enemy/Bear/BearEnemy.h"
#include "../../GameObject/CircleBlockObject/CircleBlockObject.h"
#include "../../GameObject/Fade/Fade.h"


GameScene::GameScene()
	: mbTransitionScene(false)
{
	// �����Ȃ�
}

GameScene::~GameScene()
{
	// �����Ȃ�
}

void GameScene::Initialize()
{
	// �v���C���[�̐���
	std::shared_ptr<Player> player = AddGameObject<Player>();
	std::weak_ptr<TransformComponent> playerTrans = player->GetComponent<TransformComponent>();
	player->SetPosition({ 100,0,70 });

	// �Ǐ]�J�����̐���
	std::shared_ptr<PlayerCamera> playerCamera = mpCameraManager->CreateCamera<PlayerCamera>("PlayerCamera");
	mpCameraManager->SetMainCameraByName("PlayerCamera");
	playerCamera->Init(player);

	// �G�l�~�[�̍쐬
	std::shared_ptr<BearEnemy> enemy = AddGameObject<BearEnemy>();
	enemy->SetPosition({ 100.f,0.f,100.f });
	enemy->SetRotation({ 0.0f,3.14f,0.0f });

	// �퓬�G���A�O�ɍs���Ȃ��悤�ɃT�[�N���^�̃I�u�W�F�N�g�̍쐬
	AddGameObject<CircleBlockObject>();

	// �R���W�������I��
	CollisionSystem::GetInstance().SwitchActive(true);

	// �o�g���}�l�[�W���[�̐���	
	mBattleManager = AddGameObject<BattleManager>();
	mBattleManager.lock()->Init(player, enemy);

	// �t�F�[�h�C�����I��܂ł͔�A�N�e�B�u
	mBattleManager.lock()->SetActive(false);

	// �t�B�[���h�̍쐬
	AddGameObject<Field>();

	// �t�F�[�h�I�u�W�F�N�g����
	mFade = AddGameObject<Fade>();
	mFade.lock()->FadeIn();

	// ���̃V�[���̃I�[�f�B�I���X�i�[��ݒ�
	AudioSystem::GetInstance().GetAudioListenerObject().lock()->SwitchListenerObject(player);
	
}

void GameScene::Update()
{
	// �t�F�[�h���͏��������Ȃ�
	if (mFade.lock()->IsFading())
	{
		return;
	}

	mBattleManager.lock()->SetActive(true);
	if (mbTransitionScene)
	{
		SceneManager::GetInstance().SceneEntry<TitleScene>();
	}
}
