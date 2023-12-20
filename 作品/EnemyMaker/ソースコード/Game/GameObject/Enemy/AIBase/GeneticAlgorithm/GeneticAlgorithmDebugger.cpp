#include "GeneticAlgorithmDebugger.h"
#include "GeneticInfomation.h"
#include "Gene/EnemyAttackAction.h"
#include "Gene/EnemyMoveAction.h"
#include "Gene/Situation.h"
#include "Gene/Gene.h"
#include"../../../../../ImGui/ImGuiUtility.h"
#include"../../../../../ImGui/imgui_impl_dx11.h"

GeneticAlgorithmDebugger::GeneticAlgorithmDebugger()
	: mbDisplayAttackGeneEvaluation(true)
	, mbDisplayAttackGeneEvaluationData(true)
	, mbDisplayMoveGeneEvaluation(false)
	, mbDisplayMoveGeneEvaluationData(false)
	, mDisplayGeneticIndex(0)
	, mCurrentGeneIndex(0)
{
	// 処理なし
}

void GeneticAlgorithmDebugger::DisplayGeneticDebug()
{
#ifdef _DEBUG
	int displayGene_i = static_cast<int>(mDisplayGeneticIndex);
	int geneSize = static_cast<int>(mGenes.size());

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(300.0f, 100.0f));
	ImGui::Begin("GeneticAlgorithmDebug");
	ImGui::Checkbox("Display AttackGene Evaluation", &mbDisplayAttackGeneEvaluation);
	ImGui::Checkbox("Display AttackGene EvaluationData", &mbDisplayAttackGeneEvaluationData);
	ImGui::Checkbox("Display MoveGene Evaluation", &mbDisplayMoveGeneEvaluation);
	ImGui::Checkbox("Display MoveGene EvaluationData", &mbDisplayMoveGeneEvaluationData);
	ImGui::SliderInt("Gene Size", &geneSize, 0, 1000);
	ImGui::InputInt("Display Genetic Index", &displayGene_i);
	ImGui::End();
	
	mDisplayGeneticIndex = displayGene_i < mGenes.size() ? displayGene_i : mGenes.size() - 1;

	// 状況遺伝子の表示	
	std::vector<std::shared_ptr<Situation>> situations = mGenes[mDisplayGeneticIndex]->GetSituations();
	DisplaySituation(mGenes[mDisplayGeneticIndex]);
	DisplayGenetic(mGenes[mDisplayGeneticIndex]);	

#endif
}

void GeneticAlgorithmDebugger::DisplayGenetic(const std::shared_ptr<Gene>& _genetic)
{
	std::vector<std::shared_ptr<Situation>> situations = _genetic->GetSituations();
	for (const std::weak_ptr<Situation>& situation : situations)
	{
		if (!situation.lock())
		{
			continue;
		}

		// 攻撃遺伝子の表示
		AttackGenes attackGenes = situation.lock()->GetAttackGenes();
		// DisplayAttackGeneEvaluation(attackGenes);
		DisplayAttackGeneEvaluationData(attackGenes);

		// 移動遺伝子の表示
		MoveGenes moveGenes = situation.lock()->GetMoveGenes();
		DisplayMoveGeneEvaluationData(moveGenes);
	}	
}

