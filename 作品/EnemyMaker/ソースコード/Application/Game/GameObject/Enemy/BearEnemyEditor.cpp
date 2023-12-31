//-------- INCLUDES -----------
#include "BearEnemyEditor.h"
#include "../../Component/AIComponent/EnemyAIComponent.h"
#include "AIBase/EnemyActionProcessor.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "AIBase/BlackBoard.h"
#include "AIBase/EnemyAIController.h"
#include "AIBase/EnemyActionSelector.h"
#include "Bear/AI/Action/Bear3ChainSwordAttack.h"
#include "Bear/AI/Action/BearJumpSlash.h"
#include "Bear/AI/Action/BearSwipingAttack.h"
#include "Bear/AI/Action/BearSwordSwingDownAttack.h"
#include "Bear/AI/Action/Bear2ChainSwordAttack.h"
#include "Bear/AI/Action/Bear2ChainSwordStrongAttack.h"
#include "Bear/AI/Action/BearKickAttack.h"
#include "Bear/AI/Action/BearRoarAttack.h"
#include "Bear/AI/Action/BearSwordSwingUpAttack.h"
#include "Bear/AI/Action/BearMoveAction.h"
#include "Bear/AI/Action/BearTurnRightAction.h"
#include "Bear/AI/Action/BearTurnLeftAction.h"
#include "Bear/AI/Action/Bear2ChinaBackAndFront.h"
#include "Bear/AI/Action/BearDownwardSlashStrong.h"
#include "Bear/AI/Action/Bear2ChainAttack_StrongLow.h"
#include "Bear/AI/Action/BearSlashWeak.h"
#include "Bear/AI/Action/BearBackJumpSlash.h"
#include "Bear/Animation/Notify/BearWeaponCollisionActiveNotifyState.h"
#include "../Enemy/EnemyAttackCollisionAttachNotifyState.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../System/InputSystem/Input.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../GameObject/Player/Player.h"
#include "../../Component/SkeletalMeshComponent/AnimationInstance.h"
#include "../../Resource/SkeletalMeshAnimationClip.h"
#include "../../GameObject/Camera/CameraIncludes.h"
#include "../../Component/EffectComponent/PlayEffectNotify.h"
#include "../../GameObject/Camera/CinematicCamera.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Resource/SkeletalMesh.h"
#include "../../Resource/Skeleton.h"
#include "../../Resource/Bone.h"

BearEnemyEditor::BearEnemyEditor()
{
	// 処理なし
}

BearEnemyEditor::~BearEnemyEditor()
{
	// 処理なし
}

void BearEnemyEditor::Initialize(std::shared_ptr<EnemyBase> _enemy)
{
	mActionProcessor = std::make_shared<EnemyActionProcessor>();

	mEditEnemy = _enemy;
	std::shared_ptr<EnemyAIComponent> aiComp = mEditEnemy.lock()->GetComponent<EnemyAIComponent>();
	std::shared_ptr<BlackBoard> blackboard = aiComp->GetAIController().lock()->GetBlackboard().lock();
	blackboard->SetValue<DirectX::SimpleMath::Vector3>({1000,0.0,1000}, "TargetPosition");

	mAttackActions.emplace_back(std::make_shared<Bear3ChainSwordAttack>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearSwipingAttack>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearSwordSwingDownAttack>(blackboard));
	mAttackActions.emplace_back(std::make_shared<Bear2ChainSwordAttack>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearKickAttack>(blackboard));
	mAttackActions.emplace_back(std::make_shared<Bear2ChainSwordStrongAttack>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearRoarAttack>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearSwordSwingUpAttack>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearJumpSlash>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearSlashWeak>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearBackJumpSlash>(blackboard));
	mAttackActions.emplace_back(std::make_shared<Bear2ChinaBackAndFront>(blackboard));	
	mAttackActions.emplace_back(std::make_shared<Bear2ChainAttack_StrongLow>(blackboard));
	mAttackActions.emplace_back(std::make_shared<BearDownwardSlashStrong>(blackboard));

	for (std::shared_ptr<EnemyAttackAction>& attack : mAttackActions)
	{
		attack->SetEnemy(mEditEnemy.lock().get());
	}
}

