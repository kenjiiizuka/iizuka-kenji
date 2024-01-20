/**
* @file Gene.h
* @brief Gene�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ---------
#include "DecisionData.h"
#include "Situation.h"

/**
* @class Gene
* @brief ��`�q �󋵈�`�q�̏W��
* @detail �󋵈�`�q�̐��͓G���ƂɈقȂ�
*         �����G�̈�`�q�̏󋵈�`�q�̐��͈�`�q���Ƃɓ����ł��@
*/
class Gene : public DecisionData
{
public:
	/**
	* �R���X�g���N�^
	*/
	Gene();

	/**
	* �f�X�g���N�^
	*/
	~Gene();

private:
	/** �󋵈�`�q */
	std::vector<std::shared_ptr<Situation>> mSituations;

	/** �]���l */
	float mEvaluationValue;

public:
	/**
	 * @fn Evaluate
	 * @brief �]���֐�
	 * @return void
	*/
	virtual void Evaluate(std::shared_ptr<BlackBoard> _blackboard);

	/**
	* @fn GetSituations
	* @brief �󋵈�`�q��Ԃ�
	* @return std::vector<std::shared_ptr<Situation>>
	*/
	inline std::vector<std::shared_ptr<Situation>> GetSituations() const noexcept;

	/**
	* @fn AddSituation
	* @brief �󋵈�`�q��ǉ�����֐�
	* @param std::shared_ptr<Situation> (_situation)
	* @return void
	*/
	inline void AddSituation(std::shared_ptr<Situation> _situation) noexcept;

	/**
	* @fn GetEvaluationValue
	* @brief �]���l��Ԃ��֐�
	* @return float �]���l
	*/
	inline float GetEvaluationValue() const noexcept;
};

//------------ INLINES ----------

inline std::vector<std::shared_ptr<Situation>> Gene::GetSituations() const noexcept
{
	return mSituations;
}

inline void Gene::AddSituation(std::shared_ptr<Situation> _situation) noexcept
{
	mSituations.emplace_back(_situation);
}

inline float Gene::GetEvaluationValue() const noexcept
{
	return mEvaluationValue;
}
