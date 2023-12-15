#pragma once
#include "VertexShader.h"
class VertexObject2DShader : public VertexShader
{
public:
	VertexObject2DShader(VisualEntity* _entity);

public:

	virtual void UpdateBuffer(uint8_t _dataID);
};

