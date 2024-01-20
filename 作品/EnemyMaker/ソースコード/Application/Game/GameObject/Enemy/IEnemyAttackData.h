/**
* @file IEnemyAttackData.h
* @brief IEnemyAttackData�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include "EnemyData.h"

/**
* @class IEnemyAttackData
* @brief �G�̍U���̏�����������ɃA�N�Z�X���₷���悤�ɂ����N���X
* @detail Initialize�֐����ōU���̏���ݒ肵�āA���̃N���X�������Ă���G�͂��̃N���X����U���̏����擾
*         �܂��A�A�N�Z�X���₷���悤�ɔh����̃N���X�Ŋe�U����ID�Ƃ��ė񋓌^���`���g�p����
*/
class IEnemyAttackData
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	IEnemyAttackData();

	/**
	* �f�X�g���N�^
	*/
	~IEnemyAttackData();

protected:
	/** �U���̏�� */
	std::vector<EnemyAttack> mAttackInformation;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail �U���̏��̐ݒ���s���Ă���
	* @return void
	*/
	virtual void Initialize() = 0;

	/**
	* @fn SaveData
	* @brief �U���f�[�^���Z�[�u����
	* @return void 
	*/
	virtual void SaveData() = 0;

	/**
	* @fn GetAttackInformation
	* @brief �U���̏����擾����֐�
	* @detail �����ɍU����ID��n�����Ƃ�ID�ɑΉ����čU���̏���Ԃ�
	* @param const uint8_t (_attackID)
	* @return EnemyAttack
	*/
	inline virtual EnemyAttack GetAttack(const uint8_t _attackID) const noexcept;

	/**
	* @fn SetAttackInformation
	* @brief �U���̃Z�b�^�[
	* @param const uint8_t (_attackID)
	* @param const EnemyAttack (_newAttack)
	* @return void
	*/
	inline virtual void SetAttackInformation(const uint8_t _attackID, const EnemyAttack _newAttack) noexcept;
};

//---------- INLINES ----------

inline EnemyAttack IEnemyAttackData::GetAttack(const uint8_t _attackID) const noexcept
{
	// �z��O�Q�Ƃ��Ȃ��悤�Ƀ`�F�b�N
	if (mAttackInformation.size() < _attackID)
	{
		return EnemyAttack();
	}

	return mAttackInformation[_attackID];	
}

inline void IEnemyAttackData::SetAttackInformation(const uint8_t _attackID, const EnemyAttack _newAttack) noexcept
{
	// �T�C�Y�`�F�b�N
	if (mAttackInformation.size() <= _attackID)
	{
		return;
	}

	mAttackInformation[_attackID] = _newAttack;
}


