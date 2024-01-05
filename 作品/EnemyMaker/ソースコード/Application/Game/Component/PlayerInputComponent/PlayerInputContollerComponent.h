/**
* @file PlayerInputController.h
* @brief PlayerInputController�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include "../../Component/Component.h"
#include "../../../System/InputSystem/XInput.h"
#include <array>

/**
* @class PlayerInputController
* @brief �v���C���[�̃R���g���[���\�̓��͂��Ǘ�����N���X
*/
class PlayerInputControllerComponent : public Component
{
public:
	/**
	* @enum OperationKind
	* @brief �v���C���[�̃{�^��������`��������
	*/
	enum OperationKind : uint8_t
	{
		Operation_AttackY = 0, /**< Y�U������ */
		Operation_AttackB,     /**< B�U������ */
		Operation_Step,        /**< �X�e�b�v���� */
		Operation_Guard,       /**< �K�[�h���� */
		Operation_Counter,     /**< �J�E���^�[ */
		Operation_Max,         /**< �ő吔 */
	};

	/**
	* @enum OperationType
	* @brief ����̓��͂̎�ނ�����
	*/
	enum OperationType : uint8_t
	{
		OperationType_Trigger = 0, /**< �g���K�[���� */
		OperationType_Press,       /**< ���������� */
	};


	using Operation = std::pair<Pad, OperationType>;

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	PlayerInputControllerComponent();

	/**
	* �f�X�g���N�^
	*/
	~PlayerInputControllerComponent();

private:
	/** ���͂���Ă���̌o�ߎ��� */
	float mInputElapsedFrame;

	/** ���͋��e���� */
	float mAllowInputTime;

	/** �v���C���[�̂��鑀��ƃ{�^����R�Â����z�� */
	std::array<Operation, Operation_Max> mOperationButtons;

	/** �e����ɓ��͂�����Ă��邩���i�[���� */
	std::array<bool, Operation_Max> mOperationInput;

public:
	/**
	* @fn Update
	* @brief �X�V����
	* @detail �R���g���[���[����̓��͂��Ď�
	*         ���͂�����΁AmAllowInputTime�̊Ԃ͓��͂��Ă��邱�Ƃɂ���
	*         �r���ŕʂ̃{�^���������ꂽ�炻����ɐ؂�ւ��
	* @param const double (_deltaTime) �f���^�^�C��
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn GetTrigger
	* @brief �v���C���[�̑���Ɏg���{�^����������Ă��邩��Ԃ�
	* @param const OperationKind _operation
	* @return bool true ���͂��� : false ���͂Ȃ� 
	*/
	inline bool IsInput(const OperationKind _operation) const noexcept;
};

//--------- INLINES ----------

inline bool PlayerInputControllerComponent::IsInput(const OperationKind _operation) const noexcept
{
	return mOperationInput[_operation];
}
