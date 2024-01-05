#include "BearDownwardSlashStrong.h"
#include "../../Animation/BearAnimationinstance.h"

BearDownwardSlashStrong::BearDownwardSlashStrong(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(BearDownwardSlashStrong).name();
	mAttackID = BearEnemyAttackData::DownwardSlashStrong;
}

BearDownwardSlashStrong::~BearDownwardSlashStrong()
{
	// �����Ȃ�
}

void BearDownwardSlashStrong::BeginActionExecution(EnemyBase* _enemy)
{
	// �e�N���X�Ŏ��s�񐔂̉��Z�Ɣz��̊g�����Ă���̂ŌĂяo��
	BearAttackAction::BeginActionExecution(_enemy);
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName, 1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult BearDownwardSlashStrong::UpdateActionExecution()
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

void BearDownwardSlashStrong::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool BearDownwardSlashStrong::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

void BearDownwardSlashStrong::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<BearDownwardSlashStrong>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
