/**
* @file BearEnemyAttackData.h
* @brief BearEnemyAttackData�N���X�̒�`
*/
#pragma once

//--------- INCLUDES ----------
#include "../IEnemyAttackData.h"
#include <nlohmann/json.hpp>

/**
* @class BearEnemyAttackData
* @brief �F�̓G�̍U���̏������N���X
*/
class BearEnemyAttackData : public IEnemyAttackData
{
public:
	/**
	* @enum
	* @brief �F�̓G�̍U����ID
	* @detail BearEnemyAttackData���ɒ�`���Ĕz��̓Y�����Ƃ��Ďg���₷���悤�ɂ��Ă���
	*/
	enum AttackID : uint8_t
	{
		ArmSmash = 0,          /**< �r�ŉ���U�� */
		ArmUpperSmash,         /**< �����U��U�� �� */
		DownwardSlash,         /**< �����U�艺�낷�U�� */
		DownwardSlashStrong,   /**< ����U�艺�낵 �� */
		UpwardSlash,           /**< �����U��グ��U�� */
		DoubleSlash,           /**< �����2��U��U�� */
		DoubleSlash_Strong,    /**< �����2��U��U�� �� */
		DoubleSlash_StrongLow, /**< �������n�ʂ𔇂��悤�ɐU��U�� �� */
		TripleSlash,           /**< �����3��U��U�� */
		JumpSlash,             /**< �W�����v���ĕ����U��U�� */
		BackAndFrontSlash,     /**< ���ƑO�ɕ�����U�� */
		Kick,                  /**< �R��U�� */
		BackJumpSlash,         /**< �؂艺���� */
		Max,                   /**< �ő吔 */
	};


public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BearEnemyAttackData();

	/**
	* �f�X�g���N�^
	*/
	~BearEnemyAttackData();

private:
	/** �U���̃f�[�^���Z�[�u����t�@�C���p�X */
	const std::string mSaveDataFilePath = "assets/Enemy/Config/AttackData.json";

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail �U���̏���ݒ肵�Ă��܂�
	*/
	void Initialize() override;

	/**
	* @fn SaveData
	* @brief �U���f�[�^�̕ۑ�
	* @return void
	*/
	void SaveData() override;

private:
	/**
	* @fn AddAttackDataToJson
	* @brief json�I�u�W�F�N�g�ɍU���̃f�[�^��ǉ�����
	* @param nlohmann::json&  (_json)
	* @param const AttackID&  (_id)
	* @param std::string_view (_dataName)
	* @return void
	*/
	void AddAttackDataToJson(nlohmann::json& _json, const AttackID& _id, std::string_view _dataName);

	/**
	* @fn LoadData
	* @brief �f�[�^�̓ǂݍ��݂�����
	* @return bool true �ǂݍ��ݐ��� false �ǂݍ��ݎ��s
	*/
	bool LoadData();

	/**
	* @fn GetAttackDataFromJson
	* @brief Json�t�@�C������U���̃f�[�^��ǂݍ���
	* @param nlohmann::json& (_json)
	* @param const AttackID& (_id)
	* @param std::string_view (_dataName)
	* @return void
	*/
	void GetAttackDataFromJson(nlohmann::json& _json, const AttackID& _id, std::string_view _dataName);

};

