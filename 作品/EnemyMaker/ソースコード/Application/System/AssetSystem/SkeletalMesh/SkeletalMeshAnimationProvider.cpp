//--------------- INCLUDES -----------
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "SkeletalMeshAnimationProvider.h"
#include "SkeletalMeshAnimationData.h"

//---------- LIBRARY -----------
#ifdef _DEBUG
#pragma comment (lib,"assimp-vc142-mtd.lib")
#else
#pragma comment (lib,"assimp-vc142-mt.lib")
#endif // _DEBUG

//--------- NAMESPACEALIAS ----------
namespace DXSimpleMath = DirectX::SimpleMath;

SkeletalMeshAnimationProvider::SkeletalMeshAnimationProvider()
{
	// �����Ȃ�
}

SkeletalMeshAnimationProvider::~SkeletalMeshAnimationProvider()
{
	// �����Ȃ�
}

inline std::shared_ptr<IAsset> SkeletalMeshAnimationProvider::Load(const std::string& _filePath) const
{
	// �A�j���[�V�����A�Z�b�g
	std::shared_ptr<SkeletalMeshAnimationData> skeletalMeshAnimation = std::make_shared<SkeletalMeshAnimationData>();

	// Assimp�̃C���|�[�^�\�ݒ�
	Assimp::Importer importer{};
	importer.SetPropertyBool(AI_CONFIG_IMPORT_FBX_READ_ANIMATIONS, true);

	// �ǂݍ���
	const aiScene* aiScene = importer.ReadFile(_filePath.c_str(), aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);

	// �ǂݍ��݂��ł��Ă��邩���m�F
	if (!aiScene)
	{
		std::cout << "�X�P���^�����b�V���A�j���[�V�����ǂݍ��ݎ��s" << _filePath << std::endl;
		return nullptr;
	}

	// �A�j���[�V�����f�[�^�����݂��邩�m�F
	if (!aiScene->HasAnimations())
	{
		std::cout << _filePath << "����FBX�ɂ̓A�j���[�V�����f�[�^�͂���܂���" << std::endl;
		return nullptr;
	}

	// �A�j���[�V�����̒������擾
	skeletalMeshAnimation->mDuration = static_cast<float>(aiScene->mAnimations[0]->mDuration);

	skeletalMeshAnimation->mTickPerSecond = static_cast<float>(aiScene->mAnimations[0]->mTicksPerSecond);

	// �A�j���[�V�����f�[�^���擾
	std::vector<Channel> channels(aiScene->mAnimations[0]->mNumChannels);
 	for (size_t channel_i = 0; Channel& channel : channels)
	{
		aiNodeAnim* aiChannel = aiScene->mAnimations[0]->mChannels[channel_i];

		channel.mBoneName = aiChannel->mNodeName.C_Str();
		
		// ���W�L�[���擾
		channel.mNumPositionKey = aiChannel->mNumPositionKeys;
		for (size_t position_i = 0; position_i < aiChannel->mNumPositionKeys; position_i++)
		{
			VectorKey positionKey;
			aiVector3D aiPos = aiChannel->mPositionKeys[position_i].mValue;	
			positionKey.mTime = aiChannel->mPositionKeys[position_i].mTime;
			positionKey.mValue = DXSimpleMath::Vector3(aiPos.x, aiPos.y, aiPos.z);
			positionKey.mIndex = channel.mPositionKeys.size();
			channel.mPositionKeys.emplace_back(positionKey);
		}

		// ��]�L�[���擾
		channel.mNumRotationKey = aiChannel->mNumRotationKeys;
		for (size_t rotation_i = 0; rotation_i < aiChannel->mNumRotationKeys; rotation_i++)
		{
			QuaternionKey rotationKey;
			aiQuaternion aiQuat = aiChannel->mRotationKeys[rotation_i].mValue;
			rotationKey.mTime = aiChannel->mRotationKeys[rotation_i].mTime;
			rotationKey.mValue = DXSimpleMath::Quaternion(aiQuat.x, aiQuat.y, aiQuat.z, aiQuat.w);
			rotationKey.mIndex = channel.mRotationKeys.size();
			channel.mRotationKeys.emplace_back(rotationKey);
		}

		// �X�P�[���L�[���擾
		channel.mNumScaleKey = aiChannel->mNumScalingKeys;
		for (size_t scale_i = 0; scale_i < aiChannel->mNumScalingKeys; scale_i++)
		{
			VectorKey scaleKey;
			aiVector3D aiScale = aiChannel->mScalingKeys[scale_i].mValue;
			scaleKey.mTime = aiChannel->mScalingKeys[scale_i].mTime;
			scaleKey.mValue = DXSimpleMath::Vector3(aiScale.x, aiScale.y, aiScale.z);
			scaleKey.mIndex = channel.mScaleKeys.size();
			channel.mScaleKeys.emplace_back(scaleKey);
		}
		channel_i++;
	}

	// �A�j���[�V�����A�Z�b�g�Ƀ`�����l�����Z�b�g
	skeletalMeshAnimation->mChannels = channels;

	return skeletalMeshAnimation;
}

void SkeletalMeshAnimationProvider::Setting()
{
}