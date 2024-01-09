/**
* @file SkeletalMeshAnimationClip.h
* @brief SkeletalMeshAnimationClip�N���X�̒�`
*/

#pragma once

//------------ INCLUDES -----------
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "../../System/AssetSystem/SkeletalMesh/SkeletalMeshAnimationData.h"
#include "../Component/SkeletalMeshComponent/AnimationNotifyState.h"

//------------ �O���錾 -----------
class AssetHandle;
class SkeletalMesh;


//--------- TEMPLATE ------------
template<typename Derived, typename Base>
concept DerivedAnimationNotify = std::is_base_of<Base, Derived>::value;

template<typename Derived, typename Base>
concept DerivedAnimationNotifyState = std::is_base_of<Base, Derived>::value;


/**
* @class SkeletalMeshAnimationClip
* @brief �A�j���[�V�����𐧌�A�Đ����邽�߂ɕK�v�ȃf�[�^�ւ̃A�N�Z�X�����₷������ׂ�
*        SkeletalMeshAnimationAsset�����b�v�����N���X
*/
class SkeletalMeshAnimationClip
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SkeletalMeshAnimationClip();

	/**
	* �f�X�g���N�^
	*/
	virtual ~SkeletalMeshAnimationClip();

private:
	/** �A�j���[�V�����A�Z�b�g�̃n���h�� */
	std::shared_ptr<AssetHandle> mAnimationAssetHandle;

	/** �A�j���[�V�����ʒm�̔z�� �ʒm�Ƃ��̒ʒm���A�^�b�`�����t���[���� */
	std::vector<std::pair<std::shared_ptr<AnimationNotify>, float>> mAnimNotifies;

	/** �A�^�b�`����Ă���A�j���[�V�����ʒm�X�e�[�g�̔z�� */
	std::vector<std::shared_ptr<AnimationNotifyState>> mAnimNotifyStates;

	/** �A�j���[�V�����̖��O */
	std::string mAnimationName;

protected:
	/** �L�[�t���[���f�[�^�����`�����l�� */
	std::vector<Channel> mChannels;

	/** �A�j���[�V�����̒��� */
	float mDuration;

	/** �A�j���[�V�����̏I���t���[�� */
	float mEndFrame;

	/** ��b�Ԃɐi�ރA�j���[�V�����̒��� */
	float mTickPerSeconds;

	/** ���[�v�Đ����邩 */
	bool mbLoop;

	/** �ʒu�𓯊������邩 */
	bool mbSynchroPosition;

	/** ��]�𓯊����� */
	bool mbSynchroRotation;

	/** �J�n�����[�g���炸�ꂽ�ʒu�ł��邱�Ƃ����� */
	bool mbDisplacedStartAnimation;

	/** �ʒm���������s������ */
	std::vector<bool> mbNotifyExecuted;

	/** �ʒm�̊J�n������������ �e�ʒm�X�e�[�g���ƂɃt���O���Ǘ����� */
	std::vector<bool> mbNotifyStateBeginExecuted;

	/** �ʒm�̏I�������������� �e�ʒm�X�e�[�g���ƂɃt���O���Ǘ����� */
	std::vector<bool> mbNotifyStateEndExecuted;

	/** �A�j���[�V�������K�������X�P���^�����b�V�� */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;

	/** ���݂̍Đ����� */
	float mCurrentPlayTime;

	/** ���݂̃Z�N�V���� */
	std::string mCurrentSection;

	/** �A�j���[�V�����ɐݒ肳��Ă���Z�N�V���� �f�t�H���g�ł� "Default" �Z�N�V�����ݒ肳��Ă��� */
	std::vector<std::pair<uint16_t, std::string>> mSections;

public:
	/**
	* @fn Initialize
	* @brief ����������
	* @detail �w�肳�ꂽ�A�j���[�V�����f�[�^��ǂݍ��݂����ǂݍ��񂾃A�Z�b�g�̃n���h�����擾
	* @param const std::string&     (_filePath)
	* @return void
	*/
	virtual void Initialize(const std::string& _filePath);

	/**
	* @fn Begin 
	* @brief �A�j���[�V�����̊J�n����
	* @return void
	*/
	virtual void Begin();

	/**
	* @fn Update
	* @brief �X�V����
	* @param const float (_currentPlayTime)
	* @return void
	*/
	virtual void Update(const float _currentPlayTime);

