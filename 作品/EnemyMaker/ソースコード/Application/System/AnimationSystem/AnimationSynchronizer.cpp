//------------- INCLUDES -----------
#include "AnimationSynchronizer.h"
#include "../../Game/Resource/SkeletalMeshAnimationClip.h"
#include "../../Game/Resource/Skeleton.h"
#include "../../Game/Resource/Bone.h"
#include "../../Utility/MathLibrary.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../ImGui/ImGuiUtility.h"
#include "../../Game/Component/CollisionComponent/CapsuleCollisionComponent.h"
#include "../../Game/Component/SkeletalMeshComponent/SkeletalMeshComponent.h"
#include "../../Utility/Debug.h"
#include "../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"

//------------- NAMESPACEALIAS -----------
namespace DXSimpleMath = DirectX::SimpleMath;

AnimationSynchronizer::AnimationSynchronizer()
	: mMeshOwnerObject(nullptr)
	, mbSynchroPosition(false)
	, mbSynchroRotation(false)
	, mbFirstFrame(false)
	, mbRepeated(false)
	, mbDisplacedStartAnimation(false)
	, mbPrevAnimDisplacedStartAnimation(false)
{
	// �����Ȃ�
}

AnimationSynchronizer::~AnimationSynchronizer()
{
	// �����Ȃ�
}

void AnimationSynchronizer::SynchroBegin(std::shared_ptr<SkeletalMesh> _skeletalMesh, const bool _synchroPosition, const bool _synchroRotation, const bool _repeated, const bool _displaced)
{
	mSkeletalMesh = _skeletalMesh;
	mBone = _skeletalMesh->GetSkeleton().lock()->GetRootBone();
	mMeshOwnerObject = _skeletalMesh->GetOwnerObject();

	// ���W�����t���O�̐ݒ�
	mbRepeated = _repeated;
	mbSynchroPosition = _synchroPosition;
	mbSynchroRotation = _synchroRotation;
	mbFirstFrame = true;
	mbDisplacedStartAnimation = _displaced;

	// �A�j���[�V�����J�n����SkeletalMesh�̃��[���h�s��
	mSkeletalMeshWorldMatrix = _skeletalMesh->GetWorldMatrix();
		
	// �X�P���^�����b�V���̃g�����X�t�H�[�����擾
	mSkeletalMeshTrans = _skeletalMesh->GetWorldTransform();

	// ����Root�{�[���̈ʒu�����߂�
	CalcuRootBoneTransform(mRootBoneTrans);
}

void AnimationSynchronizer::Synchro()
{
	// �Q�Ƃ��L���Ȃ̂����`�F�b�N
	if (!(mBone.lock() && mSkeletalMesh.lock()))
	{
		return;
	}

	// �A�����ē������Ă���A�ŏ��̃t���[���̏���	
	if (mbFirstFrame)
	{
		SyncSetup();
	}
	
	std::shared_ptr<SkeletalMesh> validSkeletalMesh = mSkeletalMesh.lock();

	// ���݂̃��[�g�{�[���̈ʒu�����߂�
	Transform currentBoneTrans;
	CalcuRootBoneTransform(currentBoneTrans);

	// �O�t���[���Ƃ̍��������߂�
	Transform differenceTrans;
	MathLibrary::CalucTransformDifference(currentBoneTrans, mRootBoneTrans, differenceTrans);
	differenceTrans.mPosition.y = 0.0f;
	differenceTrans.mRotation.x = 0.0f;
	differenceTrans.mRotation.z = 0.0f;

	// ���W����
	SyncPosition(differenceTrans.mPosition);

	// ��]����
	SyncRotation(differenceTrans.mRotation);
		
	// �R���W�����Ɠ���
	SynchroCollision(currentBoneTrans);
	
	// �A�j���[�V�����J�n�ʒu�Œ肷��
	validSkeletalMesh->SetWorldMatrix(mSkeletalMeshWorldMatrix);
	mRootBoneTrans = currentBoneTrans;
	mbFirstFrame = false;
}

void AnimationSynchronizer::AnimationEndSync()
{
	// �A�j���[�V�����J�n�ʒu�Œ肷��
	mSkeletalMesh.lock()->SetWorldMatrix(mSkeletalMeshWorldMatrix);
}

void AnimationSynchronizer::SyncPosition(const DirectX::SimpleMath::Vector3& _diffPosition)
{
	// ���W�������Ȃ��Ȃ烊�^�[��
	if (!mbSynchroPosition)
	{
		return;
	}

	// ������GameObject�ɓK��
	std::shared_ptr<TransformComponent> ownerTrans = mMeshOwnerObject->GetComponent<TransformComponent>();

	// ���W����
	if (mbSynchroPosition)
	{
		ownerTrans->AddPosition(_diffPosition);
	}
}

