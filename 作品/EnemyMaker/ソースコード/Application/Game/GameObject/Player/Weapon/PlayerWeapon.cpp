//---------- INCLUDES -----------
#include "PlayerWeapon.h"
#include "../Player.h"
#include "../../Enemy/EnemyBase.h"
#include "../../../Component/TransformComponent/TransformComponent.h"
#include "../../../Component/CollisionComponent/PlayerAttackCapsuleCollisionComponent.h"
#include "../../../../System/InputSystem/Input.h"
#include "../../../../System/FPSController/FPSController.h"
#include "../../../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"
#include "../../../Component/HitStopComponent/PlayerHitStopComponent.h"
#include "../../../Component/AudioComponent/AudioComponent.h"
#include "../../../Component/EffectComponent/EffectComponent.h"
#include "../../../../System/InputSystem/XInput.h"
#include "../../Camera/CameraIncludes.h"
#include "../../../../ImGui/ImGuiUtility.h"

PlayerWeapon::PlayerWeapon()
	: mPlayer(nullptr)
	, mCapsuleHeight(2.7f)
	, mCapsuleRadius(0.7f)
	, mCounterHitElapsedTime(0.0f)
	, mExecuteCounterEffectTime(0.1f)
	, mbHitCounter(false)
	, mCounterCameraShakeTime(0.1f)
	, mCounterVibrationPower(50000)
	, mCounterVibrationTime(0.2f)
{
	// �����Ȃ�
}

void PlayerWeapon::Init(const std::string& _filePath, std::shared_ptr<Bone> _attachBone, std::shared_ptr<SkeletalMesh> _skeletalMesh)
{	
	Weapon::Init(_filePath, _attachBone, _skeletalMesh);

	mPlayer = static_cast<Player*>(mParent);

	// �����蔻��̐ݒ�
	mCollisionOffsetTransform = Transform({ 0.f,87.0f,0 }, { 1,1,1 }, { 0,0,0 });
	std::shared_ptr<PlayerAttackCapsuleCollisionComponent> collision = AddComponent<PlayerAttackCapsuleCollisionComponent>();
	collision->Init(mCapsuleHeight,mCapsuleRadius, 0.0f);
	collision->SetOffSetTransform(mCollisionOffsetTransform);

 	collision->SetDebugDraw(true);

	// �����蔻��̃��C���[�ݒ�
	collision->SetCollisionChannel(Collision::Channel_PlayerAttack);
	CollisionTypes collisionTypes;
	collisionTypes[Collision::Channel_Player] = Collision::Type_None;
	collisionTypes[Collision::Channel_Enemy] = Collision::Type_Overlap;
	collisionTypes[Collision::Channel_EnemyAttack] = Collision::Type_None;
	collisionTypes[Collision::Channel_Movable] = Collision::Type_None;
	collisionTypes[Collision::Channel_Static] = Collision::Type_None;
	collision->SetCollisionTypes(collisionTypes);

	mCapsuleCollision = collision;

	// �q�b�g�G�t�F�N�g
	{
		std::shared_ptr<EffectComponent> effect = AddComponent<EffectComponent>();
		effect->Init("assets/Player/Effect/HitEffect.efkefc");
		mHitEffect = effect;
	}

	// �J�E���^�[�G�t�F�N�g
	{
		std::shared_ptr<EffectComponent> effect = AddComponent<EffectComponent>();
		effect->Init("assets/Player/Effect/Counter.efkefc");
		mCounterEffect = effect;
	}

	// �ʏ�q�b�gSE
	{
		std::shared_ptr<AudioComponent> hitSE = AddComponent<AudioComponent>();
		hitSE->Init("assets/Player/Audio/Hit.wav");
		mHitSE = hitSE;
	}

	// �J�E���^�[SE
	{
		std::shared_ptr<AudioComponent> se = AddComponent<AudioComponent>();
		se->Init("assets/Player/Audio/Counter_2.wav");
		mCounterSE = se;
	}
}

