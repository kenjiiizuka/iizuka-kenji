#include "LightPixelShader.h"
#include "../ShaderStruct.h"
#include "../../VisualEntity/VisualEntity.h"
#include "../../VisualEntity/VisualEntityData.h"
#include "../../../AssetSystem/Texture/TextureAssetInclude.h"
#include "../../../../Manager.h"
#include "../../../../Game/Scene/Scene.h"
#include "../../../../Game/GameObject/Light/LightBase.h"
#include "../../../../Game/Scene/SceneManager.h"

using namespace DirectX::SimpleMath;

std::shared_ptr<AssetHandle> LightPixelShader::mRampTexture;

LightPixelShader::LightPixelShader(VisualEntity* _entity)
	: PixelShader(_entity)
{
	LoadWithShaderReflection("PS_Lighting.cso");

	// 生成されていないときのみ読み込む
	if (!mRampTexture)
	{			
		mRampTexture = AssetManager::GetInstance().Load<TextureProvider>("assets/shader/RampTex.bmp");
	}
}

void LightPixelShader::UpdateBuffer(uint8_t _dataID)
{
	// テクスチャのセット
	VisualEntityData::Material mat = mVisualEntity->GetVisualEntityData(_dataID)->GetMaterial();
	if (mat.mTexture.IsValid())
	{
		SetTexture(0,mat.mTexture.GetResource());
	}
	else
	{
		SetTexture(0, mWhiteTexture->Get<Texture>().GetResource());
	}
	
	// ランプテクスチャのセット
	SetTexture(1, mRampTexture->Get<Texture>().GetResource());

	MATERIAL material;
	material.Ambient = mat.mAmbient;
	material.Diffuse = mat.mDiffuse;
	material.Emission = mat.Emission;
	material.Shininess = mat.mShininess;
	material.Specular = mat.mSpecular;
	WriteBuffer(0, &material);

	// ライトのセット
	std::shared_ptr<LightBase> light = SceneManager::GetInstance().GetCurrentScene().lock()->GetGameObject<LightBase>(ELayer::BaseLayer);
	Vector4 lightBuffer[3] = {
		{0.0f,-1.0f,0.0f,0.0f},
		{1.0f,1.0f,1.0f,1.0f},
		{0.3f,0.3f,0.3f,0.3f}
	};
	if (light)
	{	
		GameObject* owner = mVisualEntity->GetOwnerObject();
		Vector3 direction =  owner ? -owner->GetComponent<TransformComponent>()->GetPosition() - light->GetPosition() : light->GetDirection();
		lightBuffer[0] = { direction.x, direction.y, direction.z, 0.0f };
		lightBuffer[1] = light->GetDiffuse();
		lightBuffer[2] = light->GetAmbient();
	}
	WriteBuffer(1, &lightBuffer);
}
