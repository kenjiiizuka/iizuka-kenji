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
	
	// オーディオの設定
	SetupAudio();

	// エフェクトの設定
	SetupEffect();

	// インプットコントローラー追加
	mInputController = AddComponent<PlayerInputControllerComponent>();

	// HpBerの設定
	std::shared_ptr<PlayerHpBer> hpBer = AddChildObject<PlayerHpBer>();
	hpBer->Init(mMaxHp, mCurrentHp, { 50,600 }, { 250,35 });
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

	// カウンター攻撃中ならヒットリアクションを取らずに軽減したダメージだけを受ける
	if (mBehavior == PlayerBehaviorState::State_Counter)
	{
		damage *= 0.3f;
	}
	// ガード中ならガード中用のヒット処理をする
	else if (mBehavior == PlayerBehaviorState::State_Guard)
	{
		GuardingHit(damage, _hitComponent->GetTransform().mPosition, enemyAttackCollision->GetHitReaction());
	}
	// ガード中でないなら通常のヒット処理
	else
	{
		// ヒットリアクションステートに移行
		mBehavior = PlayerBehaviorState::State_HitReaction;

		// この攻撃のヒットリアクションの取得
		mHitReaction = enemyAttackCollision->GetHitReaction();

		// ふっとび方向の計算
		CalcuBlowVector(_hitComponent->GetTransform().mPosition);
	}
	
	// ダメージを貰う
	TakenDamage(damage);

	// ヒットリアクション大の場合はカメラ、コントローラー振動
	if (mHitReaction == CrossCharacter::HitReaction_Big)
	{
		XInput::Vibration(0.7f, XInput::mMaxVibration, XInput::mMaxVibration);
		SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->ShakeMainCamera({ 0.5f,0.5f }, 0.4f);
	}

	// コントローラー振動処理
	if (damage >= 13)
	{
		XInput::Vibration(0.18f, 2000 * damage, 2000 * damage);
	}	

	// Hpがあるか確認する
	CheckHP();
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
	skeletalMesh->SetDrawType(CullType::Draw_SolidFront, 0);
	skeletalMesh->SetDrawType(CullType::Draw_SolidBack, 1);

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
	mCollisionComp = capsuleCollision;
}

void Player::SetupAudio()
{
	// ガード
	{
		std::shared_ptr<AudioComponent> guard = AddComponent<AudioComponent>();
		guard->Init("assets/Player/Audio/Guard.wav");
		mGuardAudio = guard;
	}

	// ジャストガード
	{
		std::shared_ptr<AudioComponent> justGuard = AddComponent<AudioComponent>();
		justGuard->Init("assets/Player/Audio/JustGuard_2.wav");
		mJustGuardAudio = justGuard;
	}
}

void Player::SetupEffect()
{
	// ガードエフェクト
	{
		std::shared_ptr<EffectComponent> effect = AddComponent<EffectComponent>();
		effect->Init("assets/Player/Effect/Guard.efkefc");
		mGuardEffect = effect;
	}

	// ジャスガエフェクト
	{
		std::shared_ptr<EffectComponent> effect = AddComponent<EffectComponent>();
		effect->Init("assets/Player/Effect/JustGuard.efkefc");
		mJustGuardEffect = effect;
	}
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

	// カウンターを実行するか確認する
	if (IsExecuteCounter())
	{
		mBehavior = PlayerBehaviorState::State_Counter;
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
		mBehavior = PlayerBehaviorState::State_Attack;
		return;
	}

	// ガードを実行するかを確認する
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

	// ガードの結果を取得
	return guardState->CheckGuard(_hitCollisionPos);	
}

void Player::GuardingHit(float& _damage, const DirectX::SimpleMath::Vector3 _hitPosition, const CrossCharacter::HitReaction _hitReaction)
{
	// ガードの結果を確認する 
	GuardResult result = GuardResult::Result_Faild;	
	result = CheckGuard(_hitPosition, _damage);

	// 通常ガード
	if (result == GuardResult::Result_Guard)
	{
		_damage *= 0.5f;
		mGuardAudio.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 });
		DirectX::SimpleMath::Vector3 effectPosition = mTransform.lock()->GetPosition() + mTransform.lock()->GetForwardVector() * 1.0f;
		effectPosition.y = 4.0f;
		mGuardEffect.lock()->PlayEffect(effectPosition, { 1,1,1 }, mTransform.lock()->GetRotation().y);
	}
	// ジャストガード
	else if (result == GuardResult::Result_JustGuard)
	{
		_damage = 0.0f;
		mJustGuardAudio.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 });
		XInput::Vibration(0.7f, XInput::mMaxVibration, XInput::mMaxVibration);

	
		DirectX::SimpleMath::Vector3 effectPosition = mTransform.lock()->GetPosition() + mTransform.lock()->GetForwardVector() * 1.0f;
		effectPosition.y = 4.0f;
		mJustGuardEffect.lock()->PlayEffect(effectPosition, { 1,1,1 }, mTransform.lock()->GetRotation().y);

		// ジャスガしたらカウンター可能状態に
		mJustGuardElapsedTime = 0.0f;
	}	
	// ガードが失敗していればヒットリアクションを取る
	else if (result == GuardResult::Result_Faild)
	{
		mBehavior = PlayerBehaviorState::State_HitReaction;

		// この攻撃のヒットリアクションの取得
		mHitReaction = _hitReaction;

		// ふっとび方向の計算
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
	// 真正面のベクトルとの差分を取る　// XZ平面での角度の差分を取る
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
	// Hpが0以下なら死亡フラグを立てる
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

	// ガード中ならガードできているか確認する
	GuardResult result = GuardResult::Result_Faild;
	if (mBehavior == PlayerBehaviorState::State_Guard)
	{
		result = CheckGuard(mTransform.lock()->GetForwardVector() + mTransform.lock()->GetPosition(), damage);

		// 通常ガード
		if (result == GuardResult::Result_Guard)
		{
			damage *= 0.5f;
			mGuardAudio.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 });
			DirectX::SimpleMath::Vector3 effectPosition = mTransform.lock()->GetPosition() + mTransform.lock()->GetForwardVector() * 1.0f;
			effectPosition.y = 4.0f;
			mGuardEffect.lock()->PlayEffect(effectPosition, { 1,1,1 }, mTransform.lock()->GetRotation().y);
		}
		// ジャストガード
		else if (result == GuardResult::Result_JustGuard)
		{
			damage = 0.0f;
			mJustGuardAudio.lock()->PlaySound3D(mTransform.lock()->GetPosition(), { 0,0,0 });
			XInput::Vibration(0.7f, XInput::mMaxVibration, XInput::mMaxVibration);

			DirectX::SimpleMath::Vector3 effectPosition = mTransform.lock()->GetPosition() + mTransform.lock()->GetForwardVector() * 1.0f;
			effectPosition.y = 4.0f;
			mJustGuardEffect.lock()->PlayEffect(effectPosition, { 1,1,1 }, mTransform.lock()->GetRotation().y);

			// ジャスガしたらカウンター可能状態に
			mJustGuardElapsedTime = 0.0f;
		}
	}

	// 処理が多くないからインターフェースつかわなくてもいいかも
	TakenDamage(damage);

	// ガードが失敗していればヒットリアクションを取る
	if (result == GuardResult::Result_Faild)
	{
		mBehavior = PlayerBehaviorState::State_HitReaction;

		// この攻撃のヒットリアクションの取得
		mHitReaction = _hitReaction;
	}

	// コントローラー振動処理
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