void GeneticAlgorithmDebugger::DisplaySituation(const std::shared_ptr<Gene>& _genetic)
{
	ImGuiUtility& imGuiUtility = ImGuiUtility::GetInstance();

	ImGui::SetNextWindowPos(ImVec2(0.0f, 100.0f));
	ImGui::SetNextWindowSize(ImVec2(500.0f, 260.0f));
	ImGui::Begin("Situation");

	std::vector<std::shared_ptr<Situation>> situations = _genetic->GetSituations();
	for (size_t situation_i = 0; const std::weak_ptr<Situation>& situation : situations)
	{
		if (!situation.lock())
		{
			continue;
		}

		// TODO: 状況遺伝子のリスクタイプの比率表示グラフの改善
		// 状況遺伝子のゴールとなるリスクタイプの割合を描画する
		{	
			SituationRiskTypeRatio riskRatio = situation.lock()->GetRiskTypeTargetRatio();
			std::string nodeName = "Goal RiskTypeRatio";
			nodeName.append(std::to_string(situation_i));
			ImGui::SeparatorText(nodeName.c_str());
			//if (ImGui::TreeNode(nodeName.c_str()))
			{
				ImGui::PushID(static_cast<int>(GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn));
				imGuiUtility.ColorSliderFloat("HighRisk_HighReturn", riskRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn], 0.0f, 1.0f, ImColor(100, 0, 0), ImVec4(1.0f, 0.0f, 0.0f, 0.0f));
				ImGui::PopID();

				ImGui::PushID(static_cast<int>(GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn));
				imGuiUtility.ColorSliderFloat("LowRisk_HighReturn", riskRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn], 0.0f, 1.0f, ImColor(100, 100, 0), ImVec4(1.0f, 1.0f, 0.0f, 0.0f));
				ImGui::PopID();

				ImGui::PushID(static_cast<int>(GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn));
				imGuiUtility.ColorSliderFloat("HighRisk_LowReturn", riskRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn], 0.0f, 1.0f, ImColor(0, 100, 0), ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
				ImGui::PopID();

				ImGui::PushID(static_cast<int>(GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn));
				imGuiUtility.ColorSliderFloat("LowRisk_LowReturn", riskRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn], 0.0f, 1.0f, ImColor(0, 0, 100), ImVec4(0.0f, 0.0f, 1.0f, 0.0f));
				ImGui::PopID();	
			}
		}

		// 現在のリスクタイプの比率を表示する
		{		
			SituationRiskTypeRatio currentRiskRatio = situation.lock()->GetCurrentRiskTypeRatio();
			std::string nodeName = "Current RiskTypeRatio ";
			nodeName.append(std::to_string(situation_i));
			ImGui::SeparatorText(nodeName.c_str());
			
			ImGui::PushID(static_cast<int>(GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn));
			imGuiUtility.ColorSliderFloat("HighRisk_HighReturn", currentRiskRatio[GeneticAlgorithmInf::AttackAction_HighRisk_HighReturn], 0.0f, 1.0f, ImColor(100, 0, 0), ImVec4(1.0f, 0.0f, 0.0f, 0.0f));
			ImGui::PopID();

			ImGui::PushID(static_cast<int>(GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn));
			imGuiUtility.ColorSliderFloat("LowRisk_HighReturn", currentRiskRatio[GeneticAlgorithmInf::AttackAction_LowRisk_HighReturn], 0.0f, 1.0f, ImColor(100, 100, 0), ImVec4(1.0f, 1.0f, 0.0f, 0.0f));
			ImGui::PopID();

			ImGui::PushID(static_cast<int>(GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn));
			imGuiUtility.ColorSliderFloat("HighRisk_LowReturn", currentRiskRatio[GeneticAlgorithmInf::AttackAction_HighRisk_LowReturn], 0.0f, 1.0f, ImColor(0, 100, 0), ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
			ImGui::PopID();

			ImGui::PushID(static_cast<int>(GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn));
			imGuiUtility.ColorSliderFloat("LowRisk_LowReturn", currentRiskRatio[GeneticAlgorithmInf::AttackAction_LowRisk_LowReturn], 0.0f, 1.0f, ImColor(0, 0, 100), ImVec4(0.0f, 0.0f, 1.0f, 0.0f));
			ImGui::PopID();		
		}
		situation_i++;
	}
	ImGui::End();
}

void GeneticAlgorithmDebugger::DisplayAttackGeneEvaluation(const AttackGenes& _attackGenes)
{	
	if (!mbDisplayAttackGeneEvaluation)
	{
		return;
	}

	ImGui::SetNextWindowPos(ImVec2(0.0f, 100.0f));
	ImGui::SetNextWindowSize(ImVec2(300.0f, 300.0f));
	ImGui::Begin("AttackGeneEvaluation");

	// 攻撃遺伝子の評価値の表示
	for (const std::weak_ptr<EnemyAttackAction>& attackAction : _attackGenes)
	{
		if (!attackAction.lock())
		{
			continue;
		}

		if (ImGui::CollapsingHeader(attackAction.lock()->GetTypeName().c_str()))
		{
			std::string typeName = attackAction.lock()->GetTypeName();
			float suitable = attackAction.lock()->GetSuitable();
			float effectiveness = attackAction.lock()->GetEffectivenessToPlayer();
			float receptivity = attackAction.lock()->GetReceptivityToPlayer();
			ImGui::InputFloat("Suitable", &suitable);
			ImGui::InputFloat("Effectiveness", &effectiveness);
			ImGui::InputFloat("Receptivity", &receptivity);
		}
	}
	ImGui::End();
}