void PlayerWeapon::Update(const double _deltaTime)
{
	Weapon::Update(_deltaTime);

	// �J�E���^�[���q�b�g���Ă������̏���
	if (!mbHitCounter)
	{
		return;
	}

	if (mCounterHitElapsedTime >= mExecuteCounterEffectTime)
	{
		CounterEffect();
		mbHitCounter = false;
	}

	mCounterHitElapsedTime += _deltaTime;
}

void PlayerWeapon::BeginHit(GameObject* _hitObject, PrimitiveComponent* _hitComp)
{
	// �R���W�����������ɂȂ��Ă���Ώ������Ȃ�
	if (!mCapsuleCollision.lock()->IsActiveCollision())
	{
		return;
	}

	// �J�E���^�[�Ȃ̂����f����
	bool isCounter = mPlayer->GetCurrentAttackID() == PlayerData::AttackID_Counter;

	// �J�E���^�[�p�̏���
	if (isCounter)
	{
		mbHitCounter = true;
		mCounterEffectPosition = _hitComp->GetImpactPosition();
		mCounterHitElapsedTime = 0.0f;
	}
	// �ʏ�U���̏���
	else
	{
		// �q�b�g�G�t�F�N�g
		mHitEffect.lock()->PlayEffect(_hitComp->GetImpactPosition());
		// ���������u�Ԃɉ���炷
		Transform trans = _hitComp->GetTransform();
		mHitSE.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 }, 1.0f);
	}

	// �_���[�W�̎擾
	float damage = mPlayer->GetCurrentAttackDamage();

	// �q�b�g�X�g�b�v��������
	mPlayer->GetHitStopComponent().lock()->SetAttackDamage(damage);
	mPlayer->GetHitStopComponent().lock()->HitStop(isCounter);

	// �A���œ����邱�Ƃ�h�����߂ɃR���W�������I�t�ɂ���
	mCapsuleCollision.lock()->SetActiveCollision(false);

	// �G�l�~�[�Ȃ�_���[�W��`����
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(_hitObject);
	if (!enemy)
	{
		return;
	}

	// �G�Ƀ_���[�W��^����
	enemy->TakenDamage(damage, _hitComp->GetImpactPosition());
}

void PlayerWeapon::CounterEffect()
{
	XInput::Vibration(0.2f, 50000, 50000);
	SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->GetMainCamera()->CameraShake(1, { 0.7f,1.0f }, 0.5);
	mCounterEffect.lock()->PlayEffect(mCounterEffectPosition, { 2,2,2 });
	mCounterSE.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 }, 1.0f);
}

void PlayerWeapon::SetCapsuleCollisionSize(const float _height, const float _radius)
{
	mCapsuleCollision.lock()->SetHeight(_height);
	mCapsuleCollision.lock()->SetRadius(_radius);
}

void PlayerWeapon::SetDefaultCapsuleCollisionSize()
{
	mCapsuleCollision.lock()->SetHeight(mCapsuleHeight);
	mCapsuleCollision.lock()->SetRadius(mCapsuleRadius);
}


void PlayerWeapon::Edit()
{
	ImGuiUtility& imgui = ImGuiUtility::GetInstance();

	ImGui::Begin("Weapon");

	ImGui::InputFloat("CounterVibrationTime", &mCounterVibrationTime);
	imgui.InputInt("CounterVibrationPower", mCounterVibrationPower);
	ImGui::InputFloat("CounterCameraShakeTime", &mCounterCameraShakeTime);
	imgui.InputVector2("CounterCameraShakeVector", mCameraShakeVector);

	float effectTime = static_cast<float>(mExecuteCounterEffectTime);
	ImGui::InputFloat("CounterEffectDelayTime", &effectTime);
	mExecuteCounterEffectTime = static_cast<double>(effectTime);

	ImGui::End();
}