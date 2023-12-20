//-------- INCLUDES ---------
#include "BattleManager.h"
#include "GameScene.h"
#include "BattleSoundManager.h"
#include "../TitleScene/TitleScene.h"
#include "../SceneManager.h"
#include "../../GameObject/WinLogo/WinLogo.h"
#include "../../GameObject/LoseLogo/LoseLogo.h"
#include "../../GameObject/BattleStartLogo/BattleStartLogo.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Enemy/EnemyBase.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../../System/FPSController/FPSController.h"

BattleManager::BattleManager()
	: mState(Battle_Start)
	, mBattleElapsedTime(0.0f)
	, mResult(Result_InProgress)
{
	// �����Ȃ�
}

BattleManager::~BattleManager()
{
	// �����Ȃ�
}

void BattleManager::Initialize(const std::shared_ptr<Player> _player, const std::shared_ptr<EnemyBase> _enemy)
{
	mPlayer = _player;
	mEnemy = _enemy;

	// �o�g���J�n�X�e�[�g�������o�C���h	
	mCurrentStateUpdate = std::bind(&BattleManager::StartStateUpdate, this);
	mStartLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<BattleStartLogo>(ELayer::ObjectLayer);

	// �T�E���h�}�l�[�W���[�𐶐�
	mBattleSoundManager = std::make_shared<BattleSoundManager>();
	mBattleSoundManager->Initialize();
}

void BattleManager::Update()
{
	mBattleSoundManager->Update();

	mCurrentStateUpdate();
}

void BattleManager::StartStateUpdate()
{
	if (!mStartLogo.lock()->IsAnimationFinish())
	{	
		return;
	}

	// �v���C���[�ƃG�l�~�[�ɐ퓬�J�n��ʒm����
	mPlayer.lock()->BattleStart();
	mEnemy.lock()->BattleStart();
	mStartLogo.lock()->SetActive(false);

	// �퓬BGM���Đ�����
	mBattleSoundManager->PlayBattleBGM();

	TransitionState
	(
		std::bind(&BattleManager::BattleStateUpdate, this),
		Battle_InProgress
	);
}

void BattleManager::BattleStateUpdate()
{
	// �퓬���Ԃ��v��
	mBattleElapsedTime += FPSController::GetDeltaTime();

	// ���U���g�ւ̑J�ڂ̃`�F�b�N
	mResult = CheckBattleResult();
	// ���s��������Result�X�e�[�g�ɑJ��
	if (mResult != BattleResult::Result_InProgress)
	{
		TransitionState
		(
			std::bind(&BattleManager::ResultStateUpdate, this),
			Battle_Result
		);

		// BGM���~�߂�
		mBattleSoundManager->StopBattleBGM();
	}
}

void BattleManager::ResultStateUpdate()
{
	// ���U���g�ɉ������퓬�I������
	// �s�k����
	if (mResult == Result_Lose)
	{
		mEnemy.lock()->BattleEnd();
		LoseUpdate();
	}
	// ��������
	else if(mResult == Result_Win)
	{
		WinUpdate();
	}
	
}

void BattleManager::TransitionState(std::function<void()> _stateFunc, const BattleState _state)
{
	mCurrentStateUpdate = _stateFunc;
	mState = _state;
}

BattleManager::BattleResult BattleManager::CheckBattleResult()
{
	// �v���C���[�ƃG�l�~�[��Hp���݂ď��s�𔻒f����
	// �����t���[���Ȃ��œ�����Hp��0�ɂȂ����ꍇ�̓v���C���[�̏�����D�悷��
	if (!mEnemy.lock()->IsAlive())
	{	
		mResultLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<WinLogo>(ELayer::ObjectLayer);
		return BattleResult::Result_Win;
	}
	else if (!mPlayer.lock()->IsAlive())
	{	
		mResultLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<LoseLogo>(ELayer::ObjectLayer);	
		return BattleResult::Result_Lose;
	}

	return BattleResult::Result_InProgress;
}

void BattleManager::LoseUpdate()
{
	std::shared_ptr<LoseLogo> logo = std::static_pointer_cast<LoseLogo>(mResultLogo.lock());
	if (!logo->IsAnimationFinish())
	{
		return;
	}

	// �Ȃɂ��{�^���������ꂽ��^�C�g���V�[���ɂ���
	if (XInput::GetPressAnyKey())
	{
		SceneManager::GetInstance().SceneEntry<TitleScene>();
	}
}

void BattleManager::WinUpdate()
{
	std::shared_ptr<WinLogo> logo = std::static_pointer_cast<WinLogo>(mResultLogo.lock());
	if (!logo->IsAnimationFinish())
	{
		return;
	}

	// �Ȃɂ��{�^���������ꂽ��^�C�g���V�[���ɂ���
	if (XInput::GetPressAnyKey())
	{
		SceneManager::GetInstance().SceneEntry<TitleScene>();
	}
}