private:
	/**
	* @fn PositionKeyLerp
	* @brief �n���ꂽ�`�����l���̎w�肳�ꂽ���ԂɑΉ�������W���L�[�t���[���Ԃŕ⊮���ĕԂ�
	* @param const float                   (_time)
	* @param DirectX::SimpleMath::Vector3& (_outPutPosition)
	* @param Channel&                      (_channel)
	* @return void
	*/
	void PositionKeyLerp(const double& _time, DirectX::SimpleMath::Vector3& _outPutPosition, Channel& _channel);

	/**
	* @fn RotationKeyLerp
	* @brief �n���ꂽ�`�����l���̎w�肳�ꂽ���ԂɑΉ������]���L�[�t���[���Ԃŕ⊮���ĕԂ�
	* @param const double                      (_time)
	* @param DirectX::SimpleMath::Quaternion&  (_outPutQuaternion)
	* @param Channel&                          (_channel)
	* @return void
	*/
	void RotationKeyLerp(const double& _time, DirectX::SimpleMath::Quaternion& _outPutQuaternion, Channel& _channel);

	/**
	* @fn ScaleKeyLerp
	* @brief �n���ꂽ�`�����l���̎w�肳�ꂽ���ԂɑΉ�����X�P�[�����L�[�t���[���Ԃŕ⊮���ĕԂ�
	* @param const double                   (_time)
	* @param DirectX::SimpleMath::Vector3&  (_outPutScale)
	* @param Channel&                       (_channel)
	* @return void
	*/
	void ScaleKeyLerp(const double& _time, DirectX::SimpleMath::Vector3& _outPutScale, Channel& _channel);

	/**
	* @fn CheckCurrentSection
	* @brief ���݂̃Z�N�V�������ǂꂩ�𔻒f���Đݒ肷��
	* @return void
	*/
	void CheckCurrentSection();

