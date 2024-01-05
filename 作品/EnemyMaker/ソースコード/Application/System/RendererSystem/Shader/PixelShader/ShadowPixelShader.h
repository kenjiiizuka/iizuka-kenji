#pragma once
#include "PixelShader.h"

//-------- 前方宣言 ---------
class AssetHandle;

class ShadowPixelShader : public PixelShader
{
public:
	ShadowPixelShader(VisualEntity* _entity);
	~ShadowPixelShader();
	void UpdateBuffer(uint8_t _dataID);

	inline void SetShadowMap(ID3D11ShaderResourceView* _shadowMap);

private:
	std::shared_ptr<AssetHandle> mTexture;

	ID3D11ShaderResourceView* mShadowMap;
};

//----------------- INLINES ----------------------

inline void ShadowPixelShader::SetShadowMap(ID3D11ShaderResourceView* _shadowMap)
{
	mShadowMap = _shadowMap;
}