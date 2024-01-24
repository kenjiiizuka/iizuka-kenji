/**
* @file BattleTimer.h
* @brief BattleTimer�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ---------
#include "../GameObject.h"
#include <array>

//--------- �O���錾 ---------
class SpriteComponent;
class AssetHandle;
class CurveFloat;

/**
* @enum TimerState
* @brief �^�C�}�[�̏�Ԃ�����
*/
enum class TimerState : uint8_t
{
	Stop = 0, /**< ��~�� */
	Count ,   /**< �v���� */
	End,      /**< �I�� */
};

/**
* @class BattleTimer
* @brief �퓬���̎��Ԃ�\������^�C�}�[
*/
class BattleTimer : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BattleTimer();

	/**
	* �f�X�g���N�^
	*/
	~BattleTimer();

private:
	/** �����p�e�N�X�`�� */
	std::array<std::shared_ptr<AssetHandle>, 10> mNumberTextures;

	/** �R�����e�N�X�`�� */
	std::shared_ptr<AssetHandle> mKoronTexture;

	/** �R���}�e�N�X�`�� */
	std::shared_ptr<AssetHandle> mCommaTexture;

	/** �����\���p�̃X�v���C�g �퓬���� [m(1��) : s(2��) : ms(2��)]�@�̏��ԂŎg�� : ���܂�*/
	std::array<std::weak_ptr<SpriteComponent>, 7> mSprites;
	
	/** �c�萧������ */
	double mTimeLimitSec;

	/** �o�ߎ��� */
	double mElapsedTimeSec;

	/** �^�C�}�[�̏�� */
	TimerState mState;

	/** �t���b�V���J�n����̌o�ߎ��� */
	double mFlashElapsedTime;

	/** �^�C�}�[�_�ŗp�J�[�u */
	std::shared_ptr<CurveFloat> mFlashCurve;

	/** �^�C�}�[�̍��[�̈ʒu */
	DirectX::SimpleMath::Vector2 mInitialPosition;

	/** �\�����镶���̃T�C�Y */
	DirectX::SimpleMath::Vector2 mSize;

public:
	/**
	* @fn Init
	* @brief ����������
	* @param const double (_timeLimit) �v�����鎞��
	* @param const DirectX::SimpleMath::Vector2 (_pos) �^�C�}�[�̏����ʒu
	* @return void
	*/
	void Init(const double _timeLimit, const DirectX::SimpleMath::Vector2 _pos = {530.0f, 5.0f});

	/**
	* @fn Update
	* @brief �X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn SetupTexture
	* @brief �c�莞�Ԃɍ��킹�ăe�N�X�`����ݒ肷��
	* @return void
	*/
	void SetupTexture();

	/**
	* @fn ConvertTimeToDrawFormat
	* @brief �c�莞�Ԃ� MSSSS �̌`���ɕϊ�����@�� �b(������Q��)
	* @param const double (_second) �ϊ����������� (�b)
	* @return uint16_t
	*/
	uint16_t ConvertTimeToDrawFormat(const double _second);

	/**
	* @fn TimerFlash
	* @brief ���X�g60�b�ɂȂ�����Ԃ��_�ł�����
	* @param const double (_deltaTime)
	* @return void
	*/
	void TimerFlash(const double _deltaTime);

	/**
	* @fn TimerVibration
	* @brief �^�C�}�[��U��������
	* @param const double (_deltaTime)
	* @return void
	*/
	void TimerVibration(const double _deltaTime);

public:
	/**
	* @fn TimerStart
	* @brief �^�C�}�[���X�^�[�g������֐�
	* @return void
	*/
	inline void TimerStart();

	/**
	* @fn TimerStop
	* @brief �^�C�}�[���~������
	* @return void
	*/
	inline void TimerStop();

	/**
	* @fn IsTimerEnd
	* @brief �^�C�}�[���I����������Ԃ�
	* @return bool true �I�� false �I�����Ă��Ȃ�
	*/
	inline bool IsTimerEnd() const noexcept;

	/**
	* @fn GetElapsedTime
	* @brief �o�ߎ��Ԃ�Ԃ�
	* @return double 
	*/
	inline double GetElapsedTime() const noexcept;

};

//--------- INLINES -----------

inline bool BattleTimer::IsTimerEnd() const noexcept
{
	return mState == TimerState::End;
}

inline void BattleTimer::TimerStart()
{
	mState = TimerState::Count;

	// �c�莞�Ԃɍ��킹�ăe�N�X�`����ݒ�
	SetupTexture();
}

inline void BattleTimer::TimerStop()
{
	mState = TimerState::Stop;
}

inline double BattleTimer::GetElapsedTime() const noexcept
{
	return mElapsedTimeSec;
}