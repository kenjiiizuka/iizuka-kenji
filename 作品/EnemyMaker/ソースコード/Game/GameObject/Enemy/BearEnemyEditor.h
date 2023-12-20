/**
* @file BearEnemyEditor.h
* @brief EnemyEditor�N���X�̒�`
*/

#pragma once

//-------- INCLUDES ----------
#include "../Enemy/EnemyBase.h"

//--------- �O���錾 ----------
class EnemyAttackAction;
class EnemyActionProcessor;

/**
* @class EnemyEditor
* @brief �G�l�~�[�p�̃G�f�B�^�[
*/
class BearEnemyEditor
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BearEnemyEditor();

	/**
	* �f�X�g���N�^
	*/
	~BearEnemyEditor();

private:
	/** �ҏW����G�l�~�[ */
	std::weak_ptr<EnemyBase> mEditEnemy;

	/** �U�������s����p�̃v���Z�b�T�[ */
	std::shared_ptr<EnemyActionProcessor> mActionProcessor;

	/** �ҏW�������U���s�� */
	std::vector<std::shared_ptr<EnemyAttackAction>> mAttackActions;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @param std::shared_ptr<EnemyBase> (_enemy)
	* @return void
	*/
	void Initialize(std::shared_ptr<EnemyBase> _enemy);

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update();

private:
	/**
	* @fn AttackHeader
	* @brief �G�̍U����ҏW����w�b�_�[
	* @param std::shared_ptr<EnemyAttackAction>& (_attack)
	* @return void
	*/
	void AttackHeader();

	/**
	* @fn AttackNode
	* @brief �G�̍U����ҏW����m�[�h
	* @param std::shared_ptr<EnemyAttackAction>& (_attack) �ҏW����U��
	* @return void
	*/
	void AttackNode(std::shared_ptr<EnemyAttackAction>& _attack);

	/** 
	* @fn CameraShakeNode
	* @brief �J�����U����ҏW����m�[�h
	* @param _attack
	*/
	void CameraShakeNode(EnemyAttack _attackData);

	/**
	* @fn PlayAttack
	* @brief �U�������s����֐�
	* @param std::shared_ptr<EnemyAttackAction>& (_attack)
	* @return void
	*/
	void PlayAttack(std::shared_ptr<EnemyAttackAction>& _attack);

};