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
	// 処理なし
}

Player::~Player()
{
	// 処理なし
}

void Player::Init()
{		
	// 攻撃情報の設定
	mAttackData = std::make_shared<PlayerAttackData>();
	mAttackData->Initialize();
	mCurrentAttack = mAttackData->GetAttack(AttackID_NoAttack);
	mCurrentAttack.mStepAnimationClipName = "Roll";
	mPrevAttack = mCurrentAttack;

	// 移動コンポーネントの設定
	SetupMoveComponent();

	// スケルタルメッシュコンポーネントの設定
	SetupSkeletalMeshComponent();
	
	// ヒットストップコンポーネント
	mHitStopComp = AddComponent<PlayerHitStopComponent>();

	//  武器の設定
	SetupWeapon();

	// コリジョンの設定
	SetupCollision();
	
	// インプットコントローラー追加
	mInputController = AddComponent<PlayerInputControllerComponent>();

	// HpBerの設定
	std::shared_ptr<PlayerHpBer> hpBer = AddChildObject<PlayerHpBer>();
	hpBer->Init(mHp, mCurrentHp, { 50,600 }, { 250,35 });
	mHpBer = hpBer;

	// ステート管理クラスとオブザーバーの初期化
	mStateObserver = std::make_shared<PlayerStateObserver>(this);	
	mStateController = std::make_shared<PlayerStateController>(mStateObserver, this);
	mStateObserver->Initialize(mStateController);
}

void Player::Update(const double _deltaTime)
{	
	// 戦闘開始していなければ処理をしない
	if (!mbBattleStart)
	{
		return;
	}

	// スティックの倒れている方向を計算する
	CalculateCameraAlignedLStickDirection();

	// 現在のステート確認する
	CheckState();

	// オブザーバーの更新 プレイヤーのステートを確認して必要があればステート切り替えをする
	mStateObserver->Update();

	// ステートコントローラーの更新 現在のステートの処理をする
	mStateController->UpdateState();
}

void Player::BeginHit(GameObject* _hitObject, PrimitiveComponent* _hitComponent)
{
	EnemyAttackCapsuleCollisionComponent* enemyAttackCollision = dynamic_cast<EnemyAttackCapsuleCollisionComponent*>(_hitComponent);
	if (enemyAttackCollision)
	{
		// 処理が多くないからインターフェースつかわなくてもいいかも
		TakenDamage(enemyAttackCollision->GetDamage());

		// この攻撃のヒットリアクションの取得
		mHitReaction = enemyAttackCollision->GetHitReaction();
	}
}

void Player::SetupMoveComponent()
{
	// 移動コンポーネントの追加と速度の設定
	mMoveComp = AddComponent<PlayerMovementComponent>();
	mMoveComp.lock()->SetMaxSpeed(22.f);
	mMoveComp.lock()->SetFaceDirectionInterpSpeed(12.f);
}

void Player::SetupSkeletalMeshComponent()
{
	// SkeletalMeshComponentの追加とモデルの読み込み
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

	// アニメーションインスタンスの作成
	mAnimInstance = mMeshComp.lock()->CreateAnimInstance<PlayerAnimationInstance>();
}

void Player::SetupWeapon()
{
	//　武器を子オブジェクトに追加
	mWeapon = AddChildObject<PlayerWeapon>();

	// 武器をアタッチする用のソケットを作成
	std::shared_ptr<Skeleton> skeleton = mMeshComp.lock()->GetSkeletalMesh().lock()->GetSkeleton().lock();
	Transform socketTrans =
	{
		{-8.0f,10.0f,0.0f},
		{1.4f,1.4f,1.4f},
		{0.0f,0.0f,4.7f}
	};
	std::shared_ptr<Socket> socket = skeleton->CreateSocket("mixamorig:RightHand", socketTrans, "SwordSocket");
	
	// 武器の初期化
	mWeapon.lock()->Init("assets/Player/Weapon/Katana.fbx", socket, mMeshComp.lock()->GetSkeletalMesh().lock());
}

void Player::SetupCollision()
{
	// Collisionの設定
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
	// 死亡していたらステートの確認をしない
	if (mBehavior == PlayerBehaviorState::State_Death)
	{
		return;
	}

	// 現在のステートが入力可能なのかを確認する
	if (!mStateController->IsInputAble())
	{
		return;
	}

	// 回避を実行するかを確認する
	if (IsExecuteStep())
	{
		mBehavior = PlayerBehaviorState::State_Step;
		return;
	}

	// 攻撃を実行するかを確認する
	if (IsExecuteAttack())
	{
		// 他のフラグを折る
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
	// 真正面のベクトルとの差分を取る　// XZ平面での角度の差分を取る
	Vector3 fixRotation = { 0,camYaw,0 };
	Vector2 stick = XInput::GetPadLeftStick();
	mCameraAlignedLStickDirection = MathLibrary::RotateVector(Vector3(stick.x, 0, stick.y), fixRotation);
}

void Player::TakenDamage(float _damage)
{
	mCurrentHp -= _damage;	
	mHpBer.lock()->SetCurrentHp(mCurrentHp);
	
	// Hpが0以下なら死亡フラグを立てる
	if (mCurrentHp <= 0.0f)
	{
		mCurrentHp = 0.0f;
		mbIsDeath = true;
		mBehavior = PlayerBehaviorState::State_Death;
	}
	// Hpが残っているならヒットリアクションフラグを立てる
	else
	{
		mBehavior = PlayerBehaviorState::State_HitReaction;
	}
}

std::weak_ptr<PlayerWeapon> Player::GetWeapon()
{
	return mWeapon;
}