public:

	/**
�@�@ * @fn�@AddAnimationNotify
�@�@ * @brief �A�j���[�V�����ʒm�̒ǉ��֐�
	 * @param float (_attachFrame) �A�^�b�`����t���[��
�@�@ * @return std::shared_ptr<T> �ǉ������A�j���[�V�����ʒm�N���X�̎Q��
�@�@*/
	template<typename T>
	requires DerivedAnimationNotify<T, AnimationNotify>
	std::shared_ptr<T> AddAnimationNotify(float _attachFrame)
	{
		std::pair<std::shared_ptr<AnimationNotify>, float> animNotify;
		animNotify.first = std::make_shared<T>(this, _attachFrame);
		animNotify.second = _attachFrame;
		animNotify.first->SetAttachFrame(_attachFrame);
		mAnimNotifies.emplace_back(animNotify);	
		mbNotifyExecuted.emplace_back(false);
		return std::static_pointer_cast<T>(animNotify.first);
	}

	/**
�@�@ * @fn�@AddAnimationNotifyState
�@�@ * @brief �A�j���[�V�����ʒm�X�e�[�g�̒ǉ��֐�
	 * @param float (_attachStartFrame) �A�^�b�`����J�n�t���[��
	 * @param float (_attachEndFrame) �A�^�b�`����I���t���[��
�@�@ * @return std::shared_ptr<T> �ǉ������A�j���[�V�����ʒm�X�e�[�g�N���X�̎Q��
�@�@*/
	template<typename T>
	requires DerivedAnimationNotifyState<T, AnimationNotifyState>
	std::shared_ptr<T> AddAnimationNotifyState(uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	{
		std::shared_ptr<AnimationNotifyState> notifyState;
		notifyState = std::make_shared<T>(this, _attachStartFrame, _attachEndFrame);
		mAnimNotifyStates.emplace_back(notifyState);
		mbNotifyStateBeginExecuted.emplace_back(false);
		mbNotifyStateEndExecuted.emplace_back(false);
		return std::static_pointer_cast<T>(notifyState);
	}

	/**
�@�@ * @fn�@GetAnimationNotify
�@�@ * @brief �A�j���[�V�����ʒm�̎擾�֐�
�@�@ * @return std::shared_ptr<T> �w�肵���A�j���[�V�����ʒm
�@�@*/
	template<typename T>
	requires DerivedAnimationNotify<T, AnimationNotify>
	std::shared_ptr<T> GetAnimnotify()
	{
		for (std::pair<std::shared_ptr<AnimationNotify>, float>& notify : mAnimNotifies)
		{
			if (typeid(*notify.first.get()) == typeid(T))
			{
				return std::static_pointer_cast<T>(notify.first);
			}
		}
		return nullptr;
	}

	/**
	* @fn GetAllAnimationNotify
	* @brief �A�^�b�`����Ă���w�肳�ꂽ�^�̃A�j���[�V�����X�e�[�g�����ׂĕԂ�
	* @return std::vector<std::shared_ptr<T>>
	*/
	template<typename T>
	requires DerivedAnimationNotify<T, AnimationNotify>
	inline std::vector<std::shared_ptr<T>> GetAllAnimationNotify();

	/**
�@�@ * @fn�@GetAnimationNotifyState
�@�@ * @brief �A�j���[�V�����ʒm�̃X�e�[�g�擾�֐�
�@�@ * @return std::shared_ptr<T> �w�肵���A�j���[�V�����ʒm�X�e�[�g
�@�@*/
	template<typename T>
	requires DerivedAnimationNotifyState<T, AnimationNotifyState>
	std::shared_ptr<T> GetAnimnotifyState()
	{
		for (std::shared_ptr<AnimationNotifyState> notifyState : mAnimNotifyStates)
		{
			if (typeid(*notifyState.get()) == typeid(T))
			{
				return std::static_pointer_cast<T>(notifyState);
			}
		}
		return nullptr;
	}

	/**
	* @fn GetAllAnimNotifyState
	* @brief �w�肳�ꂽ�ʒm�X�e�[�g�����ׂĕԂ�
	* @detail �w�肳�ꂽ�ʒm�X�e�[�g���Ȃ���΃T�C�Y��0�̔z���ς��� 
	* @return std::vector<std::shared_ptr<T>>
	*/
	template<typename T>
	requires DerivedAnimationNotifyState<T, AnimationNotifyState>
	inline std::vector<std::shared_ptr<T>> GetAllAnimNotifyState();

	/**
	* @fn AddSection
	* @brief �Z�N�V�����ǉ�
	* @detail �����̃Z�N�V������ǉ�����ۂ̓t���[���������ɂȂ�悤�ɒǉ����Ă�������
	* @param const uint16_t (_frame)
	* @param std::string_view (_sectionName)
	* @return void
	*/
	inline void AddSection(const uint16_t _frame, std::string_view _sectionName);

public:
	/**
	* @fn CalucAnimationMatrix
	* @brief �`�����l���̎w�肳�ꂽ���Ԃ̃A�j���[�V�����}�g���b�N�X��Ԃ��֐�
	* @param Channel& (_channel)
	* @param const double (_time)
	* @param DirectX::SimpleMath::Matrix& (_animationMatrix)
	* @return void
	*/
	virtual void CalucAnimationMatrix(Channel& _channel, const double _time, DirectX::SimpleMath::Matrix& _animationMatrix);

	/**
	* @fn CalucAnimationKey
	* @brief �`�����l���̎w�肳�ꂽ���Ԃ̃A�j���[�V�����L�[����Ԃ�
	* @param Channel& (_channel)
	* @param const double (_time)
	* @param DirectX::SimpleMath::Vector3&    (_position)
	* @param DirectX::SimpleMath::Vector3&    (_scale)
	* @param DirectX::SimpleMath::Quaternion& (_quaternion)
	* @return void
	*/
	virtual void CalucAnimationKey(Channel& _channel, const double _time, DirectX::SimpleMath::Vector3& _position, DirectX::SimpleMath::Vector3& _scale, DirectX::SimpleMath::Quaternion& _quaternion);

	/**
	* @fn GetChannels
	* @brief �`�����l���f�[�^��Ԃ�
	* @return std::vector<Channel>
	*/
	inline std::vector<Channel> GetChannels() const;

	/**
	* @fn GetDuration
	* @brief �A�j���[�V�����̒�����Ԃ�
	* @return float
	*/
	inline float GetDuration() const noexcept;

	/**
	* @fn GetTickPerSecond
	* @brief ��b�Ԃɐi�ރA�j���[�V�����̒�����Ԃ�
	* @return float
	*/
	inline float GetTickPerSecond() const noexcept;

	/**
	* @fn SetLoop
	* @brief ���[�v�Đ����邩�Z�b�g����
	* @param const bool (_loop)
	* @return void
	*/
	inline void SetLoop(const bool _loop) noexcept;

	/**
	* @fn IsLoop
	* @brief ���[�v�Đ��Ȃ̂���Ԃ�
	* @return bool true ���[�v false ���[�v�ł͂Ȃ�
	*/
	inline bool IsLoop() const noexcept;

	/**
	* @fn SetEndFrame
	* @brief �A�j���[�V�����̏I���t���[����ݒ肷��֐�
	* @param const float (_endFrame)
	* @return void
	*/
	inline void SetEndFrame(const float _endFrame) noexcept;

	/**
	* @fn GetEndFrame
	* @brief �A�j���[�V�����I���t���[���̎擾
	* @return float 
	*/
	inline float GetEndFrame() const noexcept;

	/**
	* @fn SetSynchro
	* @brief �A�j���[�V�����ƃQ�[���I�u�W�F�N�g�𓯊����邩���Z�b�g����
	* @param const bool (_synchro) true �������� false �������Ȃ�
	* @return void
	*/
	inline void SetSynchroPosition(const bool _synchroPosition) noexcept;

	/**
	* @fn IsSynchroPosition
	* @brief �������邩��Ԃ�
	* @return bool true �������� false �������Ȃ�
	*/
	inline bool IsSynchroPosition() const noexcept;

	/**
	* @fn SetSynchroRotation
	* @brief ��]�𓯊�������̃Z�b�^�[
	* @param const bool 
	* @return void
	*/
	inline void SetSynchroRotation(const bool _synchroRotation) noexcept;

	/**
	* @fn IsSynchroRotation
	* @brief ��]�𓯊����邩�Ԃ�
	* @return bool true �������� false �������Ȃ�
	*/
	inline bool IsSynchroRotation() const noexcept;

	/**
	* @fn GetSkeletalMesh
	* @brief ���̃A�j���[�V�������K�������X�P���^�����b�V����Ԃ�
	* @return std::weak_ptr<SkeletalMesh>
	*/
	inline std::weak_ptr<SkeletalMesh> GetSkeletalMesh() const;

	/**
	* @fn SetSkeletalMesh
	* @brief �A�j���[�V�������K�������X�P���^�����b�V�����Z�b�g�֐�
	* @param const std::shared_ptr<SkeletalMesh> _skeletalMesh
	* @return void
	*/
	inline void SetSkeletalMesh(const std::shared_ptr<SkeletalMesh> _skeletalMesh);

	/**
	* @fn GetAnimationName
	* @brief �A�j���[�V��������Ԃ�
	* @return std::string
	*/
	inline std::string GetAnimationName() const noexcept;

	/**
	* @fn SetDisplaced
	* @brief �J�n�����[�g���炸�ꂽ�ʒu�ł��邩���Z�b�g����
	* @param const bool (_isDisplaced)
	* @return void
	*/
	inline void SetDisplaced(const bool _isDisplaced) noexcept;

	/**
	* @fn IsDisplaced
	* @brief �J�n�ʒu�����[�g���炸�ꂽ�A�j���[�V��������Ԃ�
	* @return bool 
	*/
	inline bool IsDisplaced() const noexcept;

	/**
	* @fn GetCurrentPlayTime
	* @brief ���݂̍Đ�����
	* @return float
	*/
	inline float GetCurrentPlayTime() const noexcept;

	/**
	* @fn GetCurrentSection
	* @brief ���݂̃Z�N�V������Ԃ�
	* @return std::string
	*/
	inline std::string GetCurrentSection() const noexcept;

};

