#include "OutlinePixelShader.h"

OutlinePixelShader::OutlinePixelShader(VisualEntity* _entity)
	: PixelShader(_entity)
	, mOutlineColor(0.0f,0.0f,0.0f,1.0f)
{
	LoadWithShaderReflection("PS_Outline.cso");
}

OutlinePixelShader::~OutlinePixelShader()
{
	// ˆ—‚È‚µ
}

void OutlinePixelShader::UpdateBuffer(uint8_t _dataID)
{
	WriteBuffer(0, &mOutlineColor);
}




