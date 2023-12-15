//---------- INCLUDES ----------
#include "BearEnemyAttackData.h"
#include "../../../../System/AssetSystem/JsonFile/JsonIncludes.h"

BearEnemyAttackData::BearEnemyAttackData()
{
	// 処理なし
}

BearEnemyAttackData::~BearEnemyAttackData()
{
	// 処理なし
}

void BearEnemyAttackData::Initialize()
{
	mAttackInformation.resize(AttackID::Max);

	// ファイルからデータを読み込む
	if (LoadData())
	{
		return;
	}

	// 腕殴り
	{
		EnemyAttack swiping;
		swiping.mAnimationClipName = "Swiping";                                                // 使用するアニメーションクリップの名前
		swiping.mCollisionOccurrence = 1;                                                      // 攻撃当たり判定の発生回数
		swiping.mDamagePerCollision.resize(swiping.mCollisionOccurrence);                      // 当たり判定ごのダメージの設定
		swiping.mDamagePerCollision[0] = 10.0f;                                                // 一回目の当たり判定のダメージ 10.0f
		swiping.mHitReactionPerCollision.resize(swiping.mCollisionOccurrence);                 // 当たり判定のごとのヒットリアクション
		swiping.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;               // 1回目の当たり判定のリアクション Small
		swiping.mCollisionFrames.resize(swiping.mCollisionOccurrence);                         // コリジョンごとの当たり判定の発生するアニメーションのフレーム数の開始と始まり
		swiping.mCollisionFrames[0].first = 79;
		swiping.mCollisionFrames[0].second = 84;
	
		// 配列に追加
		mAttackInformation[AttackID::ArmSmash] = swiping;
	}

	// 腕振り上げ
	{
		EnemyAttack armUpperSmash;
		armUpperSmash.mAnimationClipName = "ArmUpperSmash";                                                // 使用するアニメーションクリップの名前
		armUpperSmash.mCollisionOccurrence = 1;                                                      // 攻撃当たり判定の発生回数
		armUpperSmash.mDamagePerCollision.resize(armUpperSmash.mCollisionOccurrence);                      // 当たり判定ごのダメージの設定
		armUpperSmash.mDamagePerCollision[0] = 10.0f;                                                // 一回目の当たり判定のダメージ 10.0f
		armUpperSmash.mHitReactionPerCollision.resize(armUpperSmash.mCollisionOccurrence);                 // 当たり判定のごとのヒットリアクション
		armUpperSmash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;               // 1回目の当たり判定のリアクション Small
		armUpperSmash.mCollisionFrames.resize(armUpperSmash.mCollisionOccurrence);                         // コリジョンごとの当たり判定の発生するアニメーションのフレーム数の開始と始まり
		armUpperSmash.mCollisionFrames[0].first = 37;
		armUpperSmash.mCollisionFrames[0].second = 60;

		EnemyAttackExecutionConditions& condition = armUpperSmash.mExecutionCondition;
		condition.mExecuteCheckCircleNum = 1;
		condition.mCircleRadius.resize(condition.mExecuteCheckCircleNum);
		condition.mDistance.resize(condition.mExecuteCheckCircleNum);
		condition.mAngle.resize(condition.mExecuteCheckCircleNum);
		condition.mAngle[0] = 0.0f;
		condition.mCircleRadius[0] = 2.0f;
		condition.mDistance[0] = 5.0;
		// 配列に追加
		mAttackInformation[AttackID::ArmUpperSmash] = armUpperSmash;
	}

	// 武器振り下ろし
	{
		EnemyAttack downwardSlash;
		downwardSlash.mAnimationClipName = "DownwardSlash";                                     // 使用するアニメーションクリップの名前
		downwardSlash.mCollisionOccurrence = 1;                                                 // 攻撃当たり判定の発生回数
		downwardSlash.mDamagePerCollision.resize(downwardSlash.mCollisionOccurrence);           // 当たり判定ごのダメージの設定
		downwardSlash.mDamagePerCollision[0] = 10.0f;                                           // 一回目の当たり判定のダメージ 10.0f
		downwardSlash.mHitReactionPerCollision.resize(downwardSlash.mCollisionOccurrence);      // 当たり判定のごとのヒットリアクション
		downwardSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1回目の当たり判定のリアクション Small
		downwardSlash.mCollisionFrames.resize(downwardSlash.mCollisionOccurrence);
		downwardSlash.mCollisionFrames[0].first = 51;
		downwardSlash.mCollisionFrames[0].second = 60;
		// 配列に追加
		mAttackInformation[DownwardSlash] = downwardSlash;
	}

	// 武器振り上げ
	{
		EnemyAttack upwardSlash;
		upwardSlash.mAnimationClipName = "UpwardSlash";                                       // 使用するアニメーションクリップの名前
		upwardSlash.mCollisionOccurrence = 1;                                                 // 攻撃当たり判定の発生回数
		upwardSlash.mDamagePerCollision.resize(upwardSlash.mCollisionOccurrence);             // 当たり判定ごのダメージの設定
		upwardSlash.mDamagePerCollision[0] = 10.0f;                                           // 一回目の当たり判定のダメージ 10.0f
		upwardSlash.mHitReactionPerCollision.resize(upwardSlash.mCollisionOccurrence);        // 当たり判定のごとのヒットリアクション
		upwardSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1回目の当たり判定のリアクション Small
		upwardSlash.mCollisionFrames.resize(upwardSlash.mCollisionOccurrence);
		upwardSlash.mCollisionFrames[0].first = 61;
		upwardSlash.mCollisionFrames[0].second = 67;

		// 配列に追加
		mAttackInformation[UpwardSlash] = upwardSlash;	
	}

	// 武器2連撃 
	{
		EnemyAttack doubleSlash;
		doubleSlash.mAnimationClipName = "DoubleSlash";                                       // 使用するアニメーションクリップの名前
		doubleSlash.mCollisionOccurrence = 2;                                                 // 攻撃当たり判定の発生回数
		doubleSlash.mDamagePerCollision.resize(doubleSlash.mCollisionOccurrence);             // 当たり判定ごのダメージの設定
		doubleSlash.mDamagePerCollision[0] = 10.0f;                                           // 一回目の当たり判定のダメージ 10.0f
		doubleSlash.mDamagePerCollision[1] = 25.0f;                                           // 一回目の当たり判定のダメージ 25.0f
		doubleSlash.mHitReactionPerCollision.resize(doubleSlash.mCollisionOccurrence);        // 当たり判定のごとのヒットリアクション
		doubleSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1回目の当たり判定のリアクション Small
		doubleSlash.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;          // 1回目の当たり判定のリアクション Small
		doubleSlash.mCollisionFrames.resize(doubleSlash.mCollisionOccurrence);
		doubleSlash.mCollisionFrames[0].first = 65;
		doubleSlash.mCollisionFrames[0].second = 83;
		doubleSlash.mCollisionFrames[1].first = 98;
		doubleSlash.mCollisionFrames[1].second = 119;

		// 配列に追加
		mAttackInformation[DoubleSlash] = doubleSlash;
	}

	// 武器2連撃 強
	{
		EnemyAttack doubleSlashStrong;
		doubleSlashStrong.mAnimationClipName = "DoubleSlashStrong";                                 // 使用するアニメーションクリップの名前
		doubleSlashStrong.mCollisionOccurrence = 2;                                                 // 攻撃当たり判定の発生回数
		doubleSlashStrong.mDamagePerCollision.resize(doubleSlashStrong.mCollisionOccurrence);       // 当たり判定ごのダメージの設定
		doubleSlashStrong.mDamagePerCollision[0] = 20.0f;                                           // 1回目の当たり判定のダメージ 20.0f
		doubleSlashStrong.mDamagePerCollision[1] = 25.0f;                                           // 2回目の当たり判定のダメージ 25.0f
		doubleSlashStrong.mHitReactionPerCollision.resize(doubleSlashStrong.mCollisionOccurrence);  // 当たり判定のごとのヒットリアクション
		doubleSlashStrong.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1回目の当たり判定のリアクション Small
		doubleSlashStrong.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;          // 2回目の当たり判定のリアクション Small
		doubleSlashStrong.mCollisionFrames.resize(doubleSlashStrong.mCollisionOccurrence);
		doubleSlashStrong.mCollisionFrames[0].first = 110;
		doubleSlashStrong.mCollisionFrames[0].second = 130;
		doubleSlashStrong.mCollisionFrames[1].first = 165;
		doubleSlashStrong.mCollisionFrames[1].second = 195;

		// 配列に追加
		mAttackInformation[DoubleSlash_Strong] = doubleSlashStrong;
	}

	// 武器3連撃 
	{
		EnemyAttack tripleSlash;
		tripleSlash.mAnimationClipName = "TripleSlash";                                 // 使用するアニメーションクリップの名前
		tripleSlash.mCollisionOccurrence = 3;                                           // 攻撃当たり判定の発生回数
		tripleSlash.mDamagePerCollision.resize(tripleSlash.mCollisionOccurrence);       // 当たり判定ごのダメージの設定
		tripleSlash.mDamagePerCollision[0] = 20.0f;                                     // 1回目の当たり判定のダメージ 20.0f
		tripleSlash.mDamagePerCollision[1] = 10.0f;                                     // 2回目の当たり判定のダメージ 10.0f
		tripleSlash.mDamagePerCollision[2] = 25.0f;                                     // 3回目の当たり判定のダメージ 25.0f
		tripleSlash.mHitReactionPerCollision.resize(tripleSlash.mCollisionOccurrence);  // 当たり判定のごとのヒットリアクション
		tripleSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;    // 1回目の当たり判定のリアクション Small
		tripleSlash.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;    // 2回目の当たり判定のリアクション Small
		tripleSlash.mHitReactionPerCollision[2] = CrossCharacter::HitReaction_Small;    // 3回目の当たり判定のリアクション Small
		tripleSlash.mCollisionFrames.resize(tripleSlash.mCollisionOccurrence);
		tripleSlash.mCollisionFrames[0].first = 65;
		tripleSlash.mCollisionFrames[0].second = 78;
		tripleSlash.mCollisionFrames[1].first = 100;
		tripleSlash.mCollisionFrames[1].second = 120;
		tripleSlash.mCollisionFrames[2].first = 176;
		tripleSlash.mCollisionFrames[2].second = 181;

		// 配列に追加
		mAttackInformation[TripleSlash] = tripleSlash;
	}

	// ジャンプスラッシュ
	{
		EnemyAttack jumpSlash;
		jumpSlash.mAnimationClipName = "JumpSlash";                                 // 使用するアニメーションクリップの名前
		jumpSlash.mCollisionOccurrence = 1;                                         // 攻撃当たり判定の発生回数
		jumpSlash.mDamagePerCollision.resize(jumpSlash.mCollisionOccurrence);       // 当たり判定ごのダメージの設定
		jumpSlash.mDamagePerCollision[0] = 40.0f;                                   // 1回目の当たり判定のダメージ 40.0f
		jumpSlash.mHitReactionPerCollision.resize(jumpSlash.mCollisionOccurrence);  // 当たり判定のごとのヒットリアクション
		jumpSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;  // 1回目の当たり判定のリアクション Small
		jumpSlash.mCollisionFrames.resize(jumpSlash.mCollisionOccurrence);
		jumpSlash.mCollisionFrames[0].first = 105;
		jumpSlash.mCollisionFrames[0].second = 108;

		// 配列に追加
		mAttackInformation[JumpSlash] = jumpSlash;
	}

	// 後ろと前に武器を振る攻撃
	{
		EnemyAttack backAndFrontSlash;
		backAndFrontSlash.mAnimationClipName = "BackAndFrontSlash";                                 // 使用するアニメーションクリップの名前
		backAndFrontSlash.mCollisionOccurrence = 2;                                                 // 攻撃当たり判定の発生回数
		backAndFrontSlash.mDamagePerCollision.resize(backAndFrontSlash.mCollisionOccurrence);       // 当たり判定ごのダメージの設定
		backAndFrontSlash.mDamagePerCollision[0] = 15.0f;                                           // 1回目の当たり判定のダメージ
		backAndFrontSlash.mDamagePerCollision[1] = 20.0f;                                           // 2回目の当たり判定のダメージ
		backAndFrontSlash.mHitReactionPerCollision.resize(backAndFrontSlash.mCollisionOccurrence);  // 当たり判定のごとのヒットリアクション
		backAndFrontSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1回目の当たり判定のリアクション Small
		backAndFrontSlash.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;          // 1回目の当たり判定のリアクション Small
		backAndFrontSlash.mCollisionFrames.resize(backAndFrontSlash.mCollisionOccurrence);
		backAndFrontSlash.mCollisionFrames[0].first = 50;
		backAndFrontSlash.mCollisionFrames[0].second = 70;
		backAndFrontSlash.mCollisionFrames[1].first = 150;
		backAndFrontSlash.mCollisionFrames[1].second = 153;

		// 配列に追加
		mAttackInformation[BackAndFrontSlash] = backAndFrontSlash;
	}

	// 蹴り
	{
		EnemyAttack kick;
		kick.mAnimationClipName = "Kick";                                      // 使用するアニメーションクリップの名前
		kick.mCollisionOccurrence = 1;                                         // 攻撃当たり判定の発生回数
		kick.mDamagePerCollision.resize(kick.mCollisionOccurrence);            // 当たり判定ごのダメージの設定
		kick.mDamagePerCollision[0] = 10.0f;                                   // 1回目の当たり判定のダメージ 10.0f
		kick.mHitReactionPerCollision.resize(kick.mCollisionOccurrence);       // 当たり判定のごとのヒットリアクション
		kick.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;  // 1回目の当たり判定のリアクション Small
		kick.mCollisionFrames.resize(kick.mCollisionOccurrence);
		kick.mCollisionFrames[0].first = 35;
		kick.mCollisionFrames[0].second = 43;
		// 配列に追加
		mAttackInformation[Kick] = kick;
	}

	// 切り下がり
	{
		EnemyAttack backJumpSlash;
		backJumpSlash.mAnimationClipName = "BackJumpSlash";                                      // 使用するアニメーションクリップの名前
		backJumpSlash.mCollisionOccurrence = 1;                                         // 攻撃当たり判定の発生回数
		backJumpSlash.mDamagePerCollision.resize(backJumpSlash.mCollisionOccurrence);            // 当たり判定ごのダメージの設定
		backJumpSlash.mDamagePerCollision[0] = 10.0f;                                   // 1回目の当たり判定のダメージ 10.0f
		backJumpSlash.mHitReactionPerCollision.resize(backJumpSlash.mCollisionOccurrence);       // 当たり判定のごとのヒットリアクション
		backJumpSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;  // 1回目の当たり判定のリアクション Small
		backJumpSlash.mCollisionFrames.resize(backJumpSlash.mCollisionOccurrence);
		backJumpSlash.mCollisionFrames[0].first = 29;
		backJumpSlash.mCollisionFrames[0].second = 43;
		// 配列に追加
		mAttackInformation[BackJumpSlash] = backJumpSlash;
	}

	// 武器振り下ろし攻撃 強
	{
		EnemyAttack downwardSlashStrong;
		downwardSlashStrong.mAnimationClipName = "DownwardSlashStrong";                                   // 使用するアニメーションクリップの名前
		downwardSlashStrong.mCollisionOccurrence = 1;                                                     // 攻撃当たり判定の発生回数
		downwardSlashStrong.mDamagePerCollision.resize(downwardSlashStrong.mCollisionOccurrence);         // 当たり判定ごのダメージの設定
		downwardSlashStrong.mDamagePerCollision[0] = 10.0f;                                               // 1回目の当たり判定のダメージ 10.0f
		downwardSlashStrong.mHitReactionPerCollision.resize(downwardSlashStrong.mCollisionOccurrence);    // 当たり判定のごとのヒットリアクション
		downwardSlashStrong.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;              // 1回目の当たり判定のリアクション Small
		downwardSlashStrong.mCollisionFrames.resize(downwardSlashStrong.mCollisionOccurrence);
		downwardSlashStrong.mCollisionFrames[0].first = 88;
		downwardSlashStrong.mCollisionFrames[0].second= 92;

		// 配列に追加
		mAttackInformation[DownwardSlashStrong] = downwardSlashStrong;
	}

	// 武器2連撃 強 低い
	{
		EnemyAttack doubleSlash_StrongLow;
		doubleSlash_StrongLow.mAnimationClipName = "DoubleSlash_StrongLow";                                 // 使用するアニメーションクリップの名前
		doubleSlash_StrongLow.mCollisionOccurrence = 2;                                                     // 攻撃当たり判定の発生回数
		doubleSlash_StrongLow.mDamagePerCollision.resize(doubleSlash_StrongLow.mCollisionOccurrence);       // 当たり判定ごのダメージの設定
		doubleSlash_StrongLow.mDamagePerCollision[0] = 15.0f;                                               // 1回目の当たり判定のダメージ
		doubleSlash_StrongLow.mDamagePerCollision[1] = 20.0f;                                               // 2回目の当たり判定のダメージ
		doubleSlash_StrongLow.mHitReactionPerCollision.resize(doubleSlash_StrongLow.mCollisionOccurrence);  // 当たり判定のごとのヒットリアクション
		doubleSlash_StrongLow.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;              // 1回目の当たり判定のリアクション Small
		doubleSlash_StrongLow.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;              // 1回目の当たり判定のリアクション Small
		doubleSlash_StrongLow.mCollisionFrames.resize(doubleSlash_StrongLow.mCollisionOccurrence);
		doubleSlash_StrongLow.mCollisionFrames[0].first = 80;
		doubleSlash_StrongLow.mCollisionFrames[0].second = 105;
		doubleSlash_StrongLow.mCollisionFrames[1].first = 149;
		doubleSlash_StrongLow.mCollisionFrames[1].second = 170;

		// 配列に追加
		mAttackInformation[DoubleSlash_StrongLow] = doubleSlash_StrongLow;
	}
}

