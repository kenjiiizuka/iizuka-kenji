#pragma once

//---------- INCLUDES -----------
#include "PrimitiveComponent.h"


class BoxCollisionComponent : public PrimitiveComponent
{
public:
	BoxCollisionComponent();
	~BoxCollisionComponent();
private:
	DirectX::SimpleMath::Vector3 mHalfSize;
	
public:	
	void FixInit(DirectX::SimpleMath::Vector3 _halfSize);
	void Init() override;
	void SetHalfSize(DirectX::SimpleMath::Vector3 _halfSize) { mHalfSize = _halfSize; }
	DirectX::SimpleMath::Vector3 GetHalfSize() { return mHalfSize; }
};

