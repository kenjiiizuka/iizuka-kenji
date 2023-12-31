//-------- INCLUDES ----------
#include "Gene.h"

Gene::Gene()
	: mEvaluationValue(0.0f)
{
	// 処理なし
}

Gene::~Gene()
{
	// 処理なし
}

void Gene::Evaluate(std::shared_ptr<BlackBoard> _blackboard)
{
	// 持っている状況遺伝子の評価
	std::vector<float> situationEvaluationValue(mSituations.size());
	for (size_t situation_i = 0; std::shared_ptr<Situation> situation : mSituations)
	{
		situation->Evaluate(_blackboard);
		situationEvaluationValue[situation_i] = situation->GetGoalAchievement();
		situation_i++;
	}
}