void BearEnemyAttackData::SaveData()
{
	AssetManager::GetInstance().ProviderSetting<JsonFileProvider>(true);
	std::shared_ptr<AssetHandle> handle = AssetManager::GetInstance().Load<JsonFileProvider>(mSaveDataFilePath);
	AssetManager::GetInstance().ProviderSetting<JsonFileProvider>(false);
	// 読み込みできているかを確認する
	if (!handle->IsValid())
	{
		return;
	}

	JsonFile& jsonFile = handle->Get<JsonFile>();
	nlohmann::json& json = jsonFile.GetJson();

	AddAttackDataToJson(json, AttackID::ArmSmash, "ArmSmash");
	AddAttackDataToJson(json, AttackID::ArmUpperSmash, "ArmUpperSmash");
	AddAttackDataToJson(json, AttackID::DownwardSlash, "DownwardSlash");
	AddAttackDataToJson(json, AttackID::DownwardSlashStrong, "DownwardSlashStrong");
	AddAttackDataToJson(json, AttackID::UpwardSlash, "UpwardSlash");
	AddAttackDataToJson(json, AttackID::DoubleSlash, "DoubleSlash");
	AddAttackDataToJson(json, AttackID::DoubleSlash_Strong, "DoubleSlash_Strong");
	AddAttackDataToJson(json, AttackID::DoubleSlash_StrongLow, "DoubleSlash_StrongLow");
	AddAttackDataToJson(json, AttackID::TripleSlash, "TripleSlash");
	AddAttackDataToJson(json, AttackID::JumpSlash, "JumpSlash");
	AddAttackDataToJson(json, AttackID::BackAndFrontSlash, "BackAndFrontSlash");
	AddAttackDataToJson(json, AttackID::Kick, "Kick");
	AddAttackDataToJson(json, AttackID::BackJumpSlash, "BackJumpSlash");
	
	jsonFile.WriteFile();
}

