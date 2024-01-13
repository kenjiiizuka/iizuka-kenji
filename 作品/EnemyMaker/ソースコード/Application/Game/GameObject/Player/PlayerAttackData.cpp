//--------- INCLUDES ----------
#include "PlayerAttackData.h"
#include "../../../System/AssetSystem/JsonFile/JsonIncludes.h"

using namespace PlayerData;

PlayerAttackData::PlayerAttackData()
{
	// 処理なし
}

PlayerAttackData::~PlayerAttackData()
{
	// 処理なし
}

void PlayerAttackData::Initialize()
{
	mAttackInformation.resize(AttackID_Max);

	if (LoadAttackData())
	{
		return;
	}

	// 攻撃なし
	{
		PlayerAttack attackNone;
		attackNone.mAttackID = AttackID_NoAttack;
		attackNone.mNextY = AttackID_Y1;
		attackNone.mNextB = AttackID_B1;
		attackNone.mDamage = 0.0f;
		attackNone.mAnimationClipName = "Roll"; // 攻撃していない状態なのでアニメーションクリップ名なし
		mAttackInformation[AttackID_NoAttack] = attackNone;
	}

	// Y1攻撃
	{
		PlayerAttack attackY1;
		attackY1.mAttackID = AttackID_Y1;
		attackY1.mNextY = AttackID_Y2;
		attackY1.mNextB = AttackID_B2_2;
		attackY1.mDamage = 10.f;
		attackY1.mAnimationClipName = "Y1";
		attackY1.mCollision.mCollisionOccurrence = 1;
		attackY1.mCollision.mCollisionFrames.resize(attackY1.mCollision.mCollisionOccurrence);
		attackY1.mCollision.mCollisionFrames[0].first = 20;
		attackY1.mCollision.mCollisionFrames[0].second = 60;
		attackY1.mInputAbleFrame.first = 33;
		attackY1.mInputAbleFrame.second = 60;
		attackY1.mAnimationInterp.mStepInterpStartTime = 11.0f;
		attackY1.mStepAnimationClipName = "Roll";
		mAttackInformation[AttackID_Y1] = attackY1;
	}

	// Y2攻撃
	{
		PlayerAttack attackY2;
		attackY2.mAttackID = AttackID_Y2;
		attackY2.mNextY = AttackID_Y3;
		attackY2.mNextB = AttackID_B1;
		attackY2.mDamage = 10.f;
		attackY2.mAnimationClipName = "Y2";
		attackY2.mCollision.mCollisionOccurrence = 1;
		attackY2.mCollision.mCollisionFrames.resize(attackY2.mCollision.mCollisionOccurrence);
		attackY2.mCollision.mCollisionFrames[0].first = 0;
		attackY2.mCollision.mCollisionFrames[0].second = 40;
		attackY2.mInputAbleFrame.first = 30;
		attackY2.mInputAbleFrame.second = 60;
		attackY2.mAnimationInterp.mStepInterpStartTime = 11.0f;
		attackY2.mStepAnimationClipName = "RollY2";
		mAttackInformation[AttackID_Y2] = attackY2;
	}

	// Y3攻撃
	{
		PlayerAttack attackY3;
		attackY3.mAttackID = AttackID_Y3;
		attackY3.mNextY = AttackID_Y4;
		attackY3.mNextB = AttackID_B1;
		attackY3.mDamage = 10.f;
		attackY3.mAnimationClipName = "Y3";
		attackY3.mCollision.mCollisionOccurrence = 1;
		attackY3.mCollision.mCollisionFrames.resize(attackY3.mCollision.mCollisionOccurrence);
		attackY3.mCollision.mCollisionFrames[0].first = 0;
		attackY3.mCollision.mCollisionFrames[0].second = 38;
		attackY3.mInputAbleFrame.first = 25;
		attackY3.mInputAbleFrame.second = 40;
		attackY3.mAnimationInterp.mStepInterpStartTime = 11.0f;
		attackY3.mStepAnimationClipName = "RollY3";
		mAttackInformation[AttackID_Y3] = attackY3;
	}

	// Y4攻撃
	{
		PlayerAttack attackY4;
		attackY4.mAttackID = AttackID_Y4;
		attackY4.mNextY = AttackID_NoAttack;
		attackY4.mNextB = AttackID_NoAttack;
		attackY4.mDamage = 10.f;
		attackY4.mAnimationClipName = "Y4";
		attackY4.mCollision.mCollisionOccurrence = 1;
		attackY4.mCollision.mCollisionFrames.resize(attackY4.mCollision.mCollisionOccurrence);
		attackY4.mCollision.mCollisionFrames[0].first = 33;
		attackY4.mCollision.mCollisionFrames[0].second = 60;
		attackY4.mInputAbleFrame.first = 46;
		attackY4.mInputAbleFrame.second = 150;
		attackY4.mAnimationInterp.mStepInterpStartTime = 11.0f;
		attackY4.mStepAnimationClipName = "RollY4";
		mAttackInformation[AttackID_Y4] = attackY4;
	}

	// B1攻撃
	{
		PlayerAttack attackB1;
		attackB1.mAttackID = AttackID_B1;
		attackB1.mNextY = AttackID_NoAttack;
		attackB1.mNextB = AttackID_B2;
		attackB1.mDamage = 10.f;
		attackB1.mAnimationClipName = "B1";
		attackB1.mCollision.mCollisionOccurrence = 1;
		attackB1.mCollision.mCollisionFrames.resize(attackB1.mCollision.mCollisionOccurrence);
		attackB1.mCollision.mCollisionFrames[0].first = 39;
		attackB1.mCollision.mCollisionFrames[0].second = 60;
		attackB1.mInputAbleFrame.first = 55;
		attackB1.mInputAbleFrame.second = 85;
		attackB1.mAnimationInterp.mStepInterpStartTime = 11.0f;
		attackB1.mStepAnimationClipName = "Roll";
		mAttackInformation[AttackID_B1] = attackB1;
	}

	// B2攻撃
	{
		PlayerAttack attackB2;
		attackB2.mAttackID = AttackID_B2;
		attackB2.mNextY = AttackID_NoAttack;
		attackB2.mNextB = AttackID_B3;
		attackB2.mDamage = 10.f;
		attackB2.mAnimationClipName = "B2";
		attackB2.mCollision.mCollisionOccurrence = 2;
		attackB2.mCollision.mCollisionFrames.resize(attackB2.mCollision.mCollisionOccurrence);
		attackB2.mCollision.mCollisionFrames[0].first = 40;
		attackB2.mCollision.mCollisionFrames[0].second = 55;
		attackB2.mCollision.mCollisionFrames[1].first = 68;
		attackB2.mCollision.mCollisionFrames[1].second = 88;
		attackB2.mInputAbleFrame.first = 90;
		attackB2.mInputAbleFrame.second = 110;
		attackB2.mAnimationInterp.mStepInterpStartTime = 11.0f;
		attackB2.mStepAnimationClipName = "Roll";
		mAttackInformation[AttackID_B2] = attackB2;
	}

	// B2-2攻撃
	{
		PlayerAttack attackB2_2;
		attackB2_2.mAttackID = AttackID_B2_2;
		attackB2_2.mNextY = AttackID_Y2;
		attackB2_2.mNextB = AttackID_B3;
		attackB2_2.mDamage = 10.f;
		attackB2_2.mAnimationClipName = "B2_2";
		attackB2_2.mCollision.mCollisionOccurrence = 3;
		attackB2_2.mCollision.mCollisionFrames.resize(attackB2_2.mCollision.mCollisionOccurrence);
		attackB2_2.mCollision.mCollisionFrames[0].first = 40;
		attackB2_2.mCollision.mCollisionFrames[0].second = 55;
		attackB2_2.mCollision.mCollisionFrames[1].first = 68;
		attackB2_2.mCollision.mCollisionFrames[1].second = 88;
		attackB2_2.mCollision.mCollisionFrames[2].first = 109;
		attackB2_2.mCollision.mCollisionFrames[2].second = 119;
		attackB2_2.mInputAbleFrame.first = 130;
		attackB2_2.mInputAbleFrame.second = 165;
		attackB2_2.mAnimationInterp.mStepInterpStartTime = 11.0f;
		attackB2_2.mStepAnimationClipName = "Roll";
		mAttackInformation[AttackID_B2_2] = attackB2_2;
	}

	// B3攻撃
	{
		PlayerAttack attackB3;
		attackB3.mAttackID = AttackID_B3;
		attackB3.mNextY = AttackID_NoAttack;
		attackB3.mNextB = AttackID_NoAttack;
		attackB3.mDamage = 10.f;
		attackB3.mAnimationClipName = "B3";
		attackB3.mCollision.mCollisionOccurrence = 1;
		attackB3.mCollision.mCollisionFrames.resize(attackB3.mCollision.mCollisionOccurrence);
		attackB3.mCollision.mCollisionFrames[0].first = 29;
		attackB3.mCollision.mCollisionFrames[0].second = 50;
		attackB3.mInputAbleFrame.first = 55;
		attackB3.mInputAbleFrame.second = 70;
		attackB3.mAnimationInterp.mStepInterpStartTime = 11.0f;
		attackB3.mStepAnimationClipName = "StepB3";
		mAttackInformation[AttackID_B3] = attackB3;
	}
}

