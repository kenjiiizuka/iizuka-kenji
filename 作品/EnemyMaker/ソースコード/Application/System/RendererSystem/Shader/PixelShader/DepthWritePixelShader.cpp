//------------- INCLUDES ----------
#include "DepthWritePixelShader.h"

DepthWritePixelShader::DepthWritePixelShader(VisualEntity* _entity)
	: PixelShader(_entity)
{
	LoadWithShaderReflection("PS_DepthWrite.cso");
}

