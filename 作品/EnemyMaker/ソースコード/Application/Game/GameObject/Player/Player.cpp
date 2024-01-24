//-------- INCLUDES ----------
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
#include "../../../System/RendererSystem/Shader/VertexShader/OutlineSkeletalMeshVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/OutlinePixelShader.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "State/PlayerGuardState.h"
#include "../../../Manager.h"
#include "../../Component/AudioComponent/AudioComponent.h"
#include "../../Component/EffectComponent/EffectComponent.h"

using namespace DirectX::SimpleMath;
using namespace PlayerData;

Player::Player()
	: mMaxHp(100.0f)
	, mCurrentHp(100.0f)
	, mbIsDeath(false)
	, mbIsBAttack(false)
	, mbIsYAttack(false)
	, mbIsAbleAttack(true)
	, mbBattleStart(false)
	, mbIsGuardInput(false)
	, mCapsuleCollisionOffSet(Transform({ 0.f,4.0f,0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }))
	, mCapsuleCollisionHeight(2.8f)
	, mCapsuleCollisionRadius(1.6f)
	, mHitReaction(CrossCharacter::HitReaction_Small)
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
	, mCounterAbleTime(0.5f)
	, mJustGuardElapsedTime(0.0f)
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
	
	// �I�[�f�B�I�̐ݒ�
	SetupAudio();

	// �G�t�F�N�g�̐ݒ�
	SetupEffect();

	// �C���v�b�g�R���g���[���[�ǉ�
	mInputController = AddComponent<PlayerInputControllerComponent>();

	// HpBer�̐ݒ�
	std::shared_ptr<PlayerHpBer> hpBer = AddChildObject<PlayerHpBer>();
	hpBer->Init(mMaxHp, mCurrentHp, { 50,600 }, { 250,35 });
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

	if (mJustGuardElapsedTime <= mCounterAbleTime)
	{
		mJustGuardElapsedTime += _deltaTime;
		mMeshComp.lock()->GetSkeletalMesh().lock()->SetMaterialDiffuse({ 1,0,0,1 });
	}
}

void Player::BeginHit(GameObject* _hitObject, PrimitiveComponent* _hitComponent)
{
	EnemyAttackCapsuleCollisionComponent* enemyAttackCollision = dynamic_cast<EnemyAttackCapsuleCollisionComponent*>(_hitComponent);
	if (!enemyAttackCollision)
	{
		return;
	}
	float damage = enemyAttackCollision->GetDamage();

	// �J�E���^�[�U�����Ȃ�q�b�g���A�N�V��������炸�Ɍy�������_���[�W�������󂯂�
	if (mBehavior == PlayerBehaviorState::State_Counter)
	{
		damage *= 0.3f;
	}
	// �K�[�h���Ȃ�K�[�h���p�̃q�b�g����������
	else if (mBehavior == PlayerBehaviorState::State_Guard)
	{
		GuardingHit(damage, _hitComponent->GetTransform().mPosition, enemyAttackCollision->GetHitReaction());
	}
	// �K�[�h���łȂ��Ȃ�ʏ�̃q�b�g����
	else
	{
		// �q�b�g���A�N�V�����X�e�[�g�Ɉڍs
		mBehavior = PlayerBehaviorState::State_HitReaction;

		// ���̍U���̃q�b�g���A�N�V�����̎擾
		mHitReaction = enemyAttackCollision->GetHitReaction();

		// �ӂ��Ƃѕ����̌v�Z
		CalcuBlowVector(_hitComponent->GetTransform().mPosition);
	}
	
	// �_���[�W��Ⴄ
	TakenDamage(damage);

	// �q�b�g���A�N�V������̏ꍇ�̓J�����A�R���g���[���[�U��
	if (mHitReaction == CrossCharacter::HitReaction_Big)
	{
		XInput::Vibration(0.7f, XInput::mMaxVibration, XInput::mMaxVibration);
		SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->ShakeMainCamera({ 0.5f,0.5f }, 0.4f);
	}

	// �R���g���[���[�U������
	if (damage >= 13)
	{
		XInput::Vibration(0.18f, 2000 * damage, 2000 * damage);
	}	

	// Hp�����邩�m�F����
	CheckHP();
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
	skeletalMesh->SetDrawType(CullType::Draw_SolidFront, 0);
	skeletalMesh->SetDrawType(CullType::Draw_SolidBack, 1);

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
	mCollisionComp = capsuleCollision;
}

