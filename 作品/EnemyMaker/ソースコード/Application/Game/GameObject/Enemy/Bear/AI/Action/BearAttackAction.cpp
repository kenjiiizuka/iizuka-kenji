//---------- INCLUDES -------------
#include "BearAttackAction.h"
#include "../../../AIBase/BlackBoard.h"
#include "../../../EnemyWeapon.h"
#include "../../BearEnemy.h"
#include "../../../AIBase/Sensor/EnemyAttackHitSensor.h"
#include "../../Animation/BearAnimationinstance.h"
#include "../../../../../../Utility/MathLibrary.h"
#include "../../../../../../Utility/DetectorUtility.h"
#include "../../../../../Resource/SkeletalMeshAnimationClip.h"

//------------ NAMESPACEAILAS --------------
using namespace DirectX::SimpleMath;

BearAttackAction::BearAttackAction(std::shared_ptr<BlackBoard> _blackBoard)
	: EnemyAttackAction(_blackBoard)
	, mBearEnemy(nullptr)
{
	// �����Ȃ�
}

void BearAttackAction::BeginActionExecution(EnemyBase* _enemy)
{
	EnemyAttackAction::BeginActionExecution(_enemy);

	// �A�j���[�V�����C���X�^���X�A�G�A����̎Q�Ƃ��擾����
	std::weak_ptr<AnimationInstance> animIns = _enemy->GetAnimationInstance();	
	mAnimInstance = std::static_pointer_cast<BearAnimationInstance>(animIns.lock());
	mBearEnemy = static_cast<BearEnemy*>(mEnemy);
	mWeapon = mBearEnemy->GetWeapon();

	EnemyAttack attack = mBearEnemy->GetAttackData().lock()->GetAttack(mAttackID);

	// �Đ�����A�j���[�V�����N���b�v�̖��O���擾����
	mAnimationClipName = attack.mAnimationClipName;
	
	// �A�C�h���A�j���[�V�����ւ̕�ԑ��x���Z�b�g����
	mAnimInstance.lock()->SetToIdleRunInterpTime(attack.mToIdleRunInterpTime);

	// �Z���T�[�ɃR���W�������Z�b�g����
	mHitSensor->SetCollision(mWeapon.lock()->GetAttackCollision());
}

void BearAttackAction::EndActionExecution()
{
	EnemyAttackAction::EndActionExecution();
}

bool BearAttackAction::IsExecuteAble()
{
	if (!mBearEnemy)
	{
		mBearEnemy = static_cast<BearEnemy*>(mEnemy);
	}

	// ���s�������擾
	EnemyAttackExecutionConditions conditions = mBearEnemy->GetAttackData().lock()->GetAttack(mAttackID).mExecutionCondition;

	 std::shared_ptr<TransformComponent> transform = mBearEnemy->GetComponent<TransformComponent>();
	Vector3 forward = transform->GetForwardVector();
	Vector3 enemyPos = transform->GetPosition();

	// �v���C���[�̈ʒu
	Vector3 targetPos = mBlackBoard->GetValue<Vector3>("TargetPosition");
	// �f�o�b�O�\���p�̃J���[��ݒ� �f�t�H���g�͎�
	Vector4 color = {0.7f,0.0f,1.0f,1.0f};
	
	bool isExecute = false;
	for (size_t condition_i = 0; condition_i < conditions.mExecuteCheckCircleNum; condition_i++)
	{
		// �O�����x�N�g������]�����A����~�ւ̕����x�N�g���ɂ���
		Vector3 rotation = { 0.0f,conditions.mAngle[condition_i], 0.0f };
		Vector3 toCircleVector = MathLibrary::RotateVector(forward,rotation);

		// �~�̈ʒu�����߂�
		Vector3 circleCenter = toCircleVector * conditions.mDistance[condition_i] + enemyPos;

		// ����~���ɓ����Ă��邩���m�F����
	 	isExecute = DetectorUtility::IsPositionInCircle2D(
			{ targetPos.x, targetPos.z },
			{ circleCenter.x, circleCenter.z },
			conditions.mCircleRadius[condition_i],
			color
			);

		// ���s�\�Ȃ�ture��Ԃ�
		if (isExecute)
			return true;
	}

	return isExecute;
}

void BearAttackAction::FollowRotation(const float _followLevel)
{
	// �v���C���[����������Yaw�����߂�
	std::shared_ptr<TransformComponent> enemyTrans = mEnemy->GetComponent<TransformComponent>();
	float lookAtPlayerYaw = MathLibrary::LookAtYaw(enemyTrans->GetPosition(), mBlackBoard->GetValue<Vector3>("TargetPosition"));

	// �v���C���[�����̃N�H�[�^�j�I���쐬
	Quaternion targetQuat = { 0.0f, lookAtPlayerYaw, 0.0f, 1.0f };

	// �G�l�~�[�̉�]���N�H�[�^�j�I���ɕϊ�	
	Vector3 enemyRotation = enemyTrans->GetRotation();
	Quaternion enemyQuat;
	MathLibrary::ConvRotationToQuaternion(enemyRotation, enemyQuat);

	
	// ���݂̃G�l�~�[�̃N�H�[�^�j�I������v���C���[�̕��������N�H�[�^�j�I���֕�Ԃ���
	Vector3 newRotation = MathLibrary::LerpQuaternion(enemyQuat, targetQuat, static_cast<float>(mEnemy->GetCustomDeltaTime()), 1.0f);

	// ��]���Z�b�g����
	enemyTrans->SetRotation(newRotation);
}

std::string BearAttackAction::GetCurrentAnimationSection() const noexcept
{
	std::string section = mAnimInstance.lock()->GetAnimationPlayer()->GetPlayAnimation().lock()->GetCurrentSection();
	return section;
}

