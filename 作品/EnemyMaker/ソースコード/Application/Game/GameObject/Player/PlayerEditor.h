/**
* @file PlayerEditor.h
* @brief PlayerEditor�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ---------
#include "Player.h"

//-------- �O���錾 --------
class CinematicCamera;

/**
* @class PlayerDebugger
* @brief �v���C���[�̃p�����[�^�[�̒������s��
* @detail �����������v���C���[��n�����ƂŒ����ł���
*/
class PlayerEditor
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	PlayerEditor();

	/**
	* �f�X�g���N�^
	*/
	~PlayerEditor();

private:
	/** �v���C���[ */
	std::weak_ptr<Player> mPlayer;

	/** CharacterMoveComponent�ւ̎Q�� */
	std::weak_ptr<PlayerMovementComponent> mMoveComp;
	
	/** �i�s�����Ɍ��������ԑ��x */
	float mFaceDirectionInterpSpeed;

	/** �ō����x */
	float mMaxWalkSpeed;

	/** �X�P���^�����b�V�� */
	std::weak_ptr<SkeletalMeshComponent> mSkeletalMeshComp;

	/** �U���̃f�[�^ */
	std::weak_ptr<PlayerAttackData> mAttackData;

	/** ���S�������̃J���� */
	std::weak_ptr<CinematicCamera> mDeathCamera;

	/** Input�e�L�X�g�p�̕ϐ� */
	std::vector<std::string> mTempClipNameLeft;

	/** Input�e�L�X�g�p�̕ϐ� */
	std::vector<std::string> mTempClipNameRight;
public:
	/**
	* @fn Initialize
	* @brief ����������
	* @param �v���C���[�̕ҏW�������R���|�[�l���g��p�����[�^�[�Ȃǂւ̎Q�ƁA�|�C���^���擾���Ă���
	* @param const std::shared_ptr<Player> (_player)
	*/
	void Initialize(const std::shared_ptr<Player> _player);

	/**
	* @fn Uninitialize
	* @brief �I������
	* @return void
	*/
	void Uninitialize();

	/**
	* @fn Update
	* @brief �X�V����
	* @detail ImGui���g�p����GUI�ŕҏW���鏈�������Ă���
	* @return void
	*/
	void Update();

private:
	/**
	* @fn AttackHeader
	* @brief �U����ҏW�ł���w�b�_�[
	* @return void
	*/
	void AttackHeader();

	/**
	* @fn StepHeader
	* @brief �X�e�b�v��ҏW�ł���w�b�_�[
	* @return void
	*/
	void StepHeader();

	/**
	* @fn HitReactionHeader
	* @brief �q�b�g���A�N�V������ҏW�ł���w�b�_�[
	* @return void
	*/
	void HitReactionHeader();

	/**
	* @fn AttackNode
	* @brief �U���ҏW�p��TreeNode
	* @param const PlayerEntities::AttackID (_attackID)
	* @param std::string_view               (_nodeName)
	* @param const uint8_t                  (_tempString_i)
	* @return void
	*/
	void AttackNode(const PlayerData::AttackID _attackID, std::string_view _nodeName, const uint8_t _tempString_i);

	/**
	* @fn EffectNotifyNode
	* @brief �G�t�F�N�g�Đ��ʒm��ҏW����
	* @param const PlayerData::AttackID (_attackID)
	* @return void
	*/
	void EffectNotifyNode(const PlayerData::AttackID _attackID);

public:
	/**
	* @fn SetDeathCamera
	* @brief ���S�p�J�����̃Z�b�^�[
	* @param std::shared_ptr<CinematicCamera> (_camera)
	* @return void
	*/
	void SetDeathCamera(std::shared_ptr<CinematicCamera> _camera) noexcept;

};