void GeneticAlgorithmDebugger::DisplayAttackGeneEvaluationData(const AttackGenes& _attackGenes)
{
	if (!mbDisplayAttackGeneEvaluationData)
	{
		return;
	}

	ImGui::SetNextWindowPos(ImVec2(980.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(300.0f, 360.0f));
	ImGui::Begin("AttackGeneEvaluationData");

	// 攻撃遺伝子の評価値の表示
	for (const std::weak_ptr<EnemyAttackAction>& attackAction : _attackGenes)
	{
		if (!attackAction.lock())
		{
			continue;
		}

		if (ImGui::CollapsingHeader(attackAction.lock()->GetTypeName().c_str()))
		{		
			// 評価データを取得
			int executeCount = static_cast<int>(attackAction.lock()->GetExecuteCount());
			std::vector<float> damageInflicted = attackAction.lock()->GetDamageInflicted();
			std::vector<float> damageTakenDuringExecution = attackAction.lock()->GetDamageTakenDuringExecution();
			std::vector<float> executionTime = attackAction.lock()->GetExecutionTime();
			int riskType = static_cast<int>(attackAction.lock()->GetAttackActionRiskType());
	
			std::vector<std::string> riskTypeNames(GeneticAlgorithmInf::AttackAction_Max);
			riskTypeNames[0] = "HighRisk_HighReturn";
			riskTypeNames[1] = "LowRisk_HighReturn";
			riskTypeNames[2] = "HighRisk_LowReturn";
			riskTypeNames[3] = "LowRisk_LowReturn";
			riskTypeNames[4] = "None";
			ImGui::SliderInt("RiskType", &riskType, 0, static_cast<int>(GeneticAlgorithmInf::AttackAction_Max) - 1, riskTypeNames[riskType].c_str());

			ImGui::InputInt("ExecuteCount", &executeCount);

			if (ImGui::TreeNode("DamageInflicted"))
			{
				for (size_t i = 0; i < damageInflicted.size(); i++)
				{
					ImGui::InputFloat("element", &damageInflicted[i]);
				}
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("DamageTakenDuringExecution"))
			{
				for (size_t i = 0; i < damageTakenDuringExecution.size(); i++)
				{
					ImGui::InputFloat("element", &damageTakenDuringExecution[i]);
				}
				ImGui::TreePop();
			}
				
			if (ImGui::TreeNode("ExecutionTime"))
			{
				for (size_t i = 0; i < executionTime.size(); i++)
				{
					ImGui::InputFloat("element", &executionTime[i]);
				}
				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
}

void GeneticAlgorithmDebugger::DisplayMoveGeneEvaluationData(const MoveGenes& _moveGenes)
{
	// 移動遺伝子の評価をするためのデータを表示するか
	if (mbDisplayMoveGeneEvaluationData)
	{
		ImGui::SetNextWindowPos(ImVec2(0.0f, 400.0f));
		ImGui::SetNextWindowSize(ImVec2(300.0f, 100.0f));
		ImGui::Begin("MoveGeneEvaluationData");
		for (std::weak_ptr<EnemyMoveAction> moveAction : _moveGenes)
		{
			if (!moveAction.lock())
			{
				continue;
			}

			std::shared_ptr<EnemyMoveAction> validMoveAction = moveAction.lock();
			if (ImGui::CollapsingHeader(validMoveAction->GetTypeName().c_str()))
			{
				int executeCount = static_cast<int>(validMoveAction->GetExecuteCount());
				ImGui::InputInt("ExecuteCount", &executeCount);	
			}
		}
		ImGui::End();
	}
}

