#include "OutlinePixelShader.h"

OutlinePixelShader::OutlinePixelShader(VisualEntity* _entity)
	: PixelShader(_entity)
	, mOutlineColor(0.0f,0.0f,0.0f,1.0f)
{
	LoadWithShaderReflection("PS_Outline.cso");
}

OutlinePixelShader::~OutlinePixelShader()
{
	// �����Ȃ�
}

void OutlinePixelShader::UpdateBuffer(uint8_t _dataID)
{
	WriteBuffer(0, &mOutlineColor);
}




