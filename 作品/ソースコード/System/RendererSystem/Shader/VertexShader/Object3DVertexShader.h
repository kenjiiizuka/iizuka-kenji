#pragma once
#include "VertexShader.h"
class Object3DVertexShader : public VertexShader
{
public:
	Object3DVertexShader(VisualEntity* _entity);

	void UpdateBuffer(uint8_t _dataID) override;
};

