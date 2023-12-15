//---------- INCLUDES ----------
#include "TexturePixelShader.h"
#include "../../VisualEntity/VisualEntity.h"
#include "../ShaderStruct.h"
#include "../../../AssetSystem/Texture/TextureAssetInclude.h"

TexturePixelShader::TexturePixelShader(VisualEntity* _entity)
	: PixelShader(_entity)
{
	LoadWithShaderReflection("PS_Texture.cso");
}

void TexturePixelShader::UpdateBuffer(uint8_t _dataID)
{
	VisualEntityData::Material material = mVisualEntity->GetVisualEntityData(_dataID)->GetMaterial();

	MATERIAL mat;
	if (material.mTexture.IsValid())
	{
		SetTexture(0, material.mTexture.GetResource());
	}
	else
	{
		SetTexture(0, mWhiteTexture->Get<Texture>().GetResource());
	}
	mat.Diffuse = material.mDiffuse;
	mat.Emission = material.Emission;
	mat.Shininess = material.mShininess;
	WriteBuffer(0, &mat);
}
