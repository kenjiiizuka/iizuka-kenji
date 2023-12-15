#include "Player.h"
#include "UI/PlayerHpBer.h"
#include "Animation/PlayerAnimationInstance.h"
#include "Weapon/PlayerWeapon.h"
#include "Animation/Notify/PlayerInputAbleNotifyState.h"
#include "PlayerCamera/PlayerCamera.h"
#include "../Camera/CameraManager.h"
#include "../Enemy/EnemyBase.h"
#include "../../Scene/Scene.h"
#include "../../Component/PlayerInputComponent/PlayerInputContollerComponent.h"
#include "../../Component/MoveComponent/PlayerMovementComponent.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Component/CollisionComponent/CapsuleCollisionComponent.h"
#include "../../Component/StaticMeshComponent/StaticMeshComponent.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"
#include "../../Component/HitStopComponent/PlayerHitStopComponent.h"
#include "../../Scene/SceneManager.h"
#include "../../Resource/SkeletalMeshAnimationClip.h"
#include "../../Resource/Skeleton.h"
#include "../../Resource/Socket.h"
#include "../../../System/InputSystem/XInput.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../System/RendererSystem/Shader/VertexShader/OutlineSkeletalMeshVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/OutlinePixelShader.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../../Manager.h"


using namespace DirectX::SimpleMath;
using namespace PlayerData;

Player::Player()
	: mHp(100.0f)
	, mCurrentHp(100.0f)
	, mbIsDeath(false)
	, mbIsBAttack(false)
	, mbIsYAttack(false)
	, mbIsAbleAttack(true)
	, mbBattleStart(false)
	, mCapsuleCollisionOffSet(Transform({ 0.f,4.0f,0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }))
	, mCapsuleCollisionHeight(2.8f)
	, mCapsuleCollisionRadius(1.6f)
	, mRollingButton(Pad::A)
	, mYAttackButton(Pad::Y)
	, mBAttackButton(Pad::B)
	, mHitReaction(CrossCharacter::HitReaction_None)
	, mStepAnimationInterpStartTime(0.0f)
	, mBehavior(State_IdleMove)
	, mStepAnimationClipName("Roll")
	, mStepToIdleRunInterpTime()
	, mLeftStepToIdleRunInterpTime()
	, mRightStepToIdleRunInterpTime()
	, mIdleRunInterpTime(0.0f)
	, mStepAnimationInterpTime(0.0f)
	, mNextAttackInterpStartTime(0.0f)
	, mNextAttackInterpTime(0.0f)
	
{
	// �����Ȃ�
}

Player::~Player()
{
	// �����Ȃ�
}

void Player::Init()
{		
	// �U�����̐ݒ�
	mAttackData = std::make_shared<PlayerAttackData>();
	mAttackData->Initialize();
	mCurrentAttack = mAttackData->GetAttack(AttackID_NoAttack);
	mCurrentAttack.mStepAnimationClipName = "Roll";
	mPrevAttack = mCurrentAttack;

	// �ړ��R���|�[�l���g�̐ݒ�
	SetupMoveComponent();

	// �X�P���^�����b�V���R���|�[�l���g�̐ݒ�
	SetupSkeletalMeshComponent();
	
	// �q�b�g�X�g�b�v�R���|�[�l���g
	mHitStopComp = AddComponent<PlayerHitStopComponent>();

	//  ����̐ݒ�
	SetupWeapon();

	// �R���W�����̐ݒ�
	SetupCollision();
	
	// �C���v�b�g�R���g���[���[�ǉ�
	mInputController = AddComponent<PlayerInputControllerComponent>();

	// HpBer�̐ݒ�
	std::shared_ptr<PlayerHpBer> hpBer = AddChildObject<PlayerHpBer>();
	hpBer->Init(mHp, mCurrentHp, { 50,600 }, { 250,35 });
	mHpBer = hpBer;

	// �X�e�[�g�Ǘ��N���X�ƃI�u�U�[�o�[�̏�����
	mStateObserver = std::make_shared<PlayerStateObserver>(this);	
	mStateController = std::make_shared<PlayerStateController>(mStateObserver, this);
	mStateObserver->Initialize(mStateController);
}