//----------- INLINES ------------

inline std::vector<Channel> SkeletalMeshAnimationClip::GetChannels() const
{
	return mChannels;
}

inline float SkeletalMeshAnimationClip::GetDuration() const noexcept
{
	return mDuration;
}

inline float SkeletalMeshAnimationClip::GetTickPerSecond() const noexcept
{
	return mTickPerSeconds;
}

inline void SkeletalMeshAnimationClip::SetLoop(const bool _loop) noexcept
{
	mbLoop = _loop;
}

inline bool SkeletalMeshAnimationClip::IsLoop() const noexcept
{
	return mbLoop;
}

inline void SkeletalMeshAnimationClip::SetEndFrame(const float _endFrame) noexcept
{
	mEndFrame = _endFrame;
}

inline float SkeletalMeshAnimationClip::GetEndFrame() const noexcept
{
	return mEndFrame;
}

inline void SkeletalMeshAnimationClip::SetSynchroPosition(const bool _synchroPosition) noexcept
{
	mbSynchroPosition = _synchroPosition;
}

inline bool SkeletalMeshAnimationClip::IsSynchroPosition() const noexcept
{
	return mbSynchroPosition;
}

inline void SkeletalMeshAnimationClip::SetSynchroRotation(const bool _synchroRotation) noexcept
{
	mbSynchroRotation = _synchroRotation;
}

