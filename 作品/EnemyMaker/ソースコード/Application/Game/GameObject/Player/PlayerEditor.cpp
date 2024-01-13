//---------- INCLUDES ---------
#include <source_location>
#include "PlayerEditor.h"
#include "Animation/Notify/PlayerWeaponCollisionActiveNotifyState.h"
#include "Animation/Notify/PlayerInputAbleNotifyState.h"
#include "PlayerCamera/PlayerCamera.h"
#include "Weapon/PlayerWeapon.h"
#include "Animation/Notify/PlayerHitReactionBigNotifyState.h"
#include "../../Component/MoveComponent/CharacterMovementComponent.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Resource/BlendAnimationClip.h"
#include "../../Resource/SkeletalMesh.h"
#include "../../Resource/Skeleton.h"
#include "../../GameObject/Camera/CameraIncludes.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Component/EffectComponent/PlayEffectNotify.h"
#include "../../../Utility/CurveFloat.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"

PlayerEditor::PlayerEditor()
	: mMaxWalkSpeed(0.0f)
	, mFaceDirectionInterpSpeed(0.0f)
{
	// 処理なし
}

PlayerEditor::~PlayerEditor()
{
	// 処理なし
}

void PlayerEditor::Initialize(const std::shared_ptr<Player> _player)
{
	mPlayer = _player;

	//// 移動コンポーネント関連の値を取得
	//std::shared_ptr<PlayerMovementComponent> moveComp = _player->GetComponent<PlayerMovementComponent>();
	//mMaxWalkSpeed = moveComp->GetMaxWalkSpeed();
	//mFaceDirectionInterpSpeed = moveComp->GetFaceDirectionInterpSpeed();
	//mMoveComp = moveComp;

	// SkeletalMesh関連の値を取得
	mSkeletalMeshComp = _player->GetComponent<SkeletalMeshComponent>();

	mAttackData = mPlayer.lock()->GetAttackData();	
	
	std::shared_ptr<PlayerAttackData> validAttack = mAttackData.lock();

	for (uint8_t attack_i =0; attack_i < PlayerData::AttackID_Max; attack_i++) 
	{
		PlayerAttack attack = validAttack->GetAttack(static_cast<PlayerData::AttackID>(attack_i));
	}
}

void PlayerEditor::Uninitialize()
{
	// mAttackData.lock()->SaveJsonFile();
}

void PlayerEditor::Update()
{
	ImGui::Begin("PlayerEditor");
	// MovementHeader();
	StepHeader();
	AttackHeader();
	HitReactionHeader();

	if (ImGui::Button("Death"))
	{
		mPlayer.lock()->Death_debug();
		mDeathCamera.lock()->Play();
	}
	static bool editDeathCamera = false;
	ImGui::Checkbox("EditDeathCamera", &editDeathCamera);
	ImGui::End();

	if (editDeathCamera)
	{
		mPlayer.lock()->GetWeapon().lock()->Edit();
		mDeathCamera.lock()->EditAnimation("DeathAnimation");
	}
	if (Input::GetKeyPress('S') && Input::GetKeyPress(VK_CONTROL))
	{
		mAttackData.lock()->SaveJsonFile();
	}
}

void PlayerEditor::AttackHeader()
{
	ImGui::PushID("AttackNode");
	if (!ImGui::CollapsingHeader("Attack"))
	{
		ImGui::PopID();
		return;
	}

	AttackNode(PlayerData::AttackID_NoAttack, "None", 0);
	AttackNode(PlayerData::AttackID_Y1, "Y1",1);
	AttackNode(PlayerData::AttackID_Y2, "Y2",2);
	AttackNode(PlayerData::AttackID_Y3, "Y3",3);
	AttackNode(PlayerData::AttackID_Y4, "Y4",4);
	AttackNode(PlayerData::AttackID_B1, "B1",5);
	AttackNode(PlayerData::AttackID_B2, "B2",6);
	AttackNode(PlayerData::AttackID_B3, "B3",7);
	AttackNode(PlayerData::AttackID_B2_2, "B2_2",8);
	AttackNode(PlayerData::AttackID_Counter, "Counter", 9);

	ImGui::PopID();
}

void PlayerEditor::StepHeader()
{
	ImGui::PushID("StepHeader");
	if (!ImGui::CollapsingHeader("Step"))
	{
		ImGui::PopID();
		return;
	}

	ImGuiUtility& imgui = ImGuiUtility::GetInstance();

	std::shared_ptr<Player> validPlayer = mPlayer.lock();
	
	float stepToIdleRunInterpTime = validPlayer->GetStepToIdleRunInterpTime();
	float leftStepToIdleRunInterpTime = validPlayer->GetLeftStepToIdleRunInterpTime();
	float rightStepToIdleRunInterpTime = validPlayer->GetRightStepToIdleRunInterpTime();

	imgui.DragFloat("Step to IdleRun InterpTime", stepToIdleRunInterpTime, 0.0f, 1.0f);
	imgui.DragFloat("LeftStep to IdleRun InterpTime", leftStepToIdleRunInterpTime, 0.0f, 1.0f);
	imgui.DragFloat("RightStep to IdleRun InterpTime", rightStepToIdleRunInterpTime, 0.0f, 1.0f);

	validPlayer->SetStepToIdleRunInterpTime(stepToIdleRunInterpTime);
	validPlayer->SetLeftStepToIdleRunInterpTime(leftStepToIdleRunInterpTime);
	validPlayer->SetRightStepToIdleRunInterpTime(rightStepToIdleRunInterpTime);

	ImGui::PopID();
}

