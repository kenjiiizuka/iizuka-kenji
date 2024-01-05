//-------- INCLUDES ----------
#include "BearEnemy.h"
#include "BearEnemyAttackData.h"
#include "Animation/BearAnimationinstance.h"
#include "AI/BearAIController.h"
#include "../EnemyWeapon.h"
#include "../../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../../Component/CollisionComponent/CapsuleCollisionComponent.h"
#include "../../../Component/MoveComponent/CharacterMovementComponent.h"
#include "../../../Component/AIComponent/EnemyAIComponent.h"
#include "../../../Resource/SkeletalMesh.h"
#include "../../../Resource/Bone.h"
#include "../../../Resource/Skeleton.h"
#include "../../../Resource/Socket.h"
#include "../../../../ImGui/ImGuiUtility.h"
#include "../../../../Utility/MathLibrary.h"

BearEnemy::BearEnemy()
{
	// 処理なし
}

void BearEnemy::Init()
{
	// HPは600から1000の間でランダムにする
	mStatus.mMaxHp = mStatus.mCurrentHp = MathLibrary::RandomFloatInRange(600.0f, 1000.0f);
	EnemyBase::Init();
	
	// 攻撃データの作成
	mAttackData = std::make_shared<BearEnemyAttackData>();
	mAttackData->Initialize();

	// 移動の初期化
	mCharacterMoveComp = AddComponent<CharacterMovementComponent>();
	mCharacterMoveComp.lock()->SetMaxWalkSpeed(20.f);
	mCharacterMoveComp.lock()->SetFaceDirectionInterpSpeed(10.0f);

	// メッシュの初期化
	SetupSkeletalMesh("assets/Enemy/Model/Bear.fbx");

	// アニメーションインスタンスの作成
	std::shared_ptr<SkeletalMeshComponent> mesh = mMesh.lock();
	mesh->CreateAnimInstance<BearAnimationInstance>();

	// コリジョン設定
	SetupCollision();
	
	// 武器の初期化
	{
		mWeapon = AddChildObject<EnemyWeapon>();
		std::cout << mWeapon.lock().use_count() << std::endl;
		std::shared_ptr<SkeletalMesh> skeletalMesh = mesh->GetSkeletalMesh().lock();
		Transform socketTransform =
		{
			{17.0f,10.0f,-5.0f},
			{1.5f,1.5f,1.5f},
			{5.0f,2.0f,9.0f}
		};
		std::shared_ptr<Socket> socket = skeletalMesh->GetSkeleton().lock()->CreateSocket("mixamorig:RightHand", socketTransform, "joint");
		mWeapon.lock()->Init("assets/Enemy/Weapon/Sword.fbx", socket, skeletalMesh);
	}

	// AIの初期化
	{
		mAIComponent.lock()->CreateAIController<BearAIController>(this);
		mAIComponent.lock()->ControllerInitialize();
	}
}

void BearEnemy::Update(const double _deltaTime)
{
	EnemyBase::Update(_deltaTime);
	// CollisionFix();
}

void BearEnemy::CollisionFix()
{
	ImGui::Begin("Collision");

	for (size_t i = 0;std::weak_ptr<CapsuleCollisionComponent> capsule : mCapsuleCollision)
	{
		std::shared_ptr<CapsuleCollisionComponent> validCapsule = capsule.lock();
		if (!validCapsule)
		{
			continue;
		}
	
	 	std::string boneName = validCapsule->GetAttachedBone().lock()->GetBoneName();

		if (ImGui::TreeNode(boneName.c_str()))
		{
			float height = validCapsule->GetHeight();
			float radius = validCapsule->GetRadius();
			Transform offsetTrans = validCapsule->GetOffSetTransform();

			std::string h = "height";
			h += std::to_string(i);
			ImGui::PushID(h.c_str());
			ImGui::SliderFloat("Height", &height, 1.0f, 10.0f);
			ImGui::PopID();

			std::string r = "radius";
			r += std::to_string(i);
			ImGui::PushID(r.c_str());
			ImGui::SliderFloat("Radius", &radius, 1.0f, 10.0f);
			ImGui::PopID();

			std::string t = "Transform";
			t += boneName;
			ImGuiUtility::GetInstance().DragTransform(t,offsetTrans);

			ImGui::TreePop();

			validCapsule->SetHeight(height);
			validCapsule->SetRadius(radius);
			validCapsule->SetOffSetTransform(offsetTrans);
		}
		
		i++;
	}
	ImGui::End();
}