void PlayerAttackData::SaveJsonFile()
{
	AssetManager& assetManager = AssetManager::GetInstance();
	assetManager.ProviderSetting<JsonFileProvider>(true);
	std::shared_ptr<AssetHandle> handle = assetManager.Load<JsonFileProvider>(mAttackDataFilePath);
	assetManager.ProviderSetting<JsonFileProvider>(false);
	if(!handle->IsValid())
	{
		return;
	}

	JsonFile& jsonFile = handle->Get<JsonFile>();
	nlohmann::json& json = jsonFile.GetJson();

	AddAttackDataToJson(json, AttackID_NoAttack, "None");
	AddAttackDataToJson(json, AttackID_Y1, "Y1");
	AddAttackDataToJson(json, AttackID_Y2, "Y2");
	AddAttackDataToJson(json, AttackID_Y3, "Y3");
	AddAttackDataToJson(json, AttackID_Y4, "Y4");
	AddAttackDataToJson(json, AttackID_B1, "B1");
	AddAttackDataToJson(json, AttackID_B2, "B2");
	AddAttackDataToJson(json, AttackID_B3, "B3");
	AddAttackDataToJson(json, AttackID_B2_2, "B2_2");
	AddAttackDataToJson(json, AttackID_Counter, "Counter");

	jsonFile.WriteFile();
}

