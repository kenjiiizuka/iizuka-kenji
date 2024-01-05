/**
* @file EnemyAIComponent.h
* @brief EnemyAIComponent�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ---------
#include "../Component.h"

//--------- �O���錾 ---------
class EnemyAIController;
class EnemyBase;

//--------- �R���Z�v�g ----------
template<class AIController>
concept DerivedAIController = std::derived_from<AIController, EnemyAIController>;

/**
* @class EnemyAIComponent
* @brief Enemy�𐧌䂷��Enemy��p�̃N���X
*/
class EnemyAIComponent : public Component
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	EnemyAIComponent();

	/**
	* �f�X�g���N�^
	*/
	~EnemyAIComponent();

private:
	/** AI�R���g���[���[*/
	std::shared_ptr<EnemyAIController> mAIController;

	/** AI�����s���邩 */
	bool mbRunAI;

public:
	/**
	* @fn ControllerInitialize
	* @brief AIController�̏�����
	* @return void
	*/
	void ControllerInitialize();

	/**
	* @fn Update
	* @brief �X�V����
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn CreateAIController
	* @brief AIController�쐬�֐�
	*/
	template<DerivedAIController AIController>
	inline void CreateAIController(EnemyBase* _controlledeEnemy);

	/**
	* @fn StopAI
	* @brief AI�ɂ�鐧����~�߂�
	* @return void
	*/
	void StopAI();

	/**
	* @fn RunAI
	* @brief AI������J�n����
	* @return void 
	*/
	void RunAI();

	/**
	* @fn SetTakenDamage
	* @brief ��������_���[�W���Z�b�g����
	* @param const float (_takenDamage)
	* @return void
	*/
	void SetTakenDamage(const float _takenDamage);

	/**
	* @fn GetAIController
	* @brief AIController��Ԃ�
	* @return std::weak_ptr<EnemyAIController>
	*/
	inline std::weak_ptr<EnemyAIController> GetAIController() const noexcept;
};

//-------- INLINES -----------

template<DerivedAIController AIController>
inline void EnemyAIComponent::CreateAIController(EnemyBase* _controlledEnemy)
{
	mAIController = std::make_shared<AIController>(_controlledEnemy);
}

inline std::weak_ptr<EnemyAIController> EnemyAIComponent::GetAIController() const noexcept
{
	return mAIController;
}
