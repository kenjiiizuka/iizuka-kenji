/**
* @file BattleManager.h
* @brief BattleManager�N���X�̒�`
*/

#pragma once
//------- INCLUDES --------
#include <memory>
#include <functional>

//------- �O���錾 ----------
class Player;
class EnemyBase;
class GameObject;
class BattleStartLogo;
class BattleSoundManager;

/**
* @class BattleManager
* @brief �o�g���̐i�s���Ǘ�����
* @detail �o�g�����̊J�n�⃊�U���g�Ȃǂ̏��������s����
*         �v���C���[�ƓG�̗̑͂��Ď����ď����A�s�k�𔻒f����
*/
class BattleManager
{
public:
	/**
	* @enum BattleState
	* @brief �o�g���̏�Ԃ��������߂̗񋓌^
	*/
	enum BattleState : uint8_t
	{
		Battle_Start = 0,    /**< �o�g���J�n�X�e�[�g */
		Battle_InProgress,   /**< �o�g���i�s�� */
		Battle_Result,       /**< �o�g�����U���g */
	};

	/**
	* @enum BattleResult
	* @brief �퓬�̌��ʂ��������߂̗񋓌^
	*/
	enum BattleResult : uint8_t
	{
		Result_Win = 0,    /**< �v���C���[�̏��� */
		Result_Lose,       /**< �v���C���[�̕��� */
		Result_InProgress, /**< �퓬�� */
	};

public:
	/**
	* �f�t�H���g�R���g���N�^
	*/
	BattleManager();

	/**
	* �f�X�g���N�^
	*/
	~BattleManager();

private:
	/** �o�g�������Ă���v���C���[ */
	std::weak_ptr<Player> mPlayer;

	/** �o�g�������Ă���G�l�~�[ */
	std::weak_ptr<EnemyBase> mEnemy;

	/** ���U���g�̃��S�I�u�W�F�N�g */
	std::weak_ptr<GameObject> mResultLogo;

	/** �퓬�J�n�̃��S */
	std::weak_ptr<BattleStartLogo> mStartLogo;

	/** �o�g���X�e�[�g */
	BattleState mState;

	/** ���̃X�e�[�g�̍X�V�����֐� */
	std::function<void()> mCurrentStateUpdate;

	/** �퓬�̌o�ߎ��� */
	double mBattleElapsedTime;

	/** �퓬�̏��s */
	BattleResult mResult;

	/** �퓬�ɂ������T�E���h���Ǘ��Đ�����N���X */
	std::shared_ptr<BattleSoundManager> mBattleSoundManager;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail �v���C���[�ƃG�l�~�[�̎Q�Ƃ��擾���A�J�n���o�����̏���������
	* @param const std::shared_ptr<Player>      (_player)
	* @param const std::shared_ptr<EnemyBase>   (_enemy)
	* @return void
	*/
	void Initialize(const std::shared_ptr<Player> _player, const std::shared_ptr<EnemyBase> _enemy);

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update();

private:
	/**
	* @fn StartStateUpdate
	* @brief �X�^�[�g�X�e�[�g�̍X�V����
	* @return void
	*/
	void StartStateUpdate();

	/**
	* @fn BattleStateUpdate
	* @brief �퓬�X�e�[�g�̍X�V����
	* @return void
	*/
	void BattleStateUpdate();

	/**
	* @fn ResultStateUpdate
	* @brief ���U���g�X�e�[�g�̍X�V����
	* @return void
	*/
	void ResultStateUpdate();
	
	/**
	* @fn TransitionState
	* @brief �X�e�[�g�؂�ւ��֐�
	* @param std::function<void()> (_stateFunc)
	* @param const BattleState     (_state)
	* @return void
	*/
	void TransitionState(std::function<void()> _stateFunc, const BattleState _state);

	/**
	* @fn CheckBattleResult
	* @brief �퓬�̃��U���g���m�F����
	* @return BattleResult
	*/
	BattleResult CheckBattleResult();

	/**
	* @fn LoseUpdate
	* @brief �s�k�������̍X�V����
	* @return void
	*/
	void LoseUpdate();

	/**
	* @fn WinUpdate
	* @brief �����������̍X�V����
	* @return void
	*/
	void WinUpdate();

public:
	/**
	* @fn GetBattleState
	* @brief �o�g���̏�Ԃ�Ԃ�
	* @return BattleState �o�g���̏��
	*/
	inline BattleState GetBattleState() const noexcept;

};

//-------- INLINES ----------

inline BattleManager::BattleState BattleManager::GetBattleState() const noexcept
{
	return mState;
}