void AnimationSynchronizer::SyncRotation(const DirectX::SimpleMath::Vector3& _diffRotation)
{
	// ������GameObject�ɓK��
	std::shared_ptr<TransformComponent> ownerTrans = mMeshOwnerObject->GetComponent<TransformComponent>();

	if (mbSynchroRotation)
	{
		if (!mbFirstFrame)
		{
			ownerTrans->AddRotation(_diffRotation);
		}
	}
}

void AnimationSynchronizer::SynchroCollision(Transform& _rootBoneTrans)
{
	// �R���W���������邩���m�F
	// ����J�v�Z�������Ȃ̂ŃJ�v�Z���R���W���������邩�m�F����
	std::shared_ptr<CapsuleCollisionComponent> capsule = mMeshOwnerObject->GetComponent<CapsuleCollisionComponent>();

	if (!capsule)
	{
		return;
	}

	// ���t���[���ŃR���W�����ɂ߂荞�݂�����C������Ă�����A���̕��A�j���[�V������������
	if (!capsule->IsCurrentFrameFixOverlap())
	{
		return;
	}

	// �C������Ă�����SkeletalMesh�𓮂���
	// RootBone�̓����ɓ��������Ă���̂ŁAGameObject��RootBone�̈ʒu�̍��������ړ�������
	DXSimpleMath::Vector3 fixVector = mMeshOwnerObject->GetComponent<TransformComponent>()->GetPosition() - _rootBoneTrans.mPosition;
	fixVector.y = 0;
	DXSimpleMath::Matrix fixTranslation;
	MathLibrary::CreateTranslationMatrix(fixVector, fixTranslation);
	mSkeletalMeshWorldMatrix *= fixTranslation;

	// �ړ����RootBone�̈ʒu���v�Z
	DXSimpleMath::Matrix currentBoneMatrix = mBone.lock()->GetBoneMatrix() * mSkeletalMeshWorldMatrix;
	MathLibrary::DecomposeMatrix(currentBoneMatrix, _rootBoneTrans);
}

void AnimationSynchronizer::RepeatSynchroSetup()
{	
	// �X�P���^�����b�V���̈ʒu���Čv�Z
	std::shared_ptr<SkeletalMeshComponent> skeletalMeshComp = mMeshOwnerObject->GetComponent<SkeletalMeshComponent>();
	DXSimpleMath::Matrix meshCompMatrix = MathLibrary::MakeWorldMatrix(skeletalMeshComp->GetTransform());
	DXSimpleMath::Matrix meshOwnerMatrix = mMeshOwnerObject->GetComponent<TransformComponent>()->CalucWorldMatrix(DXSimpleMath::Matrix::Identity);
	mSkeletalMesh.lock()->CalucWorldMatrix(meshCompMatrix * meshOwnerMatrix);
	mSkeletalMeshWorldMatrix = mSkeletalMesh.lock()->GetWorldMatrix();
	mSkeletalMeshTrans = mSkeletalMesh.lock()->GetWorldTransform();

	// ����Root�{�[���̈ʒu�����߂�
	CalcuRootBoneTransform(mRootBoneTrans);
}

void AnimationSynchronizer::SyncSetup()
{
	// �J�n���烋�[�g�̈ʒu�����ꂢ��A�j���[�V�����Ɋւ��Ă͂��̏����͂��Ȃ�
	if (mbRepeated && !mbDisplacedStartAnimation)
	{
		RepeatSynchroSetup();
	}

	// RootBone�ւ̍������v�Z
	CalcuObjectToRootBoneVector();
}

void AnimationSynchronizer::CalcuObjectToRootBoneVector()
{
	// ���[�g�{�[���̈ʒu���v�Z
	Transform rootBoneTrans;
	CalcuRootBoneTransform(rootBoneTrans);

	// �I�[�i�[��GameObject�̃|�W�V�������擾
	DXSimpleMath::Vector3 ownerPosition = mMeshOwnerObject->GetComponent<TransformComponent>()->GetPosition();

	// GameObject��RootBone�̍��������߂�
	mObjectToRootBone = rootBoneTrans.mPosition - ownerPosition;
}

void AnimationSynchronizer::CalcuRootBoneTransform(Transform& _transform)
{
	std::shared_ptr<Bone> validBone = mBone.lock();
	DXSimpleMath::Matrix currentBoneMatrix = validBone->GetBoneMatrix() * mSkeletalMeshWorldMatrix;
	MathLibrary::DecomposeMatrix(currentBoneMatrix, _transform);
}