bool PlayerAttackData::LoadAttackData()
{
	AssetManager& assetManager = AssetManager::GetInstance();
	std::shared_ptr<AssetHandle> handle = assetManager.Load<JsonFileProvider>(mAttackDataFilePath);
	if (!handle->IsValid())
	{
		return false;
	}

	JsonFile& jsonFile = handle->Get<JsonFile>();
	nlohmann::json& json = jsonFile.GetJson();

 	GetAttackDataFromJson(json, AttackID_NoAttack, "None");
	GetAttackDataFromJson(json, AttackID_Y1, "Y1");
	GetAttackDataFromJson(json, AttackID_Y2, "Y2");
	GetAttackDataFromJson(json, AttackID_Y3, "Y3");
	GetAttackDataFromJson(json, AttackID_Y4, "Y4");
	GetAttackDataFromJson(json, AttackID_B1, "B1");
	GetAttackDataFromJson(json, AttackID_B2, "B2");
	GetAttackDataFromJson(json, AttackID_B3, "B3");
	GetAttackDataFromJson(json, AttackID_B2_2, "B2_2");
	GetAttackDataFromJson(json, AttackID_Counter, "Counter");

	return true;
}

void PlayerAttackData::AddAttackDataToJson(nlohmann::json& _json, const PlayerData::AttackID& _attackID, std::string_view _attackName)
{
	PlayerAttack attack = mAttackInformation[_attackID];
	const std::string dataName = _attackName.data();

	// 攻撃ID 次の攻撃ID ダメージ
	{
		std::string attackID = dataName + "AttackID";
		_json[attackID] = attack.mAttackID;

		std::string nextB = dataName + "NextB";
		_json[nextB] = attack.mNextB;

		std::string nextY = dataName + "NextY";
		_json[nextY] = attack.mNextY;

		std::string damage = dataName + "Damage";
		_json[damage] = attack.mDamage;
	}

	// 使用するアニメーションクリップ　ステップアニメーションクリップの名前
	{	
		std::string clipName = dataName + "AnimationClip";
		_json[clipName] = attack.mAnimationClipName;

		std::string stepClipName = dataName + "StepClipName";
		_json[stepClipName] = attack.mStepAnimationClipName;

		stepClipName = dataName + "RightStepClipName";
		_json[stepClipName] = attack.mRightStepAnimationClipName;

		stepClipName = dataName + "LeftStepClipName";
		_json[stepClipName] = attack.mLeftStepAnimationClipName;
	}

	// コリジョン
	{
		PlayerAttackCollision collision = attack.mCollision;

		// コリジョンの発生回数
		std::string collisionOccurrence = dataName + "CollisionOccurrence";
		_json[collisionOccurrence] = collision.mCollisionOccurrence;

		// コリジョンの発生と終了のフレーム
		std::string collisionFrameStart = dataName + "CollisionStart";
		std::string collisionFrameEnd = dataName + "CollisionEnd";
		// データの数だけ書き込む
		for (size_t col_i = 0;const  std::pair<uint16_t, uint16_t>& collisionFrame : collision.mCollisionFrames)
		{
			collisionFrameStart += std::to_string(col_i);
			collisionFrameEnd += std::to_string(col_i);
			_json[collisionFrameStart] = collisionFrame.first;
			_json[collisionFrameEnd] = collisionFrame.second;
			col_i++;
		}
	}

	// 入力可能フレーム
	{
		std::string inputStart = dataName + "InputStart";
		_json[inputStart] = attack.mInputAbleFrame.first;

		std::string inputEnd = dataName + "InputEnd";
		_json[inputEnd] = attack.mInputAbleFrame.second;
	}

	// 次のアニメーションの補間位置
	{
		PlayerNextAnimationClipInterp interpTime = attack.mAnimationInterp;

		std::string interpTimeY = dataName + "InterpTimeY";
		_json[interpTimeY] = interpTime.mYAttackInterpStartTime;

		std::string interpTimeB = dataName + "InterpTimeB";
		_json[interpTimeB] = interpTime.mBAttackInterpStartTime;

		std::string interpTimeStep = dataName + "InterpTimeStep";
		_json[interpTimeStep] = interpTime.mStepInterpStartTime;

		std::string interpTimeLeftStep = dataName + "InterpTimeLeftStep";
		_json[interpTimeLeftStep] = interpTime.mLeftStepInterpStartTime;

		std::string interpTimeRightStep = dataName + "InterpTimeRightStep";
		_json[interpTimeRightStep] = interpTime.mRightStepInterpStartTime;

		std::string interpY = dataName + "InterpY";
		_json[interpY] = interpTime.mYAttackInterpTime;

		std::string interpB = dataName + "InterpB";
		_json[interpB] = interpTime.mBAttackInterpTime;

		std::string interpStep = dataName + "InterpStep";
		_json[interpStep] = interpTime.mStepInterpTime;

		std::string interpLeftStep = dataName + "InterpLeftStep";
		_json[interpLeftStep] = interpTime.mLeftStepInterpTime;

		std::string interpRightStep = dataName + "InterpRightStep";
		_json[interpRightStep] = interpTime.mRightStepInterpTime;

		std::string interpIdleMove = dataName + "IdleMove";
		_json[interpIdleMove] = interpTime.mIdleMoveInterpTime;
	}
}

