//-------- INCLUDES ----------
#include "Gene.h"

Gene::Gene()
	: mEvaluationValue(0.0f)
{
	// �����Ȃ�
}

Gene::~Gene()
{
	// �����Ȃ�
}

void Gene::Evaluate(std::shared_ptr<BlackBoard> _blackboard)
{
	// �����Ă���󋵈�`�q�̕]��
	std::vector<float> situationEvaluationValue(mSituations.size());
	for (size_t situation_i = 0; std::shared_ptr<Situation> situation : mSituations)
	{
		situation->Evaluate(_blackboard);
		situationEvaluationValue[situation_i] = situation->GetGoalAchievement();
		situation_i++;
	}
}