void PlayerEditor::HitReactionHeader()
{
	ImGui::PushID("HitReactionNode");
	if (!ImGui::CollapsingHeader("HitReaction"))
	{
		ImGui::PopID();
		return;
	}

	if (ImGui::Button("HitReaction Small"))
	{
		mPlayer.lock()->HitReaction(CrossCharacter::HitReaction_Small);
		mPlayer.lock()->Recovery_debug();
	}
	if (ImGui::Button("HitRection Big"))
	{
		mPlayer.lock()->HitReaction(CrossCharacter::HitReaction_Big);
		mPlayer.lock()->Recovery_debug();
	}

	std::shared_ptr<AnimationInstance> animIns = mPlayer.lock()->GetComponent<SkeletalMeshComponent>()->GetAnimationInstance();
	std::shared_ptr<PlayerHitReactionBigNotifyState> notify = animIns->GetAnimationClipByName("Hit_Big")->GetAnimnotifyState<PlayerHitReactionBigNotifyState>();

	notify->GetBlowCurve().lock()->Edit("BlowCurve");

	ImGui::PopID();
}

void PlayerEditor::AttackNode(const PlayerData::AttackID _attackID, std::string_view _nodeName, const uint8_t _tempString_i)
{
	if (!ImGui::TreeNode(_nodeName.data()))
	{
		return;
	}

	ImGuiUtility& imgui = ImGuiUtility::GetInstance();

	// 攻撃データの取得
	std::shared_ptr<PlayerAttackData> validAttack = mAttackData.lock();
	PlayerAttack attack = validAttack->GetAttack(_attackID);

	// 次の攻撃の設定
	{
		ImGui::SeparatorText("NextCombo");
		std::vector<std::string> items = { "No_Attack", "Y1", "Y2", "Y3", "Y4", "B1", "B2","B2_2", "B3"};
		int nextY = attack.mNextY;
		imgui.Combo("NextY", items, nextY);
		int nextB = attack.mNextB;
		imgui.Combo("NextB", items, nextB);

		attack.mNextB = static_cast<PlayerData::AttackID>(nextB);
		attack.mNextY = static_cast<PlayerData::AttackID>(nextY);
	}

	// 攻撃に対応するアニメーションと通知ステートを取得
	std::shared_ptr<SkeletalMeshAnimationClip> animClip = mSkeletalMeshComp.lock()->GetAnimationInstance()->GetAnimationClipByName(attack.mAnimationClipName);
	if (animClip)
	{
		std::vector<std::shared_ptr<PlayerWeaponCollisionActiveNotifyState>> collisionNotifies = animClip->GetAllAnimNotifyState<PlayerWeaponCollisionActiveNotifyState>();

		float animDuration = animClip->GetDuration();
		ImGui::InputFloat("AnimationDuration", &animDuration);

		// 当たり判定発生位置の設定
		ImGui::SeparatorText("Collision");
		for (size_t i = 0; std::pair<uint16_t, uint16_t>&collisionFrame : attack.mCollision.mCollisionFrames)
		{
			int frame[2] = { collisionFrame.first, collisionFrame.second };

			std::string pushID = _nodeName.data();
			pushID += std::to_string(i).data();

			ImGui::PushID(pushID.c_str());
			ImGui::InputInt2("CollisionFrame Start End", frame);
			ImGui::PopID();

			collisionFrame.first = frame[0];
			collisionFrame.second = frame[1];

			collisionNotifies[i]->SetStartFrame(collisionFrame.first);
			collisionNotifies[i]->SetEndFrame(collisionFrame.second);
			i++;
		}

		if (ImGui::Button("AddCollision"))
		{
			animClip->AddAnimationNotifyState<PlayerWeaponCollisionActiveNotifyState>(0, 1);
			attack.mCollision.mCollisionFrames.emplace_back(std::pair(0,1));
			attack.mCollision.mCollisionOccurrence = static_cast<uint8_t>(attack.mCollision.mCollisionFrames.size());
		}

		// 入力可能タイミングの設定
		{
			std::shared_ptr<PlayerInputAbleNotifyState> notify = animClip->GetAnimnotifyState<PlayerInputAbleNotifyState>();

			ImGui::SeparatorText("InputAble");
			int inputAbleFrame[2] = { attack.mInputAbleFrame.first, attack.mInputAbleFrame.second };

			ImGui::PushID("InputAbleFrame");
			ImGui::InputInt2("InputAbleFrame Start End", inputAbleFrame);
			ImGui::PopID();

			attack.mInputAbleFrame.first = inputAbleFrame[0];
			attack.mInputAbleFrame.second = inputAbleFrame[1];

			notify->SetStartFrame(attack.mInputAbleFrame.first);
			notify->SetEndFrame(attack.mInputAbleFrame.second);
		}
	}


	EffectNotifyNode(_attackID);

	// ダメージ
	ImGui::SeparatorText("Damage");
	std::string damageID = _nodeName.data();
	damageID += "Damage";
	ImGui::PushID(damageID.c_str());
	ImGui::DragFloat("DamageValue", &attack.mDamage);
	ImGui::PopID();

	// 次のアニメーションへの補間
	{
		std::string treeID = _nodeName.data();
		treeID += "Tree";
		ImGui::PushID(treeID.c_str());
		if (ImGui::TreeNode("Animation Interp"))
		{
			ImGui::SeparatorText("Interp StartTime");
			std::string nextAnimInterp = _nodeName.data();
			nextAnimInterp += "Step";
			ImGui::PushID(nextAnimInterp.c_str());
			imgui.DragFloat("Step Start", attack.mAnimationInterp.mStepInterpStartTime);
			imgui.DragFloat("RightStep Start", attack.mAnimationInterp.mRightStepInterpStartTime);
			imgui.DragFloat("LeftStep Start", attack.mAnimationInterp.mLeftStepInterpStartTime);
			ImGui::PopID();

			nextAnimInterp = _nodeName.data();
			nextAnimInterp += "Attack";
			ImGui::PushID(nextAnimInterp.c_str());
			ImGui::DragFloat("NextY Start", &attack.mAnimationInterp.mYAttackInterpStartTime);
			ImGui::DragFloat("NextB Start", &attack.mAnimationInterp.mBAttackInterpStartTime);
			ImGui::PopID();

			ImGui::SeparatorText("Interp Time");
			imgui.DragFloat("NextY Time", attack.mAnimationInterp.mYAttackInterpTime);
			imgui.DragFloat("NextB Time", attack.mAnimationInterp.mBAttackInterpTime);
			imgui.DragFloat("Step Time", attack.mAnimationInterp.mStepInterpTime);
			imgui.DragFloat("RightStep Time", attack.mAnimationInterp.mRightStepInterpTime);
			imgui.DragFloat("LeftStep Time", attack.mAnimationInterp.mLeftStepInterpTime);
			imgui.DragFloat("IdleRun Time", attack.mAnimationInterp.mIdleMoveInterpTime);

			ImGui::TreePop();
		}
		ImGui::PopID();
	}
	validAttack->SetAttackInformation(_attackID, attack);
	ImGui::TreePop();
}