void PlayerAttackData::GetAttackDataFromJson(nlohmann::json& _json, const PlayerData::AttackID& _attackID, std::string_view _attackName)
{
	PlayerAttack& attack = mAttackInformation[_attackID];
	const std::string dataName = _attackName.data();

	// 攻撃ID 次の攻撃ID ダメージ
	{
		std::string attackID = dataName + "AttackID";
		attack.mAttackID =_json[attackID];

		std::string nextB = dataName + "NextB";
		attack.mNextB = _json[nextB];

		std::string nextY = dataName + "NextY";
		attack.mNextY = _json[nextY];

		std::string damage = dataName + "Damage";
		attack.mDamage = _json[damage];
	}

	// 使用するアニメーションクリップ　ステップアニメーションクリップの名前
	{
		std::string clipName = dataName + "AnimationClip";
		attack.mAnimationClipName = _json[clipName];

		std::string stepClipName = dataName + "StepClipName";
		attack.mStepAnimationClipName = _json[stepClipName];

		stepClipName = dataName + "RightStepClipName";
		attack.mRightStepAnimationClipName = _json[stepClipName];

		stepClipName = dataName + "LeftStepClipName";
		attack.mLeftStepAnimationClipName = _json[stepClipName];
	}

	// コリジョン
	{
		PlayerAttackCollision& collision = attack.mCollision;

		// コリジョンの発生回数
		std::string collisionOccurrence = dataName + "CollisionOccurrence";
		collision.mCollisionOccurrence = _json[collisionOccurrence];

		// 配列の確保
		collision.mCollisionFrames.resize(collision.mCollisionOccurrence);

		// コリジョンの発生と終了のフレーム
		std::string collisionFrameStart = dataName + "CollisionStart";
		std::string collisionFrameEnd = dataName + "CollisionEnd";
		// データの数だけ書き込む
		for (size_t col_i = 0; std::pair<uint16_t, uint16_t>&collisionFrame : collision.mCollisionFrames)
		{
			collisionFrameStart += std::to_string(col_i);
			collisionFrameEnd += std::to_string(col_i);
			collisionFrame.first = _json[collisionFrameStart];
			collisionFrame.second = _json[collisionFrameEnd];
			col_i++;
		}
	}

	// 入力可能フレーム
	{
		std::string inputStart = dataName + "InputStart";
		attack.mInputAbleFrame.first = _json[inputStart];

		std::string inputEnd = dataName + "InputEnd";
		attack.mInputAbleFrame.second = _json[inputEnd];
	}

	// 次のアニメーションの補間位置
	{
		PlayerNextAnimationClipInterp& interpTime = attack.mAnimationInterp;

		std::string interpTimeY = dataName + "InterpTimeY";
		interpTime.mYAttackInterpStartTime = _json[interpTimeY];

		std::string interpTimeB = dataName + "InterpTimeB";
		interpTime.mBAttackInterpStartTime = _json[interpTimeB];

		std::string interpTimeStep = dataName + "InterpTimeStep";
		interpTime.mStepInterpStartTime = _json[interpTimeStep];

		std::string interpTimeLeftStep = dataName + "InterpTimeLeftStep";
		interpTime.mLeftStepInterpStartTime = _json[interpTimeLeftStep];

		std::string interpTimeRightStep = dataName + "InterpTimeRightStep";
		interpTime.mRightStepInterpStartTime = _json[interpTimeRightStep];

		std::string interpY = dataName + "InterpY";
		interpTime.mYAttackInterpTime = _json[interpY];

		std::string interpB = dataName + "InterpB";
		interpTime.mBAttackInterpTime = _json[interpB];

		std::string interpStep = dataName + "InterpStep";
		interpTime.mStepInterpTime = _json[interpStep];

		std::string interpLeftStep = dataName + "InterpLeftStep";
		interpTime.mLeftStepInterpTime = _json[interpLeftStep];

		std::string interpRightStep = dataName + "InterpRightStep";
		interpTime.mRightStepInterpTime = _json[interpRightStep];

		std::string interpIdleMove = dataName + "IdleMove";
		interpTime.mIdleMoveInterpTime = _json[interpIdleMove];
	}
}
