/**
* @file PlayerAttackData.h
* @brief PlayerAttackData�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ---------
#include "PlayerData.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

/**
* @class PlayerAttackData
* @brief �v���C���[�̍U���̃f�[�^�����N���X
* @detail �v���C���[�̍U���̃f�[�^�ɃA�N�Z�X���₷���悤�Ƀ��b�v�����N���X
*/
class PlayerAttackData
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	PlayerAttackData();

	/**
	* �f�X�g���N�^
	*/
	~PlayerAttackData();

private:
	/** �U���̏�� */
	std::vector<PlayerAttack> mAttackInformation;

	/** �U���f�[�^�t�@�C���̃t�@�C���p�X */
	const std::string mAttackDataFilePath = "assets/Player/Config/AttackData.json";

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail �f�[�^�̐ݒ�����Ă���
	* @return void
	*/
	void Initialize();

	/**
	* @fn SaveJsonFile
	* @brief Json�t�@�C���ɃZ�[�u����
	* @return void
	*/
	void SaveJsonFile();

private:
	/**
	* @fn LoadAttackData
	* @brief �U���̃f�[�^��ǂݍ��ފ֐�
	* @return bool true �ǂݍ��ݐ��� false �ǂݍ��ݎ��s
	*/
	bool LoadAttackData();

	/**
	* @fn AddAttackDataToJson
	* @brief Json�I�u�W�F�N�g�ɍU���̃f�[�^���������ފ֐�
	* @param nlohmann::json& (_json) �������ݐ��Json�I�u�W�F�N�g
	* @param const AttackID& (_attackID) �������ލU����ID
	* @param std::string_view (_attackName) �������ލU���̖��O
	* @return void
	*/
	void AddAttackDataToJson(nlohmann::json& _json, const PlayerData::AttackID& _attackID, std::string_view _attackName);

	/**
	* @fn GetAttackDataFromJson
	* @brief Json�t�@�C������U���̃f�[�^���擾����
	* @param nlohmann::json& (_json) �f�[�^���͂����Ă���Json�I�u�W�F�N�g
	* @param const AttackID& (_attackID) �ǂݍ��݂����U����ID
	* @param std::string_view (_attackName) �������񂾂Ƃ��Ɠ������O���w�肷��悤��
	* @return void
	*/
	void GetAttackDataFromJson(nlohmann::json& _json, const PlayerData::AttackID& _attackID, std::string_view _attackName);

public:
	/**
	* @fn GetAttackInformation
	* @brief �U���f�[�^�̎擾
	* @param const PlayerEntities::AttackID (_attackID)
	* @return 
	*/
	inline PlayerAttack GetAttack(const PlayerData::AttackID _attackID) const;

	/**
	* @fn GetNextAttackInformation
	* @brief �����Ŏw�肳�ꂽ�U���̎���Y�{�^���U����Ԃ�
	* @param const PlayerEntities::AttackID (_attackID)
	* @return PlayerAttack ����Y�{�^���U��
	*/
	inline PlayerAttack GetNextYAttackInformation(const PlayerData::AttackID _attackID) const;

	/**
	* @fn GetNextBAttackInformation
	* @brief �����Ŏw�肳�ꂽ�U���̎���B�{�^���U����Ԃ�
	* @param const PlayerEntities::AttackID (_attackID)
	* @return PlayerAttack ����B�{�^���U��
	*/
	inline PlayerAttack GetNextBAttackInformation(const PlayerData::AttackID _attackID) const;

	/**
	* @fn SetAttackInformation
	* @brief �U���f�[�^�̃Z�b�g
	* @param const PlayerEntities::AttackID (_attackID)
	* @param const PlayerAttack& (_newAttackData)
	* @return
	*/
	inline void SetAttackInformation(const PlayerData::AttackID _attackID, const PlayerAttack& _newAttackData);

};


//----------- INLINES ------------
inline PlayerAttack PlayerAttackData::GetAttack(const PlayerData::AttackID _attackID) const
{
	return mAttackInformation[_attackID];
}

inline PlayerAttack PlayerAttackData::GetNextYAttackInformation(const PlayerData::AttackID _attackID) const
{
	PlayerData::AttackID nextYID =  mAttackInformation[_attackID].mNextY;
	return mAttackInformation[nextYID];
}

inline PlayerAttack PlayerAttackData::GetNextBAttackInformation(const PlayerData::AttackID _attackID) const
{
	PlayerData::AttackID nextBID = mAttackInformation[_attackID].mNextB;
	return mAttackInformation[nextBID];
}

inline void PlayerAttackData::SetAttackInformation(const PlayerData::AttackID _attackID, const PlayerAttack& _newAttackData)
{
	mAttackInformation[_attackID] = _newAttackData;
}