void Player::Update(const double _deltaTime)
{	
	// �퓬�J�n���Ă��Ȃ���Ώ��������Ȃ�
	if (!mbBattleStart)
	{
		return;
	}

	// �X�e�B�b�N�̓|��Ă���������v�Z����
	CalculateCameraAlignedLStickDirection();

	// ���݂̃X�e�[�g�m�F����
	CheckState();

	// �I�u�U�[�o�[�̍X�V �v���C���[�̃X�e�[�g���m�F���ĕK�v������΃X�e�[�g�؂�ւ�������
	mStateObserver->Update();

	// �X�e�[�g�R���g���[���[�̍X�V ���݂̃X�e�[�g�̏���������
	mStateController->UpdateState();
}

void Player::BeginHit(GameObject* _hitObject, PrimitiveComponent* _hitComponent)
{
	EnemyAttackCapsuleCollisionComponent* enemyAttackCollision = dynamic_cast<EnemyAttackCapsuleCollisionComponent*>(_hitComponent);
	if (enemyAttackCollision)
	{
		// �����������Ȃ�����C���^�[�t�F�[�X����Ȃ��Ă���������
		TakenDamage(enemyAttackCollision->GetDamage());

		// ���̍U���̃q�b�g���A�N�V�����̎擾
		mHitReaction = enemyAttackCollision->GetHitReaction();
	}
}

void Player::SetupMoveComponent()
{
	// �ړ��R���|�[�l���g�̒ǉ��Ƒ��x�̐ݒ�
	mMoveComp = AddComponent<PlayerMovementComponent>();
	mMoveComp.lock()->SetMaxSpeed(22.f);
	mMoveComp.lock()->SetFaceDirectionInterpSpeed(12.f);
}

void Player::SetupSkeletalMeshComponent()
{
	// SkeletalMeshComponent�̒ǉ��ƃ��f���̓ǂݍ���
	mMeshComp = AddComponent<SkeletalMeshComponent>();
	mMeshComp.lock()->Load("assets/Player/Model/Ninja.fbx");
	mMeshComp.lock()->SetRotation({ 0.0f,-3.14f,0.0f });
	mMeshComp.lock()->SetScale({ 0.04f });

	std::shared_ptr<SkeletalMesh> skeletalMesh = mMeshComp.lock()->GetSkeletalMesh().lock();
	std::shared_ptr<OutlineSkeletalMeshVertexShader> outlineVertexShader = skeletalMesh->AddVertexShader<OutlineSkeletalMeshVertexShader>();
	outlineVertexShader->SetSkeleton(skeletalMesh->GetSkeleton().lock());
	skeletalMesh->AddPixelShader<OutlinePixelShader>();
	skeletalMesh->SwapShader();
	skeletalMesh->SetDrawType(DrawType::Draw_SolidFront, 0);
	skeletalMesh->SetDrawType(DrawType::Draw_SolidBack, 1);

	// �A�j���[�V�����C���X�^���X�̍쐬
	mAnimInstance = mMeshComp.lock()->CreateAnimInstance<PlayerAnimationInstance>();
}

void Player::SetupWeapon()
{
	//�@������q�I�u�W�F�N�g�ɒǉ�
	mWeapon = AddChildObject<PlayerWeapon>();

	// ������A�^�b�`����p�̃\�P�b�g���쐬
	std::shared_ptr<Skeleton> skeleton = mMeshComp.lock()->GetSkeletalMesh().lock()->GetSkeleton().lock();
	Transform socketTrans =
	{
		{-8.0f,10.0f,0.0f},
		{1.4f,1.4f,1.4f},
		{0.0f,0.0f,4.7f}
	};
	std::shared_ptr<Socket> socket = skeleton->CreateSocket("mixamorig:RightHand", socketTrans, "SwordSocket");
	
	// ����̏�����
	mWeapon.lock()->Init("assets/Player/Weapon/Katana.fbx", socket, mMeshComp.lock()->GetSkeletalMesh().lock());
}

