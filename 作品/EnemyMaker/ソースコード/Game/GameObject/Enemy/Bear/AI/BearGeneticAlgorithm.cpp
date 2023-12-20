//---------- INCLUDES --------------
#include "BearGeneticAlgorithm.h"
#include "Action/Bear3ChainSwordAttack.h"
#include "Action/BearJumpSlash.h"
#include "Action/BearSwipingAttack.h"
#include "Action/BearSwordSwingDownAttack.h"
#include "Action/Bear2ChainSwordAttack.h"
#include "Action/Bear2ChainSwordStrongAttack.h"
#include "Action/BearKickAttack.h"
#include "Action/BearRoarAttack.h"
#include "Action/BearSwordSwingUpAttack.h"
#include "Action/BearMoveAction.h"
#include "Action/BearTurnRightAction.h"
#include "Action/BearTurnLeftAction.h"
#include "Action/Bear2ChinaBackAndFront.h"
#include "Action/BearDownwardSlashStrong.h"
#include "Action/Bear2ChainAttack_StrongLow.h"
#include "Action/BearSlashWeak.h"
#include "Action/BearBackJumpSlash.h"

BearGeneticAlgorithm::BearGeneticAlgorithm(std::shared_ptr<BlackBoard>& _blackboard)
	: EnemyGeneticAlgorithm(_blackboard)
{
	// 処理なし
}

void BearGeneticAlgorithm::SetupGeneType()
{
	// 型判別用の攻撃遺伝子生成
	mAttackGeneTypes.emplace_back(std::make_shared<Bear3ChainSwordAttack>(mBlackBoard));	
	mAttackGeneTypes.emplace_back(std::make_shared<BearSwipingAttack>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<BearSwordSwingDownAttack>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<Bear2ChainSwordAttack>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<BearKickAttack>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<Bear2ChainSwordStrongAttack>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<BearRoarAttack>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<BearSwordSwingUpAttack>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<BearJumpSlash>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<BearSlashWeak>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<BearBackJumpSlash>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<Bear2ChinaBackAndFront>(mBlackBoard));	
	mAttackGeneTypes.emplace_back(std::make_shared<Bear2ChainAttack_StrongLow>(mBlackBoard));
	mAttackGeneTypes.emplace_back(std::make_shared<BearDownwardSlashStrong>(mBlackBoard));

	// 型判別用の移動遺伝子生成
	mMoveGeneTypes.emplace_back(std::make_shared<BearMoveAction>(mBlackBoard));
	mMoveGeneTypes.emplace_back(std::make_shared<BearTurnRightAction>(mBlackBoard));
	mMoveGeneTypes.emplace_back(std::make_shared<BearTurnLeftAction>(mBlackBoard));
}
