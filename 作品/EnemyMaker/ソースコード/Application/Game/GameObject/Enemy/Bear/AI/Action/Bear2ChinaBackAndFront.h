/**
* @file Bear2ChinaBackAndFront.h
* @brief Bear2ChinaBackAndFront�N���X
*/

#pragma once

//--------- INCLUDES ---------
#include "BearAttackAction.h"

/**
* @class Bear2ChinaBackAndFront
* @brief ���ɐU������Ȃ��猕��U���āA�O�Ɍ����Ȃ����Ȃ��猕��U��U��
*/
class Bear2ChinaBackAndFront : public BearAttackAction
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param std::shared_ptr<Blackboard> (_blackboard)
	*/
	Bear2ChinaBackAndFront(std::shared_ptr<BlackBoard> _blackBoard);

	/**
	* �f�X�g���N�^
	*/
	~Bear2ChinaBackAndFront();

public:
	/**
	 * @fn BeginActionExecution
	 * @brief �s���̊J�n����
	 * @return void
	*/
	virtual void BeginActionExecution(EnemyBase* _enemy);

	/**
	 * @fn UpdateActionExecution
	 * @brief �s���̍X�V����
	 * @return EnemyActionResult
	*/
	virtual EnemyActionResult UpdateActionExecution();

	/**
	 * @fn EndActionExecution
	 * @brief �s���̏I������
	 * @return void
	*/
	virtual void EndActionExecution();

	/**
	 * @fn IsExecuteAble
	 * @brief ���̍s�������s�\���𔻒f����֐�
	 * @return bool true : ���s�\ false ���s�s��
	*/
	virtual bool IsExecuteAble();

	/**
	 * @fn DuplicateFromSelfType
	 * @brief ���g�Ɠ����^�������œn���ꂽ�l�ɐV���ɐ�������
	 * @param std::shared_ptr<EnemyAttackAction>& (_destination)
	 * @return void
	*/
	virtual void DuplicateFromSelfType(std::shared_ptr<EnemyAttackAction>& _destination);
};