void BearEnemyAttackData::AddAttackDataToJson(nlohmann::json& _json, const AttackID& _id, std::string_view _dataName)
{
	EnemyAttack attack = mAttackInformation[_id];
	const std::string dataName = _dataName.data();

	// 使用するアニメーションクリップの名前
	{
		std::string clipName = dataName + "AnimationClip";
		_json[clipName] = attack.mAnimationClipName;
	}

	// コリジョン、ダメージ, HitReaction
	{
		// コリジョンの発生回数
		std::string collisionCount = dataName + "CollisionOccurrence";
		_json[collisionCount] = attack.mCollisionOccurrence;

		// コリジョンの発生フレーム
		for (size_t frame_i = 0; std::pair<uint16_t, uint16_t>& collisionFrame : attack.mCollisionFrames)
		{
			std::string frameStart = dataName + "Start";
			frameStart += std::to_string(frame_i);
			
			std::string frameEnd = dataName + "End";
			frameEnd += std::to_string(frame_i);

			_json[frameStart] = collisionFrame.first;
			_json[frameEnd] = collisionFrame.second;

			frame_i++;
		}

		// ダメージ
		for (size_t damage_i = 0; float& damage : attack.mDamagePerCollision)
		{
			std::string damageName = dataName + "Damage";
			damageName += std::to_string(damage_i);
			_json[damageName] = damage;
			damage_i++;
		}

		// ヒットリアクション
		for (size_t hitReaction_i = 0; CrossCharacter::HitReaction& reaction : attack.mHitReactionPerCollision)
		{
			std::string hitReactionName = dataName + "HitReaction";
			hitReactionName += std::to_string(hitReaction_i);
			_json[hitReactionName] = reaction;
			hitReaction_i++;
		}
	}

	// 実行条件
	{	
		EnemyAttackExecutionConditions& conditions = attack.mExecutionCondition;

		std::string circleNum = dataName + "ExecuteCircleNum";
		_json[circleNum] = conditions.mExecuteCheckCircleNum;

		// 半径
		for (size_t radius_i = 0; float& radius : conditions.mCircleRadius)
		{
			std::string radiusName = dataName + "Radius";
			radiusName += std::to_string(radius_i);
			_json[radiusName] = radius;
			radius_i++;
		}

		// 距離
		for (size_t distance_i = 0; float& distance : conditions.mDistance)
		{
			std::string distanceName = dataName + "Distance";
			distanceName += std::to_string(distance_i);
			_json[distanceName] = distance;
			distance_i++;
		}

		// 角度
		for (size_t angle_i = 0; float& angle : conditions.mAngle)
		{
			std::string angleName = dataName + "Angle";
			angleName += std::to_string(angle_i);
			_json[angleName] = angle;
			angle_i++;
		}
	}

	// アニメーション関連
	{
		std::string idleRunToInterpTime = dataName + "IdleRunInterpTime";
		_json[idleRunToInterpTime] = attack.mToIdleRunInterpTime;
	}
}

