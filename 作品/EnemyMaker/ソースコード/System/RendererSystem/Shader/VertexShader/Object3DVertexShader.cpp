#include "Object3DVertexShader.h"
#include "../ShaderStruct.h"
#include "../../VisualEntity/VisualEntity.h"
#include "../../VisualEntity/VisualEntityData.h"
#include "../../../../Utility/Debug.h"

using namespace DirectX::SimpleMath;

Object3DVertexShader::Object3DVertexShader(VisualEntity* _entity)
	: VertexShader(_entity)
{
	LoadWithShaderReflection("VS_Lighting.cso");
}

void Object3DVertexShader::UpdateBuffer(uint8_t _dataID)
{
	VertexShader::UpdateBuffer(_dataID);
	Matrix world = mVisualEntity->GetWorldMatrix();
}
