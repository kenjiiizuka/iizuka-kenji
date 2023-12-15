#pragma once
#include "MoveComponent.h"
class DebugMoveComponent : public MoveComponent
{
public:
	DebugMoveComponent() {};
	~DebugMoveComponent();
private:
	void Move();
	void MoveRot();
	void MoveForward(const float _scaleValue) override;
	void MoveRight(const float _scaleValue) override;
	void MoveUp(const float _scaleValue) override;

public:
	void Update(const double _deltaTime) override;
};

