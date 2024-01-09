//---------- INCLUDES ----------
#include "PlayerHitReactionBigNotifyState.h"
#include "../../../../Resource/SkeletalMesh.h"
#include "../../../../Resource/SkeletalMeshAnimationClip.h"
#include "../../../GameObject.h"
#include "../../../../Component/TransformComponent/TransformComponent.h"
#include "../../../../../Utility/CurveFloat.h"
#include "../../../../../Utility/MathLibrary.h"

PlayerHitReactionBigNotifyState::PlayerHitReactionBigNotifyState(SkeletalMeshAnimationClip* _attachAnimation, uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	: AnimationNotifyState(_attachAnimation, _attachStartFrame, _attachEndFrame)
	, mAttachAnimationDuration(0.0f)
	, mBlowVector(0.0f,0.0f,-1.0f)
{
	// �J�[�u�̏�����
	mBlowCurve = std::make_shared<CurveFloat>();
	mBlowCurve->Initialize("assets/Player/Config/BlowCurve.json");
}

PlayerHitReactionBigNotifyState::~PlayerHitReactionBigNotifyState()
{
	// �����Ȃ�
}

void PlayerHitReactionBigNotifyState::NotifyInit()
{
	mPlayerTransform = mSkeletalMesh.lock()->GetOwnerObject()->GetComponent<TransformComponent>();
	mAttachAnimationDuration = mAttachedAnimation->GetDuration();
}

void PlayerHitReactionBigNotifyState::NotifyBegin()
{
	// ������ѕ����Ƃ͋t�Ƀv���C���[��������
	DirectX::SimpleMath::Vector3 rotation = mPlayerTransform.lock()->GetRotation();
	rotation.y = MathLibrary::Conv_VectorToRotation(mBlowVector).y + PIFloat;
	mPlayerTransform.lock()->SetRotation(rotation);	
}

void PlayerHitReactionBigNotifyState::NotifyUpdate()
{
	// ���݂̃A�j���[�V�����̍Đ����Ԃ𐳋K��
	float t = mAttachedAnimation->GetCurrentPlayTime() / mAttachAnimationDuration;

	// ������уx�N�g���̎擾
	DirectX::SimpleMath::Vector3 blowVector = mBlowVector * mBlowCurve->GetValueByTime(t);

	// �v���C���[���ړ�
	mPlayerTransform.lock()->AddPosition(blowVector);
}




