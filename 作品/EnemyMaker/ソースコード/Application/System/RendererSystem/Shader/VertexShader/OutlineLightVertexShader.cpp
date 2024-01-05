//------------ INCLUDES -----------
#include "OutlineLightVertexShader.h"
#include "../../../RendererSystem/VisualEntity/VisualEntity.h"

namespace DXSimpleMath = DirectX::SimpleMath;

OutlineLightVertexShader::OutlineLightVertexShader(VisualEntity* _entity)
	: VertexShader(_entity)
	, mOutlineThickness(1.0f)
{
	LoadWithShaderReflection("VS_LightingOutline.cso");
	mbIsDropShadow = false;
}

OutlineLightVertexShader::~OutlineLightVertexShader()
{
	// �����Ȃ�
}

void OutlineLightVertexShader::UpdateBuffer(uint8_t _dataID)
{
	VertexShader::UpdateBuffer(_dataID);
	DXSimpleMath::Matrix world = mVisualEntity->GetWorldMatrix();

	// �A�E�g���C���̑����̐ݒ�
	WriteBuffer(2, &mOutlineThickness);
}


