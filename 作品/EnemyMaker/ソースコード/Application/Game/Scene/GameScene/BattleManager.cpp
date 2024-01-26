//-------- INCLUDES ---------
#include "BattleManager.h"
#include "GameScene.h"
#include "../TitleScene/TitleScene.h"
#include "../SceneManager.h"
#include "../../GameObject/WinLogo/WinLogo.h"
#include "../../GameObject/LoseLogo/LoseLogo.h"
#include "../../GameObject/BattleStartLogo/BattleStartLogo.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Enemy/EnemyBase.h"
#include "../../GameObject/Camera/CameraIncludes.h"
#include "../../GameObject/BattleTimer/BattleTimer.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Resource/SkeletalMesh.h"
#include "../../Resource/Skeleton.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../../System/FPSController/FPSController.h"
#include "../../Component/AudioComponent/AudioComponent.h"

BattleManager::BattleManager()
	: mState(Battle_Start)
	, mBattleTimeSec(300.0f)
	, mResult(Result_InProgress)
{
	// �����Ȃ�
}

BattleManager::~BattleManager()
{
	// �����Ȃ�
}

void BattleManager::Init(const std::shared_ptr<Player> _player, const std::shared_ptr<EnemyBase> _enemy)
{
	mPlayer = _player;
	mEnemy = _enemy;

	// �o�g���^�C�}�[�ǉ�
	mBattleTimer = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<BattleTimer>();
	mBattleTimer.lock()->Init(mBattleTimeSec);

	// �o�g���J�n�X�e�[�g�������o�C���h	
	mCurrentStateUpdate = std::bind(&BattleManager::StartStateUpdate, this);

	// �J�n���S�ǉ�
	mStartLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<BattleStartLogo>();

	// BGM,SE�̏�����	
	std::shared_ptr<AudioComponent> battleBGM = AddComponent<AudioComponent>();
	battleBGM->Init("assets/Battle/Audio/Battle.wav",true);
	mBattleBGM = battleBGM;

	std::shared_ptr<AudioComponent> clear = AddComponent<AudioComponent>();
	clear->Init("assets/Battle/Audio/WinningBGM.wav");
	mClearSE = clear;

	std::shared_ptr<AudioComponent> lose = AddComponent<AudioComponent>();
	lose->Init("assets/Battle/Audio/LosingBGM.wav");
	mLoseSE = lose;
}

void BattleManager::Update(const double _deltaTime)
{
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

	// �J�n���S����
	mStartLogo.lock()->SetActive(false);
	
	// �^�C�}�[�v���J�n
	mBattleTimer.lock()->TimerStart();

	// �퓬BGM���Đ�����
	mBattleBGM.lock()->PlaySound2D(0.1f, true, 5.0);

	TransitionState
	(
		std::bind(&BattleManager::BattleStateUpdate, this),
		Battle_InProgress
	);
}

void BattleManager::BattleStateUpdate()
{
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
		mBattleBGM.lock()->Stop();
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
		// CinematicCamera�̐����ƍĐ�
		mResultCamera =  SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->CreateCamera<CinematicCamera>("DeathCamera");
		mResultCamera.lock()->Init("assets/Enemy/Config/DeathCamera.json");

		// �{�[���̃Z�b�g
		std::shared_ptr<SkeletalMesh> mesh = mEnemy.lock()->GetComponent<SkeletalMeshComponent>()->GetSkeletalMesh().lock();
		mResultCamera.lock()->SetTargetBone(mesh->GetSkeleton().lock()->GetBoneByName("mixamorig:Head").lock());

		// �^�C�}�[��~
		mBattleTimer.lock()->TimerStop();
	
		// �Đ�
		mResultCamera.lock()->Play();

		// �N���ASE�Đ�
		mClearSE.lock()->PlaySound2D(0.5f,true, 1.0);

		return BattleResult::Result_Win;
	}
	// �v���C���[�����S or �������Ԃ��Ȃ��ȂƔs�k
	else if (!mPlayer.lock()->IsAlive() || mBattleTimer.lock()->IsTimerEnd())
	{	
		// CinematicCamera�̐����ƍĐ�
		mResultCamera = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->CreateCamera<CinematicCamera>("DeathCamera");
		mResultCamera.lock()->Init("assets/Player/Config/DeathCamera.json");

		// �{�[���̃Z�b�g
		std::shared_ptr<SkeletalMesh> mesh = mPlayer.lock()->GetComponent<SkeletalMeshComponent>()->GetSkeletalMesh().lock();
		mResultCamera.lock()->SetTargetBone(mesh->GetSkeleton().lock()->GetBoneByName("mixamorig:Head").lock());

		// �Đ�
		mResultCamera.lock()->Play();

		// �^�C�}�[��~
		mBattleTimer.lock()->TimerStop();

		// �s�kSE�Đ�
		mLoseSE.lock()->PlaySound2D(0.5f, true, 1.0);

		return BattleResult::Result_Lose;
	}

	return BattleResult::Result_InProgress;
}

void BattleManager::LoseUpdate()
{
	std::shared_ptr<CinematicCamera> camera = mResultCamera.lock();
	if (camera->GetCurrentPlayTime() < camera->GetDuration() * 0.5f)
	{
		return;
	}

	// ���U���g���S�̐���
	if (!mResultLogo.lock())
	{
		mResultLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<LoseLogo>();
	}

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
	std::shared_ptr<CinematicCamera> camera = mResultCamera.lock();
	if (camera->GetCurrentPlayTime() < camera->GetDuration() * 0.5f )
	{
		return;
	}

	// ���U���g���S�̐���
	if (!mResultLogo.lock())
	{
		mResultLogo = SceneManager::GetInstance().GetCurrentScene().lock()->AddGameObject<WinLogo>();
	}
	
	// �A�j���[�V�����I���Ɠ����ɃN���A�^�C���\��
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
