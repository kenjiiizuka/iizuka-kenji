#include "ShadowPixelShader.h"
#include "../../../AssetSystem/Texture/TextureAssetInclude.h"

ShadowPixelShader::ShadowPixelShader(VisualEntity* _entity)
	: PixelShader(_entity)
	, mShadowMap(nullptr)
{
	LoadWithShaderReflection("PS_Shadow.cso");

	mTexture = AssetManager::GetInstance().Load<TextureProvider>("assets/Field/grass.jpg");
}

ShadowPixelShader::~ShadowPixelShader()
{
	if (mShadowMap) 
	{
		mShadowMap->Release();
	}
}

void ShadowPixelShader::UpdateBuffer(uint8_t _dataID)
{
	SetTexture(0,mTexture->Get<Texture>().GetResource());
	SetTexture(1, mShadowMap);
}