void BearEnemyEditor::Update()
{
	ImGui::Begin("AttackEditor");
	AttackHeader();

	// アニメーションの再生が終ればもとの位置に戻す
	if (ImGui::Button("ResetPosition"))
	{
		mEditEnemy.lock()->GetComponent<TransformComponent>()->SetPosition({ 0.0f,0.0f,0.0f });
	}

	if (ImGui::Button("Death"))
	{
		mEditEnemy.lock()->TakenDamage(10000, { 0,0,0 });
		mDeathCamera.lock()->Play();
	}

	ImGui::End();

	std::shared_ptr<EnemyAIComponent> aiComp = mEditEnemy.lock()->GetComponent<EnemyAIComponent>();
	std::shared_ptr<BlackBoard> blackboard = aiComp->GetAIController().lock()->GetBlackboard().lock();
	std::shared_ptr<Player> player = SceneManager::GetInstance().GetCurrentScene().lock()->GetGameObject<Player>();	
	DirectX::SimpleMath::Vector3 playerPos = player->GetComponent<TransformComponent>()->GetPosition();
	blackboard->SetValue<DirectX::SimpleMath::Vector3>(playerPos, "TargetPosition");

	mActionProcessor->Update(mEditEnemy.lock().get());
	
	// セーブ
	if (Input::GetKeyPress(VK_SHIFT) && Input::GetKeyPress('S'))
	{
		std::shared_ptr<IEnemyAttackData> attackData = mEditEnemy.lock()->GetAttackData().lock();
		attackData->SaveData();
	}

	mDeathCamera.lock()->EditAnimation("DeathCamera");
}

void BearEnemyEditor::AttackNode(std::shared_ptr<EnemyAttackAction>& _attack)
{
	std::string id = _attack->GetTypeName().c_str();
	id += "ID";
	ImGui::PushID(id.c_str());
	if (!ImGui::TreeNode(_attack->GetTypeName().c_str()))
	{
		ImGui::PopID();
		return;
	}

	// 行動の条件位置を見るために実行可能か判断する関数を実行する
	if (ImGui::Button("Execute") || _attack->IsExecuteAble())
	{
		PlayAttack(_attack);
	}

	ImGuiUtility& imgui = ImGuiUtility::GetInstance();

	// 攻撃データを取得する
	std::shared_ptr<IEnemyAttackData> attackData = mEditEnemy.lock()->GetAttackData().lock();
	EnemyAttack attack = attackData->GetAttack(_attack->GetAttackID());
	EnemyAttackExecutionConditions& condition = attack.mExecutionCondition;

	// ダメージ設定
	// ダメージリアクション
	for (size_t i = 0; float& damage : attack.mDamagePerCollision)
	{
		std::string damageLabel = id + "Damage" + std::to_string(i);
		imgui.DragFloat(damageLabel, damage);
	 	int reaction = static_cast<int>(attack.mHitReactionPerCollision[i]);
		imgui.Combo("HitReaction", {"Small", "Big"},reaction);
		attack.mHitReactionPerCollision[i] = static_cast<CrossCharacter::HitReaction>(reaction);
		i++;
	}

	if (ImGui::Button("AddCircle"))
	{
		condition.mExecuteCheckCircleNum++;
		condition.mAngle.resize(condition.mExecuteCheckCircleNum);
		condition.mDistance.resize(condition.mExecuteCheckCircleNum);
		condition.mCircleRadius.resize(condition.mExecuteCheckCircleNum);
	}
	if (ImGui::Button("DecreaseCircle"))
	{
		condition.mExecuteCheckCircleNum--;
		condition.mAngle.resize(condition.mExecuteCheckCircleNum);
		condition.mDistance.resize(condition.mExecuteCheckCircleNum);
		condition.mCircleRadius.resize(condition.mExecuteCheckCircleNum);
	}

	for (size_t condition_i = 0; condition_i < condition.mExecuteCheckCircleNum; condition_i++)
	{
		std::string angleLabel = id;
		angleLabel += "Angle" + std::to_string(condition_i);
		ImGui::SliderFloat(angleLabel.c_str(), &condition.mAngle[condition_i], -PIFloat,PIFloat);

		std::string radiusLabel = id;
		radiusLabel += "Radius" + std::to_string(condition_i);
		ImGui::DragFloat(radiusLabel.c_str(), &condition.mCircleRadius[condition_i]);

		std::string distanceLabel = id;
		distanceLabel += "Distance" + std::to_string(condition_i);
		ImGui::DragFloat(distanceLabel.c_str(), &condition.mDistance[condition_i]);
	}



	// アニメーションクリップの取得
	std::shared_ptr<SkeletalMeshAnimationClip> clip = mEditEnemy.lock()->GetAnimationInstance()->GetAnimationClipByName(attack.mAnimationClipName);
	if (!clip)
	{
		attackData->SetAttackInformation(_attack->GetAttackID(), attack);
		ImGui::TreePop();
		ImGui::PopID();
		return;
	}

	// 攻撃の当たり判定
	CollisionOnFrameNode(attack);

	// アニメーション関連
	{
		ImGui::SeparatorText("Animation");

		ImGui::Text("AnimationDuration %f", clip->GetDuration());

		ImGui::DragFloat("ToIdleRunInterpTime", &attack.mToIdleRunInterpTime, 0.0f, 3.0f);
	}
	
	// カメラ振動
	{
		CameraShakeNode(attack);
	}

	// エフェクト関連
	{
		EffectNode(attack);
	}

	attackData->SetAttackInformation(_attack->GetAttackID(), attack);
	ImGui::TreePop();
	ImGui::PopID();
}

