/**
* @file BattleSoundManager.h
* @brief BattleSoundManager�N���X�̒�`
*/

#pragma once

//--------- INCLUDES -----------
#include <memory>

//------ �O���錾 -------
class AudioClip;

/**
* @class BattleSoundManager
* @brief �퓬����BGM�A�s�k�A�N���A�Ȃǂ̃o�g���Ɋւ���T�E���h�̍Đ��A�؂�ւ�������N���X
*/
class BattleSoundManager
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BattleSoundManager();

	/**
	* �f�X�g���N�^
	*/
	~BattleSoundManager();

private:
	/** �퓬�J�n�̉� */
	std::shared_ptr<AudioClip> mBattleStartSE;

	/** �퓬����BGM */
	std::shared_ptr<AudioClip> mBattleBGM;
	
	/** �N���ABGM */
	std::shared_ptr<AudioClip> mClearBGM;

	/** �s�kBGM */
	std::shared_ptr<AudioClip> mLoseBGM;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @return void
	*/
	void Initialize();

	/***/
	void Update();

	/**
	* @fn PlayBattleBGM
	* @brief �퓬BGM���Đ�����
	* @return void
	*/
	void PlayBattleBGM();

	/**
	* @fn StopBGM
	* @brief �Đ�����Ă���BGM���~�߂�
	* @return void
	*/
	void StopBattleBGM();

};

