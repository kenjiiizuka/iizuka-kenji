#pragma once // �C���N���[�h�K�[�h

/**
* @file EnemyAttackHitSensor.h
* @brief EnemyAttackHitSensor�N���X�̒�`
*/

//-------- INCLUDES ---------
#include <memory>
#include <vector>

//-------- �O���錾 ---------
class EnemyAttackCapsuleCollisionComponent; // �G�l�~�[�̍U���p�����蔻��N���X

/**
* @class EnemyAttackHitSensor
* @brief �G�l�~�[�̍U���������������������Ă��Ȃ������ώ@���Č��ʂ�����
* @detail �n���ꂽ�G�l�~�[�̍U���R���W�������ώ@���A�v���C���[�ɓ������Ă��邩�𔻒f����
*         �R���W�����͕����ł��\�ŁA���̍ۂ͂ǂꂩ����������Ă���Γ������Ă��邱�ƂȂ�
*/
class EnemyAttackHitSensor final
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	EnemyAttackHitSensor();

	/**
	* �f�t�H���g�f�X�g���N�^
	*/
	~EnemyAttackHitSensor();

private:
	/** ���s���Ă���U���̓����蔻�� */
	std::vector<std::weak_ptr<EnemyAttackCapsuleCollisionComponent>> mAttackCollisions;
	
	/** �q�b�g���Ă��邩 */
	bool mbIsHit;

	/** �q�b�g�����R���W�����̃_���[�W */
	float mDamage;

public:
	/**
	 * @fn Init
	 * @brief ����������
	 * @return void
	*/
	void Init();

	/**
	 * @fn Update
	 * @brief �X�V����
	 * @detail �Z�b�g����Ă��铖���蔻����ώ@���A�������Ă��邩�𔻒f����
	 * @return void
	*/
	void Update();

	/**
	 * @fn SetCollision
	 * @brief �ώ@�������R���W�����𕡐��Z�b�g����֐�
	 * @param const std::vector<std::weak_ptr<EnemyAttackCapsuleCollisionComponent>> _attackCollisions
	 * @return void
	*/
	inline void SetCollision(const std::vector<std::weak_ptr<EnemyAttackCapsuleCollisionComponent>> _attackCollisions);

	/**
	 * @fn SetCollision
	 * @brief �ώ@�������R���W�������Z�b�g����֐�
	 * @param const std::weak_ptr<EnemyAttackCapsuleCollisionComponent> _attackCollision
	 * @return void
	*/
	inline void SetCollision(const std::weak_ptr<EnemyAttackCapsuleCollisionComponent> _attackCollision);

	/**
	 * @fn IsCollisionHit
	 * @brief �U�����q�b�g��������Ԃ�
	 * @return bool true �q�b�g false �q�b�g���Ă��Ȃ�
	*/
	inline bool IsCollisionHit() const noexcept;

	/**
	 * @fn GetHitDamage
	 * @brief �q�b�g�����R���W�����̃_���[�W��Ԃ�
	 * @return float
	*/
	inline float GetHitDamage() const noexcept;

};

//---------- INLINES ---------
inline void EnemyAttackHitSensor::SetCollision(const std::vector<std::weak_ptr<EnemyAttackCapsuleCollisionComponent>> _attackCollisions)
{
	mAttackCollisions = _attackCollisions;
}

inline void EnemyAttackHitSensor::SetCollision(const std::weak_ptr<EnemyAttackCapsuleCollisionComponent> _attackCollision)
{
	// �������łɃZ�b�g����Ă���ꍇ�̂��߂ɃN���A����
	mAttackCollisions.clear();
	mAttackCollisions.push_back(_attackCollision);
}

inline bool EnemyAttackHitSensor::IsCollisionHit() const noexcept
{
	return mbIsHit;
}

inline float EnemyAttackHitSensor::GetHitDamage() const noexcept
{
	return mDamage;
}