bool BearEnemyAttackData::LoadData()
{
	std::shared_ptr<AssetHandle> handle = AssetManager::GetInstance().Load<JsonFileProvider>(mSaveDataFilePath);
	if (!handle->IsValid())
	{
		return false;
	}

	JsonFile& jsonFile = handle->Get<JsonFile>();
	nlohmann::json& json = jsonFile.GetJson();

	GetAttackDataFromJson(json, AttackID::ArmSmash, "ArmSmash");
	GetAttackDataFromJson(json, AttackID::ArmUpperSmash, "ArmUpperSmash");
	GetAttackDataFromJson(json, AttackID::DownwardSlash, "DownwardSlash");
	GetAttackDataFromJson(json, AttackID::DownwardSlashStrong, "DownwardSlashStrong");
	GetAttackDataFromJson(json, AttackID::UpwardSlash, "UpwardSlash");
	GetAttackDataFromJson(json, AttackID::DoubleSlash, "DoubleSlash");
	GetAttackDataFromJson(json, AttackID::DoubleSlash_Strong, "DoubleSlash_Strong");
	GetAttackDataFromJson(json, AttackID::DoubleSlash_StrongLow, "DoubleSlash_StrongLow");
	GetAttackDataFromJson(json, AttackID::TripleSlash, "TripleSlash");
	GetAttackDataFromJson(json, AttackID::JumpSlash, "JumpSlash");
	GetAttackDataFromJson(json, AttackID::BackAndFrontSlash, "BackAndFrontSlash");
	GetAttackDataFromJson(json, AttackID::Kick, "Kick");
	GetAttackDataFromJson(json, AttackID::BackJumpSlash, "BackJumpSlash");

	return true;
}

