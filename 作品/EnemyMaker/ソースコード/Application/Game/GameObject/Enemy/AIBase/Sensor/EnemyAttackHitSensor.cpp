//---------- INCLUDES -----------
#include "EnemyAttackHitSensor.h"
#include "../../../../Component/CollisionComponent/EnemyAttackCapsuleCollisionComponent.h"
#include "../../../Player/Player.h"

EnemyAttackHitSensor::EnemyAttackHitSensor()
	: mbIsHit(false)
	, mDamage(0)
{
	// �����Ȃ�
}

EnemyAttackHitSensor::~EnemyAttackHitSensor()
{
	// �����Ȃ�
}

void EnemyAttackHitSensor::Init()
{
	// �������Ă��Ȃ���Ԃ��f�t�H���g
	mbIsHit = false;
	mDamage = 0;
}

void EnemyAttackHitSensor::Update()
{
	mbIsHit = false;
	mDamage = 0;

	// �R���W�������Z�b�g����Ă��邩�𔻒f����
	if (mAttackCollisions.size() == 0)
	{
		return;
	}
	
	// �v���C���[�ɓ������Ă���R���W�������Ȃ����m�F����
	for (std::weak_ptr<EnemyAttackCapsuleCollisionComponent> collision : mAttackCollisions)
	{
		// �Q�Ƃ��L���Ȃ̂����m�F����@�����Ȃ�X�L�b�v
		if (!collision.lock())
		{
			continue;
		}

		std::shared_ptr<EnemyAttackCapsuleCollisionComponent> validCollision = collision.lock();

		// �����ɓ������Ă���̂��𔻒f���� �������Ă��Ȃ�������X�L�b�v
		if (!validCollision->IsCurrentHit())
		{
			continue;
		}

		// �v���C���[�ɂ���������Ȃ��R���W�����Ȃ̂Ń_���[�W�����̂܂܉��Z����
		mbIsHit = true;
		mDamage = validCollision->GetDamage();
	}
}