void BearEnemyEditor::CollisionOnFrameNode(EnemyAttack& _attackData)
{
	// 当たり判定発生タイミング設定
	ImGui::SeparatorText("On Collision Frame");

	std::shared_ptr<SkeletalMeshAnimationClip> clip = mEditEnemy.lock()->GetAnimationInstance()->GetAnimationClipByName(_attackData.mAnimationClipName);
	// 武器についてる当たり判定オンオフ通知があるかを確認
	{	
		std::vector<std::shared_ptr<BearWeaponCollisionActiveNotifyState>> notifies = clip->GetAllAnimNotifyState<BearWeaponCollisionActiveNotifyState>();
		if (!notifies.empty())
		{
			ImGui::SeparatorText("Weapon Collision");
			ImGui::PushID("WeaponCollision");
			for (size_t notify_i = 0; std::shared_ptr<BearWeaponCollisionActiveNotifyState>&notify : notifies)
			{
				float onFrame = notify->GetStartFrame();
				float endFrame = notify->GetEndFrame();
				ImGui::InputFloat(("Col On Frame" + std::to_string(notify_i)).c_str(), &onFrame);
				ImGui::InputFloat(("Col Off Frame" + std::to_string(notify_i)).c_str(), &endFrame);
				notify->SetStartFrame(onFrame);
				notify->SetEndFrame(endFrame);

				_attackData.mCollisionFrames[notify_i].first = onFrame;
				_attackData.mCollisionFrames[notify_i].second = endFrame;

				notify_i++;
			}
			ImGui::PopID();
		}
	}
	// ボーン、Objectにアタッチしているコリジョン
	{
		std::vector<std::shared_ptr<EnemyAttackCollisionAttachNotifyState>> notifies = clip->GetAllAnimNotifyState<EnemyAttackCollisionAttachNotifyState>();

		if (!notifies.empty())
		{
			ImGui::SeparatorText("Attach Collision");
			ImGui::PushID("AttachCollision");
			for (size_t notify_i = 0; std::shared_ptr<EnemyAttackCollisionAttachNotifyState>&notify : notifies)
			{
				float onFrame = notify->GetStartFrame();
				float endFrame = notify->GetEndFrame();
				ImGui::InputFloat(("Col On Frame" + std::to_string(notify_i)).c_str(), &onFrame);
				ImGui::InputFloat(("Col Off Frame" + std::to_string(notify_i)).c_str(), &endFrame);
				notify->SetStartFrame(onFrame);
				notify->SetEndFrame(endFrame);

				_attackData.mCollisionFrames[notify_i].first = static_cast<uint16_t>(onFrame);
				_attackData.mCollisionFrames[notify_i].second = static_cast<uint16_t>(endFrame);

				notify_i++;
			}
			ImGui::PopID();
		}
	}
}

