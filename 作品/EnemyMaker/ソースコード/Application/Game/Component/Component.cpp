//---------- INCLUDES ----------
#include "Component.h"

Component::Component()
	: mOwner(nullptr)
	, mbActive(true)
	, mbVisible(true)
	, bIsDestroy(false)
{
	// �����Ȃ�
}

Component::~Component()
{
	// �����Ȃ�
}