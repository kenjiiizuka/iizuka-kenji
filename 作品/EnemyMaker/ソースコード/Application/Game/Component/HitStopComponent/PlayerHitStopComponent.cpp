//--------- INCLUDES ----------
#include "PlayerHitStopComponent.h"
#include "../../../Utility/MathLibrary.h"
#include "../../GameObject/GameObject.h"
#include "../../Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../GameObject/Camera/CameraIncludes.h"
#include "../../../ImGui/ImGuiUtility.h"

PlayerHitStopComponent::PlayerHitStopComponent()
	: mDamage(0.0f)
	, mHitStopSkipSecondWeight(0.09f)
	, mHitStopSecondWeight(0.002f)
	, mStopAnimationSecond(0.0f)
{
	// �����Ȃ�
}

PlayerHitStopComponent::~PlayerHitStopComponent()
{
	// �����Ȃ�
}

void PlayerHitStopComponent::Update(const double _deltaTime)
{

	ImGui::Begin("PlayerHitStop");
	ImGui::InputFloat("StopWeight", &mHitStopSecondWeight);
	ImGui::InputFloat("SkipWeight", &mHitStopSkipSecondWeight);
	ImGui::End();

	// �A�j���[�V������~���Ԃ�0�ȉ��Ȃ珈�����Ȃ�
	if (!mbStop)
	{
		return;
	}

	// ���Ԍv��
	mStopAnimationSecond -= _deltaTime;

	// ��~���Ԃ��܂��c���Ă���Ώ������Ȃ�
	if (mStopAnimationSecond > 0)
	{
		return;
	}

	// �A�j���[�V�����v���C���[���擾
	std::shared_ptr<AnimationPlayer> animPlayer = mOwner->GetComponent<SkeletalMeshComponent>()->GetAnimationPlayer().lock();
	if (!animPlayer)
	{
		return;
	}

	// �A�j���[�V�������Đ�����
	animPlayer->ResumeAnimation();
	mbStop = false;
}

void PlayerHitStopComponent::HitStop(const bool _isCounter)
{	
	std::shared_ptr<AnimationPlayer> animPlayer = mOwner->GetComponent<SkeletalMeshComponent>()->GetAnimationPlayer().lock();
	if (!animPlayer)
	{
		return;
	}

	// �J�����U��
	SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->ShakeMainCamera({ 0.2f,0.2f }, 0.1f);

	// �J�E���^�[�o�Ȃ��ꍇ�̂݃A�j���[�V�������X�L�b�v����
	if (!_isCounter)
	{
		// �t���[�����X�L�b�v����
		animPlayer->SkipAnimationFrame(-(mHitStopSkipSecondWeight * mDamage));
	}
	// �w�肳�ꂽ�t���[�������~�߂� �A�j���[�V�������~�߂�
	mStopAnimationSecond = mHitStopSecondWeight * mDamage;

	// �A�j���[�V������~
	animPlayer->StopAnimation();

	mbStop = true;
}
