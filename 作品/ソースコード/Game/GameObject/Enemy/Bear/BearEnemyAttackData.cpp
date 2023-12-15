//---------- INCLUDES ----------
#include "BearEnemyAttackData.h"
#include "../../../../System/AssetSystem/JsonFile/JsonIncludes.h"

BearEnemyAttackData::BearEnemyAttackData()
{
	// �����Ȃ�
}

BearEnemyAttackData::~BearEnemyAttackData()
{
	// �����Ȃ�
}

void BearEnemyAttackData::Initialize()
{
	mAttackInformation.resize(AttackID::Max);

	// �t�@�C������f�[�^��ǂݍ���
	if (LoadData())
	{
		return;
	}

	// �r����
	{
		EnemyAttack swiping;
		swiping.mAnimationClipName = "Swiping";                                                // �g�p����A�j���[�V�����N���b�v�̖��O
		swiping.mCollisionOccurrence = 1;                                                      // �U�������蔻��̔�����
		swiping.mDamagePerCollision.resize(swiping.mCollisionOccurrence);                      // �����蔻�育�̃_���[�W�̐ݒ�
		swiping.mDamagePerCollision[0] = 10.0f;                                                // ���ڂ̓����蔻��̃_���[�W 10.0f
		swiping.mHitReactionPerCollision.resize(swiping.mCollisionOccurrence);                 // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		swiping.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;               // 1��ڂ̓����蔻��̃��A�N�V���� Small
		swiping.mCollisionFrames.resize(swiping.mCollisionOccurrence);                         // �R���W�������Ƃ̓����蔻��̔�������A�j���[�V�����̃t���[�����̊J�n�Ǝn�܂�
		swiping.mCollisionFrames[0].first = 79;
		swiping.mCollisionFrames[0].second = 84;
	
		// �z��ɒǉ�
		mAttackInformation[AttackID::ArmSmash] = swiping;
	}

	// �r�U��グ
	{
		EnemyAttack armUpperSmash;
		armUpperSmash.mAnimationClipName = "ArmUpperSmash";                                                // �g�p����A�j���[�V�����N���b�v�̖��O
		armUpperSmash.mCollisionOccurrence = 1;                                                      // �U�������蔻��̔�����
		armUpperSmash.mDamagePerCollision.resize(armUpperSmash.mCollisionOccurrence);                      // �����蔻�育�̃_���[�W�̐ݒ�
		armUpperSmash.mDamagePerCollision[0] = 10.0f;                                                // ���ڂ̓����蔻��̃_���[�W 10.0f
		armUpperSmash.mHitReactionPerCollision.resize(armUpperSmash.mCollisionOccurrence);                 // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		armUpperSmash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;               // 1��ڂ̓����蔻��̃��A�N�V���� Small
		armUpperSmash.mCollisionFrames.resize(armUpperSmash.mCollisionOccurrence);                         // �R���W�������Ƃ̓����蔻��̔�������A�j���[�V�����̃t���[�����̊J�n�Ǝn�܂�
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
		// �z��ɒǉ�
		mAttackInformation[AttackID::ArmUpperSmash] = armUpperSmash;
	}

	// ����U�艺�낵
	{
		EnemyAttack downwardSlash;
		downwardSlash.mAnimationClipName = "DownwardSlash";                                     // �g�p����A�j���[�V�����N���b�v�̖��O
		downwardSlash.mCollisionOccurrence = 1;                                                 // �U�������蔻��̔�����
		downwardSlash.mDamagePerCollision.resize(downwardSlash.mCollisionOccurrence);           // �����蔻�育�̃_���[�W�̐ݒ�
		downwardSlash.mDamagePerCollision[0] = 10.0f;                                           // ���ڂ̓����蔻��̃_���[�W 10.0f
		downwardSlash.mHitReactionPerCollision.resize(downwardSlash.mCollisionOccurrence);      // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		downwardSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1��ڂ̓����蔻��̃��A�N�V���� Small
		downwardSlash.mCollisionFrames.resize(downwardSlash.mCollisionOccurrence);
		downwardSlash.mCollisionFrames[0].first = 51;
		downwardSlash.mCollisionFrames[0].second = 60;
		// �z��ɒǉ�
		mAttackInformation[DownwardSlash] = downwardSlash;
	}

	// ����U��グ
	{
		EnemyAttack upwardSlash;
		upwardSlash.mAnimationClipName = "UpwardSlash";                                       // �g�p����A�j���[�V�����N���b�v�̖��O
		upwardSlash.mCollisionOccurrence = 1;                                                 // �U�������蔻��̔�����
		upwardSlash.mDamagePerCollision.resize(upwardSlash.mCollisionOccurrence);             // �����蔻�育�̃_���[�W�̐ݒ�
		upwardSlash.mDamagePerCollision[0] = 10.0f;                                           // ���ڂ̓����蔻��̃_���[�W 10.0f
		upwardSlash.mHitReactionPerCollision.resize(upwardSlash.mCollisionOccurrence);        // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		upwardSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1��ڂ̓����蔻��̃��A�N�V���� Small
		upwardSlash.mCollisionFrames.resize(upwardSlash.mCollisionOccurrence);
		upwardSlash.mCollisionFrames[0].first = 61;
		upwardSlash.mCollisionFrames[0].second = 67;

		// �z��ɒǉ�
		mAttackInformation[UpwardSlash] = upwardSlash;	
	}

	// ����2�A�� 
	{
		EnemyAttack doubleSlash;
		doubleSlash.mAnimationClipName = "DoubleSlash";                                       // �g�p����A�j���[�V�����N���b�v�̖��O
		doubleSlash.mCollisionOccurrence = 2;                                                 // �U�������蔻��̔�����
		doubleSlash.mDamagePerCollision.resize(doubleSlash.mCollisionOccurrence);             // �����蔻�育�̃_���[�W�̐ݒ�
		doubleSlash.mDamagePerCollision[0] = 10.0f;                                           // ���ڂ̓����蔻��̃_���[�W 10.0f
		doubleSlash.mDamagePerCollision[1] = 25.0f;                                           // ���ڂ̓����蔻��̃_���[�W 25.0f
		doubleSlash.mHitReactionPerCollision.resize(doubleSlash.mCollisionOccurrence);        // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		doubleSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1��ڂ̓����蔻��̃��A�N�V���� Small
		doubleSlash.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;          // 1��ڂ̓����蔻��̃��A�N�V���� Small
		doubleSlash.mCollisionFrames.resize(doubleSlash.mCollisionOccurrence);
		doubleSlash.mCollisionFrames[0].first = 65;
		doubleSlash.mCollisionFrames[0].second = 83;
		doubleSlash.mCollisionFrames[1].first = 98;
		doubleSlash.mCollisionFrames[1].second = 119;

		// �z��ɒǉ�
		mAttackInformation[DoubleSlash] = doubleSlash;
	}

	// ����2�A�� ��
	{
		EnemyAttack doubleSlashStrong;
		doubleSlashStrong.mAnimationClipName = "DoubleSlashStrong";                                 // �g�p����A�j���[�V�����N���b�v�̖��O
		doubleSlashStrong.mCollisionOccurrence = 2;                                                 // �U�������蔻��̔�����
		doubleSlashStrong.mDamagePerCollision.resize(doubleSlashStrong.mCollisionOccurrence);       // �����蔻�育�̃_���[�W�̐ݒ�
		doubleSlashStrong.mDamagePerCollision[0] = 20.0f;                                           // 1��ڂ̓����蔻��̃_���[�W 20.0f
		doubleSlashStrong.mDamagePerCollision[1] = 25.0f;                                           // 2��ڂ̓����蔻��̃_���[�W 25.0f
		doubleSlashStrong.mHitReactionPerCollision.resize(doubleSlashStrong.mCollisionOccurrence);  // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		doubleSlashStrong.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1��ڂ̓����蔻��̃��A�N�V���� Small
		doubleSlashStrong.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;          // 2��ڂ̓����蔻��̃��A�N�V���� Small
		doubleSlashStrong.mCollisionFrames.resize(doubleSlashStrong.mCollisionOccurrence);
		doubleSlashStrong.mCollisionFrames[0].first = 110;
		doubleSlashStrong.mCollisionFrames[0].second = 130;
		doubleSlashStrong.mCollisionFrames[1].first = 165;
		doubleSlashStrong.mCollisionFrames[1].second = 195;

		// �z��ɒǉ�
		mAttackInformation[DoubleSlash_Strong] = doubleSlashStrong;
	}

	// ����3�A�� 
	{
		EnemyAttack tripleSlash;
		tripleSlash.mAnimationClipName = "TripleSlash";                                 // �g�p����A�j���[�V�����N���b�v�̖��O
		tripleSlash.mCollisionOccurrence = 3;                                           // �U�������蔻��̔�����
		tripleSlash.mDamagePerCollision.resize(tripleSlash.mCollisionOccurrence);       // �����蔻�育�̃_���[�W�̐ݒ�
		tripleSlash.mDamagePerCollision[0] = 20.0f;                                     // 1��ڂ̓����蔻��̃_���[�W 20.0f
		tripleSlash.mDamagePerCollision[1] = 10.0f;                                     // 2��ڂ̓����蔻��̃_���[�W 10.0f
		tripleSlash.mDamagePerCollision[2] = 25.0f;                                     // 3��ڂ̓����蔻��̃_���[�W 25.0f
		tripleSlash.mHitReactionPerCollision.resize(tripleSlash.mCollisionOccurrence);  // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		tripleSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;    // 1��ڂ̓����蔻��̃��A�N�V���� Small
		tripleSlash.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;    // 2��ڂ̓����蔻��̃��A�N�V���� Small
		tripleSlash.mHitReactionPerCollision[2] = CrossCharacter::HitReaction_Small;    // 3��ڂ̓����蔻��̃��A�N�V���� Small
		tripleSlash.mCollisionFrames.resize(tripleSlash.mCollisionOccurrence);
		tripleSlash.mCollisionFrames[0].first = 65;
		tripleSlash.mCollisionFrames[0].second = 78;
		tripleSlash.mCollisionFrames[1].first = 100;
		tripleSlash.mCollisionFrames[1].second = 120;
		tripleSlash.mCollisionFrames[2].first = 176;
		tripleSlash.mCollisionFrames[2].second = 181;

		// �z��ɒǉ�
		mAttackInformation[TripleSlash] = tripleSlash;
	}

	// �W�����v�X���b�V��
	{
		EnemyAttack jumpSlash;
		jumpSlash.mAnimationClipName = "JumpSlash";                                 // �g�p����A�j���[�V�����N���b�v�̖��O
		jumpSlash.mCollisionOccurrence = 1;                                         // �U�������蔻��̔�����
		jumpSlash.mDamagePerCollision.resize(jumpSlash.mCollisionOccurrence);       // �����蔻�育�̃_���[�W�̐ݒ�
		jumpSlash.mDamagePerCollision[0] = 40.0f;                                   // 1��ڂ̓����蔻��̃_���[�W 40.0f
		jumpSlash.mHitReactionPerCollision.resize(jumpSlash.mCollisionOccurrence);  // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		jumpSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;  // 1��ڂ̓����蔻��̃��A�N�V���� Small
		jumpSlash.mCollisionFrames.resize(jumpSlash.mCollisionOccurrence);
		jumpSlash.mCollisionFrames[0].first = 105;
		jumpSlash.mCollisionFrames[0].second = 108;

		// �z��ɒǉ�
		mAttackInformation[JumpSlash] = jumpSlash;
	}

	// ���ƑO�ɕ����U��U��
	{
		EnemyAttack backAndFrontSlash;
		backAndFrontSlash.mAnimationClipName = "BackAndFrontSlash";                                 // �g�p����A�j���[�V�����N���b�v�̖��O
		backAndFrontSlash.mCollisionOccurrence = 2;                                                 // �U�������蔻��̔�����
		backAndFrontSlash.mDamagePerCollision.resize(backAndFrontSlash.mCollisionOccurrence);       // �����蔻�育�̃_���[�W�̐ݒ�
		backAndFrontSlash.mDamagePerCollision[0] = 15.0f;                                           // 1��ڂ̓����蔻��̃_���[�W
		backAndFrontSlash.mDamagePerCollision[1] = 20.0f;                                           // 2��ڂ̓����蔻��̃_���[�W
		backAndFrontSlash.mHitReactionPerCollision.resize(backAndFrontSlash.mCollisionOccurrence);  // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		backAndFrontSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;          // 1��ڂ̓����蔻��̃��A�N�V���� Small
		backAndFrontSlash.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;          // 1��ڂ̓����蔻��̃��A�N�V���� Small
		backAndFrontSlash.mCollisionFrames.resize(backAndFrontSlash.mCollisionOccurrence);
		backAndFrontSlash.mCollisionFrames[0].first = 50;
		backAndFrontSlash.mCollisionFrames[0].second = 70;
		backAndFrontSlash.mCollisionFrames[1].first = 150;
		backAndFrontSlash.mCollisionFrames[1].second = 153;

		// �z��ɒǉ�
		mAttackInformation[BackAndFrontSlash] = backAndFrontSlash;
	}

	// �R��
	{
		EnemyAttack kick;
		kick.mAnimationClipName = "Kick";                                      // �g�p����A�j���[�V�����N���b�v�̖��O
		kick.mCollisionOccurrence = 1;                                         // �U�������蔻��̔�����
		kick.mDamagePerCollision.resize(kick.mCollisionOccurrence);            // �����蔻�育�̃_���[�W�̐ݒ�
		kick.mDamagePerCollision[0] = 10.0f;                                   // 1��ڂ̓����蔻��̃_���[�W 10.0f
		kick.mHitReactionPerCollision.resize(kick.mCollisionOccurrence);       // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		kick.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;  // 1��ڂ̓����蔻��̃��A�N�V���� Small
		kick.mCollisionFrames.resize(kick.mCollisionOccurrence);
		kick.mCollisionFrames[0].first = 35;
		kick.mCollisionFrames[0].second = 43;
		// �z��ɒǉ�
		mAttackInformation[Kick] = kick;
	}

	// �؂艺����
	{
		EnemyAttack backJumpSlash;
		backJumpSlash.mAnimationClipName = "BackJumpSlash";                                      // �g�p����A�j���[�V�����N���b�v�̖��O
		backJumpSlash.mCollisionOccurrence = 1;                                         // �U�������蔻��̔�����
		backJumpSlash.mDamagePerCollision.resize(backJumpSlash.mCollisionOccurrence);            // �����蔻�育�̃_���[�W�̐ݒ�
		backJumpSlash.mDamagePerCollision[0] = 10.0f;                                   // 1��ڂ̓����蔻��̃_���[�W 10.0f
		backJumpSlash.mHitReactionPerCollision.resize(backJumpSlash.mCollisionOccurrence);       // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		backJumpSlash.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;  // 1��ڂ̓����蔻��̃��A�N�V���� Small
		backJumpSlash.mCollisionFrames.resize(backJumpSlash.mCollisionOccurrence);
		backJumpSlash.mCollisionFrames[0].first = 29;
		backJumpSlash.mCollisionFrames[0].second = 43;
		// �z��ɒǉ�
		mAttackInformation[BackJumpSlash] = backJumpSlash;
	}

	// ����U�艺�낵�U�� ��
	{
		EnemyAttack downwardSlashStrong;
		downwardSlashStrong.mAnimationClipName = "DownwardSlashStrong";                                   // �g�p����A�j���[�V�����N���b�v�̖��O
		downwardSlashStrong.mCollisionOccurrence = 1;                                                     // �U�������蔻��̔�����
		downwardSlashStrong.mDamagePerCollision.resize(downwardSlashStrong.mCollisionOccurrence);         // �����蔻�育�̃_���[�W�̐ݒ�
		downwardSlashStrong.mDamagePerCollision[0] = 10.0f;                                               // 1��ڂ̓����蔻��̃_���[�W 10.0f
		downwardSlashStrong.mHitReactionPerCollision.resize(downwardSlashStrong.mCollisionOccurrence);    // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		downwardSlashStrong.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;              // 1��ڂ̓����蔻��̃��A�N�V���� Small
		downwardSlashStrong.mCollisionFrames.resize(downwardSlashStrong.mCollisionOccurrence);
		downwardSlashStrong.mCollisionFrames[0].first = 88;
		downwardSlashStrong.mCollisionFrames[0].second= 92;

		// �z��ɒǉ�
		mAttackInformation[DownwardSlashStrong] = downwardSlashStrong;
	}

	// ����2�A�� �� �Ⴂ
	{
		EnemyAttack doubleSlash_StrongLow;
		doubleSlash_StrongLow.mAnimationClipName = "DoubleSlash_StrongLow";                                 // �g�p����A�j���[�V�����N���b�v�̖��O
		doubleSlash_StrongLow.mCollisionOccurrence = 2;                                                     // �U�������蔻��̔�����
		doubleSlash_StrongLow.mDamagePerCollision.resize(doubleSlash_StrongLow.mCollisionOccurrence);       // �����蔻�育�̃_���[�W�̐ݒ�
		doubleSlash_StrongLow.mDamagePerCollision[0] = 15.0f;                                               // 1��ڂ̓����蔻��̃_���[�W
		doubleSlash_StrongLow.mDamagePerCollision[1] = 20.0f;                                               // 2��ڂ̓����蔻��̃_���[�W
		doubleSlash_StrongLow.mHitReactionPerCollision.resize(doubleSlash_StrongLow.mCollisionOccurrence);  // �����蔻��̂��Ƃ̃q�b�g���A�N�V����
		doubleSlash_StrongLow.mHitReactionPerCollision[0] = CrossCharacter::HitReaction_Small;              // 1��ڂ̓����蔻��̃��A�N�V���� Small
		doubleSlash_StrongLow.mHitReactionPerCollision[1] = CrossCharacter::HitReaction_Small;              // 1��ڂ̓����蔻��̃��A�N�V���� Small
		doubleSlash_StrongLow.mCollisionFrames.resize(doubleSlash_StrongLow.mCollisionOccurrence);
		doubleSlash_StrongLow.mCollisionFrames[0].first = 80;
		doubleSlash_StrongLow.mCollisionFrames[0].second = 105;
		doubleSlash_StrongLow.mCollisionFrames[1].first = 149;
		doubleSlash_StrongLow.mCollisionFrames[1].second = 170;

		// �z��ɒǉ�
		mAttackInformation[DoubleSlash_StrongLow] = doubleSlash_StrongLow;
	}
}

