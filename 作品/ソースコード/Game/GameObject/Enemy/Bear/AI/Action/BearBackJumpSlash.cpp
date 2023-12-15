#include "BearBackJumpSlash.h"
#include "../../Animation/BearAnimationinstance.h"

BearBackJumpSlash::BearBackJumpSlash(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(BearBackJumpSlash).name();
	mAttackID = BearEnemyAttackData::BackJumpSlash;
}

BearBackJumpSlash::~BearBackJumpSlash()
{
	// �����Ȃ�
}

void BearBackJumpSlash::BeginActionExecution(EnemyBase* _enemy)
{
	// �e�N���X�Ŏ��s�񐔂̉��Z�Ɣz��̊g�����Ă���̂ŌĂяo��
	BearAttackAction::BeginActionExecution(_enemy);
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName, 1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult BearBackJumpSlash::UpdateActionExecution()
{
	// �e�N���X���Ŏ��Ԃ̌v�������Ă���̂ŌĂяo��
	BearAttackAction::UpdateActionExecution();

	// �A�j���[�V�����̏I�����肪����ΐ�����Ԃ��A����ȊO�͎��s��
	std::shared_ptr<AnimationPlayer> animPlayer = mAnimInstance.lock()->GetAnimationPlayer();
	if (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame())
	{
		return EnemyActionResult::Succeeded;
	}
	return EnemyActionResult::InProgress;
}

void BearBackJumpSlash::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool BearBackJumpSlash::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

void BearBackJumpSlash::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<BearBackJumpSlash>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
