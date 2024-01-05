#pragma once
#include "Camera.h"
class DebugCamera : public Camera
{
public:
	~DebugCamera(){}
private:
	void RotateMove();
	void Move();

	bool bAnableInput = false;
public:
	void Init() override;
	void Update(const double _deltaTime) override;

	
};

