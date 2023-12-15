//---------- INCLUDES ---------
#include "BoxCollisionComponent.h"
#include "../../../System/CollisionSystem/CollisionSystem.h"
#include "../PlaneComponent/PlaneComponent.h"

using namespace DirectX::SimpleMath;

BoxCollisionComponent::BoxCollisionComponent()
	: PrimitiveComponent(Collision::PrimitiveType_Box)
	, mHalfSize(Vector3::One)
{
}

BoxCollisionComponent::~BoxCollisionComponent()
{
}

void BoxCollisionComponent::FixInit(Vector3 _halfSize)
{
	mHalfSize = _halfSize;
}

void BoxCollisionComponent::Init()
{
	PrimitiveComponent::Init();	
}