inline bool SkeletalMeshAnimationClip::IsSynchroRotation() const noexcept
{
	return mbSynchroRotation;
}

inline std::weak_ptr<SkeletalMesh> SkeletalMeshAnimationClip::GetSkeletalMesh() const
{
	return mSkeletalMesh;
}

inline void SkeletalMeshAnimationClip::SetSkeletalMesh(const std::shared_ptr<SkeletalMesh> _skeletalMesh)
{
	mSkeletalMesh = _skeletalMesh;
}

inline std::string SkeletalMeshAnimationClip::GetAnimationName() const noexcept
{
	return mAnimationName;
}

inline void SkeletalMeshAnimationClip::SetDisplaced(const bool _isDisplaced) noexcept
{
	mbDisplacedStartAnimation = _isDisplaced;
}

inline bool SkeletalMeshAnimationClip::IsDisplaced() const noexcept
{
	return mbDisplacedStartAnimation;
}

inline float SkeletalMeshAnimationClip::GetCurrentPlayTime() const noexcept
{
	return mCurrentPlayTime;
}

inline std::string SkeletalMeshAnimationClip::GetCurrentSection() const noexcept
{
	return mCurrentSection;
}

inline void SkeletalMeshAnimationClip::AddSection(const uint16_t _frame, std::string_view _sectionName)
{
	// �A�j���[�V�����̒����������Ă���Βǉ����Ȃ�
	if (_frame > mDuration)
	{
		std::cout << "Animation�̒����𒴂����ʒu�ɃZ�N�V������ǉ����悤�Ƃ��Ă��܂��B" << std::endl
			<< "AnimationName  : " << mAnimationName << std::endl
			<< "Duration       : " << mDuration << std::endl
			<< "AddFrame       : " << _frame << std::endl
			<< "AddSectionName : " << _sectionName << std::endl;
		return;
	}

	// �ǉ�
	mSections.emplace_back(std::pair<uint16_t, std::string>(_frame, _sectionName));
}

template<typename T>
requires DerivedAnimationNotify<T, AnimationNotify>
inline std::vector<std::shared_ptr<T>> SkeletalMeshAnimationClip::GetAllAnimationNotify()
{
	std::vector<std::shared_ptr<T>> notifies;
	for (std::pair<std::shared_ptr<AnimationNotify>, float> notify : mAnimNotifies)
	{
		if (typeid(*notify.first.get()) == typeid(T))
		{
			notifies.emplace_back(std::static_pointer_cast<T>(notify.first));
		}
	}
	return notifies;
}

template<typename T>
requires DerivedAnimationNotifyState<T, AnimationNotifyState>
inline std::vector<std::shared_ptr<T>> SkeletalMeshAnimationClip::GetAllAnimNotifyState()
{
	std::vector<std::shared_ptr<T>> notifies;
	for (std::shared_ptr<AnimationNotifyState> notifyState : mAnimNotifyStates)
	{
		if (typeid(*notifyState.get()) == typeid(T))
		{
			notifies.emplace_back(std::static_pointer_cast<T>(notifyState));
		}
	}
	return notifies;
}