void BearEnemy::SetupCollision()
{
	using namespace DirectX::SimpleMath;

	// エリア外に出ないようのオブジェクトとの当たり判定の設定
	std::shared_ptr<CapsuleCollisionComponent> collision = AddComponent<CapsuleCollisionComponent>();
	collision->Init(3.0f, 7.7f);
	collision->SetCollisionChannel(Collision::Channel_Enemy);
	collision->SetCollisionTypes(Collision::Channel_Static, Collision::Type_Block);
	collision->SetCollisionTypes(Collision::Channel_Enemy, Collision::Type_None);
	collision->SetCollisionTypes(Collision::Channel_PlayerAttack, Collision::Type_None);
	collision->SetCollisionTypes(Collision::Channel_Player, Collision::Type_None);
	collision->SetOffSetPosition({ 0,8,0 });

	AttachCapsuleCollision("mixamorig:Hips", 2.1f, 3.24f, { { -5.0f,10.0f,0.0f},Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:Spine2", 2.5f, 3.2f, { {0.0f,19.0f,0.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:LeftArm", 1.88f, 1.84f, { {0.0f,18.0f,6.0}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:LeftForeArm", 2.3f, 1.4f, { {-3.0f,27.0f,0.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:RightArm", 2.42f, 2.0f, { {0.0f,20.0f,0.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:RightForeArm", 2.65f, 1.65f, { {0.0f,17.0f,0.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:LeftUpLeg", 2.1f, 1.56f, { {1.0f,8.0f,5.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:LeftLeg", 1.6f, 1.2f, { {0.0f,14.0f, 0.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:LeftFoot", 1.44f, 1.18f, { {-2.0f,17.0f,0.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:RightUpLeg", 1.7f, 1.3f, { {2.0f,15.0f, 6.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:RightLeg", 1.58f, 1.37f, { {0.0f,14.0f,0.0f}, Vector3::One, Vector3::Zero });
	AttachCapsuleCollision("mixamorig:RightFoot", 1.53f, 1.28f, { {0.0f,15.0f,0.0f}, Vector3::One, Vector3::Zero });	
}

void BearEnemy::AttachCapsuleCollision(const std::string& _boneName, const float _radius, const float _height, const Transform& _offsetTrans)
{
	// アタッチするボーンを取得する
	std::shared_ptr<SkeletalMeshComponent> skeletalMeshComponent = mMesh.lock();
	std::shared_ptr<SkeletalMesh> skeletalMesh = skeletalMeshComponent->GetSkeletalMesh().lock();
	std::shared_ptr<Bone> bone = skeletalMesh->GetSkeleton().lock()->GetBoneByName(_boneName).lock();

	// ボーンがあるかを確認する
	if (!bone)
	{
		std::cout << _boneName << "このボーンは存在しない" << std::endl;
		return;
	}

	// カプセルコリジョンの設定
	std::shared_ptr<CapsuleCollisionComponent> capsule = AddComponent<CapsuleCollisionComponent>();
	capsule->Init(_height, _radius);	

	// レイヤーの設定　プレイヤーの攻撃にたいしてオーバーラップのみ エネミーの当たり判定同氏は当たらないようにする
	capsule->SetCollisionChannel(Collision::Channel_Enemy);
	capsule->SetCollisionTypes(Collision::Channel_PlayerAttack, Collision::Type_Overlap);
	capsule->SetCollisionTypes(Collision::Channel_Enemy, Collision::Type_None);
	capsule->SetCollisionTypes(Collision::Channel_Static, Collision::Type_None);
	// ボーンにアタッチする
	capsule->AttachBone(bone, skeletalMesh);
	// capsule->SetDebugDraw(true);

	capsule->SetOffSetTransform(_offsetTrans);

	mCapsuleCollision.emplace_back(capsule);
}

