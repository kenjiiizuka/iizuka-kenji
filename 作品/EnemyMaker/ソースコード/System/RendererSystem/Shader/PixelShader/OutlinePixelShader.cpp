#include "OutlinePixelShader.h"

OutlinePixelShader::OutlinePixelShader(VisualEntity* _entity)
	: PixelShader(_entity)
{
	LoadWithShaderReflection("PS_Outline.cso");
}

OutlinePixelShader::~OutlinePixelShader()
{
	// ˆ—‚È‚µ
}


