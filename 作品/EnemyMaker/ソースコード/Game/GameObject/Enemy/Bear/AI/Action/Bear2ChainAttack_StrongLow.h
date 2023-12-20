/**
* @file Bear2ChainAttack_StrongLow.h
* @brief Bear2ChainAttack_StrongLow�N���X�̒�`
*/

#pragma once

//-------- INCLUDES ----------
#include "BearAttackAction.h"


/**
* @class Bear2ChainAttack_StrongLow
* @brief �F�̕�����A���ŐU��U�� �n�ʂ𔇂킹��悤�ɕ����U��U���ł�
*/
class Bear2ChainAttack_StrongLow : public BearAttackAction
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param  std::shared_ptr<BlackBoard> (_blackBoard)
	*/
	Bear2ChainAttack_StrongLow(std::shared_ptr<BlackBoard> _blackBoard);

	/**
	* �f�X�g���N�^
	*/
	~Bear2ChainAttack_StrongLow();

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