void BearEnemyAttackData::GetAttackDataFromJson(nlohmann::json& _json, const AttackID& _id, std::string_view _dataName)
{
	EnemyAttack& attack = mAttackInformation[_id];
	const std::string dataName = _dataName.data();

	// 使用するアニメーションクリップの名前
	{
		std::string clipName = dataName + "AnimationClip";
		attack.mAnimationClipName = _json[clipName];
	}

	// コリジョン、ダメージ, HitReaction
	{
		// コリジョンの発生回数
		std::string collisionCount = dataName + "CollisionOccurrence";
		attack.mCollisionOccurrence = _json[collisionCount];

		// コリジョンの発生フレーム
		attack.mCollisionFrames.resize(attack.mCollisionOccurrence);
		for (size_t frame_i = 0; std::pair<uint16_t, uint16_t>&collisionFrame : attack.mCollisionFrames)
		{
			std::string frameStart = dataName + "Start";
			frameStart += std::to_string(frame_i);

			std::string frameEnd = dataName + "End";
			frameEnd += std::to_string(frame_i);

			collisionFrame.first = _json[frameStart];
			collisionFrame.second = _json[frameEnd];
			frame_i++;
		}

		// ダメージ
		attack.mDamagePerCollision.resize(attack.mCollisionOccurrence);
		for (size_t damage_i = 0; float& damage : attack.mDamagePerCollision)
		{
			std::string damageName = dataName + "Damage";
			damageName += std::to_string(damage_i);
			damage = _json[damageName];
			damage_i++;
		}

		// ヒットリアクション
		attack.mHitReactionPerCollision.resize(attack.mCollisionOccurrence);
		for (size_t hitReaction_i = 0; CrossCharacter::HitReaction & reaction : attack.mHitReactionPerCollision)
		{
			std::string hitReactionName = dataName + "HitReaction";
			hitReactionName += std::to_string(hitReaction_i);
			reaction = _json[hitReactionName];
			hitReaction_i++;
		}
	}

	// 実行条件
	{
		EnemyAttackExecutionConditions& conditions = attack.mExecutionCondition;

		std::string circleNum = dataName + "ExecuteCircleNum";
		conditions.mExecuteCheckCircleNum = _json[circleNum];

		// 半径
		conditions.mCircleRadius.resize(conditions.mExecuteCheckCircleNum);
		for (size_t radius_i = 0; float& radius : conditions.mCircleRadius)
		{
			std::string radiusName = dataName + "Radius";
			radiusName += std::to_string(radius_i);
			radius = _json[radiusName];
			radius_i++;
		}


		// 距離
		conditions.mDistance.resize(conditions.mExecuteCheckCircleNum);
		for (size_t distance_i = 0; float& distance : conditions.mDistance)
		{
			std::string distanceName = dataName + "Distance";
			distanceName += std::to_string(distance_i);
			distance = _json[distanceName];
			distance_i++;
		}

		// 角度
		conditions.mAngle.resize(conditions.mExecuteCheckCircleNum);
		for (size_t angle_i = 0; float& angle : conditions.mAngle)
		{
			std::string angleName = dataName + "Angle";
			angleName += std::to_string(angle_i);
			angle = _json[angleName];
			angle_i++;
		}
	}

	// アニメーション関連
	{
		std::string idleRunToInterpTime = dataName + "IdleRunInterpTime";
		attack.mToIdleRunInterpTime = _json[idleRunToInterpTime];
	}
}