void BearEnemyEditor::CameraShakeNode(EnemyAttack _attackData)
{
	std::shared_ptr<SkeletalMeshAnimationClip> clip = mEditEnemy.lock()->GetAnimationInstance()->GetAnimationClipByName(_attackData.mAnimationClipName);
	std::shared_ptr<CameraShakeNotify> notify = clip->GetAnimnotify<CameraShakeNotify>();
	if (!notify)
	{
		return;
	}

	ImGui::SeparatorText("CameraShake");

	float currentAttach = notify->GetAttachFrame();	
	DirectX::SimpleMath::Vector2 shakeVector = notify->GetShakeVector();
	float shakeTime = notify->GetShakeTime();
	int level = notify->GetShakeLevel();
	
	ImGui::InputFloat("AttachFrame", &currentAttach);
	ImGui::InputFloat("ShakeTime", &shakeTime);
	ImGui::InputInt("ShakeLevel", &level);
	ImGuiUtility::GetInstance().InputVector2("ShakeVector", shakeVector);

	notify->SetAttachFrame(currentAttach);
	notify->SetShakeLevel(level);
	notify->SetShakeVector(shakeVector);
	notify->SetShakeTime(shakeTime);
}

void BearEnemyEditor::EffectNode(EnemyAttack _attackData)
{
	// エフェクト再生通知を取得
	std::shared_ptr<SkeletalMeshAnimationClip> clip = mEditEnemy.lock()->GetAnimationInstance()->GetAnimationClipByName(_attackData.mAnimationClipName);
	std::vector<std::shared_ptr<PlayEffectNotify>> notifies = clip->GetAllAnimationNotify<PlayEffectNotify>();

	if (notifies.empty())
	{
		return;
	}

	if (!ImGui::TreeNode("Effect"))
	{
		return;
	}

	for (size_t notify_i = 0; std::shared_ptr<PlayEffectNotify> notify : notifies)
	{
		ImGui::SeparatorText(("Effect" + std::to_string(notify_i)).c_str());

		float attachFrame = notify->GetAttachFrame();
		DirectX::SimpleMath::Vector3 offsetPos = notify->GetOffset();
		DirectX::SimpleMath::Vector3 scale = notify->GetScale();
	
		ImGui::PushID(("Effect" + std::to_string(notify_i) + _attackData.mAnimationClipName).c_str());
		ImGui::InputFloat("AttachFrame", &attachFrame);	
		ImGuiUtility::GetInstance().InputVector3("EffectOffset", offsetPos);
		ImGuiUtility::GetInstance().InputVector3("EffectScale", scale);
		ImGui::PopID();

		notify->SetAttachFrame(attachFrame);
		notify->SetOffset(offsetPos);
		notify->SetScale(scale);

		notify_i++;
	}

	ImGui::TreePop();
}

void BearEnemyEditor::PlayAttack(std::shared_ptr<EnemyAttackAction>& _attack)
{
	// 攻撃がセット可能でないなら処理しない
	if (!mActionProcessor->IsActionSettable())
	{
		return;
	}
	mActionProcessor->SetExecutionAction(_attack);
}

void BearEnemyEditor::SetDeathCamera(std::shared_ptr<CinematicCamera> _camera) noexcept
{
	mDeathCamera = _camera;
	std::shared_ptr<SkeletalMesh> mesh = mEditEnemy.lock()->GetComponent<SkeletalMeshComponent>()->GetSkeletalMesh().lock();
	mDeathCamera.lock()->SetTargetBone(mesh->GetSkeleton().lock()->GetBoneByName("mixamorig:Head").lock());
}

void BearEnemyEditor::AttackHeader()
{
	if (!ImGui::CollapsingHeader("AttackHeader"))
	{
		return;
	}

	for (std::shared_ptr<EnemyAttackAction>& attack : mAttackActions)
	{
		AttackNode(attack);
	}
}
