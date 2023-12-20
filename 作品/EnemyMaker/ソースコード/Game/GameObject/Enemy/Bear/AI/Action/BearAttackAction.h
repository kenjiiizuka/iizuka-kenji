#pragma once
/**
* @file BearAttackAction.h
* @brief BearAttackAction�N���X�̒�`
*/

//---------- INCLUDES -----------
#include "../../../AIBase/GeneticAlgorithm/Gene/EnemyAttackAction.h"
#include "../../BearEnemyAttackData.h"

//--------- �O���錾 ------------
class BearAnimationInstance;
class BearEnemy;
class EnemyWeapon;

/**
* @class BearAttackAction
* @brief �F�̓G�̍U���s���̊��N���X
* @detail �F�̓G�̍U���s���̋��ʏ������܂Ƃ߂邽�߂ɒ�`����
*         ���̃N���X�𐶐����Ă��g�p���邱�Ƃ͂Ȃ�
*/
class BearAttackAction : public EnemyAttackAction
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param  std::shared_ptr<BlackBoard> (_blackBoard)
	*/
	BearAttackAction(std::shared_ptr<BlackBoard> _blackBoard);

protected:
	/** ���̍s��������G�l�~�[�̃A�j���[�V�����C���X�^���X */
	std::weak_ptr<BearAnimationInstance> mAnimInstance;

	/** ���̍s��������F�̓G */
	BearEnemy* mBearEnemy;

	/** �G�̎����Ă��镐�� */
	std::weak_ptr<EnemyWeapon> mWeapon;

	/** �Đ�����A�j���[�V�����N���b�v�̖��O */
	std::string mAnimationClipName;

public:
	/**
	 * @fn BeginActionExecution
	 * @brief �s���̊J�n����
	 * @return void
	*/
	virtual void BeginActionExecution(EnemyBase* _enemy);

	/**
	 * @fn EndActionExecution
	 * @brief �s���̏I������
	 * @return void
	*/
	virtual void EndActionExecution();

	/**
	* @fn IsExecuteAble
	* @brief �U�������s�\���𔻒f����֐�
	* @return bool true ���s�\ false ���s�s��
	*/
	virtual bool IsExecuteAble() override;

};

