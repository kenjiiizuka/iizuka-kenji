//--------- INCUDES ---------
#include "BearSlashWeak.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/MathLibrary.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../BearEnemy.h"
#include "../../../AIBase/BlackBoard.h"

BearSlashWeak::BearSlashWeak(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(BearSlashWeak).name();
	mAttackID = BearEnemyAttackData::ArmUpperSmash;
}

BearSlashWeak::~BearSlashWeak()
{
	// �����Ȃ�
}

void BearSlashWeak::BeginActionExecution(EnemyBase* _enemy)
{
	// �e�N���X�Ŏ��s�񐔂̉��Z�Ɣz��̊g�����Ă���̂ŌĂяo��
	BearAttackAction::BeginActionExecution(_enemy);
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName, 1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult BearSlashWeak::UpdateActionExecution()
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

void BearSlashWeak::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool BearSlashWeak::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();	
}

void BearSlashWeak::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<BearSlashWeak>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
