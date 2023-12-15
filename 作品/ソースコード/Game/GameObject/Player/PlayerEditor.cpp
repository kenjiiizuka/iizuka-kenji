#include "PlayerEditor.h"
#include "../../Component/MoveComponent/CharacterMovementComponent.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "Animation/Notify/PlayerWeaponCollisionActiveNotifyState.h"
#include "Animation/Notify/PlayerInputAbleNotifyState.h"
#include "../../Resource/BlendAnimationClip.h"
#include"../../../ImGui/ImGuiUtility.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"
#include <source_location>
#include "PlayerCamera/PlayerCamera.h"
#include "../Camera/CameraManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"

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

	mTempClipNameLeft.resize(9);
	mTempClipNameRight.resize(9);

	std::shared_ptr<PlayerAttackData> validAttack = mAttackData.lock();

	for (uint8_t attack_i =0; attack_i < PlayerData::AttackID_Max; attack_i++) 
	{
		PlayerAttack attack = validAttack->GetAttack(static_cast<PlayerData::AttackID>(attack_i));
		mTempClipNameLeft[attack_i] = attack.mLeftStepAnimationClipName;
		mTempClipNameRight[attack_i] = attack.mRightStepAnimationClipName;
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
	ImGui::End();

	static int shakeLevel = 1;
	static float shakeTime = 1.0f;
	static float horizonShake = 1.0f;
	static float verticalShake = 1.0f;
	std::shared_ptr<Camera> mainCamera = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->GetMainCamera();
	ImGui::Begin("Camera");

	ImGui::InputInt("ShakeLevel", &shakeLevel);
	ImGui::SliderFloat("ShakeTime", &shakeTime, 0.0f, 2.0f);

	ImGui::SliderFloat("Horizon", &horizonShake, 0.0f, 2.0f);
	ImGui::SliderFloat("Vertical", &verticalShake, 0.0f, 2.0f);


	if (ImGui::Button("Shake"))
	{
		mainCamera->CameraShake(shakeLevel, {horizonShake, verticalShake} ,shakeTime);
	}

	ImGui::End();

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
