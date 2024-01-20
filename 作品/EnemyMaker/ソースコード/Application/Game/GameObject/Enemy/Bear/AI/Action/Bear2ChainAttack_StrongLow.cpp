//---------- INCLUDES -----------
#include "Bear2ChainAttack_StrongLow.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../BearEnemy.h"
#include "../../../../../../Utility/MathLibrary.h"
#include "../../../AIBase/BlackBoard.h"

Bear2ChainAttack_StrongLow::Bear2ChainAttack_StrongLow(std::shared_ptr<BlackBoard> _blackBoard)
	: BearAttackAction(_blackBoard)
{
	mTypeName = typeid(Bear2ChainAttack_StrongLow).name();
	mAttackID = BearEnemyAttackData::DoubleSlash_StrongLow;
}

Bear2ChainAttack_StrongLow::~Bear2ChainAttack_StrongLow()
{
	// �����Ȃ�
}

void Bear2ChainAttack_StrongLow::BeginActionExecution(EnemyBase* _enemy)
{
	// �e�N���X�Ŏ��s�񐔂̉��Z�Ɣz��̊g�����Ă���̂ŌĂяo��
	BearAttackAction::BeginActionExecution(_enemy);
	mAnimInstance.lock()->PlayAnimationClip(mAnimationClipName, 1.0f, 0.2f);
	mAnimInstance.lock()->SetAttack(true);
}

EnemyActionResult Bear2ChainAttack_StrongLow::UpdateActionExecution()
{
	// ���O��ԏȗ�
	using namespace DirectX::SimpleMath;

	// �e�N���X���Ŏ��Ԃ̌v�������Ă���̂ŌĂяo��
	BearAttackAction::UpdateActionExecution();
		
	if (GetCurrentAnimationSection() == "FollowStart")
	{
		FollowRotation();
	}

	// �A�j���[�V�����̏I�����肪����ΐ�����Ԃ��A����ȊO�͎��s��
	std::shared_ptr<AnimationPlayer> animPlayer = mAnimInstance.lock()->GetAnimationPlayer();
	if (!animPlayer->IsPlay() || animPlayer->IsEndOnNextFrame())
	{
		return EnemyActionResult::Succeeded;
	}
	return EnemyActionResult::InProgress;
}

void Bear2ChainAttack_StrongLow::EndActionExecution()
{
	BearAttackAction::EndActionExecution();
	mAnimInstance.lock()->SetAttack(false);
}

bool Bear2ChainAttack_StrongLow::IsExecuteAble()
{
	return BearAttackAction::IsExecuteAble();
}

void Bear2ChainAttack_StrongLow::DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination)
{
	_destination = std::make_shared<Bear2ChainAttack_StrongLow>(mBlackBoard);
	_destination->SetAttackActionRiskType(mRiskType);
}
