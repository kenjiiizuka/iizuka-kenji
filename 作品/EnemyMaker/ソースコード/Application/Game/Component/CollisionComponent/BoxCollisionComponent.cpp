//---------- INCLUDES ---------
#include "BoxCollisionComponent.h"
#include "../../../System/CollisionSystem/CollisionSystem.h"
#include "../PlaneComponent/PlaneComponent.h"

BoxCollisionComponent::BoxCollisionComponent()
	: PrimitiveComponent(Collision::PrimitiveType_Box)
	, mHalfSize(DirectX::SimpleMath::Vector3::One)
{
	// 処理なし
}

BoxCollisionComponent::~BoxCollisionComponent()
{
	// 処理なし
}

void BoxCollisionComponent::FixInit(DirectX::SimpleMath::Vector3 _halfSize)
{
	mHalfSize = _halfSize;
}

void BoxCollisionComponent::Init()
{
	PrimitiveComponent::Init();	
}

