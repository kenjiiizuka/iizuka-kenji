//------------- INCLUDES -----------
#include "CircleCollisionComponent.h"
#include "../../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"

RingCollisionComponent::RingCollisionComponent()
	: PrimitiveComponent(Collision::PrimitiveType_Ring)
	, mRadius(0.0f)
{
	// �����Ȃ�
}

RingCollisionComponent::~RingCollisionComponent()
{
	// �����Ȃ�
}

void RingCollisionComponent::Update(const double _deltaTime)
{
	PrimitiveComponent::Update(_deltaTime);
	
#ifdef DEBUG || _DEBUG
	// �V�����_�[��̃f�o�b�O�\���̑���ɉ~���o��
	DebugRendererManager::GetInstance().DrawSphere(mTransform.mPosition, mRadius, 1, { 0,1,1,1 });
#endif // DEBUG

	
}