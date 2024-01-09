//---------- INCLUDES ----------
#include "Component.h"

Component::Component()
	: mOwner(nullptr)
	, mbActive(true)
	, mbVisible(true)
	, bIsDestroy(false)
{
	// ˆ—‚È‚µ
}

Component::~Component()
{
	// ˆ—‚È‚µ
}