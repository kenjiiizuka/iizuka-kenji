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
class CinematicCamera;

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

	/** ���S���̃J���� */
	std::weak_ptr<CinematicCamera> mDeathCamera;

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
	* @fn CollisionOnFrameNode
	* @brief �����蔻�肪�I���ɂȂ�t���[����ҏW����m�[�h
	* @param EnemyAttack _attackData
	* @return void
	*/
	void CollisionOnFrameNode(EnemyAttack& _attackData);

	/** 
	* @fn CameraShakeNode
	* @brief �J�����U����ҏW����m�[�h
	* @param (_attack)
	* @return void
	*/
	void CameraShakeNode(EnemyAttack _attackData);

	/**
	* @fn EffectNode
	* @brief �G�t�F�N�g�Đ��ʒm�̕ҏW���s���m�[�h
	* @param EnemyAttack (_attackData)
	* @return void
	* 
	*/
	void EffectNode(EnemyAttack _attackData);

	/**
	* @fn PlayAttack
	* @brief �U�������s����֐�
	* @param std::shared_ptr<EnemyAttackAction>& (_attack)
	* @return void
	*/
	void PlayAttack(std::shared_ptr<EnemyAttackAction>& _attack);

public:
	/**
	* @fn SetDeathCamera
	* @brief ���S���̃J�������Z�b�g����
	* @param std::shared_ptr<CinematicCamera> (_camera)
	* @return void
	*/
	void SetDeathCamera(std::shared_ptr<CinematicCamera> _camera) noexcept;

};