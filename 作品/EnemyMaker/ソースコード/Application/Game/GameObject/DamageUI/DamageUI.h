/**
* @file DamageUI.h
* @brief DamageUI�N���X�̒�`
*/

#pragma once

//------------ INCLUDES ----------
#include "../GameObject.h"

//----------- �O���錾 ----------
class Number;
class CurveFloat;

/**
* @class DamageUI
* @brief �v���C���[���G�ɗ^�����_���[�W��\������I�u�W�F�N�g
*/
class DamageUI : public GameObject
{
	/**
	* @struct DamageBillboard
	* @brief �_���[�W�\���r���{�[�h
	*/
	struct DamageBillboard
	{
		std::weak_ptr<Number> mBillboard;           /**< �r���{�[�h */
		double mElapsedTime;                         /**< ��������Ă���̌o�ߎ��� */
		DirectX::SimpleMath::Vector3 mDirection;    /**< �ړ����� */

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		DamageBillboard();
	};

public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	DamageUI();

	/**
	* �f�X�g���N�^
	*/
	~DamageUI();

private:
	/** �_���[�W�\���r���{�[�h <�r���{�[�h, �������Ă���̌o�ߎ���> */
	std::vector<DamageBillboard> mDamageBillboard;

	/** �r���{�[�h�̐������� */
	double mBillboardLifeTime;

	/** �\������Ă���r���{�[�h�𓮂������߂̃J�[�u */
	std::shared_ptr<CurveFloat> mCurve;

	/** �r���{�[�h���ړ�������J�[�u��ҏW����t���O */
	bool mbEditCurve;

public:	
	/**
	* @fn Init
	* @brief ����������
	* @return void
	*/
	void Init();

	/**
	* @fn Update
	* @brief �X�V����
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private: 
	/**
	* @fn MoveBillboard
	* @brief �\������Ă���_���[�W�r���{�[�h���ړ�������
	* @param DamageBillboard& (_billboard)
	* @return void
	*/
	void MoveBillboard(DamageBillboard& _billboard);

	/**
	* @fn InterpAlpha
	* @brief ���l���O�܂ŕ⊮����
	* @param DamageBillboard& (_billboard)
	* @return void
	*/
	void InterpAlpha(DamageBillboard& _billboard);

public:
	/**
	* @fn DisplayDamage
	* @brief �_���[�W��\�����J�n����֐�
	* @param const float (_damage)
	* @param const DirectX::SimpleMath::Vector3 (_position)
	* @return void
	*/
	void DisplayDamage(const float _damage, const DirectX::SimpleMath::Vector3 _position);

	/**
	* @fn SetEditCurve
	* @brief �J�[�u��ҏW���邩�̃Z�b�^�[
	* @param const bool (_edit)
	* @return void
	*/
	inline void SetEditCurve(const bool _edit) noexcept;

};

//-------- INLINES -----------

inline void DamageUI::SetEditCurve(const bool _edit) noexcept
{
	mbEditCurve = _edit;
}