void Player::SetupAudio()
{
	// �K�[�h
	{
		std::shared_ptr<AudioComponent> guard = AddComponent<AudioComponent>();
		guard->Init("assets/Player/Audio/Guard.wav");
		mGuardAudio = guard;
	}

	// �W���X�g�K�[�h
	{
		std::shared_ptr<AudioComponent> justGuard = AddComponent<AudioComponent>();
		justGuard->Init("assets/Player/Audio/JustGuard_2.wav");
		mJustGuardAudio = justGuard;
	}
}

void Player::SetupEffect()
{
	// �K�[�h�G�t�F�N�g
	{
		std::shared_ptr<EffectComponent> effect = AddComponent<EffectComponent>();
		effect->Init("assets/Player/Effect/Guard.efkefc");
		mGuardEffect = effect;
	}

	// �W���X�K�G�t�F�N�g
	{
		std::shared_ptr<EffectComponent> effect = AddComponent<EffectComponent>();
		effect->Init("assets/Player/Effect/JustGuard.efkefc");
		mJustGuardEffect = effect;
	}
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

	// �J�E���^�[�����s���邩�m�F����
	if (IsExecuteCounter())
	{
		mBehavior = PlayerBehaviorState::State_Counter;
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
		mBehavior = PlayerBehaviorState::State_Attack;
		return;
	}

	// �K�[�h�����s���邩���m�F����
	if (IsExecuteGuard())
	{
		mBehavior = PlayerBehaviorState::State_Guard;
	}
}

PlayerData::GuardResult Player::CheckGuard(const DirectX::SimpleMath::Vector3 _hitCollisionPos, float& _damage)
{
	std::shared_ptr<PlayerGuardState> guardState = std::dynamic_pointer_cast<PlayerGuardState>(mStateController->GetState().lock());
	if (!guardState)
	{
		return GuardResult::Result_Faild;
	}

	// �K�[�h�̌��ʂ��擾
	return guardState->CheckGuard(_hitCollisionPos);	
}

void Player::GuardingHit(float& _damage, const DirectX::SimpleMath::Vector3 _hitPosition, const CrossCharacter::HitReaction _hitReaction)
{
	// �K�[�h�̌��ʂ��m�F���� 
	GuardResult result = GuardResult::Result_Faild;	
	result = CheckGuard(_hitPosition, _damage);

	// �ʏ�K�[�h
	if (result == GuardResult::Result_Guard)
	{
		_damage *= 0.5f;
		mGuardAudio.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 });
		DirectX::SimpleMath::Vector3 effectPosition = mTransform.lock()->GetPosition() + mTransform.lock()->GetForwardVector() * 1.0f;
		effectPosition.y = 4.0f;
		mGuardEffect.lock()->PlayEffect(effectPosition, { 1,1,1 }, mTransform.lock()->GetRotation().y);
	}
	// �W���X�g�K�[�h
	else if (result == GuardResult::Result_JustGuard)
	{
		_damage = 0.0f;
		mJustGuardAudio.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 });
		XInput::Vibration(0.7f, XInput::mMaxVibration, XInput::mMaxVibration);

	
		DirectX::SimpleMath::Vector3 effectPosition = mTransform.lock()->GetPosition() + mTransform.lock()->GetForwardVector() * 1.0f;
		effectPosition.y = 4.0f;
		mJustGuardEffect.lock()->PlayEffect(effectPosition, { 1,1,1 }, mTransform.lock()->GetRotation().y);

		// �W���X�K������J�E���^�[�\��Ԃ�
		mJustGuardElapsedTime = 0.0f;
	}	
	// �K�[�h�����s���Ă���΃q�b�g���A�N�V���������
	else if (result == GuardResult::Result_Faild)
	{
		mBehavior = PlayerBehaviorState::State_HitReaction;

		// ���̍U���̃q�b�g���A�N�V�����̎擾
		mHitReaction = _hitReaction;

		// �ӂ��Ƃѕ����̌v�Z
		CalcuBlowVector(_hitPosition);
	}
}

bool Player::IsExecuteStep() const noexcept
{
	return mInputController.lock()->IsInput(PlayerInputControllerComponent::Operation_Step);
}

