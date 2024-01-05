#pragma once
#include "PixelShader.h"
class TexturePixelShader : public PixelShader
{
public:
	TexturePixelShader(VisualEntity* _entity);

	void UpdateBuffer(uint8_t _dataID) override;
};