void PlayerEditor::EffectNotifyNode(const PlayerData::AttackID _attackID)
{
	// 攻撃データの取得
	std::shared_ptr<PlayerAttackData> validAttack = mAttackData.lock();
	PlayerAttack attack = validAttack->GetAttack(_attackID);

	// アニメーションクリップの取得
	std::shared_ptr<SkeletalMeshAnimationClip> animClip = mSkeletalMeshComp.lock()->GetAnimationInstance()->GetAnimationClipByName(attack.mAnimationClipName);

	// エフェクト発生通知を取得
	std::shared_ptr<PlayEffectNotify> notify = animClip->GetAnimnotify<PlayEffectNotify>();

	// 編集したいパラメーターを取得
	float attachFrame = notify->GetAttachFrame();
	DirectX::SimpleMath::Vector3 offset = notify->GetOffset();
	DirectX::SimpleMath::Vector3 scale = notify->GetScale();

	// ImGuiで表示
	ImGui::SeparatorText("Effect");
	ImGui::InputFloat("PlayFrame", &attachFrame);
	ImGuiUtility::GetInstance().InputVector3("Offset", offset);
	ImGuiUtility::GetInstance().InputVector3("Scale", scale);

	// パラメーターのセット
	notify->SetAttachFrame(attachFrame);
	notify->SetOffset(offset);
	notify->SetScale(scale);
}

void PlayerEditor::SetDeathCamera(std::shared_ptr<CinematicCamera> _camera) noexcept
{
	mDeathCamera = _camera;
	std::shared_ptr<SkeletalMesh> mesh = mPlayer.lock()->GetComponent<SkeletalMeshComponent>()->GetSkeletalMesh().lock();
	mDeathCamera.lock()->SetTargetBone(mesh->GetSkeleton().lock()->GetBoneByName("mixamorig:Head").lock());
	mDeathCamera.lock()->Init("assets/Player/Config/DeathCamera.json");
}