void Player::SetupCollision()
{
	// Collision�̐ݒ�
	std::shared_ptr<CapsuleCollisionComponent> capsuleCollision = AddComponent<CapsuleCollisionComponent>();
	capsuleCollision->Init(mCapsuleCollisionHeight, mCapsuleCollisionRadius);
	capsuleCollision->SetOffSetTransform(mCapsuleCollisionOffSet);
	capsuleCollision->SetDefaultColor({ 1.0f,1.0f,1.0f,1.0f });
	capsuleCollision->SetHitColor({ 0.0f,0.0f,1.0f,1.0f });
	capsuleCollision->SetCollisionChannel(Collision::Channel_Player);
	capsuleCollision->SetCollisionTypes(Collision::Channel_Static, Collision::Type_Block);
	capsuleCollision->SetCollisionTypes(Collision::Channel_EnemyAttack, Collision::Type_Overlap);

	// capsuleCollision->SetDebugDraw(true);

	mCollisionComp = capsuleCollision;
}

void Player::CheckState()
{
	// ���S���Ă�����X�e�[�g�̊m�F�����Ȃ�
	if (mBehavior == PlayerBehaviorState::State_Death)
	{
		return;
	}

	// ���݂̃X�e�[�g�����͉\�Ȃ̂����m�F����
	if (!mStateController->IsInputAble())
	{
		return;
	}

	// ��������s���邩���m�F����
	if (IsExecuteStep())
	{
		mBehavior = PlayerBehaviorState::State_Step;
		return;
	}

	// �U�������s���邩���m�F����
	if (IsExecuteAttack())
	{
		// ���̃t���O��܂�
		mBehavior = PlayerBehaviorState::State_Attack;
		return;
	}
}

bool Player::IsExecuteStep() const noexcept
{
	return mInputController.lock()->GetTrigger(PlayerInputControllerComponent::Operation_Step);
}

bool Player::IsExecuteAttack() noexcept
{
	if (!mbIsAbleAttack)
	{
		return false;
	}
	
	if (mInputController.lock()->GetTrigger(PlayerInputControllerComponent::Operation_AttackY))
	{
		mbIsYAttack = true;
		return true;
	}

	if (mInputController.lock()->GetTrigger(PlayerInputControllerComponent::Operation_AttackB))
	{
		mbIsBAttack = true;
		return true;
	}

	return false;
}

void Player::CalculateCameraAlignedLStickDirection()
{
	float camYaw = 0;

	std::weak_ptr<Scene> currentScene = SceneManager::GetInstance().GetCurrentScene();
	std::weak_ptr<PlayerCamera> playerCamera = currentScene.lock()->GetCameraManager()->GetCamera<PlayerCamera>("PlayerCamera");
	if (playerCamera.lock())
	{
		Vector3 cameraForward = playerCamera.lock()->GetComponent<TransformComponent>()->GetForwardVector();
		camYaw = playerCamera.lock()->GetComponent<TransformComponent>()->GetRotation().y;
	}
	// �^���ʂ̃x�N�g���Ƃ̍��������@// XZ���ʂł̊p�x�̍��������
	Vector3 fixRotation = { 0,camYaw,0 };
	Vector2 stick = XInput::GetPadLeftStick();
	mCameraAlignedLStickDirection = MathLibrary::RotateVector(Vector3(stick.x, 0, stick.y), fixRotation);
}

void Player::TakenDamage(float _damage)
{
	mCurrentHp -= _damage;	
	mHpBer.lock()->SetCurrentHp(mCurrentHp);
	
	// Hp��0�ȉ��Ȃ玀�S�t���O�𗧂Ă�
	if (mCurrentHp <= 0.0f)
	{
		mCurrentHp = 0.0f;
		mbIsDeath = true;
		mBehavior = PlayerBehaviorState::State_Death;
	}
	// Hp���c���Ă���Ȃ�q�b�g���A�N�V�����t���O�𗧂Ă�
	else
	{
		mBehavior = PlayerBehaviorState::State_HitReaction;
	}
}

std::weak_ptr<PlayerWeapon> Player::GetWeapon()
{
	return mWeapon;
}