bool Player::IsExecuteAttack() noexcept
{
	if (!mbIsAbleAttack)
	{
		return false;
	}
	
	if (mInputController.lock()->IsInput(PlayerInputControllerComponent::Operation_AttackY))
	{
		mbIsYAttack = true;
		return true;
	}

	if (mInputController.lock()->IsInput(PlayerInputControllerComponent::Operation_AttackB))
	{
		mbIsBAttack = true;
		return true;
	}

	return false;
}

bool Player::IsExecuteGuard() const noexcept
{
	return mInputController.lock()->IsInput(PlayerInputControllerComponent::Operation_Guard);
}

bool Player::IsExecuteCounter() const noexcept
{
	return (mJustGuardElapsedTime <= mCounterAbleTime) && mInputController.lock()->IsInput(PlayerInputControllerComponent::Operation_Counter);
}

void Player::CalculateCameraAlignedLStickDirection()
{
	float camYaw = 0;

	std::weak_ptr<Scene> currentScene = SceneManager::GetInstance().GetCurrentScene();
	std::weak_ptr<PlayerCamera> playerCamera = currentScene.lock()->GetCameraManager()->GetCameraByName<PlayerCamera>("PlayerCamera");
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
}

bool Player::CheckHP()
{
	// Hp��0�ȉ��Ȃ玀�S�t���O�𗧂Ă�
	if (mCurrentHp <= 0.0f)
	{
		mCurrentHp = 0.0f;
		mbIsDeath = true;
		mBehavior = PlayerBehaviorState::State_Death;
		XInput::Vibration(1.0f, 40000, 40000);
		return false;
	}
	return true;
}

void Player::CalcuBlowVector(const DirectX::SimpleMath::Vector3& _hitPosition)
{
	mBlowVector = mTransform.lock()->GetPosition() - _hitPosition;
}

void Player::HitReaction(CrossCharacter::HitReaction _hitReaction)
{
	float damage = 10.0f;

	// �K�[�h���Ȃ�K�[�h�ł��Ă��邩�m�F����
	GuardResult result = GuardResult::Result_Faild;
	if (mBehavior == PlayerBehaviorState::State_Guard)
	{
		result = CheckGuard(mTransform.lock()->GetForwardVector() + mTransform.lock()->GetPosition(), damage);

		// �ʏ�K�[�h
		if (result == GuardResult::Result_Guard)
		{
			damage *= 0.5f;
			mGuardAudio.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 });
			DirectX::SimpleMath::Vector3 effectPosition = mTransform.lock()->GetPosition() + mTransform.lock()->GetForwardVector() * 1.0f;
			effectPosition.y = 4.0f;
			mGuardEffect.lock()->PlayEffect(effectPosition, { 1,1,1 }, mTransform.lock()->GetRotation().y);
		}
		// �W���X�g�K�[�h
		else if (result == GuardResult::Result_JustGuard)
		{
			damage = 0.0f;
			mJustGuardAudio.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 });
			XInput::Vibration(0.7f, XInput::mMaxVibration, XInput::mMaxVibration);

			DirectX::SimpleMath::Vector3 effectPosition = mTransform.lock()->GetPosition() + mTransform.lock()->GetForwardVector() * 1.0f;
			effectPosition.y = 4.0f;
			mJustGuardEffect.lock()->PlayEffect(effectPosition, { 1,1,1 }, mTransform.lock()->GetRotation().y);

			// �W���X�K������J�E���^�[�\��Ԃ�
			mJustGuardElapsedTime = 0.0f;
		}
	}

	// �����������Ȃ�����C���^�[�t�F�[�X����Ȃ��Ă���������
	TakenDamage(damage);

	// �K�[�h�����s���Ă���΃q�b�g���A�N�V���������
	if (result == GuardResult::Result_Faild)
	{
		mBehavior = PlayerBehaviorState::State_HitReaction;

		// ���̍U���̃q�b�g���A�N�V�����̎擾
		mHitReaction = _hitReaction;
	}

	// �R���g���[���[�U������
	if (damage >= 13)
	{
		XInput::Vibration(0.18f, 2000 * damage, 2000 * damage);
	}

	CheckHP();
}

std::weak_ptr<PlayerWeapon> Player::GetWeapon()
{
	return mWeapon;
}

void Player::Death_debug()
{
	TakenDamage(100);
	CheckHP();
}
