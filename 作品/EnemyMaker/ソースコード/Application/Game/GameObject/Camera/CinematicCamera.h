/**
* @file CinematicCamera.h
* @brief CinematicCamera�N���X�̒�`
*/

#pragma once

//------- INCLUDES --------
#include "Camera.h"

//------- �O���錾 ---------
class Bone;

/**
* @class CinematicCamera
* @brief �V�l�}�e�B�b�N�J�����A�J�������o�Ȃǂ����邽�߂̃N���X
*        �ݒ肳�ꂽ�L�[�ɉ����ăJ�����A�j���[�V����������
*        �L�[�̕ۑ���Ƃ��ăt�@�C���p�X���w�肷��K�v������܂�
*		 �L�[�̈ʒu���͈ڂ��Ώۂ��烍�[�J���ʒu
*/
class CinematicCamera : public Camera
{
	/**
	* @struct CameraAnimationKey 
	* @brief �J�����A�j���[�V�����̂��߂̏��
	*        �ړ��ʒu�A�b��������
	*/
	struct CameraAnimationKey
	{
		DirectX::SimpleMath::Vector3 mPosition;  /**< �J�����̈ړ��ʒu */
		double mTime;                            /**< ���� */
		bool mbCut;                              /**< ���̃L�[�܂ŕ�ԂȂ��Ő؂�ւ��� */

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		CameraAnimationKey();

	};

public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CinematicCamera();

	/**
	* �f�X�g���N�^
	*/
	~CinematicCamera();

private:
	/** �J�����A�j���[�V�����L�[ ���[�J����ԏ�̒l������ */
	std::vector<CameraAnimationKey> mLocalAnimKeys;

	/** �J�����A�j���[�V�����L�[ ���[���h��ԏ�̒l�����@���ۂɃA�j���[�V�����Ɏg�p */
	std::vector<CameraAnimationKey> mWorldAnimKeys;

	/** �f�[�^��ۑ����邽�߂̃t�@�C���p�X */
	std::string mSaveFilePath;

	/** �J�����A�j���[�V�������Đ����Ă��邩 */
	bool mbPlay;

	/** ���݂̍Đ����� */
	double mCurrentPlayTime;

	/** �Đ����� */
	double mDuration;

	/** �f���Ώ� */
	std::weak_ptr<GameObject> mTargetObject;

	/** �f���Ώۂ̃{�[�� �ݒ肳��Ă��Ȃ��ꍇ��TargetObject���g�p���� */
	std::weak_ptr<Bone> mTargetBone;

public:
	/**
	* @fn Init
	* @brief ����������
	* @detail �w�肳�ꂽ�t�@�C������f�[�^��ǂݍ��ށB�f�[�^���Ȃ���Γǂݍ��݂͍s��Ȃ�
	*         �����œn���ꂽ�t�@�C���p�X�Ƀf�[�^��ۑ�����
	* @param std::string_view (_filepath)
	* @return void
	*/
	void Init(std::string_view _filepath);

	/**
	* @fn Update
	* @brief �X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn CameraAnimation
	* @brief �J�����A�j���[�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void CameraAnimation(const double _deltaTime);

	/**
	* @fn InterpCameraAnimationKeyPosition
	* @brief �⊮���ă|�W�V���������߂�
	* @param CameraAnimationKey& (_keyBase) ��Ԍ��L�[
	* @param CameraAnimationKey& (_keyTo)   ��Ԑ�L�[
	* @param DirectX::SimpleMath::Vector3& (_position) ��Ԍ���
	* @return void
	*/
	void InterpCameraAnimationKeyPosition(CameraAnimationKey& _keyBase, CameraAnimationKey& _keyTo, DirectX::SimpleMath::Vector3& _position);

	/**
	* @fn GetKey
	* @brief ���݂̍Đ����Ԃ���A�⊮���邽�߂ɕK�v�ȃL�[���擾����
	* @detail ���݂̍Đ����Ԃ̒��O�̃L�[�ƁA���̃L�[���擾����
	* @param CameraAnimationKey& (_key1)
	* @param CameraAnimationKey& (_key2)
	* @return void
	*/
	void GetKey(CameraAnimationKey& _key1, CameraAnimationKey& _key2);

	/**
	* @fn CalcuFocusPosition
	* @brief �����_���v�Z����
	* @return void
	*/
	void CalcuFocusPosition() override;

	/**
	* @fn ConvertTargetWorldPosition
	* @brief �ݒ肳�ꂽ�L�[�̈ʒu�������[���h��Ԃɕϊ�����
	* @return void
	*/
	void ConvertTargetWorldPosition();

	/**
	* @fn Save
	* @brief �L�[�f�[�^���Z�[�u����
	* @return void
	*/
	void Save();

	/**
	* @fn Load
	* @brief �f�[�^�ǂݍ���
	* @return bool
	*/
	bool Load();

public:
	/**
	* @fn Edit
	* @brief �J�����A�j���[�V������ҏW����֐�
	* @param std::string_view (_label)
	* @return void
	*/
	void EditAnimation(std::string_view _label);

	/**
	* @fn Play
	* @brief �J�����A�j���[�V�����Đ�
	* @detail �f�[�^���Ȃ���΍Đ����Ȃ�
	*         �f�[�^������΍ŏ��̃L�[�̈ʒu�ɃJ������ݒ肵�A�Đ�
	* @return void
	*/
	void Play();

	/**
	* @fn SetTargetObject
	* @brief �^�[�Q�b�g�̃Q�[���I�u�W�F�N�g���Z�b�g����
	* @param std::shared_ptr<GameObject> (_targetObject)
	* @return void
	*/
	inline void SetTargetObject(std::shared_ptr<GameObject> _targetObject) noexcept;

	/**
	* @fn SetTargetBone
	* @brief �^�[�Q�b�g�ƂȂ�{�[�����Z�b�g����
	* @param std::shared_ptr<Bone> (_targetBone)
	* @return void
	*/
	inline void SetTargetBone(std::shared_ptr<Bone> _targetBone) noexcept;

	/**
	* @fn GetCurrentPlayTime
	* @brief ���݂̍Đ����Ԃ�Ԃ�
	* @return double 
	*/
	inline double GetCurrentPlayTime() const noexcept;

	/**
	* @fn GetDuration
	* @brief �A�j���[�V�����̒�����Ԃ�
	* @return double 
	*/
	inline double GetDuration() const noexcept;

};

//---------- INLINES ----------

inline void CinematicCamera::SetTargetObject(std::shared_ptr<GameObject>_targetObject) noexcept
{
	mTargetObject = _targetObject;
	mTargetBone.reset();
}

inline void CinematicCamera::SetTargetBone(std::shared_ptr<Bone> _targetBone) noexcept
{
	mTargetBone = _targetBone;
	mTargetObject.reset();
}

inline double CinematicCamera::GetCurrentPlayTime() const noexcept
{
	return mCurrentPlayTime;
}

inline double CinematicCamera::GetDuration() const noexcept
{
	return mDuration;
}
