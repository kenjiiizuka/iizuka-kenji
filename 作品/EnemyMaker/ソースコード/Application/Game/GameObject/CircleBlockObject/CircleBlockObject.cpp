//------------ INCLUDES -------------
#include "CircleBlockObject.h"
#include "../../Component/CollisionComponent/CircleCollisionComponent.h"
#include "../../../ImGui/ImGuiUtility.h"

CircleBlockObject::CircleBlockObject()
	: mRingRadius(60.0f)
{
	// èàóùÇ»Çµ
}

CircleBlockObject::~CircleBlockObject()
{
	// èàóùÇ»Çµ
}

void CircleBlockObject::Init()
{
	std::shared_ptr<RingCollisionComponent> ringCollision = AddComponent<RingCollisionComponent>();
	ringCollision->SetRadius(mRingRadius);
	ringCollision->SetCollisionChannel(Collision::Channel_Static);
	ringCollision->SetCollisionTypes(Collision::Channel_Enemy, Collision::Type_Block);
	ringCollision->SetCollisionTypes(Collision::Channel_Player, Collision::Type_Block);
	mTransform.lock()->SetPosition({ 100.0f,0.0f ,100.0f });
}

