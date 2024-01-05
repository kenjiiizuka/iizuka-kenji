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
	// 処理なし
}

PlayEffectNotify::~PlayEffectNotify()
{
	// 処理なし
}

void PlayEffectNotify::NotifyBegin()
{
	if (!mAssetHandle->IsValid())
	{
		return;
	}

	// エフェクト発生位置を求める

	// メッシュのワールドマトリックスを取得
	std::shared_ptr<TransformComponent> trans =mSkeletalMesh.lock()->GetOwnerObject()->GetComponent<TransformComponent>();
	DirectX::SimpleMath::Matrix meshMatrix = trans->GetWorldMatrix();

	// オフセット行列を作成
	DirectX::SimpleMath::Matrix offset;
	MathLibrary::CreateTranslationMatrix(mOffsetPosition,offset);

	// エフェクトの再生位置を求める
	DirectX::SimpleMath::Vector3 effectPos;
	DirectX::SimpleMath::Matrix effectMatrix = offset * meshMatrix;
	MathLibrary::GetTranslationFromMatrix(effectMatrix, effectPos);

	// エフェクトの再生
	Effekseer::ManagerRef manager = EffectSystem::GetInstance().GetEffekseerManager();
	Effekseer::EffectRef effect = mAssetHandle->Get<EffekseerEffect>().GetEffect();
	mEffectHandle = manager->Play(effect, { effectPos.x, effectPos.y, effectPos.z });

	// 回転の設定
	manager->SetRotation(mEffectHandle, { 0,1,0 }, trans->GetRotation().y);

	// スケールの設定
	manager->SetScale(mEffectHandle, mScale.x, mScale.y, mScale.z);
}

void PlayEffectNotify::LoadEffect(std::string_view _filePath)
{
	// 読み込み
	mAssetHandle = AssetManager::GetInstance().Load<EffekseerEffectProvider>(_filePath.data());
	// 読み込みできているかを確認
	if (!mAssetHandle->IsValid())
	{
		std::cout << _filePath.data() << " エフェクトの読み込み失敗 " << "PlayEffectNotify.cpp" << std::endl;
		return;
	}
}

