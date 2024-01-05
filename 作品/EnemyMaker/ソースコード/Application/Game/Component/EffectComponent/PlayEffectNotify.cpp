//-------- INCLUDES ----------
#include "PlayEffectNotify.h"
#include "../../../System/AssetSystem/Effect/EffectAssetInclude.h"
#include "../../../System/Effekseer/EffectSystem.h"
#include "../../Resource/SkeletalMesh.h"
#include "../../GameObject/GameObject.h"
#include "../../../Utility/MathLibrary.h"

PlayEffectNotify::PlayEffectNotify(SkeletalMeshAnimationClip* _attachAnimation, float _attachFrame)
	: AnimationNotify(_attachAnimation, _attachFrame)
	, mEffectHandle(0)
	, mScale{1,1,1}
{
	// �����Ȃ�
}

PlayEffectNotify::~PlayEffectNotify()
{
	// �����Ȃ�
}

void PlayEffectNotify::NotifyBegin()
{
	if (!mAssetHandle->IsValid())
	{
		return;
	}

	// �G�t�F�N�g�����ʒu�����߂�

	// ���b�V���̃��[���h�}�g���b�N�X���擾
	std::shared_ptr<TransformComponent> trans =mSkeletalMesh.lock()->GetOwnerObject()->GetComponent<TransformComponent>();
	DirectX::SimpleMath::Matrix meshMatrix = trans->GetWorldMatrix();

	// �I�t�Z�b�g�s����쐬
	DirectX::SimpleMath::Matrix offset;
	MathLibrary::CreateTranslationMatrix(mOffsetPosition,offset);

	// �G�t�F�N�g�̍Đ��ʒu�����߂�
	DirectX::SimpleMath::Vector3 effectPos;
	DirectX::SimpleMath::Matrix effectMatrix = offset * meshMatrix;
	MathLibrary::GetTranslationFromMatrix(effectMatrix, effectPos);

	// �G�t�F�N�g�̍Đ�
	Effekseer::ManagerRef manager = EffectSystem::GetInstance().GetEffekseerManager();
	Effekseer::EffectRef effect = mAssetHandle->Get<EffekseerEffect>().GetEffect();
	mEffectHandle = manager->Play(effect, { effectPos.x, effectPos.y, effectPos.z });

	// ��]�̐ݒ�
	manager->SetRotation(mEffectHandle, { 0,1,0 }, trans->GetRotation().y);

	// �X�P�[���̐ݒ�
	manager->SetScale(mEffectHandle, mScale.x, mScale.y, mScale.z);
}

void PlayEffectNotify::LoadEffect(std::string_view _filePath)
{
	// �ǂݍ���
	mAssetHandle = AssetManager::GetInstance().Load<EffekseerEffectProvider>(_filePath.data());
	// �ǂݍ��݂ł��Ă��邩���m�F
	if (!mAssetHandle->IsValid())
	{
		std::cout << _filePath.data() << " �G�t�F�N�g�̓ǂݍ��ݎ��s " << "PlayEffectNotify.cpp" << std::endl;
		return;
	}
}

