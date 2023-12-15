//------------- INCLUDES -----------
#include "CircleCollisionComponent.h"
#include "../../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"

RingCollisionComponent::RingCollisionComponent()
	: PrimitiveComponent(Collision::PrimitiveType_Ring)
	, mRadius(0.0f)
{
	// 処理なし
}

RingCollisionComponent::~RingCollisionComponent()
{
	// 処理なし
}

void RingCollisionComponent::Update(const double _deltaTime)
{
	PrimitiveComponent::Update(_deltaTime);
	
#ifdef DEBUG || _DEBUG
	// シリンダー状のデバッグ表示の代わりに円を出す
	DebugRendererManager::GetInstance().DrawSphere(mTransform.mPosition, mRadius, 1, { 0,1,1,1 });
#endif // DEBUG

	
}