void BearEnemyAttackData::SaveData()
{
	AssetManager::GetInstance().ProviderSetting<JsonFileProvider>(true);
	std::shared_ptr<AssetHandle> handle = AssetManager::GetInstance().Load<JsonFileProvider>(mSaveDataFilePath);
	AssetManager::GetInstance().ProviderSetting<JsonFileProvider>(false);
	// �ǂݍ��݂ł��Ă��邩���m�F����
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

	// �g�p����A�j���[�V�����N���b�v�̖��O
	{
		std::string clipName = dataName + "AnimationClip";
		_json[clipName] = attack.mAnimationClipName;
	}

	// �R���W�����A�_���[�W, HitReaction
	{
		// �R���W�����̔�����
		std::string collisionCount = dataName + "CollisionOccurrence";
		_json[collisionCount] = attack.mCollisionOccurrence;

		// �R���W�����̔����t���[��
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

		// �_���[�W
		for (size_t damage_i = 0; float& damage : attack.mDamagePerCollision)
		{
			std::string damageName = dataName + "Damage";
			damageName += std::to_string(damage_i);
			_json[damageName] = damage;
			damage_i++;
		}

		// �q�b�g���A�N�V����
		for (size_t hitReaction_i = 0; CrossCharacter::HitReaction& reaction : attack.mHitReactionPerCollision)
		{
			std::string hitReactionName = dataName + "HitReaction";
			hitReactionName += std::to_string(hitReaction_i);
			_json[hitReactionName] = reaction;
			hitReaction_i++;
		}
	}

	// ���s����
	{	
		EnemyAttackExecutionConditions& conditions = attack.mExecutionCondition;

		std::string circleNum = dataName + "ExecuteCircleNum";
		_json[circleNum] = conditions.mExecuteCheckCircleNum;

		// ���a
		for (size_t radius_i = 0; float& radius : conditions.mCircleRadius)
		{
			std::string radiusName = dataName + "Radius";
			radiusName += std::to_string(radius_i);
			_json[radiusName] = radius;
			radius_i++;
		}

		// ����
		for (size_t distance_i = 0; float& distance : conditions.mDistance)
		{
			std::string distanceName = dataName + "Distance";
			distanceName += std::to_string(distance_i);
			_json[distanceName] = distance;
			distance_i++;
		}

		// �p�x
		for (size_t angle_i = 0; float& angle : conditions.mAngle)
		{
			std::string angleName = dataName + "Angle";
			angleName += std::to_string(angle_i);
			_json[angleName] = angle;
			angle_i++;
		}
	}

	// �A�j���[�V�����֘A
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

	// �g�p����A�j���[�V�����N���b�v�̖��O
	{
		std::string clipName = dataName + "AnimationClip";
		attack.mAnimationClipName = _json[clipName];
	}

	// �R���W�����A�_���[�W, HitReaction
	{
		// �R���W�����̔�����
		std::string collisionCount = dataName + "CollisionOccurrence";
		attack.mCollisionOccurrence = _json[collisionCount];

		// �R���W�����̔����t���[��
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

		// �_���[�W
		attack.mDamagePerCollision.resize(attack.mCollisionOccurrence);
		for (size_t damage_i = 0; float& damage : attack.mDamagePerCollision)
		{
			std::string damageName = dataName + "Damage";
			damageName += std::to_string(damage_i);
			damage = _json[damageName];
			damage_i++;
		}

		// �q�b�g���A�N�V����
		attack.mHitReactionPerCollision.resize(attack.mCollisionOccurrence);
		for (size_t hitReaction_i = 0; CrossCharacter::HitReaction & reaction : attack.mHitReactionPerCollision)
		{
			std::string hitReactionName = dataName + "HitReaction";
			hitReactionName += std::to_string(hitReaction_i);
			reaction = _json[hitReactionName];
			hitReaction_i++;
		}
	}

	// ���s����
	{
		EnemyAttackExecutionConditions& conditions = attack.mExecutionCondition;

		std::string circleNum = dataName + "ExecuteCircleNum";
		conditions.mExecuteCheckCircleNum = _json[circleNum];

		// ���a
		conditions.mCircleRadius.resize(conditions.mExecuteCheckCircleNum);
		for (size_t radius_i = 0; float& radius : conditions.mCircleRadius)
		{
			std::string radiusName = dataName + "Radius";
			radiusName += std::to_string(radius_i);
			radius = _json[radiusName];
			radius_i++;
		}


		// ����
		conditions.mDistance.resize(conditions.mExecuteCheckCircleNum);
		for (size_t distance_i = 0; float& distance : conditions.mDistance)
		{
			std::string distanceName = dataName + "Distance";
			distanceName += std::to_string(distance_i);
			distance = _json[distanceName];
			distance_i++;
		}

		// �p�x
		conditions.mAngle.resize(conditions.mExecuteCheckCircleNum);
		for (size_t angle_i = 0; float& angle : conditions.mAngle)
		{
			std::string angleName = dataName + "Angle";
			angleName += std::to_string(angle_i);
			angle = _json[angleName];
			angle_i++;
		}
	}

	// �A�j���[�V�����֘A
	{
		std::string idleRunToInterpTime = dataName + "IdleRunInterpTime";
		attack.mToIdleRunInterpTime = _json[idleRunToInterpTime];
	}
}