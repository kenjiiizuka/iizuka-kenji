#include "VertexObject2DShader.h"

VertexObject2DShader::VertexObject2DShader(VisualEntity* _entity)
	: VertexShader(_entity)
{
	LoadWithShaderReflection("VS_Object2D.cso");
}

void VertexObject2DShader::UpdateBuffer(uint8_t _dataID)
{
	VertexShader::UpdateBuffer(_dataID);
}
