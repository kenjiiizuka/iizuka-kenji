//-------- INCLUDES ----------
#include "Gene.h"

Gene::Gene()
	: mEvaluationValue(0.0f)
{
	// ˆ—‚È‚µ
}

Gene::~Gene()
{
	// ˆ—‚È‚µ
}

void Gene::Evaluate(std::shared_ptr<BlackBoard> _blackboard)
{
	// ‚Á‚Ä‚¢‚éó‹µˆâ“`q‚Ì•]‰¿
	std::vector<float> situationEvaluationValue(mSituations.size());
	for (size_t situation_i = 0; std::shared_ptr<Situation> situation : mSituations)
	{
		situation->Evaluate(_blackboard);
		situationEvaluationValue[situation_i] = situation->GetGoalAchievement();
		situation_i++;
	}
}